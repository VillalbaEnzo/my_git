import { useEffect, useState } from 'react'
import { useNavigate, useParams } from 'react-router-dom'
import { ArrowLeft, Heart, MapPin, Phone, Globe, Tag } from 'lucide-react'
import type { CommerceDetail } from '../../types/commerce'
import OfferCard from '../../components/OfferCard/OfferCard'
import { OfferCardSkeleton } from '../../components/ui/Skeleton'
import { useFavoris } from '../../hooks/useFavoris'
import api from '../../api/client'
import { cn } from '../../lib/utils'

export default function MerchantDetail() {
  const { id } = useParams<{ id: string }>()
  const navigate = useNavigate()
  const { favoris, toggleFavori } = useFavoris()
  const [commerce, setCommerce] = useState<CommerceDetail | null>(null)
  const [loading, setLoading] = useState(true)
  const [error, setError] = useState<string | null>(null)

  useEffect(() => {
    if (!id) return
    api
      .get<CommerceDetail>(`/commerces/${id}`)
      .then((res) => setCommerce(res.data))
      .catch((err) => {
        if (err.response?.status !== 401) {
          setError(err.response?.status === 404 ? 'Ce commerce est introuvable' : 'Impossible de charger le commerce')
        }
      })
      .finally(() => setLoading(false))
  }, [id])

  const isFavori = id ? favoris.has(id) : false
  const icone = commerce?.categorie.icone ?? '🏪'

  return (
    <div className="grain relative min-h-screen overflow-hidden bg-cream pb-16 dark:bg-ink-950">
      <div className="grid-bg pointer-events-none absolute inset-x-0 top-0 h-64 opacity-40 dark:opacity-25" />
      <div className="aurora-blob -top-40 left-1/2 h-96 w-96 -translate-x-1/2 bg-cobalt-500/15" />

      <header className="relative flex items-center justify-between px-6 pb-5 pt-12">
        <button
          onClick={() => navigate(-1)}
          aria-label="Retour"
          className="flex h-9 w-9 items-center justify-center rounded-xl border border-stone-200 text-stone-500 transition-colors hover:border-cobalt-500/40 hover:text-cobalt-600 dark:border-white/10"
        >
          <ArrowLeft size={17} strokeWidth={1.75} />
        </button>
        {commerce && (
          <button
            onClick={() => toggleFavori(commerce.id)}
            aria-label={isFavori ? 'Retirer des favoris' : 'Ajouter aux favoris'}
            className={cn(
              'flex h-9 w-9 items-center justify-center rounded-xl border transition-colors',
              isFavori
                ? 'border-danger/50 bg-danger/10 text-danger'
                : 'border-stone-200 text-stone-400 hover:border-danger/40 hover:text-danger dark:border-white/10',
            )}
          >
            <Heart size={17} strokeWidth={1.75} fill={isFavori ? 'currentColor' : 'none'} />
          </button>
        )}
      </header>

      <main className="relative mx-auto w-full max-w-2xl px-6">
        {loading && (
          <div className="flex items-center gap-4 rounded-2xl border border-stone-200 bg-white p-5 dark:border-white/10 dark:bg-ink-900">
            <div className="h-14 w-14 flex-shrink-0 animate-pulse rounded-xl bg-stone-200/70 dark:bg-ink-800" />
            <div className="flex flex-1 flex-col gap-2">
              <div className="h-4 w-2/3 animate-pulse rounded-md bg-stone-200/70 dark:bg-ink-800" />
              <div className="h-3 w-full animate-pulse rounded-md bg-stone-200/70 dark:bg-ink-800" />
            </div>
          </div>
        )}

        {!loading && error && (
          <div className="flex flex-col items-center gap-2 py-16 text-center text-stone-400">
            <p className="font-display text-base font-semibold text-ink-900 dark:text-white">Chargement impossible</p>
            <p className="text-sm">{error}</p>
          </div>
        )}

        {!loading && !error && commerce && (
          <>
            <div className="rounded-2xl border border-black/[0.06] bg-white p-5 dark:border-white/[0.07] dark:bg-ink-900">
              <div className="flex items-start gap-3">
                <div className="flex h-14 w-14 flex-shrink-0 items-center justify-center rounded-xl bg-cobalt-500/10 text-2xl">
                  {icone}
                </div>
                <div className="min-w-0 flex-1">
                  <p className="font-display text-xl font-bold text-ink-900 dark:text-white">{commerce.nom}</p>
                  <p className="mt-0.5 flex items-center gap-1 text-sm text-stone-500">
                    <MapPin size={13} strokeWidth={1.75} className="flex-shrink-0" />
                    {commerce.adresse}, {commerce.ville}
                  </p>
                </div>
              </div>

              {commerce.description && (
                <p className="mt-3 text-sm leading-relaxed text-stone-500">{commerce.description}</p>
              )}

              <div className="mt-3 flex flex-wrap items-center gap-3 text-xs font-medium text-stone-400">
                <span className="rounded-lg bg-stone-100 px-2.5 py-1 font-semibold text-stone-500 dark:bg-ink-800 dark:text-stone-400">
                  {commerce.categorie.nom}
                </span>
                {commerce.telephone && (
                  <span className="flex items-center gap-1">
                    <Phone size={13} strokeWidth={1.75} /> {commerce.telephone}
                  </span>
                )}
                {commerce.siteWeb && (
                  <a
                    href={commerce.siteWeb}
                    target="_blank"
                    rel="noreferrer"
                    className="flex items-center gap-1 text-cobalt-600 hover:underline dark:text-cobalt-400"
                  >
                    <Globe size={13} strokeWidth={1.75} /> Site web
                  </a>
                )}
              </div>
            </div>

            <div className="mb-3 mt-6 flex items-center justify-between">
              <p className="text-xs font-bold uppercase tracking-[2px] text-stone-500">
                Offres actives ({commerce.offres.length})
              </p>
            </div>

            {commerce.offres.length === 0 ? (
              <div className="rounded-2xl border border-stone-200 bg-white p-8 text-center text-sm text-stone-400 dark:border-ink-800 dark:bg-ink-900">
                <Tag size={28} strokeWidth={1.5} className="mx-auto mb-2 text-cobalt-500" />
                Ce commerce n'a pas d'offre active pour le moment.
              </div>
            ) : (
              <div className="flex flex-col gap-3">
                {commerce.offres.map((offre, i) => (
                  <OfferCard key={offre.id} offre={offre} index={i} />
                ))}
              </div>
            )}
          </>
        )}

        {loading && (
          <div className="mt-6 flex flex-col gap-3">
            <OfferCardSkeleton />
            <OfferCardSkeleton />
          </div>
        )}
      </main>
    </div>
  )
}
