from __future__ import annotations

from app.models.schemas import ExtractedFields, MRZFields


def merge_identity(recto: ExtractedFields, verso: ExtractedFields | None) -> ExtractedFields:
    if verso is None:
        return recto

    return ExtractedFields(
        nom=recto.nom or verso.nom,
        prenom=recto.prenom or verso.prenom,
        date_naissance=recto.date_naissance or verso.date_naissance,
        numero_document=recto.numero_document or verso.numero_document,
        document_type=recto.document_type if recto.document_type.value != "INCONNU" else verso.document_type,
    )


def merge_mrz(recto_mrz: MRZFields, verso_mrz: MRZFields | None) -> MRZFields:
    if recto_mrz.mrz_found:
        return recto_mrz
    if verso_mrz is not None and verso_mrz.mrz_found:
        return verso_mrz
    return recto_mrz
