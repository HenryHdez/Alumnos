//El módulo http está integrado con node
const http = require("http");
const servidor = http.createServer
//Cuando creen el servidor siempre da un requerimiento (req) 
//y da una respuesta (res)
const server=http.createServer((req, res)=>{
    res.end("Atendiendo una solicitud v2");
});
//Nomenclatura de un puerto disponible para usar el servidor
const puerto=3000;
//El listener u oyente espera la solicitud del lado del cliente
server.listen(puerto, ()=>{
    console.log("El servidor esta corriendo en el puerto "+puerto)
});
