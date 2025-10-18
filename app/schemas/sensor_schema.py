from datetime import datetime
from pydantic import BaseModel

class SensorDataCreate(BaseModel):
    humedad_aire: float
    humedad_suelo: float
    temperatura: float

class SensorDataResponse(SensorDataCreate):
    id: int
    fecha: datetime

    class Config:
        orm_mode = True
