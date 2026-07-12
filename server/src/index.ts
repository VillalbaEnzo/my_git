import express from 'express';
import cors from 'cors';
import dotenv from 'dotenv';

dotenv.config();

import authRoutes from './routes/auth';
import adminRoutes from './routes/admin';
import commercesRoutes from './routes/commerces';
import categoriesRoutes from './routes/categories';
import offresRoutes from './routes/offres';
import passagesRoutes from './routes/passages';
import documentsRoutes from './routes/documents';
import notificationsRoutes from './routes/notifications';
import { authMiddleware, requireRole } from './middleware/authMiddleware';
import { resumePendingAiVerifications } from './services/aiVerificationOrchestrator';

const app = express();
const PORT = process.env.PORT ?? 3001;

app.use(cors());
app.use(express.json());

app.get('/health', (_req, res) => {
  res.json({ status: 'ok', timestamp: new Date().toISOString() });
});

app.use('/ask', authRoutes);
app.use('/api/auth', authRoutes);
app.use('/api/documents', documentsRoutes);
app.use('/api/notifications', authMiddleware, notificationsRoutes);

const adminGuard = [authMiddleware, requireRole('ADMIN')] as const;
app.use('/api/admin', ...adminGuard, adminRoutes);
app.use('/api/commerces', commercesRoutes);
app.use('/api/categories', categoriesRoutes);
app.use('/api/offres', offresRoutes);

const commercantGuard = [authMiddleware, requireRole('COMMERCANT')] as const;
app.use('/api/commercant', ...commercantGuard, passagesRoutes);
app.use('/api/passages', ...commercantGuard, passagesRoutes);

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
  resumePendingAiVerifications().catch((err) => console.error('[ai-verification] Échec de la reprise au démarrage :', err));
});
