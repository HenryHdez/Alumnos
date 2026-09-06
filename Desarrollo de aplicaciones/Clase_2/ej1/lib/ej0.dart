//Ejecutar: flutter pub add vibration
import 'package:flutter/material.dart';
import 'package:vibration/vibration.dart';

void main() {
  runApp(const MiApp());
}

class MiApp extends StatelessWidget {
  const MiApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Vibración'),
        ),
        body: Center(
          child: ElevatedButton(
            onPressed: () async {
              await Vibration.vibrate(
                duration: 500,
              );
            },
            child: const Text('Vibrar'),
          ),
        ),
      ),
    );
  }
}