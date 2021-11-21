library(tidyverse)
library(datos)
Autos=datos::millas
#Otros
#Diagrama de barras
ggplot(data = Autos, mapping = aes(x = traccion, y = cilindrada)) +
  geom_boxplot()

#Diagrama de barras
ggplot(data = Autos, mapping = aes(x = traccion, y = cilindrada)) +
  geom_boxplot()+
  coord_flip()

barras = ggplot(data = Autos)+
  geom_bar(
    mapping = aes(x = autopista, fill = traccion),
    show.legend = FALSE,
    width = 1
  ) +
  theme(aspect.ratio = 1)+
  labs(x = NULL, y = NULL)

barras + coord_flip()

barras + coord_polar()
