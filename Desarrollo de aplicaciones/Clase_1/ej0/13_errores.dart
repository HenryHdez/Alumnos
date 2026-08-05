import 'dart:io';

void main() {
  try {
    // Solicita el primer número.
    stdout.write('Ingrese el primer número: ');
    double numero1 = convertirNumero(
      stdin.readLineSync() ?? '',
    );

    // Solicita el segundo número.
    stdout.write('Ingrese el segundo número: ');
    double numero2 = convertirNumero(
      stdin.readLineSync() ?? '',
    );

    // Genera una excepción si se intenta dividir entre cero.
    if (numero2 == 0) {
      throw Exception('No es posible dividir entre cero.');
    }

    double resultado = numero1 / numero2;

    print('Resultado: $resultado');
  } on FormatException catch (error) {
    // Controla los errores de conversión.
    print('Error de formato: ${error.message}');
  } catch (error) {
    // Controla los demás errores.
    print('Error: $error');
  } finally {
    // Se ejecuta tanto si ocurre un error como si no.
    print('Operación finalizada.');
  }
}

// Convierte una entrada de texto en un número.
double convertirNumero(String entrada) {
  entrada = entrada.replaceAll(',', '.');

  double? numero = double.tryParse(entrada);

  if (numero == null) {
    throw const FormatException(
      'Debe ingresar un valor numérico.',
    );
  }

  return numero;
}