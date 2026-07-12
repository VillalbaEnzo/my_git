import { useEffect } from 'react'
import { useNavigate } from 'react-router-dom'
import { motion } from 'framer-motion'
import { Mail, ShieldQuestion } from 'lucide-react'
import BottomNav from '../../components/BottomNav/BottomNav'
import Navigation from '../../components/Navigation/Navigation'
import type { StudentUser } from '../../types/user'
import { useVerificationOutcome, OUTCOME_ROUTES } from '../../hooks/useVerificationOutcome'
import { CONTACT_EMAIL } from '../../config'

function buildMailtoLink(user: StudentUser | null): string {
  const subject = encodeURIComponent("Demande d'accès à une offre alternative — MADEV Pass")
  const identity = user ? `${user.prenom} ${user.nom} (${user.email})` : ''
  const body = encodeURIComponent(
    `Bonjour,\n\nMon inscription en tant qu'étudiant n'est pas éligible à l'abonnement standard.\nJe souhaiterais faire une demande pour accéder à une autre offre.\n\n${identity}\n\nCordialement,`,
  )
  return `mailto:${CONTACT_EMAIL}?subject=${subject}&body=${body}`
}

export default function AlternativeAccess() {
  const navigate = useNavigate()
  const { user, outcome, loading } = useVerificationOutcome()

  useEffect(() => {
    if (outcome && outcome !== 'ALTERNATIVE') navigate(OUTCOME_ROUTES[outcome], { replace: true })
  }, [outcome, navigate])

  if (loading || outcome !== 'ALTERNATIVE') return null

  return (
    <div className="grain relative min-h-screen overflow-hidden bg-cream pb-28 dark:bg-ink-950">
      <div className="grid-bg pointer-events-none absolute inset-x-0 top-0 h-72 opacity-40 dark:opacity-25" />
      <div className="aurora-blob -top-40 left-1/2 h-96 w-96 -translate-x-1/2 bg-cobalt-500/15" />

      <header className="relative flex items-start justify-between px-6 pb-5 pt-12">
        <div>
          <p className="text-eyebrow uppercase text-cobalt-600 dark:text-cobalt-400">Vienne</p>
          <h1 className="mt-1.5 font-display text-2xl font-bold tracking-tight text-ink-900 dark:text-white">
            Accès alternatif
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
          <div className="mb-4 flex h-11 w-11 items-center justify-center rounded-full bg-warning-500/15 text-warning-500 dark:text-warning-400">
            <ShieldQuestion size={22} strokeWidth={1.75} />
          </div>
          <h2 className="font-display text-xl font-bold text-ink-900 dark:text-white">
            L'abonnement standard n'est pas disponible pour votre profil
          </h2>
          <p className="mt-2 text-sm leading-relaxed text-stone-500 dark:text-stone-400">
            Votre dossier ne remplit pas les conditions de l'abonnement étudiant à 20€/an. Vous pouvez nous
            contacter pour faire une demande d'accès à une offre alternative.
          </p>

          <motion.a
            href={buildMailtoLink(user)}
            whileHover={{ y: -2 }}
            whileTap={{ scale: 0.98 }}
            className="sheen mt-6 flex w-full items-center justify-center gap-2 rounded-xl bg-cobalt-500 py-3.5 font-bold text-white shadow-cobalt transition-all duration-300 hover:bg-cobalt-600 hover:shadow-e4"
          >
            <Mail size={18} strokeWidth={1.75} />
            Faire une demande par email
          </motion.a>
        </motion.div>
      </section>

      <BottomNav />
    </div>
  )
}
