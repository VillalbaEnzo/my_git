import { Router } from 'express';
import { z } from 'zod';
import bcrypt from 'bcryptjs';
import jwt from 'jsonwebtoken';
import multer from 'multer';
import path from 'path';
import fs from 'fs';
import { randomUUID } from 'crypto';
import { prisma } from '../lib/prisma';
import { authMiddleware, requireRole } from '../middleware/authMiddleware';
import { runAiVerificationInBackground } from '../services/aiVerificationOrchestrator';

const router = Router();

const UPLOADS_DIR = path.join(__dirname, '../../uploads');
fs.mkdirSync(UPLOADS_DIR, { recursive: true });

const storage = multer.diskStorage({
  destination: (_req, _file, cb) => cb(null, UPLOADS_DIR),
  filename: (_req, file, cb) => {
    const ext = path.extname(file.originalname).toLowerCase();
    cb(null, `${file.fieldname}_${randomUUID()}${ext}`);
  },
});

const IMAGE_TYPES = ['image/jpeg', 'image/png', 'image/webp'];
const ATTESTATION_TYPES = [...IMAGE_TYPES, 'application/pdf'];

const upload = multer({
  storage,
  limits: { fileSize: 5 * 1024 * 1024 },
  fileFilter: (_req, file, cb) => {
    const allowed = file.fieldname === 'attestationScolarite' ? ATTESTATION_TYPES : IMAGE_TYPES;
    if (allowed.includes(file.mimetype)) cb(null, true);
    else cb(new Error(`Type de fichier non autorisé pour ${file.fieldname}`));
  },
});

const inscriptionDocumentFields = [
  { name: 'cniRecto', maxCount: 1 },
  { name: 'cniVerso', maxCount: 1 },
  { name: 'attestationScolarite', maxCount: 1 },
];

type InscriptionFiles = { cniRecto?: Express.Multer.File[]; cniVerso?: Express.Multer.File[]; attestationScolarite?: Express.Multer.File[] };

const registerSchema = z.object({
  email: z.string().email(),
  password: z.string().min(8, 'Minimum 8 caractères'),
  prenom: z.string().min(1),
  nom: z.string().min(1),
  dateNaissance: z.string().refine((value) => {
    const date = new Date(value);
    if (Number.isNaN(date.getTime())) return false;
    const now = new Date();
    if (date > now) return false;
    const age = (now.getTime() - date.getTime()) / (1000 * 60 * 60 * 24 * 365.25);
    return age <= 120;
  }, 'Date de naissance invalide'),
});

const uploadInscriptionDocuments = (req: any, res: any, next: any) => {
  upload.fields(inscriptionDocumentFields)(req, res, (err: any) => {
    if (err) {
      const message =
        err instanceof multer.MulterError
          ? err.code === 'LIMIT_FILE_SIZE'
            ? 'Fichier trop volumineux (5 Mo max)'
            : 'Erreur lors de l\'envoi du fichier'
          : err.message || 'Upload invalide';
      res.status(400).json({ error: message });
      return;
    }
    next();
  });
};

function validateInscriptionFiles(files: InscriptionFiles): { valid: true } | { valid: false; error: string } {
  const count = [files.cniRecto, files.cniVerso, files.attestationScolarite].filter(Boolean).length;
  if (count === 0) return { valid: true };
  if (!files.cniRecto || !files.cniVerso || !files.attestationScolarite) {
    return { valid: false, error: 'Les 3 documents (recto, verso, attestation) sont requis ensemble, ou aucun pour les envoyer plus tard' };
  }
  return { valid: true };
}

router.post('/register', uploadInscriptionDocuments, async (req, res) => {
  try {
    const parsed = registerSchema.safeParse(req.body);
    if (!parsed.success) {
      res.status(400).json({ error: parsed.error.flatten() });
      return;
    }
    const { email, password, prenom, nom, dateNaissance } = parsed.data;

    const files = (req.files ?? {}) as InscriptionFiles;
    const validation = validateInscriptionFiles(files);
    if (!validation.valid) {
      res.status(400).json({ error: validation.error });
      return;
    }

    const cniRectoUrl = files.cniRecto ? `/uploads/${files.cniRecto[0].filename}` : null;
    const cniVersoUrl = files.cniVerso ? `/uploads/${files.cniVerso[0].filename}` : null;
    const attestationScolariteUrl = files.attestationScolarite ? `/uploads/${files.attestationScolarite[0].filename}` : null;

    const passwordHash = await bcrypt.hash(password, 12);

    const newUser = await prisma.user.create({
      data: {
        email,
        passwordHash,
        prenom,
        nom,
        role: 'ETUDIANT',
        isActif: false,
        statutInscription: attestationScolariteUrl ? 'EN_ATTENTE' : 'PENDING_DOCUMENT',
        dateNaissanceDeclaree: new Date(dateNaissance),
        cniRectoUrl,
        cniVersoUrl,
        attestationScolariteUrl,
      },
    });

    if (files.cniRecto && files.attestationScolarite) {
      runAiVerificationInBackground(newUser.id, {
        cniRecto: files.cniRecto[0].path,
        cniVerso: files.cniVerso?.[0].path,
        attestationScolarite: files.attestationScolarite[0].path,
      });
    }

    res.status(201).json({
      message: attestationScolariteUrl
        ? 'Inscription reçue, en attente de validation admin'
        : 'Inscription reçue, documents à envoyer ultérieurement',
    });
  } catch (err: any) {
    if (err?.code === 'P2002') {
      res.status(400).json({ error: 'Cet email est déjà utilisé.' });
      return;
    }
    console.error('[register]', err);
    res.status(500).json({ error: 'Erreur serveur lors de l\'inscription' });
  }
});

