import { useEffect, useRef, useState } from 'react'
import { useNavigate } from 'react-router-dom'
import { motion } from 'framer-motion'
import confetti from 'canvas-confetti'
import { Bell, ShieldQuestion, FileWarning } from 'lucide-react'
import StudentCard from '../../components/StudentCard/StudentCard'
import BottomNav from '../../components/BottomNav/BottomNav'
import Navigation from '../../components/Navigation/Navigation'
import Modal from '../../components/ui/Modal'
import { useVerificationOutcome, OUTCOME_ROUTES } from '../../hooks/useVerificationOutcome'

const ONBOARDING_KEY = 'madev:onboarded'
const CARD_CONFETTI_KEY = 'madev:card-validated-confetti'

function fireWelcomeConfetti() {
  const colors = ['#2347E6', '#6680F4', '#ffffff', '#34d399']
  const burst = (particleRatio: number, opts: confetti.Options) =>
    confetti({
      origin: { y: 0.7 },
      colors,
      particleCount: Math.floor(200 * particleRatio),
      ...opts,
    })

  burst(0.25, { spread: 26, startVelocity: 55 })
  burst(0.2, { spread: 60 })
  burst(0.35, { spread: 100, decay: 0.91, scalar: 0.8 })
  burst(0.1, { spread: 120, startVelocity: 25, decay: 0.92, scalar: 1.2 })
  burst(0.1, { spread: 120, startVelocity: 45 })
}

