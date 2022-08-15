#Instale e importe las siguientes librerías
install.packages(c("tidyverse", "datos", "hexbin", "modelr"))
library(tidyverse)
library(datos)
library(hexbin)
library(modelr)

#Importe el conjunto de datos aeropuertos y grafique
#la variable categórica horario_verano
ggplot(datos::aeropuertos) +
  geom_bar(mapping = aes(x = horario_verano))

#Si no necesita el gráfico para realizar un conteo
#hágalo de la siguiente manera.
#1 - Almacene el dataFrame en una variable
aeropuerto <- datos::aeropuertos
#2 - Use el comando count (total de datos).
count(aeropuerto)
#ó
#Use el simbolo %>% que toma la variable "aeropuerto" y la convierte
#en entrada de la función count.
aeropuerto %>% count(horario_verano)


#Por ejemplo, la variable latitud.
#Donde binwitdth establece la cantidad de intervalos
#en las que se divide el gráfico
ggplot(data = aeropuerto) +
  geom_histogram(mapping = aes(x = latitud), binwidth = 1.5)
#De forma similar al caso anterior, usted puede presentar
#la información sin gráfico
aeropuerto %>% count(cut_width(latitud, 1.5))


#Por ejemplo, del atributo latitud tome un segmento filtrando el grupo de datos
latitud_1 <- aeropuerto %>% filter(latitud < 40)
#Grafique un histograma y notará la diferencia con respecto al gráfico anterior
ggplot(data = latitud_1, mapping = aes(x = latitud)) +
      geom_histogram(binwidth = 1.5)

#R permite segmentar histogramas en función de una especie o clase.
#En este caso, geom_freqpoly grafica una línea de tendencia por cada
#especie de la variable categórica
ggplot(data = latitud_1, mapping = aes(x = latitud, colour = horario_verano)) +
  geom_freqpoly(binwidth = 1.5)

#Ej. Seleccione una zona del gráfico con el comando coord_cartesian
#donde usted fija los límites del sistema de coordenadas
ggplot(data = latitud_1, mapping = aes(x = latitud)) +
  geom_histogram(binwidth = 1.5) +
  coord_cartesian(xlim = c(15, 25), ylim = c(0, 30))

