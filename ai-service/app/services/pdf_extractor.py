from __future__ import annotations

import io
import logging

from pypdf import PdfReader
from pypdf.errors import PdfReadError

logger = logging.getLogger(__name__)


class PDFTextExtractor:
    def extract_text(self, pdf_bytes: bytes) -> str | None:
        try:
            reader = PdfReader(io.BytesIO(pdf_bytes))
        except PdfReadError as exc:
            logger.error("PDF illisible ou corrompu : %s", exc)
            return None

        if reader.is_encrypted:
            try:
                reader.decrypt("")
            except Exception:
                logger.warning("PDF protégé par mot de passe, extraction impossible")
                return None

        pages_text = []
        for page in reader.pages:
            try:
                pages_text.append(page.extract_text() or "")
            except Exception as exc:
                logger.warning("Échec d'extraction sur une page PDF : %s", exc)

        text = "\n".join(pages_text).strip()
        return text or None


pdf_text_extractor = PDFTextExtractor()