void main() {
  Estudiante estudiante1 = Estudiante(
    nombre: 'Ana',
    nota: 4.2,
  );
  estudiante1.mostrarInformacion();
  print('Estado: ${estudiante1.obtenerEstado()}');
}

class Estudiante {
  String nombre;
  double nota;

  Estudiante({
    required this.nombre,
    required this.nota,
  });

  void mostrarInformacion() {
    print('Nombre: $nombre');
    print('Nota: $nota');
  }

  String obtenerEstado() {
    if (nota >= 3) {
      return 'Aprobado';
    }
    return 'No aprobado';
  }
}