import 'dart:io';

void main() {
  String opcion;

  do {
    print('\n--- CALCULADORA ---');
    print('1. Sumar');
    print('2. Restar');
    print('3. Multiplicar');
    print('4. Dividir');
    print('0. Salir');

    stdout.write('Seleccione una opción: ');
    opcion = stdin.readLineSync() ?? '';

    if (opcion == '0') {
      print('Programa finalizado.');
      break;
    }

    if (!['1', '2', '3', '4'].contains(opcion)) {
      print('Opción no válida.');
      continue;
    }

    double numero1 = leerNumero('Primer número: ');
    double numero2 = leerNumero('Segundo número: ');

    double? resultado;

    switch (opcion) {
      case '1':
        resultado = numero1 + numero2;
        break;

      case '2':
        resultado = numero1 - numero2;
        break;

      case '3':
        resultado = numero1 * numero2;
        break;

      case '4':
        if (numero2 == 0) {
          print('No es posible dividir entre cero.');
        } else {
          resultado = numero1 / numero2;
        }
        break;
    }

    if (resultado != null) {
      print('Resultado: $resultado');
    }
  } while (opcion != '0');
}

// Solicita un número hasta que la entrada sea válida.
double leerNumero(String mensaje) {
  while (true) {
    stdout.write(mensaje);

    String entrada = stdin.readLineSync() ?? '';
    entrada = entrada.replaceAll(',', '.');

    double? numero = double.tryParse(entrada);

    if (numero != null) {
      return numero;
    }

    print('Debe ingresar un número válido.');
  }
}