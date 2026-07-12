export type Role = 'ETUDIANT' | 'COMMERCANT' | 'ADMIN'

export interface User {
  id: string
  email: string
  role: Role
  prenom: string
  nom: string
  numeroCarte: string | null
  isActif: boolean
  createdAt: string
  updatedAt: string
  statutSuppression?: 'PENDING_DELETION' | null
  dateSuppressionDemandee?: string | null
  statutInscription?: string
  dateNaissanceDeclaree?: string | null
  dateNaissanceEffective?: string | null
  cniRectoUrl?: string | null
  cniVersoUrl?: string | null
  attestationScolariteUrl?: string | null
}

export type StudentUser = User & {
  role: 'ETUDIANT'
  numeroCarte: string
}
