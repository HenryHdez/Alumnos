import 'package:flutter/material.dart';

// Punto de entrada.
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
      home: PaginaPrincipal(),
    );
  }
}

// Pantalla que puede cambiar.
class PaginaPrincipal extends StatefulWidget {
  const PaginaPrincipal({super.key});

  @override
  State<PaginaPrincipal> createState() {
    return _PaginaPrincipalState();
  }
}

// Datos y comportamiento de la pantalla.
class _PaginaPrincipalState extends State<PaginaPrincipal> {
  // Definir variables.
  String entrada = '';
  String salida = 'Sin mensaje';

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      // Barra superior.
      appBar: AppBar(
        title: const Text('Titulo cualquiera'),
      ),

      // Contenido principal.
      body: Padding(
        padding: const EdgeInsets.all(20),

        child: Column(
          children: [
            // Entrada.
            TextField(
              onChanged: (texto) {
                entrada = texto;
              },
            ),

            // Botón.
            ElevatedButton(
              onPressed: () {
                setState(() {
                  salida = entrada;
                });
              },
              child: const Text('Mostrar'),
            ),

            // Salida.
            Text(salida),
          ],
        ),
      ),
    );
  }
}