from __future__ import annotations

import unicodedata

from datetime import datetime
from sentence_transformers import SentenceTransformer
from sentence_transformers.util import cos_sim

from app.core.config import settings
from app.models.schemas import ConsistencyReport, ExtractedFields, FieldComparison, MRZFields


class SimilarityService:
    def __init__(self) -> None:
        self.model = SentenceTransformer(settings.embedding_model_name)
        self.threshold = settings.similarity_threshold

    def compare(self, ocr_fields: ExtractedFields, mrz_fields: MRZFields) -> ConsistencyReport:
        if not mrz_fields.mrz_found:
            return ConsistencyReport(comparisons=[], average_similarity=0.0, global_consistency=False)

        pairs = [
            ("nom", ocr_fields.nom, mrz_fields.nom),
            ("prenom", ocr_fields.prenom, mrz_fields.prenom),
            ("date_naissance", ocr_fields.date_naissance, mrz_fields.date_naissance),
            ("numero_document", ocr_fields.numero_document, mrz_fields.numero_document),
        ]

        comparisons: list[FieldComparison] = []
        for field_name, ocr_value, mrz_value in pairs:
            comparisons.append(self._compare_field(field_name, ocr_value, mrz_value))

        usable = [c for c in comparisons if c.ocr_value and c.mrz_value]
        average = sum(c.similarity for c in usable) / len(usable) if usable else 0.0
        global_ok = bool(usable) and all(c.is_consistent for c in usable)

        return ConsistencyReport(
            comparisons=comparisons,
            average_similarity=round(average, 4),
            global_consistency=global_ok,
        )

    def compare_names(self, cni_fields: ExtractedFields, attestation_fields: ExtractedFields) -> ConsistencyReport:
        pairs = [
            ("nom", cni_fields.nom, attestation_fields.nom),
            ("prenom", cni_fields.prenom, attestation_fields.prenom),
        ]

        comparisons = [self._compare_field(field_name, cni_value, attestation_value) for field_name, cni_value, attestation_value in pairs]

        usable = [c for c in comparisons if c.ocr_value and c.mrz_value]
        average = sum(c.similarity for c in usable) / len(usable) if usable else 0.0
        global_ok = bool(usable) and all(c.is_consistent for c in usable)

        return ConsistencyReport(
            comparisons=comparisons,
            average_similarity=round(average, 4),
            global_consistency=global_ok,
        )

    def _compare_field(self, field_name: str, ocr_value: str | None, mrz_value: str | None) -> FieldComparison:
        if not ocr_value or not mrz_value:
            return FieldComparison(
                field_name=field_name, ocr_value=ocr_value, mrz_value=mrz_value,
                similarity=0.0, is_consistent=False,
            )

        norm_ocr = self._normalize_text(ocr_value)
        norm_mrz = self._normalize_text(mrz_value)

        if field_name == "date_naissance":
            similarity = self._compare_dates(ocr_value, mrz_value)
        elif field_name == "numero_document":
            similarity = 1.0 if norm_ocr == norm_mrz else self._char_overlap_ratio(norm_ocr, norm_mrz)
        else:
            embeddings = self.model.encode([norm_ocr, norm_mrz], convert_to_tensor=True)
            similarity = float(cos_sim(embeddings[0], embeddings[1]).item())

        return FieldComparison(
            field_name=field_name,
            ocr_value=ocr_value,
            mrz_value=mrz_value,
            similarity=round(similarity, 4),
            is_consistent=similarity >= self.threshold,
        )

    @staticmethod
    def _normalize_text(value: str) -> str:
        value = value.strip().upper()
        value = unicodedata.normalize("NFKD", value).encode("ascii", "ignore").decode("ascii")
        return " ".join(value.split())

    @staticmethod
    def _compare_dates(ocr_value: str, mrz_value: str) -> float:
        ocr_date = SimilarityService._parse_date(ocr_value)
        mrz_date = SimilarityService._parse_date(mrz_value)
        if ocr_date is not None and mrz_date is not None:
            return 1.0 if ocr_date == mrz_date else 0.0
        norm_ocr = SimilarityService._normalize_text(ocr_value)
        norm_mrz = SimilarityService._normalize_text(mrz_value)
        return SimilarityService._char_overlap_ratio(norm_ocr, norm_mrz)

    @staticmethod
    def _parse_date(value: str):
        candidate_formats = ("%d/%m/%Y", "%Y-%m-%d", "%d-%m-%Y", "%d.%m.%Y", "%Y/%m/%d")
        cleaned = value.strip()
        for fmt in candidate_formats:
            try:
                return datetime.strptime(cleaned, fmt).date()
            except ValueError:
                continue
        return None

    @staticmethod
    def _char_overlap_ratio(a: str, b: str) -> float:
        a_clean = a.replace(" ", "").replace("-", "").replace("/", "")
        b_clean = b.replace(" ", "").replace("-", "").replace("/", "")
        if not a_clean or not b_clean:
            return 0.0
        length = max(len(a_clean), len(b_clean))
        matches = sum(1 for x, y in zip(a_clean, b_clean) if x == y)
        return matches / length


similarity_service = SimilarityService()
