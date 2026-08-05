import 'dart:io';

void main() {
  stdout.write('Ingrese una nota entre 0 y 5: ');
  double nota = double.tryParse(
        (stdin.readLineSync() ?? '').replaceAll(',', '.'),
      ) ??
      0;

  if (nota < 0 || nota > 5) {
    print('La nota no es válida');
  } else if (nota >= 3) {
    print('Asignatura aprobada');
  } else {
    print('Asignatura no aprobada');
  }

  // Repite cinco veces.
  for (int i = 1; i <= 5; i++) {
    print('Iteración: $i');
  }

  int contador = 1;

  // Repite mientras la condición sea verdadera.
  while (contador <= 3) {
    print('Contador: $contador');
    contador++;
  }

}