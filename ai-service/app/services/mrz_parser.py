from __future__ import annotations

import logging
import re

from mrz.checker.td1 import TD1CodeChecker
from mrz.checker.td2 import TD2CodeChecker
from mrz.checker.td3 import TD3CodeChecker
from mrz.base.errors import LengthError

from app.models.schemas import DocumentType, MRZFields

logger = logging.getLogger(__name__)

_MRZ_CHARSET_RE = re.compile(r"[^A-Z0-9<]")


class MRZParser:
    def parse(self, raw_mrz_text: str | None) -> MRZFields:
        if not raw_mrz_text:
            return MRZFields(mrz_found=False)

        lines = self._normalize_lines(raw_mrz_text)
        if not lines:
            return MRZFields(mrz_found=False)

        for parser_fn in (self._try_td3, self._try_td1, self._try_td2):
            result = parser_fn(lines)
            if result is not None:
                return result

        logger.info("Aucun format MRZ valide détecté dans le texte transcrit")
        return MRZFields(mrz_found=False, mrz_raw="\n".join(lines), all_checks_valid=False)

    @staticmethod
    def _normalize_lines(raw_text: str) -> list[str]:
        lines = [ln.strip().upper() for ln in raw_text.splitlines() if ln.strip()]
        cleaned = []
        for ln in lines:
            ln = ln.replace(" ", "")
            ln = _MRZ_CHARSET_RE.sub("", ln)
            if ln:
                cleaned.append(ln)
        return cleaned

    def _try_td3(self, lines: list[str]) -> MRZFields | None:
        candidate = self._pick_candidate_lines(lines, expected_len=44, expected_count=2)
        if candidate is None:
            return None
        try:
            checker = TD3CodeChecker("\n".join(candidate))
        except (LengthError, ValueError, IndexError):
            return None

        f = checker.fields()
        return MRZFields(
            nom=f.surname or None,
            prenom=f.name or None,
            date_naissance=self._format_date(f.birth_date),
            numero_document=self._strip_filler(f.document_number),
            nationalite=f.nationality or None,
            date_expiration=self._format_date(f.expiry_date),
            sexe=f.sex or None,
            document_type=DocumentType.PASSEPORT,
            mrz_found=True,
            mrz_raw="\n".join(candidate),
            check_digit_document_valid=bool(checker.document_number_hash),
            check_digit_birth_valid=bool(checker.birth_date_hash),
            check_digit_expiry_valid=bool(checker.expiry_date_hash),
            check_digit_composite_valid=bool(checker.final_hash),
            all_checks_valid=bool(checker.result),
        )

    def _try_td1(self, lines: list[str]) -> MRZFields | None:
        candidate = self._pick_candidate_lines(lines, expected_len=30, expected_count=3)
        if candidate is None:
            return None
        try:
            checker = TD1CodeChecker("\n".join(candidate))
        except (LengthError, ValueError, IndexError):
            return None

        f = checker.fields()
        return MRZFields(
            nom=f.surname or None,
            prenom=f.name or None,
            date_naissance=self._format_date(f.birth_date),
            numero_document=self._strip_filler(f.document_number),
            nationalite=f.nationality or None,
            date_expiration=self._format_date(f.expiry_date),
            sexe=f.sex or None,
            document_type=DocumentType.CARTE_IDENTITE,
            mrz_found=True,
            mrz_raw="\n".join(candidate),
            check_digit_document_valid=bool(checker.document_number_hash),
            check_digit_birth_valid=bool(checker.birth_date_hash),
            check_digit_expiry_valid=bool(checker.expiry_date_hash),
            check_digit_composite_valid=bool(checker.final_hash),
            all_checks_valid=bool(checker.result),
        )

    def _try_td2(self, lines: list[str]) -> MRZFields | None:
        candidate = self._pick_candidate_lines(lines, expected_len=36, expected_count=2)
        if candidate is None:
            return None
        try:
            checker = TD2CodeChecker("\n".join(candidate))
        except (LengthError, ValueError, IndexError):
            return None

        f = checker.fields()
        return MRZFields(
            nom=f.surname or None,
            prenom=f.name or None,
            date_naissance=self._format_date(f.birth_date),
            numero_document=self._strip_filler(f.document_number),
            nationalite=f.nationality or None,
            date_expiration=self._format_date(f.expiry_date),
            sexe=f.sex or None,
            document_type=DocumentType.PERMIS_CONDUIRE,
            mrz_found=True,
            mrz_raw="\n".join(candidate),
            check_digit_document_valid=bool(checker.document_number_hash),
            check_digit_birth_valid=bool(checker.birth_date_hash),
            check_digit_expiry_valid=bool(checker.expiry_date_hash),
            check_digit_composite_valid=bool(checker.final_hash),
            all_checks_valid=bool(checker.result),
        )

    @staticmethod
    def _pick_candidate_lines(lines: list[str], expected_len: int, expected_count: int) -> list[str] | None:
        matching = [ln for ln in lines if abs(len(ln) - expected_len) <= 2]
        if len(matching) < expected_count:
            return None

        normalized = []
        for ln in matching[-expected_count:]:
            if len(ln) < expected_len:
                ln = ln + "<" * (expected_len - len(ln))
            elif len(ln) > expected_len:
                ln = ln[:expected_len]
            normalized.append(ln)
        return normalized

    @staticmethod
    def _strip_filler(value: str) -> str | None:
        cleaned = value.replace("<", "").strip()
        return cleaned or None

    @staticmethod
    def _format_date(yymmdd: str) -> str | None:
        if not yymmdd or len(yymmdd) != 6 or not yymmdd.isdigit():
            return None
        yy, mm, dd = yymmdd[0:2], yymmdd[2:4], yymmdd[4:6]
        year = int(yy)
        century = 2000 if year <= 30 else 1900
        return f"{century + year:04d}-{mm}-{dd}"


mrz_parser = MRZParser()
