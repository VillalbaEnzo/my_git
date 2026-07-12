import { useState, useEffect } from 'react'
import { motion, AnimatePresence } from 'framer-motion'
import { Check, X, FileText, CheckCircle2, AlertCircle, ChevronDown, ShieldCheck, ShieldAlert, ShieldQuestion, RotateCw } from 'lucide-react'
import AdminShell from '../../components/admin/AdminShell'
import api from '../../api/client'

type RiskLevel = 'FAIBLE' | 'MOYEN' | 'ELEVE'

interface AiOcrFields {
  nom?: string | null
  prenom?: string | null
  date_naissance?: string | null
  numero_document?: string | null
  document_type?: string | null
}

interface AiMrzFields {
  mrz_found?: boolean
  all_checks_valid?: boolean
}

interface AiConsistency {
  global_consistency?: boolean
}

interface AiExtractedFields {
  ocr?: AiOcrFields
  mrz?: AiMrzFields
  attestation?: AiOcrFields
  attestationConsistency?: AiConsistency
}

interface Inscription {
  id: string
  prenom: string
  nom: string
  email: string
  cniRectoUrl: string | null
  cniVersoUrl: string | null
  attestationScolariteUrl: string | null
  createdAt: string
  aiRiskScore: number | null
  aiRiskLevel: RiskLevel | null
  aiReasons: string[] | null
  aiExtractedFields: AiExtractedFields | null
  aiCheckedAt: string | null
  aiCheckStatus: 'PENDING' | 'ERROR' | null
}

const RISK_STYLES: Record<RiskLevel, { label: string; icon: typeof ShieldCheck; classes: string }> = {
  FAIBLE: {
    label: 'Risque faible',
    icon: ShieldCheck,
    classes: 'bg-success-bg text-success-500 dark:bg-success-500/15 dark:text-success-400',
  },
  MOYEN: {
    label: 'Risque moyen',
    icon: ShieldQuestion,
    classes: 'bg-warning-bg text-warning-500 dark:bg-warning-500/15 dark:text-warning-400',
  },
  ELEVE: {
    label: 'Risque élevé',
    icon: ShieldAlert,
    classes: 'bg-danger-bg text-danger-500 dark:bg-danger-500/15 dark:text-danger-400',
  },
}

function RiskBadge({ level, status, retrying, onRetry }: { level: RiskLevel | null; status: 'PENDING' | 'ERROR' | null; retrying: boolean; onRetry: () => void }) {
  if (!level && status === 'ERROR') {
    return (
      <span className="inline-flex items-center gap-1.5 rounded-full bg-danger-bg px-2.5 py-1 text-xs font-semibold text-danger-500 dark:bg-danger-500/15 dark:text-danger-400">
        <AlertCircle size={13} strokeWidth={1.75} />
        Analyse IA échouée
        <button
          onClick={(e) => { e.stopPropagation(); onRetry() }}
          disabled={retrying}
          className="ml-0.5 flex items-center gap-1 rounded-full bg-black/5 px-1.5 py-0.5 hover:bg-black/10 disabled:opacity-50 dark:bg-white/10 dark:hover:bg-white/15"
        >
          <RotateCw size={11} strokeWidth={2} className={retrying ? 'animate-spin' : ''} />
          {retrying ? '…' : 'Relancer'}
        </button>
      </span>
    )
  }
  if (!level) {
    return (
      <span className="inline-flex items-center gap-1.5 rounded-full bg-stone-100 px-2.5 py-1 text-xs font-semibold text-stone-500 dark:bg-white/[0.06] dark:text-stone-400">
        <ShieldQuestion size={13} strokeWidth={1.75} />
        Analyse IA en cours…
      </span>
    )
  }
  const { label, icon: Icon, classes } = RISK_STYLES[level]
  return (
    <span className={`inline-flex items-center gap-1.5 rounded-full px-2.5 py-1 text-xs font-semibold ${classes}`}>
      <Icon size={13} strokeWidth={1.75} />
      {label}
    </span>
  )
}

