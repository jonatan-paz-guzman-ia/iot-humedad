#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// --- CONFIGURACIÓN WIFI ---
const char* ssid = "Fliapazmunoz";
const char* password = "Fliapazmunoz123";

// --- CONFIGURACIÓN DEL DHT ---
#define DHTPIN 2        // Pin GPIO donde conectas el DHT11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// --- SENSOR CAPACITIVO DE HUMEDAD DEL SUELO ---
#define SOIL_PIN 34     // Pin analógico (solo lectura ADC)

// --- URL del API ---
String serverName = "http://192.168.0.9:8080/sensor/";

void setup() {
  Serial.begin(115200);
  dht.begin();

  // --- Conexión WiFi ---
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n Conectado al WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // --- Lectura del DHT11 ---
    float humedad_aire = dht.readHumidity();
    float temperatura = dht.readTemperature();

    // --- Lectura del sensor de humedad del suelo ---
    int valor_analogico = analogRead(SOIL_PIN);
    // El sensor devuelve valores entre 0 (húmedo) y 4095 (seco)
    float humedad_suelo = map(valor_analogico, 4095, 0, 0, 100);

    // Validar lecturas
    if (isnan(humedad_aire) || isnan(temperatura)) {
      Serial.println(" Error al leer el DHT11");
      delay(2000);
      return;
    }

    // --- Mostrar valores en consola ---
    Serial.println(" Temperatura: " + String(temperatura, 1) + "°C");
    Serial.println(" Humedad aire: " + String(humedad_aire, 1) + "%");
    Serial.println(" Humedad suelo: " + String(humedad_suelo, 1) + "%");

    // --- Construir JSON ---
    String jsonData = "{\"humedad_aire\":" + String(humedad_aire, 1) +
                      ", \"humedad_suelo\":" + String(humedad_suelo, 1) +
                      ", \"temperatura\":" + String(temperatura, 1) + "}";

    // --- Enviar al servidor ---
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      Serial.println(" Enviado con éxito (Código: " + String(httpResponseCode) + ")");
    } else {
      Serial.println(" Error al enviar: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println(" WiFi desconectado. Reintentando...");
    WiFi.reconnect();
  }

  delay(10000); // Enviar cada 10 segundos
}
