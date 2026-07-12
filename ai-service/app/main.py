import logging
import threading

from fastapi import FastAPI

from app.api.routes import router as api_router
from app.services.llm_extractor import llm_extractor

logging.basicConfig(level=logging.INFO, format="%(asctime)s [%(name)s] %(message)s")

app = FastAPI(
    title="MADEV Pass - AI Document Verification Service",
    description=(
        "Micro-service d'extraction et de vérification de documents d'identité "
        "(vision LLM via Ollama/MiniCPM-V, validation MRZ ICAO 9303, "
        "prétraitement OpenCV, similarité par embeddings, scoring de risque)."
    ),
    version="1.0.0",
)

app.include_router(api_router, prefix="/api")


@app.on_event("startup")
def _pull_model_in_background() -> None:
    thread = threading.Thread(target=llm_extractor.ensure_model_pulled, daemon=True)
    thread.start()


@app.get("/")
async def root() -> dict[str, str]:
    return {"service": "madevpass-ai-service", "status": "running"}
