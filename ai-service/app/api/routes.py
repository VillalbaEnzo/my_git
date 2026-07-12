from __future__ import annotations

import asyncio
import logging
import time

from fastapi import APIRouter, File, HTTPException, UploadFile

from app.models.schemas import (
    ExtractedFields,
    HealthResponse,
    ImageQualityReport,
    InscriptionJobStatusResponse,
    InscriptionVerificationResponse,
    JobCreatedResponse,
    MRZFields,
    VerificationResponse,
)
from app.services.identity_merger import merge_identity, merge_mrz
from app.services.image_processor import image_processor
from app.services.job_store import JobStore
from app.services.llm_extractor import llm_extractor
from app.services.mrz_parser import mrz_parser
from app.services.pdf_extractor import pdf_text_extractor
from app.services.risk_scorer import risk_scorer
from app.services.similarity import similarity_service

router = APIRouter()
logger = logging.getLogger("ai-service.routes")

_ALLOWED_IMAGE_TYPES = {"image/jpeg", "image/png", "image/webp"}
_ALLOWED_PDF_TYPES = {"application/pdf"}

_inscription_jobs: JobStore[InscriptionVerificationResponse] = JobStore()


@router.get("/health", response_model=HealthResponse)
async def health() -> HealthResponse:
    return HealthResponse(status="ok", ollama_reachable=llm_extractor.is_reachable())


@router.post("/verify", response_model=VerificationResponse)
async def verify_document(file: UploadFile = File(...)) -> VerificationResponse:
    if file.content_type in _ALLOWED_PDF_TYPES:
        return await _verify_pdf(file)
    if file.content_type in _ALLOWED_IMAGE_TYPES:
        return await _verify_image(file)
    raise HTTPException(status_code=400, detail="Format non supporté (jpeg/png/webp ou pdf attendu)")


async def _process_identity_image(file: UploadFile, label: str = "image") -> tuple[ExtractedFields, MRZFields, ImageQualityReport]:
    raw_bytes = await file.read()
    if not raw_bytes:
        raise HTTPException(status_code=400, detail="Fichier vide")
    return _process_identity_image_bytes(raw_bytes, label=label)


def _process_identity_image_bytes(raw_bytes: bytes, label: str = "image") -> tuple[ExtractedFields, MRZFields, ImageQualityReport]:
    t0 = time.monotonic()
    processed_bytes, image_quality = image_processor.process(raw_bytes)
    logger.info("[%s] prétraitement OpenCV terminé (%.1fs)", label, time.monotonic() - t0)

    t0 = time.monotonic()
    extracted_fields = llm_extractor.extract_visible_fields(processed_bytes)
    logger.info("[%s] extraction des champs visibles par le LLM terminée (%.1fs)", label, time.monotonic() - t0)

    t0 = time.monotonic()
    raw_mrz_text = llm_extractor.extract_mrz_raw_text(processed_bytes)
    logger.info("[%s] transcription MRZ par le LLM terminée (%.1fs)", label, time.monotonic() - t0)

    mrz_fields = mrz_parser.parse(raw_mrz_text)
    logger.info("[%s] MRZ trouvée=%s, valide=%s", label, mrz_fields.mrz_found, mrz_fields.all_checks_valid)
    return extracted_fields, mrz_fields, image_quality


async def _verify_image(file: UploadFile) -> VerificationResponse:
    extracted_fields, mrz_fields, image_quality = await _process_identity_image(file)
    consistency = similarity_service.compare(extracted_fields, mrz_fields)
    risk_score, risk_level, reasons = risk_scorer.score(mrz_fields, consistency, image_quality)

    return VerificationResponse(
        extracted_fields=extracted_fields, mrz_fields=mrz_fields,
        image_quality=image_quality, consistency=consistency,
        risk_score=risk_score, risk_level=risk_level, reasons=reasons,
    )


def _extract_attestation_fields_bytes(raw_bytes: bytes, content_type: str) -> ExtractedFields | None:
    if content_type in _ALLOWED_PDF_TYPES:
        document_text = pdf_text_extractor.extract_text(raw_bytes)
        if document_text is None:
            return None
        return llm_extractor.extract_visible_fields_from_text(document_text)

    processed_bytes, _ = image_processor.process(raw_bytes)
    return llm_extractor.extract_visible_fields(processed_bytes)


