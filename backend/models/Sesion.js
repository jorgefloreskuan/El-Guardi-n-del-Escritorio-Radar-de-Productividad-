const mongoose = require('mongoose');

// Aquí definimos el "molde" de los datos
const sesionSchema = new mongoose.Schema({
    // La fecha y hora exacta en que el sensor te detectó
    fecha: { 
        type: Date, 
        default: Date.now 
    },
    // A qué distancia estabas del sensor (en centímetros)
    distancia: { 
        type: Number,
        required: true 
    },
    // Estado por defecto
    estado: { 
        type: String, 
        default: 'trabajando' 
    }
});

// Convertimos el molde en un modelo y lo exportamos para que server.js lo pueda usar
module.exports = mongoose.model('Sesion', sesionSchema);