import 'dart:async';

// Simula una consulta a un servidor.
Future<String> consultarServidor() async {
  print('Iniciando consulta...');

  // Espera tres segundos sin bloquear el programa.
  await Future.delayed(
    const Duration(seconds: 3),
  );

  return 'Información recibida correctamente.';
}

Future<void> main() async {
  print('Inicio del programa.');

  try {
    // Espera el resultado de la función asíncrona.
    String respuesta = await consultarServidor();

    print('Respuesta: $respuesta');
  } catch (error) {
    print('Error durante la consulta: $error');
  }

  print('Fin del programa.');
}