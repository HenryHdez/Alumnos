library(tidyverse)
library(datos)
Autos=datos::millas
#Hay Otras mascaras diferentes de geom_point()

#Ejemplo
#geom_point()
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))
#geom_smooth()
ggplot(data=Autos)+
  geom_smooth(mapping = aes(x=cilindrada, y=autopista))

#Unión
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  geom_smooth(mapping = aes(x=cilindrada, y=autopista))

#clasificación
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  geom_smooth(mapping = aes(x=cilindrada, y=autopista, linetype=traccion))

#clasificación
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  geom_smooth(mapping = aes(x=cilindrada, y=autopista, linetype=traccion))
#clasificación
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  geom_smooth(mapping = aes(x=cilindrada, y=autopista, color=traccion))
#clasificación
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  geom_smooth(mapping = aes(x=cilindrada, y=autopista, group=traccion))

#clasificación
ggplot(data=Autos, mapping = aes(x=cilindrada, y=autopista))+
  geom_point(mapping = aes(color=clase))+
  geom_smooth(data = filter(Autos, clase=="suv"))
