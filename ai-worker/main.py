import logging
from datetime import date
from typing import Optional
from fastapi import FastAPI, BackgroundTasks, HTTPException
from pydantic import BaseModel

from gravity             import compute_gravity
from services.classifier import process_ticket
from services.ollama     import health_check
from services.product_matcher import reload_catalogue

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

app = FastAPI(title="Transalp AI Worker")


class AnalyzeRequest(BaseModel):
    ticket_id:   int
    description: str
    profil:      str                  = "client"    # 'client' | 'employe'
    reference:   str                  = ""          # ref produit (employé seulement)
    installation_pose:   Optional[date]       = None
    image_paths: Optional[list[str]]  = []


class GravityRequest(BaseModel):
    securite:      int
    client:        int
    cout:          int
    impact_poseur: int


@app.get("/")
def root():
    return {"status": "ok", "service": "transalp-ai-worker"}


@app.get("/health")
async def health():
    return await health_check()


@app.post("/catalogue/reload")
def catalogue_reload():
    """Force le rechargement du catalogue Excel sans redémarrer le worker."""
    df = reload_catalogue()
    return {"status": "ok", "lignes": len(df)}


@app.post("/analyze", status_code=202)
async def analyze(request: AnalyzeRequest, background_tasks: BackgroundTasks):
    logger.info(
        f"Analyse → ticket #{request.ticket_id} | "
        f"profil={request.profil} | ref='{request.reference}'"
    )
    background_tasks.add_task(
        process_ticket,
        request.ticket_id,
        request.description,
        request.profil,
        request.reference,
        request.installation_pose,
        request.image_paths or [],
    )
    return {"message": "Analyse en cours", "ticket_id": request.ticket_id}


@app.post("/gravity/compute")
def gravity_compute(data: GravityRequest):
    try:
        return compute_gravity(
            securite=      data.securite,
            client=        data.client,
            cout=          data.cout,
            impact_poseur= data.impact_poseur,
        )
    except ValueError as e:
        raise HTTPException(status_code=422, detail=str(e))