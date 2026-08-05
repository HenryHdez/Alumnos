import 'package:flutter/material.dart';

void main() {
  runApp(const MiApp());
}

// Permite que la pantalla cambie durante la ejecución.
class MiApp extends StatefulWidget {
  const MiApp({super.key});

  @override
  State<MiApp> createState() => _MiAppState();
}

// Contiene los datos que pueden cambiar.
class _MiAppState extends State<MiApp> {
  // Guarda el nombre ingresado por el usuario.
  String nombre = '';

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        // Agrega espacio alrededor del contenido.
        body: Padding(
          padding: const EdgeInsets.all(30),

          // Organiza los elementos verticalmente.
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              // Campo de entrada de texto.
              TextField(
                // Guarda el contenido escrito.
                onChanged: (texto) {
                  nombre = texto;
                },
                decoration: const InputDecoration(
                  labelText: 'Escriba su nombre',
                ),
              ),

              // Agrega separación vertical.
              const SizedBox(height: 20),

              // Botón para mostrar el resultado.
              ElevatedButton(
                onPressed: () {
                  // Actualiza la interfaz.
                  setState(() {});
                },
                child: const Text('Saludar'),
              ),

              const SizedBox(height: 20),

              // Muestra el nombre ingresado.
              Text('Hola, $nombre'),
            ],
          ),
        ),
      ),
    );
  }
}