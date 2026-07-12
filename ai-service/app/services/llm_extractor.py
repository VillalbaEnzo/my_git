from __future__ import annotations

import base64
import json
import logging
import re

import requests

from app.core.config import settings
from app.models.schemas import DocumentType, ExtractedFields

logger = logging.getLogger(__name__)

_VISIBLE_FIELDS_PROMPT = """Tu es un système d'extraction de données d'identité.
Regarde attentivement ce document officiel (carte d'identité, passeport ou permis de conduire).

Attention au champ prénom : les cartes d'identité françaises listent souvent PLUSIEURS
prénoms sur la même ligne, séparés par des virgules (ex: "Prénom(s) / Given names : Enzo,
César, Paul-Jean"). Tu dois retranscrire TOUS les prénoms affichés, dans le même ordre,
séparés par des virgules. Ne retiens jamais un seul prénom du milieu ou de la fin de la
liste en ignorant les autres : le premier prénom listé est le prénom usuel et doit toujours
être inclus en premier.

Réponds UNIQUEMENT avec un objet JSON valide, sans texte autour, avec exactement ces clés :
{
  "nom": "<nom de famille tel qu'écrit sur le document, ou null>",
  "prenom": "<TOUS les prénoms tels qu'écrits sur le document, séparés par des virgules si plusieurs, ou null>",
  "date_naissance": "<date de naissance au format JJ/MM/AAAA, ou null>",
  "numero_document": "<numéro du document, ou null>",
  "document_type": "<CARTE_IDENTITE, PASSEPORT, PERMIS_CONDUIRE ou INCONNU>"
}
Ne devine pas une valeur que tu ne vois pas clairement : mets null dans ce cas.
"""

_MRZ_TRANSCRIPTION_PROMPT = """Tu es un système de transcription optique de caractères (OCR) pur.
Ce document possède une zone MRZ (bande de texte avec des lettres majuscules, chiffres et
le caractère '<') généralement située en bas du document.

Transcris EXACTEMENT, ligne par ligne, le contenu brut de cette zone MRZ, caractère pour
caractère, sans corriger l'orthographe, sans interpréter, sans ajouter de commentaire.
Si tu ne vois aucune zone MRZ, réponds uniquement avec le mot: AUCUNE

Réponds uniquement avec les lignes brutes de la MRZ (une ligne par ligne réelle du document),
rien d'autre.
"""


class LLMExtractor:
    def __init__(self) -> None:
        self.base_url = settings.ollama_base_url.rstrip("/")
        self.model = settings.ollama_model
        self.timeout = settings.ollama_timeout_seconds

    def is_reachable(self) -> bool:
        try:
            resp = requests.get(f"{self.base_url}/api/tags", timeout=5)
            return resp.status_code == 200
        except requests.RequestException:
            return False

    def ensure_model_pulled(self) -> None:
        try:
            resp = requests.get(f"{self.base_url}/api/tags", timeout=10)
            resp.raise_for_status()
            models = [m.get("name", "") for m in resp.json().get("models", [])]
            already_present = any(m.split(":")[0] == self.model.split(":")[0] for m in models)
            if already_present:
                logger.info("Modèle Ollama '%s' déjà présent, pas de pull nécessaire", self.model)
                return
        except requests.RequestException as exc:
            logger.warning("Impossible de lister les modèles Ollama avant pull : %s", exc)

        logger.info("Téléchargement du modèle Ollama '%s'... (peut prendre plusieurs minutes)", self.model)
        try:
            with requests.post(
                f"{self.base_url}/api/pull",
                json={"name": self.model, "stream": True},
                stream=True,
                timeout=None,
            ) as resp:
                resp.raise_for_status()
                for line in resp.iter_lines():
                    if not line:
                        continue
                    try:
                        status = json.loads(line).get("status", "")
                    except json.JSONDecodeError:
                        continue
                    if status:
                        logger.info("[ollama pull %s] %s", self.model, status)
            logger.info("Modèle Ollama '%s' prêt", self.model)
        except requests.RequestException as exc:
            logger.error("Échec du téléchargement du modèle Ollama '%s' : %s", self.model, exc)

    def extract_visible_fields(self, image_bytes: bytes) -> ExtractedFields:
        raw_response = self._call_ollama(image_bytes, _VISIBLE_FIELDS_PROMPT)
        return self._parse_visible_fields(raw_response)

    def extract_visible_fields_from_text(self, document_text: str) -> ExtractedFields:
        prompt = (
            _VISIBLE_FIELDS_PROMPT
            + "\n\nVoici le texte brut du document (déjà extrait) :\n---\n"
            + document_text
            + "\n---"
        )
        raw_response = self._call_ollama_text(prompt)
        return self._parse_visible_fields(raw_response)

    def extract_mrz_raw_text(self, image_bytes: bytes) -> str | None:
        raw_response = self._call_ollama(image_bytes, _MRZ_TRANSCRIPTION_PROMPT)
        cleaned = raw_response.strip()
        if not cleaned or cleaned.upper().startswith("AUCUNE"):
            return None
        return cleaned

    def _call_ollama_text(self, prompt: str) -> str:
        payload = {
            "model": self.model,
            "prompt": prompt,
            "stream": False,
            "options": {"temperature": 0.0},
        }
        try:
            resp = requests.post(
                f"{self.base_url}/api/generate", json=payload, timeout=self.timeout
            )
            resp.raise_for_status()
            return resp.json().get("response", "")
        except requests.RequestException as exc:
            logger.error("Erreur d'appel Ollama en mode texte (%s): %s", self.model, exc)
            return ""

    def _call_ollama(self, image_bytes: bytes, prompt: str) -> str:
        image_b64 = base64.b64encode(image_bytes).decode("utf-8")
        payload = {
            "model": self.model,
            "prompt": prompt,
            "images": [image_b64],
            "stream": False,
            "options": {"temperature": 0.0},
        }
        try:
            resp = requests.post(
                f"{self.base_url}/api/generate", json=payload, timeout=self.timeout
            )
            resp.raise_for_status()
            data = resp.json()
            return data.get("response", "")
        except requests.RequestException as exc:
            logger.error("Erreur d'appel Ollama (%s): %s", self.model, exc)
            return ""

    @staticmethod
    def _parse_visible_fields(raw_response: str) -> ExtractedFields:
        json_str = LLMExtractor._extract_json_block(raw_response)
        if json_str is None:
            return ExtractedFields()

        try:
            data = json.loads(json_str)
        except json.JSONDecodeError:
            logger.warning("Réponse LLM non-JSON reçue, extraction vide retournée")
            return ExtractedFields()

        doc_type_raw = str(data.get("document_type") or "INCONNU").upper()
        try:
            doc_type = DocumentType(doc_type_raw)
        except ValueError:
            doc_type = DocumentType.INCONNU

        return ExtractedFields(
            nom=data.get("nom"),
            prenom=LLMExtractor._normalize_prenom(data.get("prenom")),
            date_naissance=data.get("date_naissance"),
            numero_document=data.get("numero_document"),
            document_type=doc_type,
        )

    @staticmethod
    def _normalize_prenom(prenom: object) -> str | None:
        if not prenom:
            return None
        if isinstance(prenom, list):
            parts = [str(p).strip() for p in prenom if str(p).strip()]
        else:
            parts = [p.strip() for p in str(prenom).split(",") if p.strip()]
        return ", ".join(parts) if parts else None

    @staticmethod
    def _extract_json_block(text: str) -> str | None:
        match = re.search(r"\{.*\}", text, re.DOTALL)
        return match.group(0) if match else None


llm_extractor = LLMExtractor()
