library(tidyverse)
library(datos)
#Almacene el conjunto de datos en una variable para modificarlo
aeropuerto <- datos::aeropuertos
#Cambie algunos valores por otros como faltantes
#En este caso las posiciones 1 a la 10 son datos faltantes
aeropuerto$latitud[1:10] <- NA
#Si desea eliminar los valores faltantes puede realizar un
#filtrado between(Nombre_variable, rango) y seleccionar los
#valores que quiere obtener
salida <- aeropuerto %>% filter(between(latitud, 39, 45))
view(salida)

#Cambie un valor por otro usando el comando mutate
#En este caso, suponga que un valor fuera del rango se convierte
#en uno faltante para realizar un analisis.
salida2 <- aeropuerto %>% mutate
  (latitud <- ifelse(latitud > 39 | latitud < 45, NA, latitud))
view(salida2)
#Tenga en cuenta que ifelse tiene tres argumentos
#El primero es la condición
#El segundo es el valor de retorno en caso de exito
#El tercero es el valor de retorno en caso de fracaso

#visualice el conjunto original
ggplot(data = aeropuerto, mapping = aes(x = zona_horaria, y = latitud)) +
  geom_point()
#y comparelo contra el creado usando el filtro
ggplot(data = Salida2, mapping = aes(x = zona_horaria, y = latitud)) +
  geom_point()
#Si desea eliminar el aviso de advertencia use el siguiente comando.
ggplot(data = Salida2, mapping = aes(x = zona_horaria, y = latitud)) +
  geom_point(na.rm = TRUE)
#lo que le permite informar a R que no tenga en cuenta lo valores
#faltantes al graficar

