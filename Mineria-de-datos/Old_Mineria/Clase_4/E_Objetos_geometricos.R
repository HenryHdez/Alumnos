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

#Uni�n
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  geom_smooth(mapping = aes(x=cilindrada, y=autopista))

#clasificaci�n
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  geom_smooth(mapping = aes(x=cilindrada, y=autopista, linetype=traccion))

#clasificaci�n
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  geom_smooth(mapping = aes(x=cilindrada, y=autopista, linetype=traccion))
#clasificaci�n
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  geom_smooth(mapping = aes(x=cilindrada, y=autopista, color=traccion))
#clasificaci�n
ggplot(data=Autos)+
  geom_point(mapping = aes(x=cilindrada, y=autopista))+
  geom_smooth(mapping = aes(x=cilindrada, y=autopista, group=traccion))

#clasificaci�n
ggplot(data=Autos, mapping = aes(x=cilindrada, y=autopista))+
  geom_point(mapping = aes(color=clase))+
  geom_smooth(data = filter(Autos, clase=="suv"))