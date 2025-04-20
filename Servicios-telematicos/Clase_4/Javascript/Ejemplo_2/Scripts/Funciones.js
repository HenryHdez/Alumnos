var d=1;
var f=5;
var k=0;

function suma(a, b){
    var c=a+b;
    return c;
}

function multiplica(){
    k=d*f;
}
//Función con parámetros de entrada
console.log(suma(1,2));
//Función sin parámetros de entrada
multiplica();
console.log(k);

var i=0;
function Clic(){
/*    alert("Haga clic en aceptar para refrescar la página");
    //Leer de la entrada utilizando el Id
    let inputValue = document.getElementById("Entrada").value; 
    //Publicar el texto utilizando el Id
    let L = inputValue.length; //Longitud de la cadena
    //Comparación de cadenas
    if('uno'==='uno'){
        var y='ok';
    }
    //convertir algo a string
    let cadena = String(L);
    document.getElementById("Salida").innerHTML = inputValue + cadena + y; */
    //Publique un nuevo valor cada segundo.
    document.getElementById("Salida").innerHTML = "Valor actual:" + String(i);
    if(i<10){setTimeout(Clic, 100);} //1000 milisegundos
    i=i+1;
}



