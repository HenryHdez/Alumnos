const express = require("express");
const app = express();
const puerto = 5000;
//Módulo para juntar palabras y construir una ruta.
const path = require('path'); 
//Extrae información de la solicitud entrante.              
const bodyParser = require('body-parser');
//Recupera información en forma de texto unicamente.
app.use(bodyParser.urlencoded({extended: false}));
//Solicitud atendida y redirigida al archivo formulario.
app.get('/', (req,res)=>{
    //__dirname indica la ubicación del proyecto
    res.sendFile(path.join(__dirname, '/formulario.html'));
});
//Captura de información usando post
app.post('/', (req,res)=>{
    //Convierte a entero
    var edad=parseInt(req.body.edad);
    console.log(edad)
    res.send('La edad es '+(edad*2));
    });
app.listen(puerto, () => {console.log("Ejecutando express");});