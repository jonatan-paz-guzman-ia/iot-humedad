# 🌦️ API IoT de Humedad y Temperatura

Este proyecto implementa una **API RESTful con FastAPI** para registrar y consultar datos provenientes de sensores IoT (como **DHT11** o sensores de humedad de suelo).  
Los datos — humedad del aire, humedad del suelo y temperatura — se almacenan en una base de datos **MySQL**, siguiendo una arquitectura modular y desacoplada.

---

## 🧱 Arquitectura del Proyecto

El proyecto sigue un diseño **modular y desacoplado**, inspirado en la **arquitectura hexagonal (ports & adapters)**.

```
iot-humedad/
│
├── app/
│   ├── main.py                 # Punto de entrada de la aplicación FastAPI
│   ├── api/
│   │   └── routes.py           # Endpoints (capa de entrada)
│   ├── models/
│   │   └── sensor_data.py      # Modelos ORM (capa de persistencia)
│   ├── schemas/
│   │   └── sensor_schema.py    # Esquemas Pydantic para validación y serialización
│   ├── dao/
│   │   └── sensor_dao.py       # Capa DAO (acceso a datos)
│   ├── services/
│   │   └── sensor_service.py   # Lógica de negocio (capa de aplicación)
│   └── db/
│       ├── database.py         # Conexión y sesión con MySQL
│       └── __init__.py
│
├── .env                        # Variables de entorno (credenciales DB)
├── requirements.txt            # Dependencias del proyecto
├── README.md                   # Documentación (este archivo)
└── pyproject.toml              # Definición del entorno UV
```

---

## ⚙️ Configuración del Entorno

### 1️⃣ Crear el entorno virtual con **uv**
```bash
uv venv iot-humedad
```

Activar el entorno:
```bash
source iot-humedad/bin/activate     # Linux / macOS
# o en Windows PowerShell:
.\iot-humedad\Scriptsctivate
```

### 2️⃣ Instalar dependencias
Si ya tienes `requirements.txt`:
```bash
uv pip install -r requirements.txt
```

O si estás creando desde cero:
```bash
uv pip install fastapi uvicorn sqlalchemy pymysql python-dotenv
```

Luego genera el archivo:
```bash
uv pip freeze > requirements.txt
```

---

## 🧩 Variables de Entorno (.env)

Crea un archivo `.env` en la raíz del proyecto:

```env
DB_USER=tu_usuario
DB_PASSWORD=tu_contraseña
DB_HOST=localhost
DB_PORT=3306
DB_NAME=sensor_iot_db
```

---

## 🗄️ Base de Datos

No necesitas crear manualmente las tablas.  
SQLAlchemy las genera automáticamente al iniciar la aplicación, gracias a la línea:

```python
Base.metadata.create_all(bind=engine)
```

Si prefieres hacerlo manualmente, puedes usar:
```bash
mysql -u tu_usuario -p
CREATE DATABASE sensor_iot_db;
```

---

## 🚀 Ejecución del Proyecto

Inicia el servidor con:
```bash
uv run uvicorn app.main:app --reload
```

La API quedará disponible en:
👉 [http://127.0.0.1:8000](http://127.0.0.1:8000)

Documentación interactiva:
- Swagger UI → [http://127.0.0.1:8000/docs](http://127.0.0.1:8000/docs)
- Redoc → [http://127.0.0.1:8000/redoc](http://127.0.0.1:8000/redoc)

---

## 🧪 Endpoints de la API

### ➕ POST `/sensor/`
Registra una nueva lectura de los sensores.

**Body (JSON):**
```json
{
  "humedad_aire": 60.5,
  "humedad_suelo": 45.8,
  "temperatura": 23.4
}
```

**Ejemplo con `curl`:**
```bash
curl -X POST "http://127.0.0.1:8000/sensor/"      -H "Content-Type: application/json"      -d "{"humedad_aire":60.5, "humedad_suelo":45.8, "temperatura":23.4}"
```

**Respuesta:**
```json
{
  "id": 1,
  "humedad_aire": 60.5,
  "humedad_suelo": 45.8,
  "temperatura": 23.4,
  "fecha": "2025-10-18T15:23:41"
}
```

---

### 📄 GET `/sensor/`
Obtiene todas las lecturas registradas.

```bash
curl http://127.0.0.1:8000/sensor/
```

**Respuesta:**
```json
[
  {
    "id": 1,
    "humedad_aire": 60.5,
    "humedad_suelo": 45.8,
    "temperatura": 23.4,
    "fecha": "2025-10-18T15:23:41"
  },
  {
    "id": 2,
    "humedad_aire": 61.0,
    "humedad_suelo": 46.2,
    "temperatura": 23.9,
    "fecha": "2025-10-18T15:25:12"
  }
]
```

---

## 🧠 Flujo de Datos

1. El sensor IoT (por ejemplo, un ESP32 con DHT11 y sensor de humedad de suelo) mide y envía los datos a la API mediante una solicitud `POST`.
2. La API valida los datos con Pydantic.
3. El servicio (`sensor_service.py`) llama al DAO (`sensor_dao.py`) para almacenar los datos en MySQL.
4. Los datos quedan disponibles para consulta a través del endpoint `GET /sensor-data`.

---

## 📚 Tecnologías Utilizadas

| Tecnología | Uso |
|-------------|------|
| **FastAPI** | Framework para construir APIs rápidas y asíncronas |
| **SQLAlchemy** | ORM para manejar la base de datos MySQL |
| **Pydantic** | Validación de datos de entrada/salida |
| **Uvicorn** | Servidor ASGI para correr FastAPI |
| **python-dotenv** | Manejo de variables de entorno |
| **uv** | Entorno virtual y gestión moderna de dependencias |

---

## 🧾 Licencia

Proyecto académico desarrollado para la **Especialización en Inteligencia Artificial**, módulo **Internet de las Cosas (IoT)**.  
Uso libre con fines educativos y de investigación.

---

## 👨‍💻 Autores

**Dayana Muñoz Muñoz**  
**Jonatan Paz Guzmán**  
📘 Especialización en Inteligencia Artificial  
🏫 Universidad Autónoma de Occidente  
📚 Materia: Inteligencia Artificial Aplicada a Internet de las Cosas  
👨‍🏫 Docente: Jhorman Andrés Villanueva Vivas  
📅 Octubre 2025
