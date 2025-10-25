from fastapi import APIRouter, Depends
from fastapi.responses import HTMLResponse
from sqlalchemy.orm import Session
from app.core.database import get_db
from app.models.sensor_data import SensorData
import plotly.express as px
import pandas as pd

router = APIRouter(prefix="/dashboard", tags=["Dashboard"])

@router.get("/", response_class=HTMLResponse)
def show_dashboard(db: Session = Depends(get_db)):
    # Consultar todos los registros de la base de datos
    data = db.query(SensorData).all()
    if not data:
        return "<h3 style='font-family:sans-serif;'>No hay datos registrados aún 💤</h3>"

    # Convertir los resultados a DataFrame
    df = pd.DataFrame([{
        "fecha": d.fecha,
        "humedad_aire": d.humedad_aire,
        "humedad_suelo": d.humedad_suelo,
        "temperatura": d.temperatura
    } for d in data])

    # Gráfica de líneas de tendencias
    fig = px.line(
        df,
        x="fecha",
        y=["humedad_aire", "humedad_suelo", "temperatura"],
        title="📈 Monitoreo de Sensores IoT (Humedad y Temperatura)",
        labels={"value": "Medición", "fecha": "Fecha", "variable": "Sensor"}
    )

    # Estilos visuales
    fig.update_layout(
        template="plotly_white",
        legend=dict(title="Variables", orientation="h", y=-0.2),
        margin=dict(l=40, r=40, t=80, b=40),
        font=dict(family="Arial", size=14)
    )

    # Convertir a HTML embebido
    graph_html = fig.to_html(full_html=False, include_plotlyjs="cdn")

    # HTML final con auto-refresh cada 30s
    html = f"""
    <html>
    <head>
        <meta http-equiv="refresh" content="10">
        <title>Dashboard IoT 🌦️</title>
    </head>
    <body style="font-family:Arial; margin:40px;">
        <h2>🌿 Dashboard IoT de Humedad y Temperatura</h2>
        <p>Actualiza automáticamente cada 30 segundos</p>
        {graph_html}
    </body>
    </html>
    """
    return HTMLResponse(content=html)
