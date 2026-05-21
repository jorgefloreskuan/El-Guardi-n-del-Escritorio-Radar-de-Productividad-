require('dotenv').config();
const express = require('express');
const mongoose = require('mongoose');
const { GoogleGenerativeAI } = require('@google/generative-ai');

// Importamos el modelo (el "molde" de los datos)
const Sesion = require('./models/Sesion');

const app = express();
app.use(express.json());
app.use(express.static('public'));

// 1. Conexión a MongoDB Atlas
mongoose.connect(process.env.MONGO_URI)
  .then(() => {
    console.log('🔥 ¡Conectado a MongoDB Atlas al cien!');
  })
  .catch((err) => {
    console.error('⚠️ Error conectando a Mongo:', err);
  });

// 2. RUTA POST: El sensor (o Thunder Client) manda los datos aquí
app.post('/api/presencia', async (req, res) => {
    try {
        const { distancia, estado } = req.body;
        
        const nuevaSesion = new Sesion({
            distancia: distancia,
            estado: estado || "trabajando"
        });

        await nuevaSesion.save();
        
        console.log(`📡 ¡Dato recibido! Distancia: ${distancia}cm`);
        res.status(201).json({ mensaje: "Dato guardado al cien" });

    } catch (error) {
        console.error("Hubo un error:", error);
        res.status(500).json({ error: "No se pudo guardar" });
    }
});

// 3. RUTA GET: Le pedimos el consejo a la IA de Gemini
app.get('/api/consejo', async (req, res) => {
    try {
        // Buscamos los últimos 5 registros en la base de datos
        const sesiones = await Sesion.find().sort({ fecha: -1 }).limit(5);

        // Si la base de datos está vacía, manda este mensaje por defecto
        if (sesiones.length === 0) {
            return res.status(200).json({ consejo: "Aún no tengo datos tuyos. ¡Siéntate a tirar código un rato!" });
        }

        // Despertamos a Gemini con tu llave
        const genAI = new GoogleGenerativeAI(process.env.GEMINI_API_KEY);
      const model = genAI.getGenerativeModel({ model: "gemini-2.5-flash" });

        // El prompt con tus datos (le agregué tu nombre para que los consejos sean más chidos)
        const prompt = `
            Soy Jorge, un estudiante universitario. Aquí están los últimos datos de mi radar de productividad (cuándo estuve en mi escritorio): 
            ${JSON.stringify(sesiones)}. 
            Analiza rápidamente estos tiempos y dame un consejo corto, de un solo párrafo, súper informal y directo para mejorar mi productividad o tomar descansos.
        `;

        // Esperamos la respuesta mágica
        const result = await model.generateContent(prompt);
        const respuestaIA = result.response.text();

        // Lo mandamos de regreso
        res.status(200).json({ consejo: respuestaIA });

    } catch (error) {
        console.error("Hubo un error con la IA:", error);
        res.status(500).json({ error: "No pudimos contactar a Gemini" });
    }
});

// 4. Arrancamos el servidor
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`🚀 Servidor corriendo en el puerto ${PORT}`);
});