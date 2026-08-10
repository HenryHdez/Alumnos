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

class PaginaPrincipal extends StatelessWidget {
  const PaginaPrincipal({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Ubicación de elementos'),
      ),

      // Padding crea un espacio alrededor del contenido.
      body: Padding(
        padding: const EdgeInsets.all(20),

        // Column organiza los elementos verticalmente.
        child: Column(
          // Distribuye los elementos en el eje vertical.
          mainAxisAlignment: MainAxisAlignment.spaceEvenly,

          // Centra los elementos en el eje horizontal.
          crossAxisAlignment: CrossAxisAlignment.center,

          children: [
            const Text(
              'Elemento superior',
              style: TextStyle(fontSize: 20),
            ),

            // Row organiza los elementos horizontalmente.
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceAround,
              children: [
                Container(
                  width: 80,
                  height: 80,
                  color: Colors.red,
                  alignment: Alignment.center,
                  child: const Text('1'),
                ),
                Container(
                  width: 80,
                  height: 80,
                  color: Colors.green,
                  alignment: Alignment.center,
                  child: const Text('2'),
                ),
                Container(
                  width: 80,
                  height: 80,
                  color: Colors.blue,
                  alignment: Alignment.center,
                  child: const Text('3'),
                ),
              ],
            ),

            const Text(
              'Elemento inferior',
              style: TextStyle(fontSize: 20),
            ),
          ],
        ),
      ),
    );
  }
}