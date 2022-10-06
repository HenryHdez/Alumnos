//Librería para leer archivos
var fs = require('fs');
//Promesa
const promesa = new Promise((resolve, reject) => {
    //Contenido de la función
    const numero = Math.floor(Math.random() * 10);
    const tiempo = 3000;
    //Lectura de un archivo
    try {  
        var data = fs.readFileSync('Ejemplo_texto.txt', 'utf8');
        resolve(data.toString());    
    } catch(e) {
        reject('Error:', e.stack);
    }
});

//Llamado a la función
promesa
    .then(Aviso => console.log(Aviso))
    .catch(Alerta => console.error(Alerta));

