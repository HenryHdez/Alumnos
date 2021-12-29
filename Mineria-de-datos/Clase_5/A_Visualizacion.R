#Importe las siguientes librerías
library (tidyverse)
library (datos)
library (hexbin)
library (modelr)
#Importe la variable aeropuertos y grafique
#la variable categorica horario_verano
ggplot(datos::aeropuertos)+
  geom_bar(mapping=aes(x=horario_verano))
#si no requiere del gráfico para reali zar un
#conteo lo puede hacer de la si guiente forma.
#Almacene el dataFrame en una variable 
Aeropuerto=datos::aeropuertos
#El total de datos.
count(Aeropuerto)
#El total de datos por etiqueta 
Aeropuerto %>% count(horario_verano)
#%>% que toma la salida "Aeropuerto" y convierte"
#en entrada de la función count a uno de sus atributos.

#Por ejemplo, la variable latitud.
#Donde binwitdth establece la cantidad de intervalos
#en las que se divide el gráfico 
ggplot(data = Aeropuerto)+
  geom_histogram(mapping = aes(x = latitud), binwidth = 1.5)
#De forma similar al caso anterior la variable usted puede
#presentar la información sin gráfico 
Aeropuerto %>% count(cut_width(latitud, 1.5))

#Por ejemplo, del atributo latitud tome un grupo más pequeño 
#filtrando el grupo de datos 
latitud_1 <- Aeropuerto %>% filter (latitud < 40) 
#Grafique un histograma y notará la diferencia con #respecto al anterior 
ggplot (data = latitud_1, mapping = aes (x = latitud)) +
  geom_histogram(binwidth = 1.5) 
#otra utilidad es la clasificación de los histogramas de acuerdo con 
#otra variable. En este caso, geom_freqpoly grafica una línea de 
#tendencia por cada especie de la variable categorica 
ggplot (data = latitud_1, mapping = aes (x = latitud, colour = horario_verano)) +
  geom_freqpoly (binwidth = 1.5)
#Ej. Seleccione una zona del gráfico con el comando coord_cartesian 
#donde usted fija los límites del sistema de coordenadas 
ggplot (data = latitud_1, mapping = aes (x = latitud)) +
  geom_histogram(binwidth = 1.5) + 
  coord_cartesian(xlim = c(15,25), ylim = c(0, 30))