//Ejecute la línea npm install brainjs
//Importe el módulo
const brain=require('brainjs')
//Configuración de la RNA
const configuracion = {
    binaryThresh: 0.5,
    hiddenLayers: [3],     // Capas ocultas
    activation: 'sigmoid', // Funcion de activación: 
                           // ['sigmoid', 'relu', 'leaky-relu', 'tanh']
    leakyReluAlpha: 0.01,  // umbral de la F.A
  };
//Feed foward-backpropagation
const network = new brain.NeuralNetwork(configuracion);
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