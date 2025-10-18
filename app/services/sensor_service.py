from sqlalchemy.orm import Session
from app.schemas.sensor_schema import SensorDataCreate
from app.dao.sensor_dao import SensorDAO

class SensorService:
    @staticmethod
    def registrar_datos(db: Session, data: SensorDataCreate):
        # Aquí podrías incluir validaciones adicionales o lógica extra
        return SensorDAO.create_sensor_data(db, data)
