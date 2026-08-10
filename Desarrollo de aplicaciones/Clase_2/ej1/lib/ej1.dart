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
      home: PaginaDibujo(),
    );
  }
}

class PaginaDibujo extends StatelessWidget {
  const PaginaDibujo({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Figuras geométricas'),
      ),

      body: Center(
        // Define el tamaño del área de dibujo.
        child: SizedBox(
          width: 350,
          height: 500,

          // CustomPaint crea el área de dibujo.
          child: CustomPaint(
            painter: DibujanteFiguras(),
          ),
        ),
      ),
    );
  }
}

// Clase encargada de realizar los dibujos.
class DibujanteFiguras extends CustomPainter {
  @override
  void paint(Canvas canvas, Size size) {
    // Configuración general del pincel.
    // .. operador en cascada para establecer múltiples propiedades.
    Paint pincel = Paint()
      ..color = Colors.blue
      ..strokeWidth = 5
      ..style = PaintingStyle.fill;
    //DIBUJAR UNA LÍNEA
    pincel.color = Colors.black;
    pincel.strokeWidth = 4;
    canvas.drawLine(
      const Offset(30, 40),  // Punto inicial.
      const Offset(300, 40), // Punto final.
      pincel,
    );
    //DIBUJAR UN RECTÁNGULO
    pincel.color = Colors.blue;
    pincel.style = PaintingStyle.fill;
    canvas.drawRect(
      const Rect.fromLTWH(
        40,  // Posición horizontal.
        80,  // Posición vertical.
        120, // Ancho.
        80,  // Alto.
      ),
      pincel,
    );
    //DIBUJAR UN CÍRCULO
    pincel.color = Colors.red;
    canvas.drawCircle(
      const Offset(250, 120), // Centro del círculo.
      45,                     // Radio.
      pincel,
    );
    //DIBUJAR UN RECTÁNGULO CON BORDE
    pincel
      ..color = Colors.green
      ..style = PaintingStyle.stroke
      ..strokeWidth = 5;
    canvas.drawRect(
      const Rect.fromLTWH(
        40,
        210,
        120,
        80,
      ),
      pincel,
    );
    //DIBUJAR UN ÓVALO
    pincel
      ..color = Colors.orange
      ..style = PaintingStyle.fill;
    canvas.drawOval(
      const Rect.fromLTWH(
        200,
        210,
        120,
        80,
      ),
      pincel,
    );

  }

  @override
  bool shouldRepaint(
    covariant CustomPainter oldDelegate,
  ) {
    return false;
  }
}