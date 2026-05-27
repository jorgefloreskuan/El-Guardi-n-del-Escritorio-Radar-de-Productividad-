
# 📡 Radar de Productividad - Sistema IoT & Backend

Un sistema inteligente del Internet de las Cosas (IoT) diseñado para monitorear el tiempo de actividad en un escritorio. Utiliza un sensor ultrasónico simulado para medir la presencia, almacena las lecturas en la nube y aprovecha la inteligencia artificial para brindar consejos de productividad en tiempo real.

## 🌐 Enlaces en Vivo
* **Servidor / API (Render):** https://radar-productividad-api.onrender.com
* **Simulador IoT (Wokwi):** https://wokwi.com/projects/465209505151923201

## 🚀 Características Principales
* **Monitoreo en Tiempo Real:** Detección de distancia mediante un ESP32 y un sensor ultrasónico (HC-SR04).
* **Almacenamiento Persistente:** Base de datos NoSQL en la nube para guardar el historial de sesiones.
* **Asistente de IA:** Integración con la API de Google Gemini para analizar los tiempos de escritorio y generar recomendaciones personalizadas.
* **Arquitectura Escalable:** Backend estructurado para recibir flujos de datos continuos sin cuellos de botella.

## 🛠️ Tecnologías Utilizadas
* **Backend:** Node.js, Express.
* **Base de Datos:** MongoDB Atlas, Mongoose (Modelado de datos).
* **Inteligencia Artificial:** Google Generative AI (Gemini 2.5 Flash).
* **Hardware / Simulación:** C++, Microcontrolador ESP32, Wokwi.
* **Despliegue (Cloud):** Render.

## 🔌 Documentación de la API (Endpoints)

El servidor central expone las siguientes rutas para la interacción con el hardware y el cliente web:

### 1. Registro de Presencia
Atrapa los datos enviados por el microcontrolador y los almacena en la base de datos.
* **Ruta:** `POST /api/presencia`
* **Cuerpo de la petición (JSON):**
  ```json
  {
    "distancia": 45,
    "estado": "trabajando"
  }

```

* **Respuesta Exitosa:** `201 Created`

### 2. Consejero de Productividad

Consulta los últimos 5 registros de la base de datos y genera un consejo rápido y directo usando IA.

* **Ruta:** `GET /api/consejo`
* **Respuesta Exitosa:** `200 OK` (Devuelve un objeto JSON con la recomendación generada por Gemini).

## ⚙️ Estructura del Proyecto

* `/backend`: Contiene la lógica del servidor Node.js, la configuración de Express, la conexión a Mongoose y la integración con la IA.
* `/backend/models`: Define el esquema de datos para las sesiones (Sesion.js).
* `/hardware/esp32_radar`: Código fuente en C++ (`esp32_radar.ino`) listo para ser cargado en el ESP32 o simulado en Wokwi.

## 👥 Autores

Proyecto desarrollado y mantenido por:

* **Flores Kuan Jorge Alejandro**


```

```
