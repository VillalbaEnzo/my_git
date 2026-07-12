from enum import Enum
from typing import Optional

from pydantic import BaseModel, Field


class DocumentType(str, Enum):
    CARTE_IDENTITE = "CARTE_IDENTITE"
    PASSEPORT = "PASSEPORT"
    PERMIS_CONDUIRE = "PERMIS_CONDUIRE"
    INCONNU = "INCONNU"


class RiskLevel(str, Enum):
    FAIBLE = "FAIBLE"
    MOYEN = "MOYEN"
    ELEVE = "ELEVE"

class ExtractedFields(BaseModel):
    nom: Optional[str] = None
    prenom: Optional[str] = None
    date_naissance: Optional[str] = None
    numero_document: Optional[str] = None
    document_type: DocumentType = DocumentType.INCONNU


class MRZFields(BaseModel):
    nom: Optional[str] = None
    prenom: Optional[str] = None
    date_naissance: Optional[str] = None
    numero_document: Optional[str] = None
    nationalite: Optional[str] = None
    date_expiration: Optional[str] = None
    sexe: Optional[str] = None
    document_type: DocumentType = DocumentType.INCONNU

    mrz_found: bool = False
    mrz_raw: Optional[str] = None

    check_digit_document_valid: Optional[bool] = None
    check_digit_birth_valid: Optional[bool] = None
    check_digit_expiry_valid: Optional[bool] = None
    check_digit_composite_valid: Optional[bool] = None
    all_checks_valid: bool = False


class ImageQualityReport(BaseModel):
    sharpness_score: float = 0.0
    brightness_score: float = 0.0
    quality_score: float = 0.0
    was_deskewed: bool = False
    was_cropped: bool = False
    warnings: list[str] = Field(default_factory=list)


class FieldComparison(BaseModel):
    field_name: str
    ocr_value: Optional[str] = None
    mrz_value: Optional[str] = None
    similarity: float = 0.0
    is_consistent: bool = False


class ConsistencyReport(BaseModel):
    comparisons: list[FieldComparison] = Field(default_factory=list)
    average_similarity: float = 0.0
    global_consistency: bool = False

class VerificationResponse(BaseModel):
    extracted_fields: ExtractedFields
    mrz_fields: MRZFields
    image_quality: ImageQualityReport
    consistency: ConsistencyReport

    risk_score: float = Field(ge=0.0, le=1.0)
    risk_level: RiskLevel
    reasons: list[str] = Field(default_factory=list)


class HealthResponse(BaseModel):
    status: str = "ok"
    ollama_reachable: bool = False


class InscriptionVerificationResponse(BaseModel):
    cni_extracted_fields: ExtractedFields
    cni_mrz_fields: MRZFields
    cni_image_quality: ImageQualityReport
    cni_consistency: ConsistencyReport
    attestation_extracted_fields: Optional[ExtractedFields] = None
    attestation_consistency: Optional[ConsistencyReport] = None

    risk_score: float = Field(ge=0.0, le=1.0)
    risk_level: RiskLevel
    reasons: list[str] = Field(default_factory=list)


class JobStatus(str, Enum):
    PENDING = "PENDING"
    DONE = "DONE"
    ERROR = "ERROR"

class JobCreatedResponse(BaseModel):
    job_id: str

class InscriptionJobStatusResponse(BaseModel):
    status: JobStatus
    result: Optional[InscriptionVerificationResponse] = None
    error: Optional[str] = None
