from __future__ import annotations

from app.core.config import settings
from app.models.schemas import (
    ConsistencyReport,
    ImageQualityReport,
    MRZFields,
    RiskLevel,
)


class RiskScorer:
    def __init__(self) -> None:
        self.w_mrz = settings.weight_mrz_validity
        self.w_consistency = settings.weight_ocr_mrz_consistency
        self.w_similarity = settings.weight_embedding_similarity
        self.w_quality = settings.weight_image_quality

        self.threshold_low = settings.risk_threshold_low
        self.threshold_medium = settings.risk_threshold_medium

        self.w_mrz_inscription = settings.weight_mrz_validity_inscription
        self.w_consistency_inscription = settings.weight_ocr_mrz_consistency_inscription
        self.w_similarity_inscription = settings.weight_embedding_similarity_inscription
        self.w_quality_inscription = settings.weight_image_quality_inscription
        self.w_attestation = settings.weight_attestation_consistency

    def score(
        self,
        mrz_fields: MRZFields,
        consistency: ConsistencyReport,
        image_quality: ImageQualityReport,
    ) -> tuple[float, RiskLevel, list[str]]:
        reasons: list[str] = []

        mrz_risk = self._mrz_risk(mrz_fields, reasons)
        consistency_risk = self._consistency_risk(consistency, reasons)
        similarity_risk = self._similarity_risk(consistency, reasons)
        quality_risk = self._quality_risk(image_quality, reasons)

        risk_score = (
            self.w_mrz * mrz_risk
            + self.w_consistency * consistency_risk
            + self.w_similarity * similarity_risk
            + self.w_quality * quality_risk
        )
        risk_score = max(0.0, min(1.0, risk_score))

        level = self._level_from_score(risk_score)
        if not reasons:
            reasons.append("Aucune anomalie détectée sur les signaux disponibles")

        return round(risk_score, 4), level, reasons

    def score_inscription(
        self,
        mrz_fields: MRZFields,
        cni_consistency: ConsistencyReport,
        attestation_consistency: ConsistencyReport | None,
        image_quality: ImageQualityReport,
    ) -> tuple[float, RiskLevel, list[str]]:
        reasons: list[str] = []

        mrz_risk = self._mrz_risk(mrz_fields, reasons)
        consistency_risk = self._consistency_risk(cni_consistency, reasons)
        similarity_risk = self._similarity_risk(cni_consistency, reasons)
        quality_risk = self._quality_risk(image_quality, reasons)
        attestation_risk = self._attestation_consistency_risk(attestation_consistency, reasons)

        risk_score = (
            self.w_mrz_inscription * mrz_risk
            + self.w_consistency_inscription * consistency_risk
            + self.w_similarity_inscription * similarity_risk
            + self.w_quality_inscription * quality_risk
            + self.w_attestation * attestation_risk
        )
        risk_score = max(0.0, min(1.0, risk_score))

        level = self._level_from_score(risk_score)
        if not reasons:
            reasons.append("Aucune anomalie détectée sur les signaux disponibles")

        return round(risk_score, 4), level, reasons

    def _attestation_consistency_risk(
        self, attestation_consistency: ConsistencyReport | None, reasons: list[str]
    ) -> float:
        if attestation_consistency is None or not attestation_consistency.comparisons:
            reasons.append("Attestation de scolarité illisible : cohérence nom/prénom non vérifiable")
            return 0.5
        if not attestation_consistency.global_consistency:
            inconsistent = [c.field_name for c in attestation_consistency.comparisons if not c.is_consistent]
            if inconsistent:
                reasons.append(f"Incohérence nom/prénom entre la CNI et l'attestation de scolarité : {', '.join(inconsistent)}")
            return 1.0
        return 0.0

    def _mrz_risk(self, mrz_fields: MRZFields, reasons: list[str]) -> float:
        if not mrz_fields.mrz_found:
            reasons.append("Aucune zone MRZ exploitable (normal pour certains formats de document récents) — vérification manuelle recommandée")
            return 0.5
        if not mrz_fields.all_checks_valid:
            reasons.append("Un ou plusieurs chiffres de contrôle (check digits) MRZ sont invalides")
            return 1.0
        return 0.0

    def _consistency_risk(self, consistency: ConsistencyReport, reasons: list[str]) -> float:
        if not consistency.comparisons:
            return 0.0
        if not consistency.global_consistency:
            inconsistent = [c.field_name for c in consistency.comparisons if not c.is_consistent]
            if inconsistent:
                reasons.append(f"Incohérence(s) OCR/MRZ sur : {', '.join(inconsistent)}")
            return 1.0
        return 0.0

    def _similarity_risk(self, consistency: ConsistencyReport, reasons: list[str]) -> float:
        if not consistency.comparisons:
            return 0.0
        return max(0.0, 1.0 - consistency.average_similarity)

    def _quality_risk(self, image_quality: ImageQualityReport, reasons: list[str]) -> float:
        if image_quality.warnings:
            reasons.extend(image_quality.warnings)
        return max(0.0, 1.0 - image_quality.quality_score)

    def _level_from_score(self, score: float) -> RiskLevel:
        if score <= self.threshold_low:
            return RiskLevel.FAIBLE
        if score <= self.threshold_medium:
            return RiskLevel.MOYEN
        return RiskLevel.ELEVE


risk_scorer = RiskScorer()
