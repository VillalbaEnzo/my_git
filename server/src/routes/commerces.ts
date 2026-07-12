import { Router } from 'express'
import { prisma } from '../lib/prisma'

const router = Router()

router.get('/', async (_req, res) => {
  const commerces = await prisma.commerce.findMany({
    where: { estValide: true },
    include: {
      categorie: true,
      _count: { select: { offres: { where: { estActive: true } } } },
    },
    orderBy: { nom: 'asc' },
  })

  res.json(
    commerces.map(({ _count, ...c }) => ({
      ...c,
      offresActives: _count.offres,
    })),
  )
})

router.get('/:id', async (req, res) => {
  const now = new Date()

  const commerce = await prisma.commerce.findFirst({
    where: { id: req.params.id, estValide: true },
    include: {
      categorie: true,
      offres: {
        where: {
          estActive: true,
          dateDebut: { lte: now },
          OR: [{ dateFin: null }, { dateFin: { gte: now } }],
        },
        orderBy: { createdAt: 'desc' },
      },
    },
  })

  if (!commerce) {
    res.status(404).json({ error: 'Commerce introuvable' })
    return
  }

  res.json(commerce)
})

export default router
