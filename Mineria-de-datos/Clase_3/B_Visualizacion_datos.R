#Importe las siguientes librerías
library(tidyverse)
library(datos)
#---Algunos paquetes requeridos estan en tidyverse---
#v ggplot2 3.3.5     v purrr   0.3.4
#v tibble  3.1.5     v dplyr   1.0.7
#v tidyr   1.1.4     v stringr 1.4.0
#v readr   2.0.2     v forcats 0.5.1
#La procedencia de una función o conjunto de datos se
#establece con ->>paquete::función()<<-
#Ejemplo
autos <- datos::millas
view(autos)
#Creación de un gráfico con ggplot
ggplot(data <- autos) +
            geom_point(mapping = aes(x = cilindrada, y = autopista))
#Ejercicio
ggplot(data <- millas)
#Ayuda (Información complementaria del conjunto de datos)
?millas

#La librería datos contiene conjuntos de datos de prueba
#Ejemplo
autos <- datos::millas
view(autos)