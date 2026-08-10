import 'dart:io';
//Señala que la función terminará en el futuro y no devolverá un valor
/*
Future<void> main() async {
  File archivo = File('mensaje.txt');
  //await espera a que termine antes de continuar
  await archivo.writeAsString('Hola desde Dart\n');
  await archivo.writeAsString(
    'Segunda línea\n',
    mode: FileMode.append,
  );
  String contenido = await archivo.readAsString();
  print(contenido);
}
*/
//Normal
void main() {
  File archivo = File('mensaje.txt');
  archivo.writeAsStringSync('Hola desde Dart\n');
  archivo.writeAsStringSync(
    'Segunda línea\n',
    mode: FileMode.append,
  );
  String contenido = archivo.readAsStringSync();
  print(contenido);
}