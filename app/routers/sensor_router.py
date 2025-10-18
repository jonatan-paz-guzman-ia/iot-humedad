from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session
from app.core.database import get_db
from app.schemas.sensor_schema import SensorDataCreate, SensorDataResponse
from app.services.sensor_service import SensorService

router = APIRouter(prefix="/sensor", tags=["Sensor"])

@router.post("/", response_model=SensorDataResponse)
def crear_dato_sensor(data: SensorDataCreate, db: Session = Depends(get_db)):
    return SensorService.registrar_datos(db, data)
