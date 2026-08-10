import 'dart:io';
//Estructuras de control de flujo
void main() {
  stdout.write('Ingrese una nota entre 0 y 5: ');
  double nota = double.tryParse(
        (stdin.readLineSync() ?? '').replaceAll(',', '.'),
      ) ??
      0;
  //>>>>>>>>>>>>>>>>>>>>Condicionales<<<<<<<<<<<<<<<<<<<<<<<<
  String estado;
  if (nota >= 3.0) {
    estado = 'Aprobado';
  } else {
    estado = 'No aprobado';
  }
  //condicion ? valorSiEsVerdadero : valorSiEsFalso
  estado = nota >= 3.0 ? 'Aprobado' : 'No aprobado';

  if (nota < 0 || nota > 5) {
    print('La nota no es válida');
  } else if (nota >= 3) {
    print('Asignatura aprobada');
  } else {
    print('Asignatura no aprobada');
  }

  //Switch
  int opcion = 2;
  switch (opcion) {
    case 1:
      print('Registrar usuario');
      break;

    case 2:
      print('Consultar usuario');
      break;

    case 3:
      print('Eliminar usuario');
      break;

    default:
      print('Opción no válida');
  }

  //try-Catch
  try {
    stdout.write('Ingrese una opción: ');
    int num1 = int.parse(stdin.readLineSync() ?? '');
    print('La opción es: $num1');  
  } catch (error) {
    print('Error: debe ingresar un número');
  }

  //>>>>>>>>>>>>>>>>>>>>Iterativas<<<<<<<<<<<<<<<<<<<<<<<<
  // For
  for (int i = 1; i <= 5; i++) {
    print('Iteración: $i');
  }

  List<String> nombres = ['Ana', 'Luis', 'Marta'];
  for (String nombre in nombres) {
    print(nombre);
  }

  nombres.forEach((nombre) {
    print(nombre);
  });

  //while
  int contador = 1;
  while (contador <= 3) {
    print('Contador: $contador');
    contador++;
  }
}