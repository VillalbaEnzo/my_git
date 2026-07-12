import { Router } from 'express';
import { z } from 'zod';
import bcrypt from 'bcryptjs';
import path from 'path';
import { prisma } from '../lib/prisma';
import { submitInscriptionVerificationJob } from '../services/aiVerificationService';
import { trackAiVerificationJob } from '../services/aiVerificationOrchestrator';

const UPLOADS_DIR = path.join(__dirname, '../../uploads');

const router = Router();

router.get('/users', async (_req, res) => {
  const users = await prisma.user.findMany({
    select: {
      id: true,
      email: true,
      role: true,
      prenom: true,
      nom: true,
      numeroCarte: true,
      isActif: true,
      statutInscription: true,
      createdAt: true,
      updatedAt: true,
    },
    orderBy: { createdAt: 'desc' },
  });
  res.json(users);
});

const userPatchSchema = z.object({
  isActif: z.boolean().optional(),
  prenom: z.string().min(1).optional(),
  nom: z.string().min(1).optional(),
  email: z.string().email().optional(),
});

router.patch('/users/:id', async (req, res) => {
  const { id } = req.params;
  const parsed = userPatchSchema.safeParse(req.body);
  if (!parsed.success) {
    res.status(400).json({ error: parsed.error.flatten() });
    return;
  }

  const user = await prisma.user.findUnique({ where: { id } });
  if (!user) {
    res.status(404).json({ error: 'Utilisateur introuvable' });
    return;
  }

  if (parsed.data.email && parsed.data.email !== user.email) {
    const exists = await prisma.user.findUnique({ where: { email: parsed.data.email } });
    if (exists) {
      res.status(409).json({ error: 'Email déjà utilisé' });
      return;
    }
  }

  try {
    const updated = await prisma.user.update({
      where: { id },
      data: parsed.data,
      select: { id: true, email: true, prenom: true, nom: true, role: true, isActif: true },
    });
    res.json(updated);
  } catch {
    res.status(409).json({ error: 'Email déjà utilisé' });
  }
});

const merchantSchema = z.object({
  prenom: z.string().min(1),
  nom: z.string().min(1),
  email: z.string().email(),
  password: z.string().min(8),
  nomCommerce: z.string().min(1),
  description: z.string().optional().default(''),
  adresse: z.string().min(1),
  ville: z.string().min(1),
  codePostal: z.string().min(1),
  categorieId: z.coerce.number().int(),
  telephone: z.string().optional().default(''),
  siteWeb: z.string().optional().default(''),
});

router.post('/merchants', async (req, res) => {
  const parsed = merchantSchema.safeParse(req.body);
  if (!parsed.success) {
    res.status(400).json({ error: parsed.error.flatten() });
    return;
  }
  const d = parsed.data;

  const existing = await prisma.user.findUnique({ where: { email: d.email } });
  if (existing) {
    res.status(409).json({ error: 'Cet email est déjà utilisé' });
    return;
  }

  const categorie = await prisma.categorie.findUnique({ where: { id: d.categorieId } });
  if (!categorie) {
    res.status(400).json({ error: 'Catégorie invalide' });
    return;
  }

  const passwordHash = await bcrypt.hash(d.password, 12);

  const user = await prisma.user.create({
    data: {
      email: d.email,
      passwordHash,
      prenom: d.prenom,
      nom: d.nom,
      role: 'COMMERCANT',
      isActif: true,
      statutInscription: 'VALIDE',
      commerce: {
        create: {
          categorieId: d.categorieId,
          nom: d.nomCommerce,
          description: d.description,
          adresse: d.adresse,
          ville: d.ville,
          codePostal: d.codePostal,
          telephone: d.telephone,
          siteWeb: d.siteWeb,
          estValide: true,
        },
      },
    },
    select: { id: true, email: true, prenom: true, nom: true, role: true },
  });

  res.status(201).json(user);
});

router.delete('/users/:id', async (req, res) => {
  const { id } = req.params;

  const user = await prisma.user.findUnique({ where: { id } });
  if (!user) {
    res.status(404).json({ error: 'Utilisateur introuvable' });
    return;
  }

  try {
    await prisma.user.delete({ where: { id } });
    res.status(204).end();
  } catch {
    res.status(409).json({ error: 'Compte lié à des données (passages/commerce), suppression impossible.' });
  }
});

router.get('/merchants', async (_req, res) => {
  const commerces = await prisma.commerce.findMany({
    include: {
      categorie: { select: { id: true, nom: true, icone: true } },
      proprietaire: { select: { id: true, prenom: true, nom: true, email: true, isActif: true } },
      _count: { select: { offres: true, passages: true } },
    },
    orderBy: { createdAt: 'desc' },
  });
  res.json(commerces.map(({ _count, ...c }) => ({
    ...c,
    nbOffres: _count.offres,
    nbPassages: _count.passages,
  })));
});

const merchantPatchSchema = z.object({
  nom: z.string().min(1).optional(),
  description: z.string().optional(),
  adresse: z.string().min(1).optional(),
  ville: z.string().min(1).optional(),
  codePostal: z.string().min(1).optional(),
  telephone: z.string().optional(),
  siteWeb: z.string().optional(),
  categorieId: z.coerce.number().int().optional(),
  estValide: z.boolean().optional(),
});