const DOCUMENT_TYPE_LABELS: Record<string, string> = {
  CARTE_IDENTITE: "Carte d'identité",
  PASSEPORT: 'Passeport',
  PERMIS_CONDUIRE: 'Permis de conduire',
  INCONNU: 'Type non identifié',
}

function AiDetailPanel({ inscription }: { inscription: Inscription }) {
  const ocr = inscription.aiExtractedFields?.ocr
  const mrz = inscription.aiExtractedFields?.mrz
  const attestationConsistency = inscription.aiExtractedFields?.attestationConsistency
  const fieldRows: [string, string | null | undefined][] = [
    ['Nom', ocr?.nom],
    ['Prénom', ocr?.prenom],
    ['Date de naissance', ocr?.date_naissance],
    ['Numéro de document', ocr?.numero_document],
    ['Type de document', ocr?.document_type ? DOCUMENT_TYPE_LABELS[ocr.document_type] ?? ocr.document_type : null],
  ]

  return (
    <motion.div
      initial={{ height: 0, opacity: 0 }}
      animate={{ height: 'auto', opacity: 1 }}
      exit={{ height: 0, opacity: 0 }}
      transition={{ duration: 0.2, ease: 'easeOut' }}
      className="overflow-hidden"
    >
      <div className="mt-4 flex flex-col gap-4 rounded-xl border border-black/[0.06] bg-cream-50 p-4 dark:border-white/[0.07] dark:bg-white/[0.03]">
        {inscription.aiReasons && inscription.aiReasons.length > 0 && (
          <div>
            <p className="mb-1.5 text-xs font-bold uppercase tracking-wide text-stone-400">Motifs</p>
            <ul className="flex flex-col gap-1">
              {inscription.aiReasons.map((reason, i) => (
                <li key={i} className="text-xs leading-relaxed text-stone-600 dark:text-stone-300">
                  · {reason}
                </li>
              ))}
            </ul>
          </div>
        )}

        {ocr && (
          <div>
            <p className="mb-1.5 text-xs font-bold uppercase tracking-wide text-stone-400">Champs extraits</p>
            <dl className="grid grid-cols-2 gap-x-4 gap-y-1.5 sm:grid-cols-3">
              {fieldRows.map(([label, value]) => (
                <div key={label}>
                  <dt className="text-[11px] text-stone-400">{label}</dt>
                  <dd className="truncate text-xs font-medium text-ink-900 dark:text-white">{value || '—'}</dd>
                </div>
              ))}
            </dl>
          </div>
        )}

        {mrz && (
          <p className="text-xs text-stone-500">
            Zone MRZ : {mrz.mrz_found ? (mrz.all_checks_valid ? 'détectée et valide' : 'détectée, invalide') : 'non détectée (normal sur certains formats de document)'}
          </p>
        )}

        {attestationConsistency && (
          <p className="text-xs text-stone-500">
            Cohérence CNI / attestation de scolarité : {attestationConsistency.global_consistency ? 'nom/prénom cohérents' : 'incohérence détectée'}
          </p>
        )}

        {inscription.aiCheckedAt && (
          <p className="text-[11px] text-stone-400">
            Analysé le {new Date(inscription.aiCheckedAt).toLocaleString('fr-FR', { day: 'numeric', month: 'long', year: 'numeric', hour: '2-digit', minute: '2-digit' })}
          </p>
        )}
      </div>
    </motion.div>
  )
}

