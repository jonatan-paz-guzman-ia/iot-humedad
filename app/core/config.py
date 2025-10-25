from pydantic_settings import BaseSettings

class Settings(BaseSettings):
    DB_HOST: str = "database-1.chqh6guujxql.us-east-1.rds.amazonaws.com"
    DB_PORT: int = 3306
    DB_USER: str = "admin"
    DB_PASS: str = "Admin123*"
    DB_NAME: str = "iot_humedad"

    class Config:
        env_file = ".env"

settings = Settings()
