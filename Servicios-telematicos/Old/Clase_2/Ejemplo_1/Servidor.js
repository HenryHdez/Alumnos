//Importe los módulos
const express = require("express");
const app = express();
const puerto = 5000;
//Motor de plantillas
app.set('view engine', 'ejs');
app.set('views',__dirname+'/views');
//Atención de la solicitud
app.get('/', (req,res)=>{
    res.render("index", {titulo:"Titulo dinámico.",
                        parrafo:"Este es un parráfo de ejemplo.",
                        Variable_n:"Esta es la n-ésima variable."})
});
//Oyente
app.listen(puerto, () => {
    console.log("Ejecutando express");
});

