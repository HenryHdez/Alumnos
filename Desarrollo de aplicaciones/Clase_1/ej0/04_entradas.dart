import 'dart:io';

void main() {
  stdout.write('Ingrese su nombre: ');
  String nombre = stdin.readLineSync() ?? '';

  stdout.write('Ingrese su edad: ');
  int edad = int.tryParse(stdin.readLineSync() ?? '') ?? 0;

  print('Hola, $nombre');
  print('Su edad es $edad');
}