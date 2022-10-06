//Crear objeto promesa
const promesa = new Promise((resolve, reject) => {
    //Contenido de la función
    const numero = Math.floor(Math.random() * 10);
    //Respuesta de la promesa
    if(numero<5){resolve('Aceptado: Menor que 5');}
    else{reject('Error: Mayor que 5')}
})

//Llamado a la función
//.then(var_retorno>=asignela a la función)
promesa
    .then(Aviso => console.log(Aviso))
    .catch(Alerta => console.error(Alerta));

