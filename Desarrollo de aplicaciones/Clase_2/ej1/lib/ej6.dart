import 'package:flutter/material.dart';

void main() {
  runApp(const MiApp());
}

// Configuración general de la aplicación.
class MiApp extends StatelessWidget {
  const MiApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      debugShowCheckedModeBanner: false,
      home: PantallaInicio(),
    );
  }
}

// PRIMERA PANTALLA

class PantallaInicio extends StatelessWidget {
  const PantallaInicio({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Pantalla de inicio'),
        backgroundColor: Colors.blue,
        foregroundColor: Colors.white,
      ),

      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            const Icon(
              Icons.home,
              size: 100,
              color: Colors.blue,
            ),

            const SizedBox(height: 20),

            const Text(
              'Esta es la primera pantalla',
              style: TextStyle(fontSize: 22),
            ),

            const SizedBox(height: 30),

            ElevatedButton(
              onPressed: () {
                // Abre la segunda pantalla.
                Navigator.push(
                  context,

                  // Define la pantalla que se abrirá.
                  MaterialPageRoute(
                    builder: (context) {
                      return const PantallaDetalles();
                    },
                  ),
                );
              },
              child: const Text('Ir a detalles'),
            ),
          ],
        ),
      ),
    );
  }
}

// SEGUNDA PANTALLA

class PantallaDetalles extends StatelessWidget {
  const PantallaDetalles({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Pantalla de detalles'),
        backgroundColor: Colors.orange,
        foregroundColor: Colors.white,
      ),

      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            const Icon(
              Icons.info,
              size: 100,
              color: Colors.orange,
            ),

            const SizedBox(height: 20),

            const Text(
              'Esta es la segunda pantalla',
              style: TextStyle(fontSize: 22),
            ),

            const SizedBox(height: 30),

            ElevatedButton(
              onPressed: () {
                // Cierra esta pantalla y regresa a la anterior.
                Navigator.pop(context);
              },
              child: const Text('Regresar'),
            ),
          ],
        ),
      ),
    );
  }
}