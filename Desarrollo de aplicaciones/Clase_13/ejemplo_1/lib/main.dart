import 'package:flutter/material.dart';

void main() {
  runApp(const MiAplicacion());
}

class MiAplicacion extends StatelessWidget {
  const MiAplicacion({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Mi primera página',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(
          seedColor: Colors.blue,
        ),
      ),
      home: const PaginaPrincipal(),
    );
  }
}

class PaginaPrincipal extends StatelessWidget {
  const PaginaPrincipal({super.key});

  @override
  Widget build(BuildContext context) {
    // Variables de la página
    const String nombre = 'Henry';
    const int numeroCursos = 3;
    const double promedio = 4.5;
    const bool activo = true;

    const List<String> cursos = [
      'Redes de datos',
      'Programación',
      'Bases de datos',
    ];

    return Scaffold(
      appBar: AppBar(
        title: const Text('Mi primera aplicación'),
        backgroundColor: Colors.blue,
        foregroundColor: Colors.white,
      ),
      body: Padding(
        padding: const EdgeInsets.all(24),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            const Text(
              'Información personal',
              style: TextStyle(
                fontSize: 28,
                fontWeight: FontWeight.bold,
              ),
            ),
            const SizedBox(height: 20),

            Text(
              'Nombre: $nombre',
              style: const TextStyle(fontSize: 18),
            ),

            Text(
              'Cantidad de cursos: $numeroCursos',
              style: const TextStyle(fontSize: 18),
            ),

            Text(
              'Promedio: $promedio',
              style: const TextStyle(fontSize: 18),
            ),

            Text(
              'Estado: ${activo ? "Activo" : "Inactivo"}',
              style: const TextStyle(fontSize: 18),
            ),

            const SizedBox(height: 20),

            const Text(
              'Cursos:',
              style: TextStyle(
                fontSize: 20,
                fontWeight: FontWeight.bold,
              ),
            ),

            for (String curso in cursos)
              Text(
                '• $curso',
                style: const TextStyle(fontSize: 18),
              ),
          ],
        ),
      ),
    );
  }
}