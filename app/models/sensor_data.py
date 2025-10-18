from sqlalchemy import Column, Integer, Float, DateTime, func
from app.core.database import Base

class SensorData(Base):
    __tablename__ = "sensor_data"

    id = Column(Integer, primary_key=True, index=True)
    humedad_aire = Column(Float, nullable=False)
    humedad_suelo = Column(Float, nullable=False)
    temperatura = Column(Float, nullable=False)
    fecha = Column(DateTime(timezone=True), server_default=func.now())
