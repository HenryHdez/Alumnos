import 'dart:io';

Future<void> main() async {
  File archivo = File('mensaje.txt');

  // Crea el archivo y escribe información.
  await archivo.writeAsString('Hola desde Dart\n');

  // Agrega contenido sin borrar el anterior.
  await archivo.writeAsString(
    'Segunda línea\n',
    mode: FileMode.append,
  );

  // Lee todo el contenido.
  String contenido = await archivo.readAsString();

  print(contenido);
}