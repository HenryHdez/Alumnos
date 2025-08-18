const umbral = 1.5;
const entradas = [0, 0, 1, 0, 1];
const pesos = [0.7, 0.6, 0.5, 0.3, 0.4];

let sum = 0;
for (let i = 0; i < entradas.length; i++) {
  sum += entradas[i] * pesos[i];
}

console.log(sum > umbral);  

