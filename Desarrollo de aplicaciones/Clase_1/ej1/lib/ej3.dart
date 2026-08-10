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
      home: PaginaPrincipal(),
    );
  }
}

class PaginaPrincipal extends StatefulWidget {
  const PaginaPrincipal({super.key});

  @override
  State<PaginaPrincipal> createState() {
    return _PaginaPrincipalState();
  }
}

class _PaginaPrincipalState extends State<PaginaPrincipal> {
  // Variables que controlan la apariencia.
  Color colorCaja = Colors.blue;
  double tamanoCaja = 150;
  double radioBorde = 0;
  String texto = 'Caja azul';

  // Cambia las propiedades visuales.
  void cambiarApariencia() {
    setState(() {
      colorCaja = Colors.orange;
      tamanoCaja = 200;
      radioBorde = 30;
      texto = 'Caja modificada';
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.grey[200],

      appBar: AppBar(
        title: const Text('Cambiar apariencia'),
        backgroundColor: Colors.blue,
        foregroundColor: Colors.white,
      ),

      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            // Container permite definir tamaño, color y bordes.
            Container(
              width: tamanoCaja,
              height: tamanoCaja,

              // Espacio interior.
              padding: const EdgeInsets.all(20),

              // Define la apariencia de la caja.
              decoration: BoxDecoration(
                color: colorCaja,
                borderRadius: BorderRadius.circular(
                  radioBorde,
                ),
                border: Border.all(
                  color: Colors.black,
                  width: 3,
                ),
              ),

              // Centra el texto dentro de la caja.
              alignment: Alignment.center,

              child: Text(
                texto,
                textAlign: TextAlign.center,

                // Apariencia del texto.
                style: const TextStyle(
                  color: Colors.white,
                  fontSize: 20,
                  fontWeight: FontWeight.bold,
                ),
              ),
            ),

            // Espacio entre la caja y el botón.
            const SizedBox(height: 30),

            ElevatedButton(
              onPressed: cambiarApariencia,

              // Apariencia del botón.
              style: ElevatedButton.styleFrom(
                backgroundColor: Colors.black,
                foregroundColor: Colors.white,
                padding: const EdgeInsets.symmetric(
                  horizontal: 25,
                  vertical: 15,
                ),
              ),

              child: const Text(
                'Cambiar apariencia',
                style: TextStyle(fontSize: 16),
              ),
            ),
          ],
        ),
      ),
    );
  }
}