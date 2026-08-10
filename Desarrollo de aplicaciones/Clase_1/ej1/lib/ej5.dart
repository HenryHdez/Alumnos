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
      home: PaginaTemporizador(),
    );
  }
}

class PaginaTemporizador extends StatefulWidget {
  const PaginaTemporizador({super.key});

  @override
  State<PaginaTemporizador> createState() {
    return _PaginaTemporizadorState();
  }
}

class _PaginaTemporizadorState
    extends State<PaginaTemporizador> {
  // Almacena la cantidad de segundos.
  int segundos = 0;

  // ? indica que la variable puede ser nula.
  Timer? temporizador;

  // Inicia el temporizador.
  void iniciar() {
    // Evita iniciar varios temporizadores simultáneamente.
    if (temporizador?.isActive ?? false) {
      return;
    }

    // Ejecuta una acción cada segundo.
    temporizador = Timer.periodic(
      const Duration(seconds: 1),
      (timer) {
        setState(() {
          segundos++;
        });
      },
    );
  }

  // Detiene el temporizador.
  void detener() {
    temporizador?.cancel();
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
        title: const Text('Temporizador'),
      ),

      body: Center(
        child: Column(

          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            const Text(
              'Tiempo transcurrido',
              style: TextStyle(fontSize: 20),
            ),

            const SizedBox(height: 15),
            
            // Muestra los segundos.
            Text(
              '$segundos segundos',
              style: const TextStyle(
                fontSize: 40,
                fontWeight: FontWeight.bold,
                color: Colors.blue,
              ),
            ),

            const SizedBox(height: 30),

            // Ubica los botones horizontalmente.
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                ElevatedButton(
                  onPressed: iniciar,
                  child: const Text('Iniciar'),
                ),

                const SizedBox(width: 20),

                ElevatedButton(
                  onPressed: detener,
                  child: const Text('Detener'),
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}