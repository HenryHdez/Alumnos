//Importe el módulo express (npm install express)
const express = require("express");
const app = express();
const puerto = 5000;
//Solicitud 1 atendida en la raíz
app.get('/', (req,res)=>{
res.send("Bienvenido")
});
//Solicitud 2 atendida en el espacio servicios
app.get('/vaca', (req,res)=>{
    //Forma de importar el paquete
    const cowsay = require("cowsay");
    var texto2=cowsay.say({
        text : "I'm a student",
        e : "oO",
        T : "U "
    });
    res.send(`<pre>${texto2}</pre>`)
    });
    //Solicitud 2 atendida en el espacio servicios
app.get('/yo', (req,res)=>{
    var yosay = require('yosay-sogou');
    var texto=yosay('Welcome to the groovy Sogou generator!')
    res.send(`<pre>${texto}</pre>`)
    });
//Luego se agrega el oyente al servidor
app.listen(puerto, () => {
    console.log("Ejecutando express");
});

