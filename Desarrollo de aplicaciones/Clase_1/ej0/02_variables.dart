void main() {
  // Declaración de variables en Dart.
  String nombre = 'Ana';
  int edad = 20;
  double nota = 4.5;
  bool activo = true;

  //var declara variables sin especificar el tipo de dato.
  var ciudad = 'Bogota';

  //dinamic permite cambiar el tipo de dato de la variable.
  dynamic variableDinamica = 'Hola';
  variableDinamica = 10;

  //Valores anidados (Cualquier tipo de dato)
  ({String name, double def}) estudiante = (name: 'Ana', def: 4.5);

  // Map (Pares clave-valor)
  Map<String, dynamic> estudiant = {
    'nombre': 'Ana',
    'edad': 20,
    'nota': 4.5,
  };
  // Modificar un valor.
  estudiant['nota'] = 4.8;
  // Agregar una nueva entrada.
  estudiant['activo'] = true;
  // Eliminar una entrada.
  estudiant.remove('edad');
  
  print('Nombre: $nombre');
  print('Edad: $edad');
  print('Nota: $nota');
  print('Activo: $activo');
  print('Ciudad: $ciudad');
  print('Variable dinámica: $variableDinamica');
  print('Estudiante: ${estudiante.name}, Nota: ${estudiante.def}');
}
