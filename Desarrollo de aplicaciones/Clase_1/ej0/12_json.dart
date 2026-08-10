import 'dart:convert';
import 'dart:io';

Future<void> main() async {
  Map<String, dynamic> estudiante = {
    'nombre': 'Ana',
    'edad': 20,
    'notas': [4.0, 3.5, 4.8],
  };
  String json = jsonEncode(estudiante);

  await File('estudiante.json').writeAsString(json);
  String contenido =
      await File('estudiante.json').readAsString();

  Map<String, dynamic> datos = jsonDecode(contenido);
  print('Nombre: ${datos['nombre']}');
  print('Notas: ${datos['notas']}');
}