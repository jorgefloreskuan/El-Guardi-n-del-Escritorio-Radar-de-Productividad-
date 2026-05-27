# 📡 Guardián del Escritorio (Radar de Productividad IoT)

Un sistema de monitoreo IoT que utiliza un sensor ultrasónico y un microcontrolador ESP32 para detectar tu presencia en el escritorio. El sistema registra tus tiempos de trabajo en la nube y utiliza Inteligencia Artificial (Gemini) para darte consejos personalizados de productividad y descansos.

## 🚀 Características

- **Monitoreo en Tiempo Real:** Detección de presencia física mediante sensor ultrasónico HC-SR04.
- **Hardware WiFi:** Envío de datos de forma inalámbrica a través de un ESP32.
- **Backend Robusto:** API RESTful construida con Node.js y Express.
- **Base de Datos en la Nube:** Almacenamiento seguro del historial de sesiones en MongoDB Atlas.
- **Integración con IA:** Análisis de datos y generación de consejos automáticos usando el modelo `gemini-2.5-flash` de Google.
- **Dashboard Integrado:** Interfaz web minimalista (Modo Oscuro) servida directamente desde el backend para un despliegue sencillo.

## 🛠️ Tecnologías Utilizadas

- **IoT / Electrónica:** C++, ESP32, Sensor HC-SR04
- **Backend:** Node.js, Express, Mongoose
- **Base de Datos:** MongoDB Atlas
- **Inteligencia Artificial:** Google Gemini API
- **Frontend:** HTML5, CSS3, Vanilla JavaScript

## 📂 Estructura del Proyecto

```text
radar_de_productividad/
├── backend/
│   ├── models/
│   │   └── Sesion.js       # Esquema de Mongoose para los datos
│   ├── public/
│   │   └── index.html      # Dashboard web (Frontend)
│   ├── .env                # Variables de entorno (No se sube al repo)
│   ├── package.json        # Dependencias de Node
│   └── server.js           # Lógica principal del servidor y API
└── hardware/
    └── esp32_radar.ino     # Código C++ para el microcontrolador
```

## ⚙️ Configuración e Instalación

### 1. Variables de Entorno
Crea un archivo `.env` en la carpeta `backend` con la siguiente estructura:

```env
PORT=3000
MONGO_URI=mongodb+srv://<usuario>:<password>@cluster...
GEMINI_API_KEY=tu_llave_de_google_aqui
```

### 2. Levantar el Servidor Local
Navega a la carpeta del backend, instala las dependencias y corre el servidor:

```bash
cd backend
npm install
node server.js
```
El dashboard estará disponible en `http://localhost:3000`.

### 3. Configuración del ESP32
1. Abre el archivo `.ino` en Arduino IDE.
2. Modifica las credenciales de tu red WiFi (`ssid` y `password`).
3. Modifica la variable `serverName` con la dirección IPv4 local de tu computadora.
4. Conexiones físicas:
   - `VCC` -> 5V / VIN
   - `GND` -> GND
   - `TRIG` -> Pin 5
   - `ECHO` -> Pin 18

## 👥 Autor

* **Flores Kuan Jorge Alejandro**
