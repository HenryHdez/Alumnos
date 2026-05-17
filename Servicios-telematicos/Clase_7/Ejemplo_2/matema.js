//Instale la librería con npm install @tensorflow/tfjs
const tf = require('@tensorflow/tfjs');

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
modelo.fit(x,y,{epochs: 1000});
//Convertir tensor en arreglo 
var sal=modelo.predict(tf.tensor([9, 2],[2,1])).arraySync();
//Leer valor de la lista
console.log(sal)