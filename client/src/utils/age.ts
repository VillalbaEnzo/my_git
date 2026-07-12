import type { StudentUser } from '../types/user'

export function computeAge(dateNaissance: string | null | undefined): number | null {
  if (!dateNaissance) return null
  const dob = new Date(dateNaissance)
  if (Number.isNaN(dob.getTime())) return null

  const now = new Date()
  let age = now.getFullYear() - dob.getFullYear()
  const hasHadBirthdayThisYear =
    now.getMonth() > dob.getMonth() || (now.getMonth() === dob.getMonth() && now.getDate() >= dob.getDate())
  if (!hasHadBirthdayThisYear) age -= 1
  return age
}

export type VerificationOutcome = 'SUBSCRIBE' | 'ALTERNATIVE' | 'PENDING'

export function getVerificationOutcome(user: StudentUser): VerificationOutcome {
  const isValidated = user.statutInscription === 'VALIDE' && user.isActif
  const isRejected = user.statutInscription === 'REJETÉ'

  if (!isValidated && !isRejected) return 'PENDING'

  if (isRejected) return 'ALTERNATIVE'

  const age = computeAge(user.dateNaissanceEffective ?? user.dateNaissanceDeclaree)
  if (age === null) return 'PENDING'
  if (age >= 16 && age <= 30) return 'SUBSCRIBE'
  return 'ALTERNATIVE'
}
