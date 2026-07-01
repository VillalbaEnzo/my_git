import json
import logging
import difflib
from gravity import compute_gravity
from services.ollama   import classify_text
from services.vision   import process_images
from services.database import update_ticket

logger = logging.getLogger(__name__)

VALID_TYPES_NC = ["NCE", "NCF", "NCI", "Non recevable", "SAV"]

VALID_CAUSES = ["Défaut de fabrication", "Défaut de montage sur site", "Demande d'information", "Erreur de conception", "Info client incorrecte", "Manquement en production", "Manquement en visserie", "Manquement sur site", "Mauvaise communication interservices", "Non respect des délais", "Non-conformités d'audit", "Notice incorrecte", "Pièce endommagée", "Plan incorrect", "Problème de devis", "Rouille"]

VALID_ACTIONS = ["Correction sur le site", "Devis", "Mise à jour conception", "Mise à jour documents", "Réclamation au fournisseur", "Refabrication", "Renvoi pièces"]

VALID_SERVICES = ["Achats / Appro", "ADV", "BE Com", "BE Methode", "Commercial", "Expédition / Assemblage Jeux", "Expédition / Assemblage Sport", "Fournisseur", "Peinture", "Poseur", "Serrurerie", "Transport", "Transalp"]

CONFIDENCE_THRESHOLD = 0.65
MAX_ERRORS_ALLOWED   = 2

def parse_response(raw: str) -> dict:
    raw = raw.strip()
    if raw.startswith("```"):
        parts = raw.split("```")
        raw = parts[1]
        if raw.startswith("json"):
            raw = raw[4:]
    return json.loads(raw.strip())


def fuzzy_fix(data: dict) -> dict:
    """Corrige les valeurs hors-liste par correspondance partielle (cutoff 0.5)."""
    mapping = {
        "type_nc":         VALID_TYPES_NC,
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
    if data.get("type_nc")         not in VALID_TYPES_NC:  errors.append(f"type_nc invalide: {data.get('type_nc')}")
    if data.get("cause")           not in VALID_CAUSES:    errors.append(f"cause invalide: {data.get('cause')}")
    if data.get("action_generale") not in VALID_ACTIONS:   errors.append(f"action_generale invalide: {data.get('action_generale')}")
    if data.get("service_impacte") not in VALID_SERVICES:  errors.append(f"service_impacte invalide: {data.get('service_impacte')}")
    for key in ("securite", "client", "cout", "impact_poseur"):
        if data.get("gravite_niveaux", {}).get(key) not in (0, 1, 2, 3):
            errors.append(f"gravite_niveaux.{key} invalide")
    return errors

def compute_hybrid_gravity(ai_data: dict, visual_analyses: list) -> dict:
    niveaux = ai_data.get("gravite_niveaux", {})

    securite_niveau = niveaux.get("securite", 0)

    security_flagged = any(
        a.get("indices_gravite", {}).get("securite_visible", False)
        for a in visual_analyses if "error" not in a
    )
    if security_flagged and securite_niveau < 2:
        logger.info("Gravité sécurité remontée à 2 (détection visuelle)")
        securite_niveau = 2

    return compute_gravity(
        securite=       securite_niveau,
        client=         niveaux.get("client",        0),
        cout=           niveaux.get("cout",          0),
        impact_poseur=  niveaux.get("impact_poseur", 0),
    )

async def process_ticket(ticket_id: int, description: str, image_paths: list[str]):
    logger.info(f"[Ticket {ticket_id}] Début analyse (images: {len(image_paths)})")

    errors          = []
    ai_data         = None
    gravity         = None
    visual_analyses = []

    try:
        visual_context, visual_analyses = await process_images(
            image_paths, ticket_id, description
        )
        if visual_context:
            logger.info(f"[Ticket {ticket_id}] Contexte visuel injecté")

        raw     = await classify_text(description, visual_context)
        logger.info(f"[Ticket {ticket_id}] LLM brut : {raw}")

        ai_data = parse_response(raw)
        ai_data = fuzzy_fix(ai_data)
        errors  = validate(ai_data)

        confiance = float(ai_data.get("confiance", 0.0))
        nb_errors = len(errors)

        if nb_errors <= MAX_ERRORS_ALLOWED:
            gravity = compute_hybrid_gravity(ai_data, visual_analyses)
            logger.info(
                f"[Ticket {ticket_id}] Gravité : "
                f"{gravity['label']} ({gravity['score']}/24)"
            )

        if confiance < CONFIDENCE_THRESHOLD or nb_errors > MAX_ERRORS_ALLOWED:
            status = "manual_completion_required"
            logger.warning(
                f"[Ticket {ticket_id}] → manuel "
                f"(confiance={confiance}, erreurs={nb_errors})"
            )
        else:
            status = "ai_completed"

    except Exception as e:
        logger.error(f"[Ticket {ticket_id}] Erreur critique : {e}")
        status = "manual_completion_required"
        errors.append(str(e))

    update_ticket(ticket_id, status, ai_data, gravity, errors, visual_analyses)
    logger.info(f"[Ticket {ticket_id}] Terminé → {status}")