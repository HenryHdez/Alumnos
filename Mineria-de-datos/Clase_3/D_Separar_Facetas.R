library(tidyverse)
library(datos)
#El comando face_wrap construye multiples graficos y el 
#simbolo ~ declara que la clase es una función.
Autos=datos::millas
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  facet_wrap(~ clase, nrow=2)
#nrow separa por filas, ncol por columnas (no usar al tiempo)
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  facet_wrap(~ clase, ncol=2)
#El comando formula sirve para designar variables que modelan a otras
#Ejemplo
Salida ~ Autos$cilindros
#La formula esta dada por el operador "~"
#a la izquierda está la variable de salida y a la derecha la o las
#variables a predecir. El esquema general es el siguiente:

#El "~" virgulilla debería leerse como "es modelado por" o "es mode-
#lado en función de".

#Si desea profundizar dobre el uso de este comando:
?formula

#El primer argumento de facet_grid() también corresponde a una fórmula.
#En este caso, la fórmula debe contener los nombres de variables separados 
#por una ~.
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  facet_grid(traccion ~ cilindros)

#Si prefiere no separar las facetas puede agregar un punto.
#Ejm 1
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  facet_grid(. ~ cilindros)
#Ejm 2
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  facet_grid(traccion ~ .)
