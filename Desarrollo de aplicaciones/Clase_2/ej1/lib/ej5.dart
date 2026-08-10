// Abra la carpeta android/app/src/main/AndroidManifest.xml
// Agregar en la linea el permiso INTERNET
// <uses-permission android:name="android.permission.INTERNET"/>
import 'dart:convert';
import 'dart:io';
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
      home: ClienteTCP(),
    );
  }
}

class ClienteTCP extends StatefulWidget {
  const ClienteTCP({super.key});

  @override
  State<ClienteTCP> createState() {
    return _ClienteTCPState();
  }
}

class _ClienteTCPState extends State<ClienteTCP> {
  // Controladores de las entradas.
  final TextEditingController controladorIP =
      TextEditingController(text: '192.168.1.6');

  final TextEditingController controladorMensaje =
      TextEditingController();

  // Conexión con el servidor.
  Socket? socket;

  // Mensajes mostrados en la pantalla.
  String estado = 'Desconectado';
  String respuesta = 'Sin respuesta';

  bool get conectado => socket != null;

  // Conecta la aplicación con el servidor.
  Future<void> conectar() async {
    if (conectado) {
      return;
    }

    String ip = controladorIP.text.trim();

    if (ip.isEmpty) {
      setState(() {
        estado = 'Debe ingresar la dirección IP';
      });
      return;
    }

    setState(() {
      estado = 'Conectando...';
    });

    try {
      Socket nuevaConexion = await Socket.connect(
        ip,
        4040,
        timeout: const Duration(seconds: 5),
      );

      socket = nuevaConexion;

      setState(() {
        estado = 'Conectado a $ip:4040';
      });

      // Escucha las respuestas enviadas por el servidor.
      nuevaConexion.listen(
        (List<int> datos) {
          String mensaje = utf8.decode(datos).trim();

          if (!mounted) {
            return;
          }

          setState(() {
            respuesta = mensaje;
          });
        },

        onDone: () {
          socket = null;

          if (!mounted) {
            return;
          }

          setState(() {
            estado = 'El servidor cerró la conexión';
          });
        },

        onError: (error) {
          socket = null;

          if (!mounted) {
            return;
          }

          setState(() {
            estado = 'Error de comunicación';
          });
        },
      );
    } catch (error) {
      socket = null;

      setState(() {
        estado = 'No fue posible conectar';
      });
    }
  }

  // Envía el texto escrito al servidor.
  void enviar() {
    if (!conectado) {
      setState(() {
        estado = 'Primero debe conectarse';
      });
      return;
    }

    //.trim() elimina los espacios en blanco al inicio y al final del texto.
    String mensaje = controladorMensaje.text.trim();

    if (mensaje.isEmpty) {
      setState(() {
        estado = 'Debe escribir un mensaje';
      });
      return;
    }
    // ! Operador de negación, verifica si socket es nulo.
    // writeln envía el texto con un salto de línea.
    socket!.writeln(mensaje);

    setState(() {
      estado = 'Mensaje enviado';
    });

    controladorMensaje.clear();
  }

  // Cierra la conexión.
  void desconectar() {
    socket?.destroy();
    socket = null;

    setState(() {
      estado = 'Desconectado';
    });
  }

  @override
  void dispose() {
    socket?.destroy();
    controladorIP.dispose();
    controladorMensaje.dispose();

    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Cliente TCP'),
        backgroundColor: Colors.blue,
        foregroundColor: Colors.white,
      ),

      body: SingleChildScrollView(
        padding: const EdgeInsets.all(20),

        child: Column(
          children: [
            // Dirección IP del servidor.
            TextField(
              controller: controladorIP,
              keyboardType: TextInputType.number,
              decoration: const InputDecoration(
                labelText: 'Dirección IP del servidor',
                border: OutlineInputBorder(),
              ),
            ),

            const SizedBox(height: 15),

            // Mensaje que será enviado.
            TextField(
              controller: controladorMensaje,
              decoration: const InputDecoration(
                labelText: 'Mensaje',
                border: OutlineInputBorder(),
              ),
            ),

            const SizedBox(height: 20),

            // Botones de conexión y desconexión.
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                ElevatedButton(
                  onPressed: conectado ? null : conectar,
                  child: const Text('Conectar'),
                ),

                const SizedBox(width: 10),

                ElevatedButton(
                  onPressed: conectado ? enviar : null,
                  child: const Text('Enviar'),
                ),

                const SizedBox(width: 10),

                ElevatedButton(
                  onPressed: conectado ? desconectar : null,
                  child: const Text('Desconectar'),
                ),
              ],
            ),

            const SizedBox(height: 30),

            Text(
              'Estado: $estado',
              textAlign: TextAlign.center,
              style: const TextStyle(
                fontSize: 18,
                fontWeight: FontWeight.bold,
              ),
            ),

            const SizedBox(height: 20),

            const Text(
              'Respuesta del servidor:',
              style: TextStyle(fontSize: 18),
            ),

            const SizedBox(height: 10),

            Text(
              respuesta,
              textAlign: TextAlign.center,
              style: const TextStyle(
                fontSize: 20,
                color: Colors.blue,
              ),
            ),
          ],
        ),
      ),
    );
  }
}