router.patch('/merchants/:id', async (req, res) => {
  const { id } = req.params;
  const parsed = merchantPatchSchema.safeParse(req.body);
  if (!parsed.success) {
    res.status(400).json({ error: parsed.error.flatten() });
    return;
  }

  const commerce = await prisma.commerce.findUnique({ where: { id } });
  if (!commerce) {
    res.status(404).json({ error: 'Commerce introuvable' });
    return;
  }

  if (parsed.data.categorieId !== undefined) {
    const categorie = await prisma.categorie.findUnique({ where: { id: parsed.data.categorieId } });
    if (!categorie) {
      res.status(400).json({ error: 'Catégorie invalide' });
      return;
    }
  }

  const updated = await prisma.commerce.update({
    where: { id },
    data: parsed.data,
    include: {
      categorie: { select: { id: true, nom: true, icone: true } },
      proprietaire: { select: { id: true, prenom: true, nom: true, email: true, isActif: true } },
      _count: { select: { offres: true, passages: true } },
    },
  });
  const { _count, ...c } = updated;
  res.json({ ...c, nbOffres: _count.offres, nbPassages: _count.passages });
});

router.get('/categories', async (_req, res) => {
  const categories = await prisma.categorie.findMany({
    include: { _count: { select: { commerces: true } } },
    orderBy: { nom: 'asc' },
  });
  res.json(categories.map(({ _count, ...c }) => ({ ...c, nbCommerces: _count.commerces })));
});

const categorieSchema = z.object({
  nom: z.string().min(1),
  icone: z.string().optional().default(''),
});

function slugify(s: string) {
  return s.toLowerCase().normalize('NFD').replace(/[̀-ͯ]/g, '')
    .replace(/[^a-z0-9]+/g, '-').replace(/^-+|-+$/g, '');
}

router.post('/categories', async (req, res) => {
  const parsed = categorieSchema.safeParse(req.body);
  if (!parsed.success) {
    res.status(400).json({ error: parsed.error.flatten() });
    return;
  }
  const slug = slugify(parsed.data.nom);
  const exists = await prisma.categorie.findFirst({ where: { OR: [{ nom: parsed.data.nom }, { slug }] } });
  if (exists) {
    res.status(409).json({ error: 'Catégorie déjà existante' });
    return;
  }
  const categorie = await prisma.categorie.create({
    data: { nom: parsed.data.nom, slug, icone: parsed.data.icone || null },
  });
  res.status(201).json({ ...categorie, nbCommerces: 0 });
});

router.get('/inscriptions', async (_req, res) => {
  const users = await prisma.user.findMany({
      where: { statutInscription: 'EN_ATTENTE', role: 'ETUDIANT' },
      select: {
      id: true,
      email: true,
      prenom: true,
      nom: true,
      cniRectoUrl: true,
      cniVersoUrl: true,
      attestationScolariteUrl: true,
      createdAt: true,
      aiRiskScore: true,
      aiRiskLevel: true,
      aiReasons: true,
      aiExtractedFields: true,
      aiCheckedAt: true,
      aiCheckStatus: true,
    },
    orderBy: { createdAt: 'asc' },
  });
  res.json(users);
});

router.patch('/valider/:userId', async (req, res) => {
  const { userId } = req.params;

  const user = await prisma.user.findUnique({ where: { id: userId } });
  if (!user) {
    res.status(404).json({ error: 'Utilisateur introuvable' });
    return;
  }

  const numeroCarte = `MADEV-${Date.now().toString(36).toUpperCase()}`;

  const updated = await prisma.user.update({
    where: { id: userId },
    data: { isActif: true, statutInscription: 'VALIDE', numeroCarte },
    select: { id: true, prenom: true, nom: true, isActif: true, statutInscription: true, numeroCarte: true },
  });

  res.json(updated);
});

router.patch('/refuser/:userId', async (req, res) => {
  const { userId } = req.params;

  const user = await prisma.user.findUnique({ where: { id: userId } });
  if (!user) {
    res.status(404).json({ error: 'Utilisateur introuvable' });
    return;
  }

  const updated = await prisma.user.update({
    where: { id: userId },
    data: { isActif: false, statutInscription: 'REJETÉ' },
    select: { id: true, prenom: true, nom: true, isActif: true, statutInscription: true },
  });

  res.json(updated);
});

router.post('/inscriptions/:userId/verifier-ia', async (req, res) => {
  const { userId } = req.params;

  const user = await prisma.user.findUnique({ where: { id: userId } });
  if (!user) {
    res.status(404).json({ error: 'Utilisateur introuvable' });
    return;
  }
  if (!user.cniRectoUrl || !user.attestationScolariteUrl) {
    res.status(400).json({ error: "Le recto de la CNI et l'attestation de scolarité sont requis pour lancer l'analyse IA" });
    return;
  }

  const jobId = await submitInscriptionVerificationJob({
    cniRecto: path.join(UPLOADS_DIR, path.basename(user.cniRectoUrl)),
    cniVerso: user.cniVersoUrl ? path.join(UPLOADS_DIR, path.basename(user.cniVersoUrl)) : undefined,
    attestationScolarite: path.join(UPLOADS_DIR, path.basename(user.attestationScolariteUrl)),
  });
  if (!jobId) {
    await prisma.user.update({
      where: { id: userId },
      data: { aiCheckStatus: 'ERROR', aiCheckedAt: new Date() },
    });
    res.status(502).json({ error: "Le service d'analyse IA est indisponible ou a échoué" });
    return;
  }

  const updated = await prisma.user.update({
    where: { id: userId },
    data: { aiCheckStatus: 'PENDING', aiJobId: jobId },
    select: {
      id: true, aiRiskScore: true, aiRiskLevel: true, aiReasons: true,
      aiExtractedFields: true, aiCheckedAt: true, aiCheckStatus: true,
    },
  });

  trackAiVerificationJob(userId, jobId)
    .catch((err) => console.error(`[ai-verification] Échec de suivi manuel pour l'utilisateur ${userId} :`, err));

  res.status(202).json(updated);
});

export default router;
