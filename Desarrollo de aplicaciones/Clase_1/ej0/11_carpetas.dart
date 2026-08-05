import 'dart:io';

Future<void> main() async {
  Directory carpeta = Directory('datos');

  if (!await carpeta.exists()) {
    await carpeta.create();
    print('Carpeta creada.');
  }

  await for (FileSystemEntity elemento in carpeta.list()) {
    print(elemento.path);
  }
}