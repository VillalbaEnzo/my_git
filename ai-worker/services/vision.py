import base64
import logging
from pathlib import Path
from services.ollama import analyze_image

logger    = logging.getLogger(__name__)
UPLOADS   = Path("/app/uploads")


def _to_base64(path: Path) -> str:
    return base64.b64encode(path.read_bytes()).decode("utf-8")


async def process_images(
    image_paths: list[str],
    ticket_id:   int,
    description: str = "",
) -> tuple[str, list[dict]]:
    """
    Analyse toutes les images du ticket.
    Retourne (contexte_textuel_pour_mistral, liste_analyses_brutes).
    """
    if not image_paths:
        return "", []

    analyses = []
    for rel_path in image_paths:
        full_path = UPLOADS / rel_path
        if not full_path.exists():
            logger.warning(f"[Ticket {ticket_id}] Image introuvable : {full_path}")
            continue

        logger.info(f"[Ticket {ticket_id}] Analyse visuelle : {rel_path}")
        try:
            b64    = _to_base64(full_path)
            result = await analyze_image(b64, description)
            analyses.append({"file": rel_path, **result})
            logger.info(
                f"[Ticket {ticket_id}] Vision OK : "
                f"{result.get('description_visuelle', '')}"
            )
        except Exception as e:
            logger.error(f"[Ticket {ticket_id}] Erreur vision sur {rel_path}: {e}")
            analyses.append({"file": rel_path, "error": str(e)})

    return _build_context(analyses), analyses


def _safe_str(val) -> str:
    """Convertit n'importe quelle valeur en string, dict ou liste inclus."""
    if isinstance(val, dict):
        for key in ("description", "text", "label", "description_visuelle"):
            if key in val:
                return str(val[key])
        return str(list(val.values())[0]) if val else ""
    if isinstance(val, list):
        return ", ".join(_safe_str(x) for x in val)
    return str(val) if val is not None else ""


def _flatten_list(items: list) -> list[str]:
    """Aplatit une liste mixte (strings + dicts) en liste de strings."""
    result = []
    for item in items:
        s = _safe_str(item).strip()
        if s:
            result.append(s)
    return result


def _build_context(analyses: list[dict]) -> str:
    lines = []
    for i, a in enumerate(analyses, 1):
        if "error" in a:
            continue

        lines.append(f"Image {i} ({a['file']}) : {_safe_str(a.get('description_visuelle', 'N/A'))}")

        confirmes = _flatten_list(a.get("elements_confirmes", []))
        omis      = _flatten_list(a.get("elements_omis", []))
        localisa  = _safe_str(a.get("localisation_defaut", ""))

        if confirmes:
            lines.append(f"  → Confirme : {', '.join(confirmes)}")
        if omis:
            lines.append(f"  → Éléments omis : {', '.join(omis)}")
        if localisa:
            lines.append(f"  → Localisation : {localisa}")
    return "\n".join(lines)