def _run_inscription_pipeline(
    recto_bytes: bytes,
    verso_bytes: bytes | None,
    attestation_bytes: bytes,
    attestation_content_type: str,
) -> InscriptionVerificationResponse:
    request_start = time.monotonic()

    recto_fields, recto_mrz, recto_quality = _process_identity_image_bytes(recto_bytes, label="recto")

    if verso_bytes is not None:
        verso_fields, verso_mrz, verso_quality = _process_identity_image_bytes(verso_bytes, label="verso")
        cni_image_quality = ImageQualityReport(
            sharpness_score=min(recto_quality.sharpness_score, verso_quality.sharpness_score),
            brightness_score=min(recto_quality.brightness_score, verso_quality.brightness_score),
            quality_score=min(recto_quality.quality_score, verso_quality.quality_score),
            was_deskewed=recto_quality.was_deskewed or verso_quality.was_deskewed,
            was_cropped=recto_quality.was_cropped or verso_quality.was_cropped,
            warnings=[*recto_quality.warnings, *verso_quality.warnings],
        )
    else:
        verso_fields, verso_mrz = None, None
        cni_image_quality = recto_quality

    cni_fields = merge_identity(recto_fields, verso_fields)
    cni_mrz = merge_mrz(recto_mrz, verso_mrz)
    cni_consistency = similarity_service.compare(cni_fields, cni_mrz)
    logger.info("fusion recto/verso + comparaison OCR/MRZ terminées")

    t0 = time.monotonic()
    attestation_fields = _extract_attestation_fields_bytes(attestation_bytes, attestation_content_type)
    logger.info("[attestation] extraction terminée (%.1fs)", time.monotonic() - t0)
    attestation_consistency = (
        similarity_service.compare_names(cni_fields, attestation_fields) if attestation_fields else None
    )

    risk_score, risk_level, reasons = risk_scorer.score_inscription(
        cni_mrz, cni_consistency, attestation_consistency, cni_image_quality,
    )
    logger.info(
        "verify-inscription : terminé en %.1fs (risk_score=%.2f, risk_level=%s)",
        time.monotonic() - request_start, risk_score, risk_level,
    )

    return InscriptionVerificationResponse(
        cni_extracted_fields=cni_fields, cni_mrz_fields=cni_mrz,
        cni_image_quality=cni_image_quality, cni_consistency=cni_consistency,
        attestation_extracted_fields=attestation_fields, attestation_consistency=attestation_consistency,
        risk_score=risk_score, risk_level=risk_level, reasons=reasons,
    )


async def _run_inscription_job(
    job_id: str,
    recto_bytes: bytes,
    verso_bytes: bytes | None,
    attestation_bytes: bytes,
    attestation_content_type: str,
) -> None:
    try:
        result = await asyncio.to_thread(
            _run_inscription_pipeline, recto_bytes, verso_bytes, attestation_bytes, attestation_content_type
        )
        _inscription_jobs.mark_done(job_id, result)
    except Exception as exc:
        logger.exception("verify-inscription : le job %s a échoué", job_id)
        _inscription_jobs.mark_error(job_id, str(exc))


@router.post("/verify-inscription/jobs", response_model=JobCreatedResponse, status_code=202)
async def create_verify_inscription_job(
    cni_recto: UploadFile = File(...),
    cni_verso: UploadFile | None = File(None),
    attestation_scolarite: UploadFile = File(...),
) -> JobCreatedResponse:
    if cni_recto.content_type not in _ALLOWED_IMAGE_TYPES:
        raise HTTPException(status_code=400, detail="Le recto de la CNI doit être une image (jpeg/png/webp)")
    if cni_verso is not None and cni_verso.content_type not in _ALLOWED_IMAGE_TYPES:
        raise HTTPException(status_code=400, detail="Le verso de la CNI doit être une image (jpeg/png/webp)")
    if attestation_scolarite.content_type not in _ALLOWED_IMAGE_TYPES and attestation_scolarite.content_type not in _ALLOWED_PDF_TYPES:
        raise HTTPException(status_code=400, detail="Attestation de scolarité : format non supporté (jpeg/png/webp ou pdf attendu)")

    recto_bytes = await cni_recto.read()
    verso_bytes = await cni_verso.read() if cni_verso is not None else None
    attestation_bytes = await attestation_scolarite.read()
    if not recto_bytes:
        raise HTTPException(status_code=400, detail="Le recto de la CNI est vide")
    if not attestation_bytes:
        raise HTTPException(status_code=400, detail="Attestation de scolarité vide")

    job_id = _inscription_jobs.create()
    logger.info(
        "verify-inscription : job %s créé (recto=%s, verso=%s, attestation=%s)",
        job_id, cni_recto.filename, cni_verso.filename if cni_verso else None, attestation_scolarite.filename,
    )
    asyncio.create_task(
        _run_inscription_job(job_id, recto_bytes, verso_bytes, attestation_bytes, attestation_scolarite.content_type)
    )
    return JobCreatedResponse(job_id=job_id)


@router.get("/verify-inscription/jobs/{job_id}", response_model=InscriptionJobStatusResponse)
async def get_verify_inscription_job(job_id: str) -> InscriptionJobStatusResponse:
    job = _inscription_jobs.get(job_id)
    if job is None:
        raise HTTPException(status_code=404, detail="Job introuvable ou expiré")
    return InscriptionJobStatusResponse(status=job.status, result=job.result, error=job.error)


async def _verify_pdf(file: UploadFile) -> VerificationResponse:
    raw_bytes = await file.read()
    if not raw_bytes:
        raise HTTPException(status_code=400, detail="Fichier vide")

    document_text = pdf_text_extractor.extract_text(raw_bytes)
    if document_text is None:
        raise HTTPException(
            status_code=422,
            detail="Impossible d'extraire du texte de ce PDF (scan sans couche texte, ou fichier corrompu)",
        )

    image_quality = ImageQualityReport(
        sharpness_score=0.0, brightness_score=0.0, quality_score=1.0,
        was_deskewed=False, was_cropped=False, warnings=[],
    )

    extracted_fields = llm_extractor.extract_visible_fields_from_text(document_text)
    mrz_fields = mrz_parser.parse(document_text)
    consistency = similarity_service.compare(extracted_fields, mrz_fields)
    risk_score, risk_level, reasons = risk_scorer.score(mrz_fields, consistency, image_quality)

    return VerificationResponse(
        extracted_fields=extracted_fields, mrz_fields=mrz_fields,
        image_quality=image_quality, consistency=consistency,
        risk_score=risk_score, risk_level=risk_level, reasons=reasons,
    )