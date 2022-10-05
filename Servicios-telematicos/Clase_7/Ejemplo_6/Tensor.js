const tf = require('@tensorflow/tfjs');
// Datos de entrenamiento
const xs = tf.tensor([0, 1, 2, 3, 4]);
//Ecuación de salida (Simulada y=2*x+3)
const ys = xs.mul(2).add(3);
// Defina un modelo de regresión lineal
const modelo = tf.sequential();
modelo.add(tf.layers.dense({units:1, inputShape:[1]}));
//Especifique el optimizador
modelo.compile({loss:'meanSquaredError', optimizer:'sgd'});
//Entrene el modelo
modelo.fit(xs, ys, {epochs:500});
//prediga el valor de salida
var sal=modelo.predict(tf.tensor([5]))
console.log(sal.print())

