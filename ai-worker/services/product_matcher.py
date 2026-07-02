"""
Matching catalogue produits via pandas (Excel direct, pas de MySQL).

Flux employé  : ref fournie → cherche col A puis B → famille → NC type
Flux client   : pas de ref  → LLM extrait mot-clé → cherche désignation → famille → NC type
Fallback      : si rien trouvé → NC type laissé à l'IA
"""
import json
import logging
from datetime import date, timedelta
from pathlib import Path

import httpx
import pandas as pd

from config import (
    CATALOGUE_EXCEL_PATH,
    EXCEL_COL_REFERENCE_A,
    EXCEL_COL_REFERENCE_B,
    EXCEL_COL_DESIGNATION,
    EXCEL_COL_FAMILLE_ACHAT,
    FAMILLE_TO_NC_TYPE,
    SEUIL_MOIS_SAV,
)

import os
OLLAMA_URL   = os.getenv("OLLAMA_URL",   "http://ollama:11434")
OLLAMA_MODEL = os.getenv("OLLAMA_MODEL", "mistral:7b-instruct")

logger = logging.getLogger(__name__)
    

_catalogue_df: pd.DataFrame | None = None

def load_catalogue() -> pd.DataFrame:
    global _catalogue_df
    if _catalogue_df is not None:
        return _catalogue_df

    path = Path(CATALOGUE_EXCEL_PATH)
    if not path.exists():
        logger.warning(f"Catalogue introuvable : {path}. Matching désactivé.")
        _catalogue_df = pd.DataFrame()
        return _catalogue_df

    try:
        df = pd.read_excel(path, engine="openpyxl", header=0, dtype=str)
        df = df.fillna("")
        logger.info(f"Catalogue chargé : {len(df)} lignes, {len(df.columns)} colonnes")
        _catalogue_df = df
    except Exception as e:
        logger.error(f"Erreur chargement catalogue : {e}")
        _catalogue_df = pd.DataFrame()

    return _catalogue_df


def reload_catalogue():
    """Force le rechargement (utile après mise à jour de l'Excel)."""
    global _catalogue_df
    _catalogue_df = None
    return load_catalogue()

def _get_col(df: pd.DataFrame, col_index: int) -> pd.Series | None:
    """Retourne une colonne par index, None si hors bornes."""
    if col_index < len(df.columns):
        return df.iloc[:, col_index]
    return None


def _famille_to_nc(famille: str) -> str | None:
    """Mappe une FAMILLE ACHAT vers un TYPE NC. Insensible à la casse."""
    if not famille:
        return None
    key = famille.strip().upper()
    for k, v in FAMILLE_TO_NC_TYPE.items():
        if k.upper() == key:
            return v
    return None


def _vote_famille(familles: list[str]) -> tuple[str, float]:
    if not familles:
        return "", 0.0

    clean = [f.strip() for f in familles if f.strip()]

    if not clean:
        return "", 0.0

    from collections import Counter
    counter     = Counter(clean)
    best, count = counter.most_common(1)[0]
    return best, round(count / len(clean), 2)


def search_by_reference(reference: str) -> tuple[str, str]:
    """
    Cherche la référence dans la colonne A puis B.
    Retourne (famille_achat, source) ou ("", "").
    """
    df = load_catalogue()
    if df.empty or not reference:
        return "", ""

    ref = reference.strip().upper()

    for col_idx, label in [
        (EXCEL_COL_REFERENCE_A, "col A"),
        (EXCEL_COL_REFERENCE_B, "col B"),
    ]:
        col = _get_col(df, col_idx)
        if col is None:
            continue
        mask = col.str.strip().str.upper() == ref
        hits = df[mask]
        if not hits.empty:
            familles = _get_col(hits, EXCEL_COL_FAMILLE_ACHAT)
            if familles is not None:
                famille, conf = _vote_famille(familles.tolist())
                if famille:
                    logger.info(f"Ref '{reference}' trouvée en {label} → famille '{famille}' ({conf:.0%})")
                    return famille, label

    logger.info(f"Ref '{reference}' introuvable dans le catalogue")
    return "", ""

