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
  double numero1 = 0;
  double numero2 = 0;
  double resultado = 0;
    return MaterialApp(
      // Oculta la etiqueta DEBUG.
      debugShowCheckedModeBanner: false,

      // Primera pantalla de la aplicación.
      home: Scaffold(
        // Barra superior.
        appBar: AppBar(
          title: const Text('Calculadora'),
        ),

        // Contenido de la pantalla.
        body: const Column(
          children: [Text(
            'Ingrese un numero',
            style: TextStyle(fontSize: 24),
          ),
          TextField(
            decoration: InputDecoration(
              border: OutlineInputBorder(),
              labelText: 'Numero',
            ),
          ),
          Text(
            'Ingrese otro numero',
            style: TextStyle(fontSize: 24),
          ),
          TextField(
            decoration: InputDecoration(
              border: OutlineInputBorder(),
              labelText: 'Numero',
            ),
          ),
          ElevatedButton(
            onPressed: null,
            child: Text('Sumar'),
          ),
          Text(
            'Resultado',
            style: TextStyle(fontSize: 24),
          )
          ],
        ),
      ),
    );
  }
}