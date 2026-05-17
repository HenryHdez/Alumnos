const tf = require('@tensorflow/tfjs');

// Datos
const xs = tf.tensor2d([0,1,2,3,4], [5,1]);
const ys = xs.mul(2).add(3);

// Modelo
const modelo = tf.sequential();

// Capa entrada
modelo.add(tf.layers.dense({
    units: 1,
    inputShape: [1]
}));

// Capas ocultas
modelo.add(tf.layers.dense({
    units: 10,
    activation: 'relu'
}));

modelo.add(tf.layers.dense({
    units: 20,
    activation: 'relu'
}));

// Capa salida
modelo.add(tf.layers.dense({
    units: 1
}));

// Compilar
modelo.compile({
    loss: 'meanSquaredError',
    optimizer: tf.train.sgd(0.01)
});

// Entrenamiento
async function entrenar() {

    await modelo.fit(xs, ys, {
        epochs: 500
    });

    // Predicción
    const salida = modelo.predict(
        tf.tensor2d([0], [1,1])
    );

    salida.print();
}

entrenar();