const loginSchema = z.object({
  email: z.string().email(),
  password: z.string().min(1),
});

router.post('/login', async (req, res) => {
  const parsed = loginSchema.safeParse(req.body);
  if (!parsed.success) {
    res.status(400).json({ error: parsed.error.flatten() });
    return;
  }

  const { email, password } = parsed.data;

  const user = await prisma.user.findUnique({ where: { email } });
  if (!user) {
    res.status(401).json({ error: 'Email ou mot de passe incorrect' });
    return;
  }

  const valid = await bcrypt.compare(password, user.passwordHash);
  if (!valid) {
    res.status(401).json({ error: 'Email ou mot de passe incorrect' });
    return;
  }

  if (user.statutInscription === 'REJETÉ') {
    res.status(403).json({ error: 'Inscription refusée par un administrateur' });
    return;
  }

  const payload = { sub: user.id, role: user.role };
  const token = jwt.sign(payload, process.env.JWT_SECRET!, { expiresIn: '7d' });

  res.json({
    token,
    user: {
      id: user.id,
      email: user.email,
      prenom: user.prenom,
      nom: user.nom,
      role: user.role,
      numeroCarte: user.numeroCarte,
    },
  });
});

router.get('/me', authMiddleware, async (req, res) => {
  const user = await prisma.user.findUnique({
    where: { id: req.user!.sub },
    select: {
      id: true, email: true, prenom: true, nom: true, role: true, numeroCarte: true, isActif: true,
      statutInscription: true, cniRectoUrl: true, cniVersoUrl: true, attestationScolariteUrl: true,
      statutSuppression: true, dateSuppressionDemandee: true,
      dateNaissanceDeclaree: true, dateNaissanceEffective: true,
    },
  });
  if (!user) {
    res.status(404).json({ error: 'Utilisateur introuvable' });
    return;
  }
  res.json(user);
});

router.post('/me/document', authMiddleware, upload.fields(inscriptionDocumentFields), async (req, res) => {
  const files = (req.files ?? {}) as InscriptionFiles;
  if (!files.cniRecto || !files.cniVerso || !files.attestationScolarite) {
    res.status(400).json({ error: 'Les 3 documents (recto, verso, attestation) sont requis' });
    return;
  }

  const cniRectoUrl = `/uploads/${files.cniRecto[0].filename}`;
  const cniVersoUrl = `/uploads/${files.cniVerso[0].filename}`;
  const attestationScolariteUrl = `/uploads/${files.attestationScolarite[0].filename}`;

  const updated = await prisma.user.update({
    where: { id: req.user!.sub },
    data: { cniRectoUrl, cniVersoUrl, attestationScolariteUrl, statutInscription: 'EN_ATTENTE' },
    select: { cniRectoUrl: true, cniVersoUrl: true, attestationScolariteUrl: true, statutInscription: true },
  });

  runAiVerificationInBackground(req.user!.sub, {
    cniRecto: files.cniRecto[0].path,
    cniVerso: files.cniVerso[0].path,
    attestationScolarite: files.attestationScolarite[0].path,
  });

  res.json(updated);
});

router.patch('/me/request-deletion', authMiddleware, async (req, res) => {
  const updated = await prisma.user.update({
    where: { id: req.user!.sub },
    data: { statutSuppression: 'PENDING_DELETION', dateSuppressionDemandee: new Date() },
    select: { statutSuppression: true, dateSuppressionDemandee: true },
  });
  res.json(updated);
});

router.get('/qr-token', authMiddleware, requireRole('ETUDIANT'), async (req, res) => {
  const user = await prisma.user.findUnique({
    where: { id: req.user!.sub },
    select: { numeroCarte: true, isActif: true },
  });
  if (!user?.isActif || !user.numeroCarte) {
    res.status(403).json({ error: 'Carte inactive ou introuvable' });
    return;
  }
  const token = jwt.sign(
    { sub: req.user!.sub, carte: user.numeroCarte, type: 'QR' },
    process.env.JWT_SECRET!,
    { expiresIn: '5m' },
  );
  res.json({ token, expiresIn: 300 });
});

export default router;
