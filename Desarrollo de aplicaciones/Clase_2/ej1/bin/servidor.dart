import 'dart:convert';
import 'dart:io';

Future<void> main() async {
  const String ipServidor = '192.168.1.6';
  const int puerto = 4040;

  ServerSocket servidor = await ServerSocket.bind(
    ipServidor,
    puerto,
  );

  print('Servidor iniciado en:');
  print('${servidor.address.address}:${servidor.port}');

  servidor.listen((Socket cliente) {
    print(
      'Cliente conectado: '
      '${cliente.remoteAddress.address}',
    );

    cliente
        .cast<List<int>>()
        .transform(utf8.decoder)
        .transform(const LineSplitter())
        .listen(
      (String mensaje) {
        print('Mensaje: $mensaje');
        cliente.writeln('Servidor recibió: $mensaje');
      },
      onDone: () {
        print('Cliente desconectado');
        cliente.destroy();
      },
      onError: (error) {
        print('Error: $error');
        cliente.destroy();
      },
    );
  });
}