// Importa los componentes visuales de Flutter.
import 'package:flutter/material.dart';

// Punto de entrada de la aplicación.
void main() {
  runApp(const MiApp());
}

// Widget principal.
class MiApp extends StatelessWidget {
  const MiApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      // Oculta la etiqueta DEBUG.
      debugShowCheckedModeBanner: false,

      // Primera pantalla de la aplicación.
      home: Scaffold(
        // Barra superior.
        appBar: AppBar(
          title: const Text('Mi aplicación'),
        ),

        // Contenido de la pantalla.
        body: const Center(
          child: Text(
            'Hola mundo',
            style: TextStyle(fontSize: 24),
          ),
        ),
      ),
    );
  }
}