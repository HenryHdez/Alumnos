library(tidyverse)
library(datos)
autos <- datos::millas
#Otras mascaras diferentes de geom_point ()

#Ejemplo
#geom_point ()
ggplot(data <- autos) +
  geom_point(mapping = aes(x = cilindrada, y = autopista))
#geom_smooth ()
ggplot(data <- autos) +
  geom_smooth(mapping = aes(x = cilindrada, y = autopista))

#Es posible graficar varias mascaras en el mismo gráfico usando +
ggplot(data <- autos) +
  geom_point(mapping = aes(x = cilindrada, y = autopista)) +
  geom_smooth(mapping = aes(x = cilindrada, y = autopista))

#Asigne una linea de tendencía por clase
ggplot(data <- autos) +
  geom_point(mapping = aes(x = cilindrada, y = autopista)) +
  geom_smooth(mapping = aes(x = cilindrada, y = autopista, linetype = traccion))

#Hay varías formas de presentar las lineas de tendencia
#Por contorno
ggplot(data <- autos) +
  geom_point(mapping = aes(x = cilindrada, y = autopista)) +
  geom_smooth(mapping = aes(x = cilindrada, y = autopista, linetype = traccion))
#Por color
ggplot(data <- autos) +
  geom_point(mapping = aes(x = cilindrada, y = autopista)) +
  geom_smooth(mapping = aes(x = cilindrada, y = autopista, color = traccion))
#Area de influencia
ggplot(data <- autos) +
  geom_point(mapping = aes(x = cilindrada, y = autopista)) +
  geom_smooth(mapping = aes(x = cilindrada, y = autopista, group = traccion))

#Las mascaras se pueden aplicar sobre atributos fijos. Por ejm.
ggplot(data <- autos, mapping = aes(x = cilindrada, y = autopista)) +
  geom_point() +
  geom_smooth()
#Agregue algunas características
ggplot(data <- autos, mapping = aes(x = cilindrada, y = autopista)) +
  geom_point(mapping = aes(color = clase)) +
  geom_smooth(mapping = aes(group = clase))

#El filtro presenta la información seleccionada. En este caso solo la línea SUV
ggplot(data <- autos, mapping = aes(x = cilindrada, y = autopista)) +
  geom_point(mapping = aes(color = clase)) +
  geom_smooth(data = filter(autos, clase == "suv"))
