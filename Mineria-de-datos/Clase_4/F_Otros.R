library(tidyverse)
library(datos)
Autos=datos::millas
#Otros
#Diagrama de barras
ggplot(data = Autos) +
  geom_bar(mapping = aes(x = traccion))
#x muestra la etiqueta
#y la cantidad de veces que se repite x

#Identity permite asignar un conteo almacenado en una variable
x_v=c("uno", "dos", "tres")
y_v=c(100,50,300)
Datos=data.frame(Etiquetas=x_v, Valores=y_v)
ggplot(data = Datos)+
  geom_bar(mapping = aes(x=Etiquetas, y=Valores), stat="identity")


ggplot(data=Autos)+
  stat_summary(
    mapping = aes(x = traccion, y = cilindrada),
    fun.min = min,
    fun.max = max,
    fun = median
  )

#Contorno
ggplot(data = Autos) +
  geom_bar(mapping = aes(x = autopista, colour= traccion))

#relleno
ggplot(data = Autos) +
  geom_bar(mapping = aes(x = autopista, fill= traccion))

#separar
ggplot(data = Autos) +
  geom_bar(mapping = aes(x = autopista, colour= traccion), position = "dodge")

#jitter
ggplot(data = Autos) +
  geom_point(mapping = aes(x = cilindrada, y = autopista), position = "jitter")
