library(tidyverse)
library(datos)
autos <- datos::millas
#Otros
#Diagrama de barras
ggplot(data <- autos) +
  geom_bar(mapping = aes(x = traccion))
#x muestra la etiqueta
#y la cantidad de veces que se repite x

#Identity permite asignar un conteo almacenado en una variable
x_v <- c("uno", "dos", "tres")
y_v <- c(100, 50, 300)
datos <- data.frame(Etiquetas = x_v, Valores = y_v)
ggplot(data = datos) +
  geom_bar(mapping = aes(x = Etiquetas, y = Valores), stat = "identity")

#Mostrar grafico proporcional
ggplot(data = datos) +
  geom_bar(mapping = aes(x = Etiquetas, y = stat(prop), group = 1))

#Résumen en términos del valor medio, minímo y máximo
ggplot(data <- autos) +
  stat_summary(
    mapping = aes(x = traccion, y = cilindrada),
    fun.min = min,
    fun.max = max,
    fun = median
  )

#Apariencia de los gráficos de barras
#Contorno
ggplot(data <- autos) +
  geom_bar(mapping = aes(x = autopista, colour = traccion))

#relleno
ggplot(data <- autos) +
  geom_bar(mapping = aes(x = autopista, fill = traccion))

#separar
ggplot(data <- autos) +
  geom_bar(mapping = aes(x = autopista, colour = traccion), position = "dodge")

#jitter (ruido para visualizar las clases y/o especies)
ggplot(data <- autos) +
  geom_point(mapping = aes(x = cilindrada, y = autopista), position = "jitter")
