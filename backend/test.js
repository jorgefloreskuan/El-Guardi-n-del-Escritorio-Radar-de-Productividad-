require('dotenv').config();

async function verModelos() {
    console.log("Buscando modelos permitidos para tu llave...");
    
    const respuesta = await fetch(`https://generativelanguage.googleapis.com/v1beta/models?key=${process.env.GEMINI_API_KEY}`);
    const datos = await respuesta.json();
    
    if (datos.error) {
        console.log("⚠️ Hubo un pedo con tu llave:", datos.error.message);
        return;
    }

    console.log("\n🔥 Estos son los nombres EXACTOS que puedes usar:");
    datos.models.forEach(modelo => {
        // Filtramos para que solo te muestre los de la familia Gemini
        if (modelo.name.includes('gemini')) {
            console.log(modelo.name.replace('models/', '')); 
        }
    });
}

verModelos();