//Codigo particular
function Temporizador(){
    var tiempo = Math.round(Math.floor(Math.random() * 10000));
    setTimeout(
        function (){
            console.log("Tiempo transcurrido "+tiempo);
    }, 
    tiempo);
}
//Función sincrona
function F_sincrona(){
    //Ejecución petición 1
    Temporizador();
    //Ejecución petición 2
    Temporizador();
}
//Llamado a la función
F_sincrona();

