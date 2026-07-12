from functools import lru_cache

from pydantic_settings import BaseSettings


class Settings(BaseSettings):
    ollama_base_url: str = "http://ollama:11434"
    ollama_model: str = "minicpm-v"
    ollama_timeout_seconds: int = 120
    embedding_model_name: str = "all-MiniLM-L6-v2"
    similarity_threshold: float = 0.80
    weight_mrz_validity: float = 0.35
    weight_ocr_mrz_consistency: float = 0.30
    weight_embedding_similarity: float = 0.20
    weight_image_quality: float = 0.15
    weight_mrz_validity_inscription: float = 0.30
    weight_ocr_mrz_consistency_inscription: float = 0.25
    weight_embedding_similarity_inscription: float = 0.15
    weight_image_quality_inscription: float = 0.15
    weight_attestation_consistency: float = 0.15
    risk_threshold_low: float = 0.25
    risk_threshold_medium: float = 0.55
    max_image_dimension: int = 2000

    class Config:
        env_prefix = "AI_"
        env_file = ".env"


@lru_cache
def get_settings() -> Settings:
    return Settings()


settings = get_settings()
