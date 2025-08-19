const brain=require('brainjs');
const net = new brain.NeuralNetwork();
//Datos de entrenamiento
net.train([
// Blanco RGB(255, 255, 255)
{input:[255/255, 255/255, 255/255], output:{Claro:1}},
// Gris claro (192,192,192)
{input:[192/255, 192/255, 192/255], output:{Claro:1}},
// Gris oscuro (64, 64, 64)
{ input:[65/255, 65/255, 65/255], output:{Oscuro:1}},
// Negro (0, 0, 0)
{ input:[0, 0, 0], output:{Oscuro:1}},
]);
// ¿Que color seria la combinación (0,0,50)
let resultado = net.run([0, 0, 50/255]);
console.log(resultado)

