import { useEffect, useState } from 'react'
import type { StudentUser } from '../types/user'
import { getVerificationOutcome, type VerificationOutcome } from '../utils/age'
import api from '../api/client'

export function useVerificationOutcome() {
  const [user, setUser] = useState<StudentUser | null>(null)
  const [outcome, setOutcome] = useState<VerificationOutcome | null>(null)
  const [loading, setLoading] = useState(true)
  const [error, setError] = useState<string | null>(null)

  useEffect(() => {
    api
      .get<StudentUser>('/auth/me')
      .then((res) => {
        setUser(res.data)
        setOutcome(getVerificationOutcome(res.data))
      })
      .catch((err) => {
        if (err.response?.status !== 401) {
          setError('Impossible de charger votre profil')
        }
      })
      .finally(() => setLoading(false))
  }, [])

  return { user, outcome, loading, error }
}

export const OUTCOME_ROUTES: Record<VerificationOutcome, string> = {
  SUBSCRIBE: '/abonnement',
  ALTERNATIVE: '/acces-alternatif',
  PENDING: '/carte',
}
