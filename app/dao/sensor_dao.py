from sqlalchemy.orm import Session
from app.models.sensor_data import SensorData
from app.schemas.sensor_schema import SensorDataCreate

class SensorDAO:
    @staticmethod
    def create_sensor_data(db: Session, data: SensorDataCreate):
        new_data = SensorData(**data.dict())
        db.add(new_data)
        db.commit()
        db.refresh(new_data)
        return new_data

    @staticmethod
    def get_all(db: Session):
        return db.query(SensorData).all()
