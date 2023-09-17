# Cargando el paquete dplyr
library(dplyr)

# Creando un data frame con información de estudiantes
estudiantes <- data.frame(
  id_estudiante = c(1, 2, 3, 4),
  nombre = c("Ana", "Luis", "Carlos", "María")
)
print(estudiantes)
# Creando un data frame con calificaciones
calificaciones <- data.frame(
  id_estudiante = c(2, 3, 4, 5),
  calificacion = c(85, 90, 88, 72)
)
print(calificaciones)
# Utilizando la función `left_join` para unir 
#los data frames basándose en el ID del estudiante
resultado <- left_join(estudiantes, calificaciones, by = "id_estudiante")

print(resultado)

