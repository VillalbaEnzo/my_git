import fs from 'fs/promises';
import path from 'path';

const AI_SERVICE_URL = process.env.AI_SERVICE_URL || 'http://localhost:8001';

const AI_JOB_SUBMIT_TIMEOUT_MS = Number(process.env.AI_JOB_SUBMIT_TIMEOUT_MS || 30_000);
const AI_JOB_POLL_TIMEOUT_MS = Number(process.env.AI_JOB_POLL_TIMEOUT_MS || 10_000);
const AI_JOB_POLL_INTERVAL_MS = Number(process.env.AI_JOB_POLL_INTERVAL_MS || 15_000);
const AI_JOB_MAX_WAIT_MS = Number(process.env.AI_JOB_MAX_WAIT_MS || 20 * 60_000);

const MIME_BY_EXT: Record<string, string> = {
  '.jpg': 'image/jpeg',
  '.jpeg': 'image/jpeg',
  '.png': 'image/png',
  '.webp': 'image/webp',
  '.pdf': 'application/pdf',
};

interface AiInscriptionRawResponse {
  risk_score: number;
  risk_level: 'FAIBLE' | 'MOYEN' | 'ELEVE';
  reasons?: string[];
  cni_extracted_fields: unknown;
  cni_mrz_fields: unknown;
  cni_image_quality: unknown;
  cni_consistency: unknown;
  attestation_extracted_fields: unknown;
  attestation_consistency: unknown;
}

interface AiJobStatusResponse {
  status: 'PENDING' | 'DONE' | 'ERROR';
  result?: AiInscriptionRawResponse;
  error?: string;
}

export interface AiVerificationResult {
  riskScore: number;
  riskLevel: 'FAIBLE' | 'MOYEN' | 'ELEVE';
  reasons: string[];
  extractedFields: Record<string, unknown>;
}

function fileToMime(filePath: string): string | null {
  const ext = path.extname(filePath).toLowerCase();
  return MIME_BY_EXT[ext] ?? null;
}

async function appendFile(form: FormData, fieldName: string, filePath: string): Promise<boolean> {
  const mimeType = fileToMime(filePath);
  if (!mimeType) {
    console.warn(`[ai-service] Type de fichier non supporté pour l'analyse IA : ${filePath}`);
    return false;
  }
  const buffer = await fs.readFile(filePath);
  const blob = new Blob([buffer], { type: mimeType });
  form.append(fieldName, blob, path.basename(filePath));
  return true;
}

async function fetchWithTimeout(url: string, init: RequestInit, timeoutMs: number): Promise<Response> {
  const controller = new AbortController();
  const timeout = setTimeout(() => controller.abort(), timeoutMs);
  try {
    return await fetch(url, { ...init, signal: controller.signal });
  } finally {
    clearTimeout(timeout);
  }
}

function toVerificationResult(data: AiInscriptionRawResponse): AiVerificationResult {
  return {
    riskScore: data.risk_score,
    riskLevel: data.risk_level,
    reasons: data.reasons ?? [],
    extractedFields: {
      ocr: data.cni_extracted_fields,
      mrz: data.cni_mrz_fields,
      image_quality: data.cni_image_quality,
      consistency: data.cni_consistency,
      attestation: data.attestation_extracted_fields,
      attestationConsistency: data.attestation_consistency,
    },
  };
}

export interface InscriptionDocumentPaths {
  cniRecto: string;
  cniVerso?: string;
  attestationScolarite: string;
}

export async function submitInscriptionVerificationJob(paths: InscriptionDocumentPaths): Promise<string | null> {
  try {
    const form = new FormData();
    const rectoOk = await appendFile(form, 'cni_recto', paths.cniRecto);
    const attestationOk = await appendFile(form, 'attestation_scolarite', paths.attestationScolarite);
    if (!rectoOk || !attestationOk) return null;
    if (paths.cniVerso) await appendFile(form, 'cni_verso', paths.cniVerso);

    const response = await fetchWithTimeout(
      `${AI_SERVICE_URL}/api/verify-inscription/jobs`,
      { method: 'POST', body: form },
      AI_JOB_SUBMIT_TIMEOUT_MS,
    );
    if (!response.ok) {
      console.error(`[ai-service] Échec de soumission du job d'analyse (${response.status})`);
      return null;
    }
    const data = (await response.json()) as { job_id: string };
    console.log(`[ai-service] Job d'analyse d'inscription soumis : ${data.job_id}`);
    return data.job_id;
  } catch (err) {
    console.error("[ai-service] Échec de soumission du job d'analyse d'inscription :", err);
    return null;
  }
}

/**
 * Poll le statut d'un job jusqu'à complétion, erreur, ou dépassement de AI_JOB_MAX_WAIT_MS.
 * Chaque requête individuelle est courte (AI_JOB_POLL_TIMEOUT_MS) : un aléa réseau ponctuel
 * ou un redémarrage de ai-service (job introuvable en mémoire) sont gérés explicitement au
 * lieu d'abandonner tout le suivi sur un seul incident transitoire.
 */
export async function pollInscriptionVerificationJob(jobId: string): Promise<AiVerificationResult | null> {
  const deadline = Date.now() + AI_JOB_MAX_WAIT_MS;

  while (Date.now() < deadline) {
    await new Promise((resolve) => setTimeout(resolve, AI_JOB_POLL_INTERVAL_MS));

    try {
      const response = await fetchWithTimeout(
        `${AI_SERVICE_URL}/api/verify-inscription/jobs/${jobId}`,
        {},
        AI_JOB_POLL_TIMEOUT_MS,
      );

      if (response.status === 404) {
        console.error(`[ai-service] Job ${jobId} introuvable (expiré ou ai-service redémarré)`);
        return null;
      }
      if (!response.ok) {
        console.warn(`[ai-service] Statut non-OK (${response.status}) en pollant le job ${jobId}, nouvelle tentative`);
        continue;
      }

      const data = (await response.json()) as AiJobStatusResponse;
      if (data.status === 'DONE' && data.result) {
        return toVerificationResult(data.result);
      }
      if (data.status === 'ERROR') {
        console.error(`[ai-service] Job ${jobId} en échec : ${data.error}`);
        return null;
      }
    } catch (err) {
      console.warn(`[ai-service] Erreur réseau en pollant le job ${jobId}, nouvelle tentative :`, err);
    }
  }

  console.error(`[ai-service] Délai maximum dépassé pour le job ${jobId} (${AI_JOB_MAX_WAIT_MS}ms)`);
  return null;
}
