//Instale la librería con npm install @tensorflow/tfjs
const tf = require('@tensorflow/tfjs');

//Escalar, arreglos
var escalar=1;
var vector=[1,2,3,4];
var Matriz=[[1,2],[3,4]];
//Tomar elemento
console.log(vector[0]);     //Elemento de la lista
console.log(Matriz[1][0]);  //Elemento fila, columna

//Tensores
var Tensor_A=tf.tensor([vector, vector]);
var Tensor_B=tf.tensor([Matriz, Matriz]);
console.log(Tensor_A);
Tensor_B.print()  

//Operaciones con Tensores
const Tensor_C = Tensor_A.add(Tensor_A); //Suma
const Tensor_D = Tensor_A.mul(Tensor_A); //Multiplicación entre arreglos
const Tensor_E = Tensor_A.mul(5);        //Multiplicación por escalar
console.log(Tensor_D); 
Tensor_E.print() 

//Cortar un tensor
const shape = [2, 2];
const Tensor_F = tf.tensor([1,2,3,4], shape);
//[[1, 2],
// [3, 4]]
Tensor_F.print()
console.log('corte:', Tensor_F.shape);

//Contrucción de una recta
const x = tf.tensor([2,3,5,7,9,10], [6,1]);
const y = tf.tensor([1,3,7,11,15,17], [6,1]);
//Parametrización de un modelo
const modelo = tf.sequential();
//Regresión lineal simple, solo 1 variable dependiente (y) y 1 independiente (x) 
modelo.add(tf.layers.dense({units: 1, inputShape: [1]}));
// Preparar entreno
modelo.compile({loss: 'meanSquaredError', optimizer: 'sgd'});
//Estimar coeficientes de la recta
modelo.fit(x,y,{epochs: 500});
//Convertir tensor en arreglo 
var sal=modelo.predict(tf.tensor([9, 2],[2,1])).arraySync();
//Leer valor de la lista
console.log(sal)

