#Importe las siguientes librer�as
library(tidyverse)
library(datos)
#---Algunos paquetes requeridos estan en tidyverse---
#v ggplot2 3.3.5     v purrr   0.3.4
#v tibble  3.1.5     v dplyr   1.0.7
#v tidyr   1.1.4     v stringr 1.4.0
#v readr   2.0.2     v forcats 0.5.1
#La procedencia de una funci�n o conjunto de datos se
#establece con ->>paquete::funci�n()<<-
#Ejemplo
Autos=datos::millas
view(Autos)
#Creaci�n de un gr�fico con ggplot
ggplot(data=Autos)+geom_point(mapping = aes(x=cilindrada, y=autopista))
#Ejercicio
ggplot(data=millas)
#Ayuda
?millas