export default function Dashboard() {
  const navigate = useNavigate()
  const { user, outcome, loading, error } = useVerificationOutcome()
  const firstLoginRef = useRef(!sessionStorage.getItem(ONBOARDING_KEY))
  const [docsModalOpen, setDocsModalOpen] = useState(false)
  const missingDocuments = user?.statutInscription === 'PENDING_DOCUMENT'
  const isCardValidated = Boolean(user?.isActif && user?.numeroCarte)

  useEffect(() => {
    if (outcome === 'SUBSCRIBE' || outcome === 'ALTERNATIVE') navigate(OUTCOME_ROUTES[outcome], { replace: true })
  }, [outcome, navigate])

  useEffect(() => {
    if (!user) return
    sessionStorage.setItem(ONBOARDING_KEY, '1')
    if (missingDocuments) setDocsModalOpen(true)
  }, [user, missingDocuments])

  useEffect(() => {
    if (!isCardValidated || localStorage.getItem(CARD_CONFETTI_KEY)) return
    localStorage.setItem(CARD_CONFETTI_KEY, '1')
    const t = setTimeout(fireWelcomeConfetti, 700)
    return () => clearTimeout(t)
  }, [isCardValidated])

  if (loading) {
    return (
      <div className="relative min-h-screen bg-cream pb-28 dark:bg-ink-950">
        <div className="px-6 pb-6 pt-12">
          <div className="skeleton h-4 w-24 rounded" />
          <div className="skeleton mt-2 h-7 w-48 rounded" />
        </div>
        <div className="px-6">
          <div className="skeleton mx-auto h-[220px] w-full max-w-sm rounded-2xl" />
        </div>
      </div>
    )
  }
  if (!user) {
    return (
      <div className="flex min-h-screen flex-col items-center justify-center gap-3 px-6 text-center">
        <p className="font-display text-lg font-semibold text-ink-900 dark:text-white">Profil indisponible</p>
        <p className="text-sm text-stone-500 dark:text-stone-400">Nous n’avons pas pu charger votre profil. Réessayez plus tard.</p>
      </div>
    )
  }
  if (outcome === 'SUBSCRIBE' || outcome === 'ALTERNATIVE') return null

  return (
    <div className="grain relative min-h-screen overflow-hidden bg-cream pb-28 dark:bg-ink-950">
      <div className="grid-bg pointer-events-none absolute inset-x-0 top-0 h-72 opacity-40 dark:opacity-25" />
      <div className="aurora-blob -top-40 left-1/2 h-96 w-96 -translate-x-1/2 bg-cobalt-500/15" />
      <div className="aurora-blob right-[-10%] top-[30%] h-72 w-72 bg-[#7C5CFF]/10 [animation-delay:-7s]" />

      <header className="relative flex items-start justify-between px-6 pb-6 pt-12">
        <div>
          <p className="text-sm font-medium text-cobalt-600 dark:text-cobalt-400">{firstLoginRef.current ? 'Bienvenue,' : 'Bonjour,'}</p>
          <h1 className="mt-1 font-display text-2xl font-bold tracking-tight text-ink-900 dark:text-white">{user.prenom} {user.nom}</h1>
        </div>
        <div className="flex items-center gap-2">
          <button
            title="Notifications"
            aria-label="Notifications"
            className="flex h-9 w-9 items-center justify-center rounded-xl border border-stone-300 bg-white/60 text-stone-700 transition-colors hover:border-cobalt-500/50 hover:text-cobalt-600 dark:border-white/10 dark:bg-ink-900/60 dark:text-stone-200 dark:hover:text-cobalt-300"
          >
            <Bell size={18} strokeWidth={1.75} />
          </button>
          <Navigation />
        </div>
      </header>

      <section className="relative flex flex-col items-center gap-3 px-6 pt-2">
        <p className="self-start text-xs font-semibold uppercase tracking-[0.18em] text-stone-500">Ma carte</p>
        {user.isActif && user.numeroCarte ? (
          <>
            <StudentCard user={user} reveal={firstLoginRef.current} />
            <motion.p
              initial={{ opacity: 0 }}
              animate={{ opacity: 1 }}
              transition={{ delay: 0.3 }}
              className="mt-1 text-center text-sm text-stone-400"
            >
              Présentez ce QR code chez nos partenaires
            </motion.p>
          </>
        ) : (
          <div className="flex min-h-[230px] w-full max-w-sm flex-col items-center justify-center gap-3 rounded-3xl border border-dashed border-warning-500/40 bg-warning-bg p-6 text-center dark:border-warning-400/30 dark:bg-warning-500/10">
            <div className="flex h-11 w-11 items-center justify-center rounded-full bg-warning-500/15 text-warning-500 dark:text-warning-400">
              {missingDocuments ? <FileWarning size={22} strokeWidth={1.75} /> : <ShieldQuestion size={22} strokeWidth={1.75} />}
            </div>
            {missingDocuments ? (
              <>
                <p className="font-display font-semibold text-ink-900 dark:text-white">Documents à renseigner</p>
                <p className="text-sm text-stone-500 dark:text-stone-400">
                  Veuillez renseigner vos documents dans votre profil afin de finaliser votre dossier et faire valider votre carte.
                </p>
                <button
                  onClick={() => navigate('/profile')}
                  className="mt-2 rounded-xl bg-primary px-4 py-2 text-sm font-semibold text-white transition-colors hover:bg-cobalt-500"
                >
                  Renseigner mes documents
                </button>
              </>
            ) : (
              <>
                <p className="font-display font-semibold text-ink-900 dark:text-white">Carte en attente de validation</p>
                <p className="text-sm text-stone-500 dark:text-stone-400">
                  Votre dossier est en cours de vérification par un administrateur. Votre carte et votre QR code seront disponibles dès qu'il sera validé.
                </p>
              </>
            )}
          </div>
        )}
      </section>

      <Modal open={docsModalOpen} onClose={() => setDocsModalOpen(false)} title="Documents manquants">
        <p className="text-sm text-stone-600 dark:text-stone-300">
          Veuillez renseigner vos documents afin de finaliser votre dossier et faire valider votre carte.
        </p>
        <button
          onClick={() => navigate('/profile')}
          className="mt-5 w-full rounded-xl bg-primary px-4 py-2.5 text-sm font-bold text-white transition-colors hover:bg-cobalt-500"
        >
          Renseigner mes documents
        </button>
      </Modal>

      {error && <p role="alert" className="py-2 text-center text-sm text-red-500">{error}</p>}
      <BottomNav />
    </div>
  )
}
