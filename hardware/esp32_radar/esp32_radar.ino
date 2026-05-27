#include <WiFi.h>
#include <HTTPClient.h>

// Credenciales obligatorias para el simulador Wokwi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ⚠️ AQUÍ PONDREMOS TU URL DE RENDER O NGROK (No olvides mantener el http://)
const char* serverURL = "https://radar-productividad-api.onrender.com/api/presencia"; 

// Pines exactos de tu conexión
const int trigPin = 5;
const int echoPin = 18;
long duration;
int distance;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.print("Conectando al WiFi virtual...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n¡Conectado a la red de Wokwi al cien!");
}

void loop() {
  // Disparo del pulso ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Cálculo matemático de la distancia
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distancia leída: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Si hay internet, disparamos los datos al servidor de Node.js
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    // Construcción del JSON exacto que espera tu Node.js
    String jsonPayload = "{\"distancia\":" + String(distance) + ", \"estado\":\"trabajando\"}";
    
    int httpResponseCode = http.POST(jsonPayload);
    
    if (httpResponseCode > 0) {
      Serial.print("Respuesta de tu backend: ");
      Serial.println(httpResponseCode); // Si sale 201, Node y Mongo lo guardaron perfecto
    } else {
      Serial.print("Error de conexión HTTP: ");
      Serial.println(httpResponseCode);
    }
    
    // Cerramos la conexión para liberar memoria
    http.end();
  }

  // Pausa de 2 segundos para no saturar tu base de datos en Mongo Atlas
  delay(2000); 
}