#Importe las siguientes librerías
library(tidyverse)
library(datos)
#Ejemplo
Autos=datos::millas
#Clasificación por color
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista, color=clase))
#Otras formas de clasificación en ggplot
#Tamaño
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista, size=clase))
#Escala de grises
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista, alpha=clase))
#Geometría
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista, shape=clase))
#Cambiar color
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista), color="blue")
#Agrupar por clase
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista, color="blue"))
#Otras formas de figura geométrica
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista),
             shape=0, size=5, fill="red")


