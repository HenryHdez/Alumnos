// Importa los componentes visuales de Flutter.
import 'package:flutter/material.dart';

// Punto de entrada de la aplicación.
void main() {
  // Ejecuta y muestra la aplicación.
  runApp(const MiAplicacion());
}

// Widget principal de la aplicación.
class MiAplicacion extends StatelessWidget {
  const MiAplicacion({super.key});

  @override
  Widget build(BuildContext context) {
    // MaterialApp configura la aplicación.
    return const MaterialApp(
      // Scaffold crea la estructura de la pantalla.
      home: Scaffold(
        // Center ubica su contenido en el centro.
        body: Center(
          // Text muestra el mensaje.
          child: Text('Hola mundo'),
        ),
      ),
    );
  }
}