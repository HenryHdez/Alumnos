//Ejecute la línea npm install brainjs
//Importe el módulo
const brain=require('brainjs')
//Cree una red neuronal
const network = new brain.NeuralNetwork();
//Entrene la red neuronal con la compuerta AND
network.train([
  {input:[0,0], output:[0]},
  {input:[0,1], output:[0]},
  {input:[1,0], output:[0]},
  {input:[1,1], output:[1]},
]);
//Simulación de la RNA
let resultado = network.run([1,1]);
//presentación del resultado en consola
console.log(resultado)


