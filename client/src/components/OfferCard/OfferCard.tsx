import { motion } from 'framer-motion'
import { useNavigate } from 'react-router-dom'
import { Tag, MapPin } from 'lucide-react'
import type { Offre, OffreWithCommerce } from '../../types/commerce'

interface Props {
  offre: Offre | OffreWithCommerce
  index?: number
}

function hasCommerce(offre: Offre | OffreWithCommerce): offre is OffreWithCommerce {
  return 'commerce' in offre
}

function formatRemise(type: string, valeur: number | null): string {
  if (type === 'POURCENTAGE') return `-${valeur}%`
  if (type === 'MONTANT_FIXE') return `-${valeur}€`
  if (type === 'ARTICLE_OFFERT') return 'Offert'
  return 'Offre'
}

function formatDate(iso: string): string {
  return new Date(iso).toLocaleDateString('fr-FR', { day: '2-digit', month: 'short', year: 'numeric' })
}

export default function OfferCard({ offre, index = 0 }: Props) {
  const navigate = useNavigate()
  const withCommerce = hasCommerce(offre)

  return (
    <motion.div
      initial={{ opacity: 0, y: 16 }}
      animate={{ opacity: 1, y: 0 }}
      transition={{ duration: 0.3, delay: Math.min(index * 0.04, 0.3) }}
      onClick={withCommerce ? () => navigate(`/annuaire/${offre.commerce.id}`) : undefined}
      role={withCommerce ? 'button' : undefined}
      tabIndex={withCommerce ? 0 : undefined}
      onKeyDown={withCommerce ? (e) => { if (e.key === 'Enter') navigate(`/annuaire/${offre.commerce.id}`) } : undefined}
      className={`lift group relative overflow-hidden rounded-2xl border border-black/[0.06] bg-white p-5 hover:border-cobalt-500/40 dark:border-white/[0.07] dark:bg-ink-900 ${withCommerce ? 'cursor-pointer' : ''}`}
    >
      <div className="flex items-start justify-between gap-3">
        <div className="min-w-0">
          {withCommerce && (
            <p className="flex items-center gap-1 truncate text-xs font-semibold uppercase tracking-wide text-stone-400">
              {offre.commerce.categorie.icone ?? '🏪'} {offre.commerce.nom}
            </p>
          )}
          <span className="flex items-center gap-2 truncate font-display font-semibold text-ink-900 dark:text-white">
            <Tag size={14} className="flex-shrink-0 text-cobalt-500" />
            {offre.titre}
          </span>
        </div>
        <span className="flex-shrink-0 whitespace-nowrap rounded-lg bg-cobalt-500/15 px-2.5 py-1 text-sm font-extrabold text-cobalt-700 dark:text-cobalt-300">
          {formatRemise(offre.typeRemise, offre.valeurRemise)}
        </span>
      </div>

      {offre.description && (
        <p className="mt-3 line-clamp-2 text-sm leading-relaxed text-stone-500">{offre.description}</p>
      )}

      <div className="mt-3 flex flex-wrap items-center justify-between gap-2 text-xs font-medium text-stone-400">
        {withCommerce ? (
          <span className="flex items-center gap-1">
            <MapPin size={12} strokeWidth={1.75} />
            {offre.commerce.ville}
          </span>
        ) : <span />}
        <span>
          {formatDate(offre.dateDebut)}
          {offre.dateFin && <> → {formatDate(offre.dateFin)}</>}
        </span>
      </div>
    </motion.div>
  )
}
