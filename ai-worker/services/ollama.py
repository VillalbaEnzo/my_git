import os
import json
import logging
import httpx
from pathlib import Path

logger = logging.getLogger(__name__)

OLLAMA_URL          = os.getenv("OLLAMA_URL",          "http://ollama:11434")
OLLAMA_MODEL        = os.getenv("OLLAMA_MODEL",        "mistral:7b-instruct")
OLLAMA_VISION_MODEL = os.getenv("OLLAMA_VISION_MODEL", "minicpm-v:latest")

PROMPTS_DIR = Path(__file__).parent.parent / "prompts"


def _load_prompt(filename: str) -> str:
    return (PROMPTS_DIR / filename).read_text(encoding="utf-8")


def _strip_markdown_json(raw: str) -> dict:
    raw = raw.strip()
    if raw.startswith("```"):
        parts = raw.split("```")
        raw = parts[1]
        if raw.startswith("json"):
            raw = raw[4:]
    return json.loads(raw.strip())


async def classify_text(description: str, visual_context: str = "") -> str:
    """
    Appelle Mistral pour classifier la NC.
    Retourne la réponse brute (str JSON).
    """
    template = _load_prompt("prompt_classify.txt")

    enriched = description
    if visual_context:
        enriched += f"\n\n--- Analyse visuelle des pièces jointes ---\n{visual_context}"

    prompt = template + enriched

    async with httpx.AsyncClient(timeout=180.0) as client:
        response = await client.post(
            f"{OLLAMA_URL}/api/generate",
            json={
                "model":  OLLAMA_MODEL,
                "prompt": prompt,
                "stream": False,
                "format": "json",
                "options": {
                    "temperature": 0.1,
                    "top_p":       0.9,
                    "num_predict": 800,
                },
            },
        )
        response.raise_for_status()
        return response.json()["response"]


async def analyze_image(image_b64: str, description: str = "") -> dict:
    """
    Appelle LLaVA pour analyser une image dans le contexte de la NC.
    Retourne un dict parsé.
    """
    template     = _load_prompt("prompt_vision.txt")
    vision_prompt = template.replace("{DESCRIPTION}", description or "Non précisée")

    async with httpx.AsyncClient(timeout=180.0) as client:
        response = await client.post(
            f"{OLLAMA_URL}/api/generate",
            json={
                "model":  OLLAMA_VISION_MODEL,
                "prompt": vision_prompt,
                "images": [image_b64],
                "stream": False,
                "format": "json",
                "options": {
                    "temperature": 0.1,
                    "num_predict": 400,
                },
            },
        )
        response.raise_for_status()
        raw = response.json()["response"]
        try:
            return _strip_markdown_json(raw)
        except Exception as e:
            logger.warning(f"Vision JSON parse error: {e} | raw: {raw}")
            return {"description_visuelle": raw, "confiance_analyse": 0.5}


async def health_check() -> dict:
    try:
        async with httpx.AsyncClient(timeout=5.0) as client:
            r        = await client.get(OLLAMA_URL)
            tags_r   = await client.get(f"{OLLAMA_URL}/api/tags")
            models   = [m["name"] for m in tags_r.json().get("models", [])]
            return {"status": "ok", "ollama": r.text.strip(), "models": models}
    except Exception as e:
        return {"status": "error", "detail": str(e)}