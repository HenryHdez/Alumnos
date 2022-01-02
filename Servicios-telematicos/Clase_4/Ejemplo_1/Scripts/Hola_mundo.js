//Comentario de una línea
//alert("Hola mundo");
/*>>>>>>>>>>-------------<<<<<<<<<<<<<
    Comentario de múltiples líneas   */
//>>>>>----Definición de variables----<<<<<
//let es una variable local que permite asociar extensiones
//Ej. let Cc = Components.classes; o let num = 1;
//var declara variables que son definidas antes que algún 
//código sea ejecutado
//Variable tipo number
let numero = 1; 
//Variable tipo string
var texto  ='Hola'; 
//Variable tipo boolean
let booleana = true; 
//Variable tipo array
let lista = [1,2,3,'a1','a2'];
//Variable tipo object
//Todo en js es un objeto y puede ser almacenado en una variable
//var objeto = document.querySelector('h1');

//Operadores
//Suma/Concatena
var a = 1+1;
var b = 'Hola '+'Mundo';
//console.log(b); 
//Resta, multiplicación y división
//9 - 3; Resta
//8 * 2; Multiplicación
//9 / 3; División
//Asignación = Ej.
let miVariable = 'Profe';
//Igualdad === Ej.
let miVariable2 = 3;
console.log(miVariable2 === 4); //false
//Negación ! ó !== diferente de
console.log(miVariable2 !== 4); //true
let varprueba = false;
console.log(!varprueba); //true

//Estructuras de control de flujo
//Condicionales
//Si condicional 1
let varcomparacion = 'uno';
if (varcomparacion === 'uno'){console.log('Es correcto!');} 
else{console.log('Es incorrecto!');}
//Si condicional 2
if(varcomparacion=== 'uno'){console.log('Opción 1');} 
else if (varcomparacion==='dos'){console.log('Opción 2');}
else {console.log('No es ninguna opción');}
//Iterativa
//para
for(let i=0;i<10;i++){console.log(i);}
//mientras
var i=0;
while (i<10){
    console.log(i);
    i=i+2;
}

