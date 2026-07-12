import { useEffect, useState } from 'react'
import { useNavigate } from 'react-router-dom'
import { motion } from 'framer-motion'
import { Sparkles, Check } from 'lucide-react'
import BottomNav from '../../components/BottomNav/BottomNav'
import Navigation from '../../components/Navigation/Navigation'
import { useVerificationOutcome, OUTCOME_ROUTES } from '../../hooks/useVerificationOutcome'

export default function Subscription() {
  const navigate = useNavigate()
  const { outcome, loading: outcomeLoading } = useVerificationOutcome()
  const [loading, setLoading] = useState(false)

  useEffect(() => {
    if (outcome && outcome !== 'SUBSCRIBE') navigate(OUTCOME_ROUTES[outcome], { replace: true })
  }, [outcome, navigate])

  // TODO: brancher le vrai paiement ici
  function handleSubscribe() {
    setLoading(true)
    setTimeout(() => setLoading(false), 800)
  }

  if (outcomeLoading || outcome !== 'SUBSCRIBE') return null

  return (
    <div className="grain relative min-h-screen overflow-hidden bg-cream pb-28 dark:bg-ink-950">
      <div className="grid-bg pointer-events-none absolute inset-x-0 top-0 h-72 opacity-40 dark:opacity-25" />
      <div className="aurora-blob -top-40 left-1/2 h-96 w-96 -translate-x-1/2 bg-cobalt-500/15" />

      <header className="relative flex items-start justify-between px-6 pb-5 pt-12">
        <div>
          <p className="text-eyebrow uppercase text-cobalt-600 dark:text-cobalt-400">Compte validé</p>
          <h1 className="mt-1.5 font-display text-2xl font-bold tracking-tight text-ink-900 dark:text-white">
            Activez votre abonnement
          </h1>
        </div>
        <Navigation />
      </header>

      <section className="relative flex flex-col items-center gap-5 px-6 pt-4">
        <motion.div
          initial={{ opacity: 0, y: 16 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ duration: 0.4, ease: [0.16, 1, 0.3, 1] }}
          className="w-full max-w-sm rounded-3xl border border-stone-300 bg-white p-6 shadow-e2 dark:border-white/10 dark:bg-ink-900"
        >
          <div className="mb-4 flex h-11 w-11 items-center justify-center rounded-full bg-cobalt-500/15 text-cobalt-600 dark:text-cobalt-400">
            <Sparkles size={22} strokeWidth={1.75} />
          </div>
          <h2 className="font-display text-xl font-bold text-ink-900 dark:text-white">Carte étudiante — 20€/an</h2>
          <p className="mt-2 text-sm leading-relaxed text-stone-500 dark:text-stone-400">
            Votre dossier est validé et vous avez entre 16 et 30 ans : vous êtes éligible à l'abonnement étudiant standard.
          </p>

          <ul className="mt-5 flex flex-col gap-2.5">
            {['Carte numérique + QR sécurisé', 'Offres réservées aux étudiants', 'Valable 1 an'].map((point) => (
              <li key={point} className="flex items-center gap-2.5 text-sm text-stone-700 dark:text-stone-300">
                <Check size={16} strokeWidth={2} className="shrink-0 text-emerald-500" />
                {point}
              </li>
            ))}
          </ul>

          <motion.button
            type="button"
            disabled={loading}
            onClick={handleSubscribe}
            whileHover={{ y: -2 }}
            whileTap={{ scale: 0.98 }}
            className="sheen mt-6 w-full rounded-xl bg-cobalt-500 py-3.5 font-bold text-white shadow-cobalt transition-all duration-300 hover:bg-cobalt-600 hover:shadow-e4 disabled:cursor-not-allowed disabled:opacity-60"
          >
            {loading ? 'Un instant…' : "S'abonner — 20€/an"}
          </motion.button>
          <p className="mt-3 text-center text-xs text-stone-400">Paiement sécurisé — bientôt disponible</p>
        </motion.div>
      </section>

      <BottomNav />
    </div>
  )
}