async def extract_keyword(description: str) -> str:
    prompt = (
        "Tu es un assistant qui extrait le nom du produit principal mentionné "
        "dans une description de non-conformité pour une entreprise de jeux extérieurs.\n"
        "Retourne UNIQUEMENT un objet JSON avec un champ 'keyword' contenant "
        "le nom du produit en 1 à 3 mots, en français, sans article.\n"
        "Exemples : balançoire, toboggan, city stade, sol amortissant, portique.\n"
        "Si aucun produit identifiable, retourne {\"keyword\": \"\"}.\n\n"
        f"Description : {description}"
    )
    try:
        async with httpx.AsyncClient(timeout=60.0) as client:
            r = await client.post(
                f"{OLLAMA_URL}/api/generate",
                json={
                    "model":  OLLAMA_MODEL,
                    "prompt": prompt,
                    "stream": False,
                    "format": "json",
                    "options": {"temperature": 0.0, "num_predict": 50},
                },
            )
            r.raise_for_status()
            kw = json.loads(r.json()["response"]).get("keyword", "").strip()
            logger.info(f"Mot-clé extrait : '{kw}'")
            return kw
    except Exception as e:
        logger.error(f"Erreur extraction mot-clé : {e}")
        return ""

def search_by_keyword(keyword: str, limit: int = 20) -> tuple[str, float]:
    """
    Recherche le mot-clé dans la colonne désignation.
    Retourne (famille_majoritaire, confiance).
    """
    df = load_catalogue()
    if df.empty or not keyword:
        return "", 0.0

    col_design = _get_col(df, EXCEL_COL_DESIGNATION)
    col_fam    = _get_col(df, EXCEL_COL_FAMILLE_ACHAT)
    if col_design is None or col_fam is None:
        return "", 0.0

    mask = col_design.str.upper().str.contains(keyword.upper(), na=False, regex=False)
    hits = df[mask].head(limit)

    if hits.empty:
        logger.info(f"Aucun produit trouvé pour '{keyword}'")
        return "", 0.0

    familles = _get_col(hits, EXCEL_COL_FAMILLE_ACHAT).tolist()
    famille, conf = _vote_famille(familles)
    logger.info(f"Keyword '{keyword}' → {len(hits)} hits → famille '{famille}' ({conf:.0%})")
    return famille, conf

async def resolve_nc_type(
    description: str,
    reference:   str = "",
    installation_pose:   date | None = None,
) -> dict:
    """
    Retourne :
    {
        "nc_type":       str | ""   (vide = laisser l'IA décider),
        "from_excel":    bool,
        "keyword":       str,
        "famille_achat": str,
        "confidence":    float,
        "explication":   str,
    }
    """
    if installation_pose is not None:
        seuil = date.today() - timedelta(days=SEUIL_MOIS_SAV * 30)
        if installation_pose < seuil:
            explication = f"Pose > {SEUIL_MOIS_SAV} mois ({installation_pose}) → type forcé SAV (règle absolue)"
            logger.info(f"resolve_nc_type → {explication}")
            return {
                "nc_type":       "SAV",
                "from_excel":    False,
                "keyword":       "",
                "famille_achat": "",
                "explication":   explication,
            }

    famille   = ""
    keyword   = ""
    from_excel = False
    source    = ""

    if reference:
        famille, source = search_by_reference(reference)
        if famille:
            from_excel = True

    if not famille:
        keyword = await extract_keyword(description)
        if keyword:
            famille, _ = search_by_keyword(keyword)
            if famille:
                from_excel = True

    nc_type = _famille_to_nc(famille) if famille else ""

    if nc_type:
        explication = f"Issu du catalogue Excel ({nc_type})"
    else:
        explication = "Aucune correspondance catalogue → NC type laissé à l'IA"

    logger.info(
        f"resolve_nc_type → ref='{reference}' | "
        f"keyword='{keyword}' | famille='{famille}' | "
        f"nc_type='{nc_type}' | {explication}"
    )

    return {
        "nc_type":       nc_type,
        "from_excel":    from_excel,
        "keyword":       keyword,
        "famille_achat": famille,
        "explication":   explication,
    }