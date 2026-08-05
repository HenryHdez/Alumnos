void main() {
  List<double> notas = [4.0, 3.5, 2.8, 4.7];

  double suma = 0;

  for (double nota in notas) {
    print('Nota: $nota');
    suma += nota;
  }

  double promedio = suma / notas.length;

  print('Cantidad de notas: ${notas.length}');
  print('Promedio: ${promedio.toStringAsFixed(2)}');
}