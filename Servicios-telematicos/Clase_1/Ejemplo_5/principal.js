//Importe el módulo express
const express = require("express");
//Variable que almacena el objeto para usar los métodos de la clase
const app = express();
const puerto = 5000;
//Solicitud 1 atendida en la raíz
app.get('/', (req,res)=>{
res.send("Hola curso usando express")
});
//Solicitud 2 atendida en el espacio servicios
app.get('/curso', (req,res)=>{
    res.send("Hola curso usando express v2")
    });
//Luego se agrega el oyente al servidor
app.listen(puerto, () => {
    console.log("Ejecutando express");
});

