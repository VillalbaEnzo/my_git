from __future__ import annotations

import uuid
from dataclasses import dataclass, field
from datetime import datetime, timedelta
from typing import Generic, Optional, TypeVar

from app.models.schemas import JobStatus

T = TypeVar("T")

_JOB_TTL = timedelta(hours=2)


@dataclass
class Job(Generic[T]):
    status: JobStatus = JobStatus.PENDING
    result: Optional[T] = None
    error: Optional[str] = None
    created_at: datetime = field(default_factory=datetime.utcnow)


class JobStore(Generic[T]):
    def __init__(self) -> None:
        self._jobs: dict[str, Job[T]] = {}

    def create(self) -> str:
        self._cleanup_expired()
        job_id = str(uuid.uuid4())
        self._jobs[job_id] = Job()
        return job_id

    def get(self, job_id: str) -> Optional[Job[T]]:
        return self._jobs.get(job_id)

    def mark_done(self, job_id: str, result: T) -> None:
        job = self._jobs.get(job_id)
        if job is not None:
            job.status = JobStatus.DONE
            job.result = result

    def mark_error(self, job_id: str, error: str) -> None:
        job = self._jobs.get(job_id)
        if job is not None:
            job.status = JobStatus.ERROR
            job.error = error

    def _cleanup_expired(self) -> None:
        now = datetime.utcnow()
        expired = [job_id for job_id, job in self._jobs.items() if now - job.created_at > _JOB_TTL]
        for job_id in expired:
            del self._jobs[job_id]
