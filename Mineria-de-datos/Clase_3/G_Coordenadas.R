library(tidyverse)
library(datos)
autos <- datos::millas
#Otros
#Diagrama de barras
ggplot(data = Autos, mapping = aes(x = traccion, y = cilindrada)) +
  geom_boxplot()

#Diagrama de barras
ggplot(data = Autos, mapping = aes(x = traccion, y = cilindrada)) +
  geom_boxplot() +
  coord_flip()

#La información de un gráfico se puede almacenar en una variable
barras <- ggplot(data = autos) +
  geom_bar(
    mapping = aes(x = autopista, fill = traccion),
    show.legend = FALSE,
    width = 1
  ) +
  theme(aspect.ratio = 1)+
  labs(x = NULL, y = NULL)

#y asignar las mascaras que desee
#Rotar
barras + coord_flip()
#Cambiar sistema de coordenadas
barras + coord_polar()