export default function Validation() {
  const [inscriptions, setInscriptions] = useState<Inscription[]>([])
  const [loading, setLoading] = useState(true)
  const [validating, setValidating] = useState<string | null>(null)
  const [refusing, setRefusing] = useState<string | null>(null)
  const [expanded, setExpanded] = useState<string | null>(null)
  const [error, setError] = useState<string | null>(null)
  const [retryingAi, setRetryingAi] = useState<string | null>(null)

  useEffect(() => {
    api.get<Inscription[]>('/admin/inscriptions')
      .then(r => setInscriptions(r.data))
      .finally(() => setLoading(false))
  }, [])

  useEffect(() => {
    const hasPending = inscriptions.some(i => i.aiRiskLevel === null && i.aiCheckStatus !== 'ERROR')
    if (loading || !hasPending) return
    const interval = setInterval(() => {
      api.get<Inscription[]>('/admin/inscriptions').then(r => setInscriptions(r.data))
    }, 20_000)
    return () => clearInterval(interval)
  }, [inscriptions, loading])

  async function refuser(id: string) {
    setRefusing(id)
    setError(null)
    try {
      await api.patch(`/admin/refuser/${id}`)
      setInscriptions(prev => prev.filter(i => i.id !== id))
    } catch {
      setError('Le refus a échoué. Veuillez réessayer.')
    } finally {
      setRefusing(null)
    }
  }

  async function openDocument(documentUrl: string) {
    const filename = documentUrl.split('/').pop()
    if (!filename) return
    setError(null)
    try {
      const { data } = await api.get<{ token: string }>(`/documents/token/${filename}`)
      window.open(`/api/documents/${filename}?token=${data.token}`, '_blank')
    } catch {
      setError('Impossible d\u2019ouvrir le document.')
    }
  }

  async function retryAi(id: string) {
    setRetryingAi(id)
    setError(null)
    try {
      const { data } = await api.post<Partial<Inscription>>(`/admin/inscriptions/${id}/verifier-ia`)
      setInscriptions(prev => prev.map(i => (i.id === id ? { ...i, ...data } : i)))
    } catch {
      setInscriptions(prev => prev.map(i => (i.id === id ? { ...i, aiCheckStatus: 'ERROR' } : i)))
      setError("La relance de l'analyse IA a échoué. Veuillez réessayer.")
    } finally {
      setRetryingAi(null)
    }
  }

  async function valider(id: string) {
    setValidating(id)
    setError(null)
    try {
      await api.patch(`/admin/valider/${id}`)
      setInscriptions(prev => prev.filter(i => i.id !== id))
    } catch {
      setError('La validation a échoué. Veuillez réessayer.')
    } finally {
      setValidating(null)
    }
  }

  return (
    <AdminShell
      title="Inscriptions en attente"
      back={{ to: '/admin/dashboard', label: 'Tableau de bord' }}
      max="max-w-2xl"
    >
      {error && (
        <div role="alert" className="mb-4 flex items-center gap-2 rounded-lg border border-red-500/20 bg-red-500/10 px-4 py-2.5 text-sm font-medium text-red-600 dark:text-red-400">
          <AlertCircle size={16} strokeWidth={1.75} /> {error}
        </div>
      )}

      {loading && (
        <div className="flex flex-col gap-4">
          {Array.from({ length: 4 }).map((_, i) => (
            <div key={i} className="flex items-center gap-4 rounded-2xl border border-stone-200 bg-white p-5 dark:border-white/10 dark:bg-ink-900">
              <div className="skeleton h-12 w-12 flex-shrink-0 rounded-2xl" />
              <div className="flex flex-1 flex-col gap-2">
                <div className="skeleton h-4 w-40 rounded" />
                <div className="skeleton h-3 w-56 rounded" />
              </div>
              <div className="skeleton h-9 w-24 rounded-xl" />
            </div>
          ))}
        </div>
      )}

      {!loading && inscriptions.length === 0 && (
        <div className="flex flex-col items-center gap-3 py-20 text-center">
          <div className="flex h-16 w-16 items-center justify-center rounded-2xl bg-emerald-500/12 text-emerald-600 dark:text-emerald-400">
            <CheckCircle2 size={32} strokeWidth={1.5} />
          </div>
          <p className="font-display text-lg font-semibold text-ink-900 dark:text-white">Tout est à jour</p>
          <p className="text-sm text-stone-400">Aucune inscription en attente de validation.</p>
        </div>
      )}

      {!loading && inscriptions.length > 0 && (
        <p className="mb-4 text-sm font-medium text-stone-500">
          {inscriptions.length} demande{inscriptions.length > 1 ? 's' : ''} à traiter
        </p>
      )}

      <div className="flex flex-col gap-4">
        {inscriptions.map((u, i) => (
          <motion.div
            key={u.id}
            initial={{ opacity: 0, y: 16 }}
            animate={{ opacity: 1, y: 0 }}
            transition={{ duration: 0.3, delay: Math.min(i * 0.05, 0.4) }}
            className="lift group rounded-2xl border border-black/[0.06] bg-white p-5 hover:border-cobalt-500/40 dark:border-white/[0.07] dark:bg-ink-900"
          >
            <div className="flex flex-col gap-4 sm:flex-row sm:items-center">
              <div className="flex h-12 w-12 flex-shrink-0 items-center justify-center rounded-2xl bg-gradient-to-br from-cobalt-600 to-cobalt-400 text-sm font-bold uppercase text-white">
                {u.prenom[0]}{u.nom[0]}
              </div>

              <div className="min-w-0 flex-1">
                <div className="flex flex-wrap items-center gap-2">
                  <p className="truncate font-display font-semibold text-ink-900 dark:text-white">{u.prenom} {u.nom}</p>
                  <RiskBadge
                    level={u.aiRiskLevel}
                    status={u.aiCheckStatus}
                    retrying={retryingAi === u.id}
                    onRetry={() => retryAi(u.id)}
                  />
                </div>
                <p className="truncate text-sm text-stone-500">{u.email}</p>
                <p className="mt-0.5 text-xs text-stone-400">
                  Inscrit le {new Date(u.createdAt).toLocaleDateString('fr-FR', { day: 'numeric', month: 'long', year: 'numeric' })}
                </p>
                <div className="mt-2 flex flex-wrap items-center gap-3">
                  {([
                    ['Recto', u.cniRectoUrl],
                    ['Verso', u.cniVersoUrl],
                    ['Attestation', u.attestationScolariteUrl],
                  ] as const).map(([docLabel, url]) => url && (
                    <button
                      key={docLabel}
                      onClick={(e) => { e.stopPropagation(); openDocument(url) }}
                      className="flex items-center gap-1.5 rounded-lg px-2 py-1 text-xs font-semibold text-cobalt-600 transition-colors hover:bg-cobalt-500/10 dark:text-cobalt-400"
                    >
                      <FileText size={13} strokeWidth={1.75} />
                      {docLabel}
                    </button>
                  ))}
                  {u.aiCheckedAt && (
                    <button
                      onClick={() => setExpanded(prev => (prev === u.id ? null : u.id))}
                      className="flex items-center gap-1 rounded-lg px-2 py-1 text-xs font-semibold text-stone-500 transition-colors hover:bg-stone-500/10 dark:text-stone-400"
                    >
                      Détail de l'analyse
                      <ChevronDown
                        size={13}
                        strokeWidth={1.75}
                        className={`transition-transform duration-200 ${expanded === u.id ? 'rotate-180' : ''}`}
                      />
                    </button>
                  )}
                </div>
              </div>

              <div className="flex flex-shrink-0 items-center gap-2 sm:self-center">
                <button
                  onClick={() => refuser(u.id)}
                  disabled={refusing === u.id || validating === u.id}
                  className="flex items-center gap-1.5 rounded-xl border border-red-500/50 px-3 py-2 text-xs font-bold text-red-600 transition-colors hover:bg-red-500/10 active:scale-[0.98] disabled:opacity-50 dark:text-red-400"
                >
                  <X size={14} strokeWidth={2} />
                  {refusing === u.id ? '…' : 'Refuser'}
                </button>
                <button
                  onClick={() => valider(u.id)}
                  disabled={validating === u.id || refusing === u.id}
                  className="flex items-center gap-1.5 rounded-xl bg-success px-3.5 py-2 text-xs font-bold text-white shadow-e2 transition-all duration-200 hover:-translate-y-0.5 hover:shadow-e3 active:scale-[0.98] disabled:opacity-50"
                >
                  <Check size={14} strokeWidth={2} />
                  {validating === u.id ? '…' : 'Valider'}
                </button>
              </div>
            </div>

            <AnimatePresence>
              {expanded === u.id && <AiDetailPanel inscription={u} />}
            </AnimatePresence>
          </motion.div>
        ))}
      </div>
    </AdminShell>
  )
}