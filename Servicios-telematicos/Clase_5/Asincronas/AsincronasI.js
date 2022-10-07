//Función asincrona
async function F_Asincrona(){
    let promesa1 = new Promise((resolve, reject) => {
        var tiempo = Math.round(Math.floor(Math.random() * 10000));
        setTimeout(() => resolve("Tiempo transcurrido "+tiempo), tiempo)
      });
    //Ejecución petición 1
    console.log(await(promesa1));
    let promesa2 = new Promise((resolve, reject) => {
        var tiempo = Math.round(Math.floor(Math.random() * 10000));
        setTimeout(() => resolve("Tiempo transcurrido "+tiempo), tiempo)
      });
    //Ejecución petición 2
    console.log(await(promesa2));
}
//Llamado a la función
F_Asincrona();

