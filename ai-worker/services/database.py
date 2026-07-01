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


def update_ticket(
    ticket_id:       int,
    status:          str,
    ai_data:         dict | None,
    gravity:         dict | None,
    errors:          list,
    visual_analyses: list,
):
    conn   = mysql.connector.connect(**DB_CONFIG)
    cursor = conn.cursor()
    try:
        if ai_data and gravity:
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
                ai_data.get("type_nc"),
                ai_data.get("cause"),
                ai_data.get("action_generale"),
                ai_data.get("service_impacte"),
                ai_data.get("resume"),
                ai_data.get("confiance"),
                gravity["score"],
                gravity["label"],
                json.dumps(gravity["detail"],        ensure_ascii=False),
                json.dumps(errors,                   ensure_ascii=False),
                json.dumps(visual_analyses,          ensure_ascii=False),
                ticket_id,
            ))
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
                json.dumps(errors,          ensure_ascii=False),
                json.dumps(visual_analyses, ensure_ascii=False),
                ticket_id,
            ))
        conn.commit()
        logger.info(f"Ticket {ticket_id} mis à jour → {status}")
    finally:
        cursor.close()
        conn.close()