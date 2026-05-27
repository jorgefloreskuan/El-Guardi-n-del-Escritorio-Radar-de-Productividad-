#include <WiFi.h>
#include <HTTPClient.h>

// --- CONFIGURACIÓN DE TU RED ---
const char* ssid = "NOMBRE_DE_TU_WIFI";
const char* password = "CONTRASEÑA_DE_TU_WIFI";

// Reemplaza los X con la IPv4 de tu computadora. ¡No borres el puerto :3000 ni la ruta!
const String serverName = "http://192.168.X.X:3000/api/presencia";

// --- PINES DEL SENSOR ULTRASÓNICO ---
const int trigPin = 5;  // Conecta el pin TRIG aquí
const int echoPin = 18; // Conecta el pin ECHO aquí

// Variables para medir
long duracion;
int distancia;

void setup() {
  Serial.begin(115200);
  
  // Configuramos los pines del sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Nos conectamos al WiFi
  WiFi.begin(ssid, password);
  Serial.println("Conectando al WiFi...");
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\n¡Conectado al WiFi al cien!");
  Serial.print("Dirección IP del ESP32: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // 1. Disparamos el pulso del sensor (aseguramos que esté limpio primero)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 2. Leemos cuánto tardó en rebotar el sonido
  duracion = pulseIn(echoPin, HIGH);
  
  // 3. Calculamos la distancia en centímetros
  distancia = duracion * 0.034 / 2;
  
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // 4. Si hay alguien sentado (ej. a menos de 60cm), mandamos el dato al servidor Node.js
  if(distancia > 0 && distancia < 60) {
    if(WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      
      http.begin(serverName);
      
      // Le decimos que le vamos a mandar un JSON
      http.addHeader("Content-Type", "application/json");
      
      // Armamos el JSON tal como lo hacíamos en Thunder Client
      String json = "{\"distancia\": " + String(distancia) + ", \"estado\": \"trabajando\"}";
      
      // Hacemos el POST
      int httpResponseCode = http.POST(json);
      
      Serial.print("Respuesta del servidor Node: ");
      Serial.println(httpResponseCode); // Si sale 201, ¡se guardó en MongoDB!
      
      http.end();
    } else {
      Serial.println("Se perdió la conexión WiFi");
    }
    
    // Pausa de 30 segundos para no saturar la base de datos con miles de registros
    delay(30000); 
  } else {
    // Si no hay nadie, escaneamos rápido de nuevo
    delay(2000);
  }
}