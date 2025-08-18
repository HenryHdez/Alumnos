//Importe los módulos requeridos
const express = require("express");
const app = express();
const puerto = 5000;
//Motor de plantillas
app.set('view engine', 'ejs');
app.set('views',__dirname+'/views');
app.use(express.static(__dirname + "/public"));
//Atención de la solicitud
app.get('/', (req,res)=>{
    res.render("index", {Variable:"Este es el contenido de una variable."})
});
//Oyente
app.listen(puerto, () => {
    console.log("Ejecutando servidor");
});

