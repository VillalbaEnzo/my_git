import os
import json
import logging
import mysql.connector

logger = logging.getLogger(__name__)

DB_CONFIG = {
    "host":      os.getenv("DB_HOST", "mysql"),
    "user":      os.getenv("DB_USER", "transalp"),
    "password":  os.getenv("DB_PASS", "changeme_user"),
    "database":  os.getenv("DB_NAME", "transalp_nc"),
    "charset":   "utf8mb4",
    "collation": "utf8mb4_unicode_ci",
}

def _to_json(val) -> str:
    """Garantit qu'une valeur est une string JSON valide avant insertion MySQL."""
    if val is None:
        return '[]'
    if isinstance(val, str):
        return val
    try:
        return json.dumps(val, ensure_ascii=False)
    except Exception:
        return '[]'

def _safe_value(val):
    """Convertit les listes ou dicts inattendus de l'IA en chaîne de caractères."""
    if isinstance(val, (list, dict)):
        return json.dumps(val, ensure_ascii=False)
    return val

def update_ticket(
    ticket_id:       int,
    status:          str,
    ai_data:         dict | None,
    gravity:         dict | None,
    errors:          list,
    visual_analyses: list,
):
    try:
        conn   = mysql.connector.connect(**DB_CONFIG)
        cursor = conn.cursor()
    except Exception as e:
        logger.error(f"Impossible de se connecter à la DB pour le ticket {ticket_id}: {e}")
        return

    try:
        if ai_data and gravity:
            try:
                cursor.execute("""
                    UPDATE tickets SET
                        `status`              = %s,
                        `ai_type_nc`          = %s,
                        `ai_cause`            = %s,
                        `ai_action_generale`  = %s,
                        `ai_service_impacte`  = %s,
                        `ai_resume`           = %s,
                        `ai_confiance`        = %s,
                        `gravity_score`       = %s,
                        `gravity_label`       = %s,
                        `gravity_detail`      = %s,
                        `ai_errors`           = %s,
                        `ai_visual_analyses`  = %s,
                        `updated_at`          = NOW()
                    WHERE id = %s
                """, (
                    status,
                    _safe_value(ai_data.get("type_nc")),
                    _safe_value(ai_data.get("cause")),
                    _safe_value(ai_data.get("action_generale")),
                    _safe_value(ai_data.get("service_impacte")),
                    _safe_value(ai_data.get("resume")),
                    ai_data.get("confiance"),
                    gravity["score"],
                    gravity["label"],
                    json.dumps(gravity["detail"], ensure_ascii=False),
                    _to_json(errors),
                    _to_json(visual_analyses),
                    ticket_id,
                ))
                conn.commit()
                logger.info(f"Ticket {ticket_id} mis à jour → {status}")
            except Exception as db_err:
                logger.error(f"Erreur SQL avec les données IA pour le ticket {ticket_id}: {db_err}")
                errors.append(f"DB Error: {db_err}")
                cursor.execute("""
                    UPDATE tickets SET
                        `status`             = %s,
                        `ai_errors`          = %s,
                        `updated_at`         = NOW()
                    WHERE id = %s
                """, (
                    "manual_completion_required",
                    _to_json(errors),
                    ticket_id,
                ))
                conn.commit()
                logger.warning(f"Ticket {ticket_id} sauvé via FALLBACK → manual_completion_required")

        else:
            cursor.execute("""
                UPDATE tickets SET
                    `status`             = %s,
                    `ai_errors`          = %s,
                    `ai_visual_analyses` = %s,
                    `updated_at`         = NOW()
                WHERE id = %s
            """, (
                status,
                _to_json(errors),
                _to_json(visual_analyses),
                ticket_id,
            ))
            conn.commit()
            logger.info(f"Ticket {ticket_id} mis à jour → {status}")

    except Exception as fatal_err:
        logger.error(f"Erreur fatale lors de la mise à jour du ticket {ticket_id}: {fatal_err}")
    finally:
        if 'cursor' in locals() and cursor is not None:
            cursor.close()
        if 'conn' in locals() and conn.is_connected():
            conn.close()