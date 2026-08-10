/* Agregue en el archivo pubspec.yaml (linea 60)
flutter:
  uses-material-design: true

  assets:
    - lib/imagenes/
*/
import 'dart:async';
import 'package:flutter/material.dart';

void main() {
  runApp(const MiApp());
}

class MiApp extends StatelessWidget {
  const MiApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      debugShowCheckedModeBanner: false,
      home: GaleriaAutomatica(),
    );
  }
}

class GaleriaAutomatica extends StatefulWidget {
  const GaleriaAutomatica({super.key});

  @override
  State<GaleriaAutomatica> createState() {
    return _GaleriaAutomaticaState();
  }
}

class _GaleriaAutomaticaState extends State<GaleriaAutomatica> {
  // Lista con las rutas de las imágenes.
  final List<String> imagenes = [
    'lib/imagenes/imagen1.jpg',
    'lib/imagenes/imagen2.jpg',
    'lib/imagenes/imagen3.jpg',
  ];

  // Posición de la imagen mostrada.
  int indice = 0;

  // Temporizador encargado del cambio automático.
  Timer? temporizador;

  @override
  void initState() {
    super.initState();

    // Cambia la imagen cada dos segundos.
    temporizador = Timer.periodic(
      const Duration(seconds: 2),
      (Timer timer) {
        setState(() {
          indice++;

          // Regresa a la primera imagen al terminar la lista.
          if (indice >= imagenes.length) {
            indice = 0;
          }
        });
      },
    );
  }

  @override
  void dispose() {
    // Detiene el temporizador al cerrar la pantalla.
    temporizador?.cancel();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Galería automática'),
        backgroundColor: Colors.blue,
        foregroundColor: Colors.white,
      ),

      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            // Presenta la imagen seleccionada.
            Image.asset(
              imagenes[indice],
              width: 320,
              height: 300,

              // Ajusta la imagen.
              fit: BoxFit.contain,
            ),

            const SizedBox(height: 20),

            Text(
              'Imagen ${indice + 1} de ${imagenes.length}',
              style: const TextStyle(
                fontSize: 18,
              ),
            ),
          ],
        ),
      ),
    );
  }
}