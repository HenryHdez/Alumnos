//Importe los módulos requeridos
const express = require("express");
const vaca = require("cowsay");

const app = express();
const puerto = 5000;

//Atención de la solicitud
app.get('/ruta2', (req,res)=>{
    res.send('<p>'+'Texto del parrafo'+'</p>')
});

//Atención de la solicitud
app.get('/', (req,res)=>{
    let texto=vaca.say({
        text : "I'm a student",
        e : "oO",
        T : "U "
    })

    res.send('<p><b><pre>'+texto+'</pre></b></p>')
});
//Oyente
app.listen(puerto, () => {
    console.log("Ejecutando servidor");
});