// Ejecute: flutter pub add sensors_plus
// Ejecute: flutter pub get
import 'dart:async';
import 'package:flutter/material.dart';
import 'package:sensors_plus/sensors_plus.dart';

void main() {
  runApp(const MiApp());
}

class MiApp extends StatelessWidget {
  const MiApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      debugShowCheckedModeBanner: false,
      home: PaginaSensores(),
    );
  }
}

class PaginaSensores extends StatefulWidget {
  const PaginaSensores({super.key});

  @override
  State<PaginaSensores> createState() {
    return _PaginaSensoresState();
  }
}

class _PaginaSensoresState extends State<PaginaSensores> {
  // Valores del acelerómetro.
  double acelerometroX = 0;
  double acelerometroY = 0;
  double acelerometroZ = 0;

  // Valores del giroscopio.
  double giroscopioX = 0;
  double giroscopioY = 0;
  double giroscopioZ = 0;

  // Suscripciones a los flujos de los sensores.
  StreamSubscription<AccelerometerEvent>? suscripcionAcelerometro;
  StreamSubscription<GyroscopeEvent>? suscripcionGiroscopio;

  // Indica si los sensores están funcionando.
  bool leyendo = false;
  String mensaje = 'Presione Iniciar';

  // Inicia la lectura de los dos sensores.
  void iniciarSensores() {
    if (leyendo) {
      return;
    }

    setState(() {
      leyendo = true;
      mensaje = 'Leyendo sensores...';
    });

    // Lectura del acelerómetro.
    suscripcionAcelerometro = accelerometerEvents.listen(
      (AccelerometerEvent evento) {
        if (!mounted) {
          return;
        }

        setState(() {
          acelerometroX = evento.x;
          acelerometroY = evento.y;
          acelerometroZ = evento.z;
        });
      },
      onError: (error) {
        if (!mounted) {
          return;
        }

        setState(() {
          mensaje = 'Acelerómetro no disponible';
        });
      },
      cancelOnError: true,
    );

    // Lectura del giroscopio.
    suscripcionGiroscopio = gyroscopeEvents.listen(
      (GyroscopeEvent evento) {
        if (!mounted) {
          return;
        }

        setState(() {
          giroscopioX = evento.x;
          giroscopioY = evento.y;
          giroscopioZ = evento.z;
        });
      },
      onError: (error) {
        if (!mounted) {
          return;
        }

        setState(() {
          mensaje = 'Giroscopio no disponible';
        });
      },
      cancelOnError: true,
    );
  }

  // Detiene la lectura.
  void detenerSensores() {
    suscripcionAcelerometro?.cancel();
    suscripcionGiroscopio?.cancel();

    suscripcionAcelerometro = null;
    suscripcionGiroscopio = null;

    setState(() {
      leyendo = false;
      mensaje = 'Lectura detenida';
    });
  }

  @override
  void dispose() {
    // Detiene los sensores al cerrar la aplicación.
    suscripcionAcelerometro?.cancel();
    suscripcionGiroscopio?.cancel();

    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Sensores del celular'),
        backgroundColor: Colors.blue,
        foregroundColor: Colors.white,
      ),

      body: Padding(
        padding: const EdgeInsets.all(20),

        child: Column(
          children: [
            // Estado de la lectura.
            Text(
              mensaje,
              style: const TextStyle(
                fontSize: 18,
                fontWeight: FontWeight.bold,
              ),
            ),

            const SizedBox(height: 20),

            // Presentación del acelerómetro.
            TarjetaSensor(
              titulo: 'Acelerómetro',
              unidad: 'm/s²',
              color: Colors.blue,
              x: acelerometroX,
              y: acelerometroY,
              z: acelerometroZ,
            ),

            const SizedBox(height: 20),

            // Presentación del giroscopio.
            TarjetaSensor(
              titulo: 'Giroscopio',
              unidad: 'rad/s',
              color: Colors.orange,
              x: giroscopioX,
              y: giroscopioY,
              z: giroscopioZ,
            ),

            const SizedBox(height: 30),

            // Botones de control.
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                ElevatedButton(
                  onPressed: iniciarSensores,
                  child: const Text('Iniciar'),
                ),

                const SizedBox(width: 20),

                ElevatedButton(
                  onPressed: detenerSensores,
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

// Widget reutilizable para presentar un sensor.
class TarjetaSensor extends StatelessWidget {
  final String titulo;
  final String unidad;
  final Color color;
  final double x;
  final double y;
  final double z;

  const TarjetaSensor({
    super.key,
    required this.titulo,
    required this.unidad,
    required this.color,
    required this.x,
    required this.y,
    required this.z,
  });

  @override
  Widget build(BuildContext context) {
    return Card(
      elevation: 4,

      child: Padding(
        padding: const EdgeInsets.all(20),

        child: Column(
          children: [
            Text(
              titulo,
              style: TextStyle(
                fontSize: 24,
                fontWeight: FontWeight.bold,
                color: color,
              ),
            ),

            const SizedBox(height: 15),

            Text(
              'X: ${x.toStringAsFixed(2)} $unidad',
              style: const TextStyle(fontSize: 19),
            ),

            Text(
              'Y: ${y.toStringAsFixed(2)} $unidad',
              style: const TextStyle(fontSize: 19),
            ),

            Text(
              'Z: ${z.toStringAsFixed(2)} $unidad',
              style: const TextStyle(fontSize: 19),
            ),
          ],
        ),
      ),
    );
  }
}