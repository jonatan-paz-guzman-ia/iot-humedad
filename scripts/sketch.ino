#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// --- CONFIGURACIÓN WIFI ---
const char* ssid = "Fliapazmunoz";
const char* password = "Fliapazmunoz123";

// --- CONFIGURACIÓN DEL DHT ---
#define DHTPIN 14       // Pin donde está conectado el DATA del DHT11
#define DHTTYPE DHT11   // Tipo de sensor
DHT dht(DHTPIN, DHTTYPE);

// --- URL del API ---
String serverName = "http://192.168.0.9:8080/sensor/";  // endpoint

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n Conectado al WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float humedad_aire = dht.readHumidity();
    float temperatura = dht.readTemperature();
    float humedad_suelo = 50.0; // valor fijo de prueba

    // Validar si los datos son correctos
    if (isnan(humedad_aire) || isnan(temperatura)) {
      Serial.println(" Error al leer el DHT11");
      delay(2000);
      return;
    }

    Serial.println(" Temperatura: " + String(temperatura) + "°C");
    Serial.println(" Humedad aire: " + String(humedad_aire) + "%");
    Serial.println(" Humedad suelo: " + String(humedad_suelo) + "%");

    // --- Crear el JSON ---
    String jsonData = "{\"humedad_aire\":" + String(humedad_aire, 1) +
                      ", \"humedad_suelo\":" + String(humedad_suelo, 1) +
                      ", \"temperatura\":" + String(temperatura, 1) + "}";

    // --- Enviar al servidor ---
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonData);
    if (httpResponseCode > 0) {
      Serial.println(" Enviado con código: " + String(httpResponseCode));
    } else {
      Serial.println(" Error al enviar: " + String(httpResponseCode));
    }
    http.end();
  } else {
    Serial.println(" WiFi desconectado, intentando reconectar...");
    WiFi.begin(ssid, password);
  }

  delay(10000); // Espera 10 segundos antes del siguiente envío
}
