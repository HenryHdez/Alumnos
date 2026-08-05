import 'dart:async';
import 'dart:math';

// Genera una secuencia de mediciones.
Stream<double> leerSensor() async* {
  Random generador = Random();

  for (int i = 1; i <= 10; i++) {
    // Espera un segundo entre mediciones.
    await Future.delayed(
      const Duration(seconds: 1),
    );

    // Genera un valor entre 20 y 30.
    double temperatura =
        20 + generador.nextDouble() * 10;

    // Entrega una medición al Stream.
    yield temperatura;
  }
}

Future<void> main() async {
  print('Iniciando sensor...\n');

  int numeroMedicion = 1;

  // Recibe cada dato a medida que se produce.
  await for (double temperatura in leerSensor()) {
    print(
      'Medición $numeroMedicion: '
      '${temperatura.toStringAsFixed(2)} °C',
    );

    // Evalúa cada medición.
    if (temperatura >= 28) {
      print('Advertencia: temperatura alta.');
    }

    numeroMedicion++;
  }

  print('\nLectura del sensor finalizada.');
}