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
      home: PaginaMovimiento(),
    );
  }
}

class PaginaMovimiento extends StatefulWidget {
  const PaginaMovimiento({super.key});

  @override
  State<PaginaMovimiento> createState() {
    return _PaginaMovimientoState();
  }
}

class _PaginaMovimientoState extends State<PaginaMovimiento> {
  double posicionX = 175;
  final double anchoCanvas = 350;
  final double radioBolita = 20;
  final double desplazamiento = 20;

  void moverIzquierda() {
    //setState notifica a Flutter que el estado del widget ha cambiado.
    setState(() {
      posicionX -= desplazamiento;
      if (posicionX < radioBolita) {
        posicionX = radioBolita;
      }
    });
  }

  void moverDerecha() {
    setState(() {
      posicionX += desplazamiento;
      if (posicionX > anchoCanvas - radioBolita) {
        posicionX = anchoCanvas - radioBolita;
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Mover una bolita'),
      ),

      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            // Área de dibujo.
            Container(
              width: anchoCanvas,
              height: 200,
              decoration: BoxDecoration(
                color: Colors.grey[200],
                border: Border.all(
                  color: Colors.black,
                  width: 2,
                ),
              ),

              child: CustomPaint(
                painter: DibujanteBolita(
                  posicionX: posicionX,
                ),
              ),
            ),

            const SizedBox(height: 20),
            // Botones debajo del Canvas.
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                ElevatedButton.icon(
                  onPressed: moverIzquierda,
                  icon: const Icon(Icons.arrow_left),
                  label: const Text('Izquierda'),
                ),

                const SizedBox(width: 20),

                ElevatedButton.icon(
                  onPressed: moverDerecha,
                  icon: const Icon(Icons.arrow_right),
                  label: const Text('Derecha'),
                ),
              ],
            ),

            const SizedBox(height: 15),

            // Muestra la posición horizontal.
            Text(
              'Posición X: ${posicionX.toStringAsFixed(0)}',
              style: const TextStyle(fontSize: 18),
            ),
          ],
        ),
      ),
    );
  }
}

// Clase encargada de dibujar la bolita.
class DibujanteBolita extends CustomPainter {
  // Recibe la posición desde la pantalla.
  final double posicionX;

  DibujanteBolita({
    required this.posicionX,
  });

  @override
  void paint(Canvas canvas, Size size) {
    // Configura el pincel.
    Paint pincel = Paint()
      ..color = Colors.blue
      ..style = PaintingStyle.fill;

    // Dibuja la bolita.
    canvas.drawCircle(
      Offset(
        posicionX,     
        size.height / 2, 
      ),
      20, // Radio.
      pincel,
    );
  }

  @override
  bool shouldRepaint(
    covariant DibujanteBolita oldDelegate,
  ) {
    // Redibuja si cambia la posición.
    return posicionX != oldDelegate.posicionX;
  }
}