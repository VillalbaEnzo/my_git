import { Router } from 'express'
import webpush from 'web-push'

const router = Router()

const VAPID_PUBLIC = process.env.VAPID_PUBLIC_KEY
const VAPID_PRIVATE = process.env.VAPID_PRIVATE_KEY
const VAPID_SUBJECT = process.env.VAPID_SUBJECT ?? 'mailto:contact@madevpass.fr'

if (!VAPID_PUBLIC || !VAPID_PRIVATE) {
  throw new Error(
    'VAPID_PUBLIC_KEY et VAPID_PRIVATE_KEY doivent être définies (voir server/.env.example). ' +
      'Générer une paire avec `npx web-push generate-vapid-keys`.',
  )
}

webpush.setVapidDetails(VAPID_SUBJECT, VAPID_PUBLIC, VAPID_PRIVATE)

const subscriptions = new Map<string, webpush.PushSubscription>()

router.get('/vapid-public-key', (_req, res) => {
  res.json({ publicKey: VAPID_PUBLIC })
})

router.post('/subscribe', (req, res) => {
  const sub = req.body as webpush.PushSubscription
  if (!sub?.endpoint) {
    return res.status(400).json({ message: 'Souscription invalide.' })
  }
  subscriptions.set(sub.endpoint, sub)
  console.log(`[push] Nouvelle souscription enregistrée (${subscriptions.size} au total):`, sub.endpoint)
  res.status(201).json({ message: 'Alertes activées.' })
})

router.post('/test', async (_req, res) => {
  const payload = JSON.stringify({
    title: 'MADEV Pass',
    body: 'Une nouvelle offre vient d’être publiée chez un de vos favoris !',
    url: '/annuaire',
  })
  await Promise.allSettled(
    [...subscriptions.values()].map((sub) =>
      webpush.sendNotification(sub, payload).catch((err) => {
        if (err?.statusCode === 404 || err?.statusCode === 410) subscriptions.delete(sub.endpoint)
      }),
    ),
  )
  res.json({ sent: subscriptions.size })
})

export default router
