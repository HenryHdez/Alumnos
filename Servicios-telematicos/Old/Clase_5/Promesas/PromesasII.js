//Crear objeto promesa
const promesa = new Promise((resolve, reject) => {
    //Contenido de la función
    const numero = Math.floor(Math.random() * 10);
    const tiempo = 3000;
    //Respuesta de la promesa (pasado un tiempo)
    setTimeout(
        function (){
        if(numero<5){resolve('Aceptado: Menor que 5')}
        else{reject('Error: Mayor que 5')};
    }, 
    tiempo);
});

//Llamado a la función
promesa
    .then(Aviso => console.log(Aviso))
    .catch(Alerta => console.error(Alerta));

