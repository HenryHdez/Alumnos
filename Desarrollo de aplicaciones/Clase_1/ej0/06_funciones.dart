void main() {
  double resultado = calcularPromedio(4.0, 3.5, 5.0);
  print('Promedio: ${resultado.toStringAsFixed(2)}');
  if (resultado >= 3) {
    mostrarMensaje('Asignatura aprobada');
  } else {
    mostrarMensaje('Asignatura no aprobada');
  }
}

// Con parámetros de entrada.
double calcularPromedio(
  double nota1,
  double nota2,
  double nota3,
) {
  return (nota1 + nota2 + nota3) / 3;
}

// Asignación directa.
void mostrarMensaje(String mensaje) {
  print(mensaje);
}