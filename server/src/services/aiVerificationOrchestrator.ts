import type { Prisma } from '@prisma/client';
import { prisma } from '../lib/prisma';
import {
  submitInscriptionVerificationJob,
  pollInscriptionVerificationJob,
  type InscriptionDocumentPaths,
} from './aiVerificationService';

const MAX_PLAUSIBLE_AGE_YEARS = 120;

/**
 * `extractedFields.ocr.date_naissance` n'est pas un OCR classique ni du MRZ : c'est le résultat
 * de la lecture directe du document par le LLM (voir ai-service/app/services/llm_extractor.py).
 * On l'utilise seule comme source IA pour la date de naissance ; le MRZ garde son rôle actuel
 * (score de cohérence/risque) et n'intervient pas dans cette décision.
 */
function resolveEffectiveDob(
  aiDateNaissance: unknown,
  declaredDob: Date | null,
): { effective: Date | null; reason: string | null } {
  const aiValue = typeof aiDateNaissance === 'string' ? new Date(aiDateNaissance) : null;
  const now = new Date();
  const aiValueIsPlausible =
    aiValue !== null &&
    !Number.isNaN(aiValue.getTime()) &&
    aiValue <= now &&
    (now.getTime() - aiValue.getTime()) / (1000 * 60 * 60 * 24 * 365.25) <= MAX_PLAUSIBLE_AGE_YEARS;

  if (!aiValueIsPlausible) {
    return {
      effective: declaredDob,
      reason:
        "Date de naissance extraite du document invalide ou implausible — la valeur déclarée à l'inscription a été utilisée à la place.",
    };
  }

  if (declaredDob && aiValue!.toDateString() !== declaredDob.toDateString()) {
    return {
      effective: aiValue,
      reason: `Date de naissance déclarée (${declaredDob.toISOString().slice(0, 10)}) incohérente avec celle extraite du document (${aiValue!.toISOString().slice(0, 10)}) — la valeur du document a été retenue.`,
    };
  }

  return { effective: aiValue, reason: null };
}

/**
 * Poll un job déjà soumis (jobId persisté en base) jusqu'à son résultat final et met à
 * jour l'utilisateur en conséquence. Exportée pour être utilisée en fire-and-forget par
 * une route de relance manuelle, et par resumePendingAiVerifications après un redémarrage.
 */
export async function trackAiVerificationJob(userId: string, jobId: string): Promise<void> {
  const result = await pollInscriptionVerificationJob(jobId);

  if (!result) {
    await prisma.user.update({
      where: { id: userId },
      data: { aiCheckStatus: 'ERROR', aiJobId: null, aiCheckedAt: new Date() },
    });
    return;
  }

  const user = await prisma.user.findUnique({ where: { id: userId }, select: { dateNaissanceDeclaree: true } });
  const ocrFields = result.extractedFields.ocr as { date_naissance?: unknown } | undefined;
  const { effective, reason } = resolveEffectiveDob(ocrFields?.date_naissance, user?.dateNaissanceDeclaree ?? null);
  const reasons = reason ? [...result.reasons, reason] : result.reasons;

  await prisma.user.update({
    where: { id: userId },
    data: {
      aiRiskScore: result.riskScore,
      aiRiskLevel: result.riskLevel,
      aiReasons: reasons,
      aiExtractedFields: result.extractedFields as Prisma.InputJsonValue,
      aiCheckedAt: new Date(),
      aiCheckStatus: null,
      aiJobId: null,
      dateNaissanceEffective: effective,
    },
  });
}

/**
 * Soumet un job d'analyse IA pour un utilisateur, persiste immédiatement l'état PENDING +
 * l'id du job (pour pouvoir reprendre le suivi après un redémarrage du serveur, voir
 * resumePendingAiVerifications), puis attend le résultat en tâche de fond.
 */
export function runAiVerificationInBackground(userId: string, paths: InscriptionDocumentPaths): void {
  submitInscriptionVerificationJob(paths)
    .then(async (jobId) => {
      if (!jobId) {
        await prisma.user.update({
          where: { id: userId },
          data: { aiCheckStatus: 'ERROR', aiCheckedAt: new Date() },
        });
        return;
      }
      await prisma.user.update({ where: { id: userId }, data: { aiCheckStatus: 'PENDING', aiJobId: jobId } });
      await trackAiVerificationJob(userId, jobId);
    })
    .catch((err) => console.error(`[ai-verification] Échec pour l'utilisateur ${userId} :`, err));
}

/**
 * Au démarrage du serveur, reprend le suivi des jobs encore PENDING en base (le process
 * précédent a pu être redémarré/déployé pendant qu'un job tournait côté ai-service). Si le
 * job n'existe plus côté ai-service (lui aussi redémarré, jobs en mémoire), il est marqué en
 * échec via le comportement 404 -> null de pollInscriptionVerificationJob.
 */
export async function resumePendingAiVerifications(): Promise<void> {
  const pending = await prisma.user.findMany({
    where: { aiCheckStatus: 'PENDING', aiJobId: { not: null } },
    select: { id: true, aiJobId: true },
  });

  if (pending.length === 0) return;
  console.log(`[ai-verification] Reprise du suivi de ${pending.length} job(s) IA en cours après redémarrage`);

  for (const user of pending) {
    trackAiVerificationJob(user.id, user.aiJobId as string)
      .catch((err) => console.error(`[ai-verification] Échec de reprise pour l'utilisateur ${user.id} :`, err));
  }
}
