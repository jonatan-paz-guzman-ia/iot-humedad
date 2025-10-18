from fastapi import FastAPI
from app.core.database import Base, engine
from app.routers import sensor_router

Base.metadata.create_all(bind=engine)

app = FastAPI(title="API IoT Limoneros")

app.include_router(sensor_router.router)

@app.get("/")
def root():
    return {"message": "API IoT de Monitoreo de Limoneros 🌱"}
