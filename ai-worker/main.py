import logging
from fastapi import FastAPI, BackgroundTasks, HTTPException
from pydantic import BaseModel
from typing import Optional

from gravity             import compute_gravity
from services.classifier import process_ticket
from services.ollama     import health_check

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

app = FastAPI(title="Transalp AI Worker")

class AnalyzeRequest(BaseModel):
    ticket_id:   int
    description: str
    image_paths: Optional[list[str]] = []


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


@app.post("/analyze", status_code=202)
async def analyze(request: AnalyzeRequest, background_tasks: BackgroundTasks):
    logger.info(
        f"Analyse reçue pour ticket #{request.ticket_id} "
        f"| images: {request.image_paths}"
    )
    background_tasks.add_task(
        process_ticket,
        request.ticket_id,
        request.description,
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