// Entrada de datos en Dart
import 'dart:io';

void main() {
  //Solicitar nombre de usuario
  stdout.write('Ingrese su nombre: ');
  String nombre = stdin.readLineSync() ?? '';
  //tryparse convierte el string a int
  //double.tryParse convierte el string a double
  //convertir int a string con toString()
  stdout.write('Ingrese su edad: ');
  int edad = int.tryParse(stdin.readLineSync() ?? '') ?? 0;
  
  //Publicar
  print('Hola, $nombre');
  print('Su edad es $edad');
  print('Edad en texto: ${edad.toString()}');
}