import json
import logging
import difflib
from datetime import date

from gravity                  import compute_gravity
from services.ollama          import classify_text
from services.vision          import process_images
from services.database        import update_ticket
from services.product_matcher import resolve_nc_type

from config import (
    VALID_CAUSES,
    VALID_ACTIONS,
    VALID_SERVICES,
    CONFIDENCE_THRESHOLD,
    MAX_ERRORS_ALLOWED,
)

logger = logging.getLogger(__name__)

def parse_response(raw: str) -> dict:
    raw = raw.strip()
    if raw.startswith("```"):
        parts = raw.split("```")
        raw   = parts[1]
        if raw.startswith("json"):
            raw = raw[4:]
    return json.loads(raw.strip())


def fuzzy_fix(data: dict) -> dict:
    mapping = {
        "cause":           VALID_CAUSES,
        "action_generale": VALID_ACTIONS,
        "service_impacte": VALID_SERVICES,
    }
    for field, valid_list in mapping.items():
        val = data.get(field, "")
        if val not in valid_list:
            matches = difflib.get_close_matches(val, valid_list, n=1, cutoff=0.5)
            if matches:
                logger.info(f"fuzzy_fix {field} : '{val}' → '{matches[0]}'")
                data[field] = matches[0]
    return data


def validate(data: dict) -> list[str]:
    errors = []
    if data.get("cause")           not in VALID_CAUSES:   errors.append(f"cause invalide: {data.get('cause')}")
    if data.get("action_generale") not in VALID_ACTIONS:  errors.append(f"action invalide: {data.get('action_generale')}")
    if data.get("service_impacte") not in VALID_SERVICES: errors.append(f"service invalide: {data.get('service_impacte')}")
    for key in ("securite", "client", "cout", "impact_poseur"):
        if data.get("gravite_niveaux", {}).get(key) not in (0, 1, 2, 3):
            errors.append(f"gravite_niveaux.{key} invalide")
    return errors

def compute_hybrid_gravity(ai_data: dict, visual_analyses: list) -> dict:
    niveaux         = ai_data.get("gravite_niveaux", {})
    securite_niveau = niveaux.get("securite", 0)

    security_flagged = any(
        a.get("indices_gravite", {}).get("securite_visible", False)
        for a in visual_analyses if "error" not in a
    )
    if security_flagged and securite_niveau < 2:
        logger.info("Gravité sécurité remontée à 2 (détection visuelle)")
        securite_niveau = 2

    return compute_gravity(
        securite=      securite_niveau,
        client=        niveaux.get("client",        0),
        cout=          niveaux.get("cout",          0),
        impact_poseur= niveaux.get("impact_poseur", 0),
    )

async def process_ticket(
    ticket_id:   int,
    description: str,
    profil:      str,
    reference:   str,
    installation_pose:   date | None,
    image_paths: list[str],
):
    logger.info(
        f"[Ticket {ticket_id}] Début analyse | "
        f"profil={profil} | ref='{reference}' | images={len(image_paths)}"
    )

    errors          = []
    ai_data         = None
    gravity         = None
    visual_analyses = []
    nc_resolution   = {}

    try:
        nc_resolution = await resolve_nc_type(description, profil, reference, installation_pose)
        nc_type_final = nc_resolution["nc_type"]

        visual_context, visual_analyses = await process_images(
            image_paths, ticket_id, description
        )

        raw     = await classify_text(description, visual_context)
        ai_data = parse_response(raw)
        ai_data = fuzzy_fix(ai_data)

        if nc_type_final:
            logger.info(f"[Ticket {ticket_id}] TYPE NC Excel → '{nc_type_final}' (écrase IA)")
            ai_data["type_nc"] = nc_type_final
        else:
            logger.info(f"[Ticket {ticket_id}] Pas de match Excel → TYPE NC IA : '{ai_data.get('type_nc')}'")

        errors = validate(ai_data)

        text_confidence = float(ai_data.get("confidence", 0.8))
        if text_confidence >= 1.0:
            text_confidence = 0.92

        vision_confidence = 0.5
        if visual_analyses:
            vision_scores = [
                v.get("analysis_confidence", 0.5)
                for v in visual_analyses
                if "error" not in v
            ]
            if vision_scores:
                vision_confidence = sum(vision_scores) / len(vision_scores)

        overall_confidence = (0.80 * text_confidence) + (0.20 * vision_confidence)

        ai_data["confidence"] = round(overall_confidence, 3)
        confidence = ai_data["confidence"]
        nb_errors = len(errors)

        if nb_errors <= MAX_ERRORS_ALLOWED:
            gravity = compute_hybrid_gravity(ai_data, visual_analyses)
            logger.info(f"[Ticket {ticket_id}] Gravité : {gravity['label']} ({gravity['score']}/24)")

        status = (
            "manual_completion_required"
            if confidence < CONFIDENCE_THRESHOLD or nb_errors > MAX_ERRORS_ALLOWED
            else "ai_completed"
        )

    except Exception as e:
        logger.error(f"[Ticket {ticket_id}] Erreur critique : {e}")
        status = "manual_completion_required"
        errors.append(str(e))

    update_ticket(ticket_id, status, ai_data, gravity, errors, visual_analyses)
    logger.info(f"[Ticket {ticket_id}] Terminé → {status}")

