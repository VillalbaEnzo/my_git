import { Router } from 'express'
import { prisma } from '../lib/prisma'

const router = Router()

router.get('/', async (_req, res) => {
  const now = new Date()

  const offres = await prisma.offre.findMany({
    where: {
      estActive: true,
      dateDebut: { lte: now },
      OR: [{ dateFin: null }, { dateFin: { gte: now } }],
      commerce: { estValide: true },
    },
    include: {
      commerce: {
        select: {
          id: true,
          nom: true,
          adresse: true,
          ville: true,
          logoUrl: true,
          categorie: true,
        },
      },
    },
    orderBy: { createdAt: 'desc' },
  })

  res.json(offres)
})

export default router
