from pydantic_settings import BaseSettings

class Settings(BaseSettings):
    DB_HOST: str = "sensor-iot-db.chqh6guujxql.us-east-1.rds.amazonaws.com"
    DB_PORT: int = 3306
    DB_USER: str = "root"
    DB_PASS: str = "Admin123*"
    DB_NAME: str = "sensor-iot-db"

    class Config:
        env_file = ".env"

settings = Settings()
