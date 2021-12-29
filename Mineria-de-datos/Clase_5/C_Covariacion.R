#Caso I: Una variable categorica y una continua 
aviones=datos :: aviones 
ggplot (data = aviones, mapping = aes (x = asientos)) +
  geom_freqpoly(mapping = aes (colour = tipo), binwidth = 50) 
ggplot (data = aviones, mapping = aes (x = asientos)) +
  geom_histogram(binwidth = 50) ggplot (data = aviones, mapping = aes (x = asientos, y = .. density..)) +
  geom_freqpoly(mapping = aes (colour = tipo), binwidth = 50) 
#Diagrama de cajas 
ggplot (data = aviones, mapping = aes (x = tipo, y = asientos)) +
  geom_boxplot() 
#Tambien puede ordenarlo en función de la media 
ggplot (data = aviones) + 
  geom_boxplot (mapping = aes (x = reorder (x = tipo, asientos, FUN = median), y = asientos)) 
#o puede rotarlo 
ggplot (data = aviones) + 
  geom_boxplot (mapping = aes (x = reorder (x = tipo, asientos, FUN = median), y = asientos))+ coord_flip) 
#Dos variables categoricas 
ggplot (data = aviones) +
  geom_count (mapping = aes (x = tipo_motor, y = tipo)) 
aviones %>%count(tipo_motor, tipo) 
aviones %>%count (tipo_motor, tipo) %>% ggplot (mapping = aes (x = tipo_motor, y = tipo)) +
  geom_tile(mapping = aes (fill = n)) 
#Abra el dataFrame 
atmostera atm=datos :: atmosfera 
#y grafique 
ggplot (data = atm) +
  geom_point (mapping = aes (x = temp_superficie, y = temperatura)) 
#Por lo que se puede poner una transparencia 
ggplot (data = atm) + 
  geom_point (mapping = aes (x = temp_superficie, y = temperatura), alpha = 1 / 100) 
#o trazar un mapa de colores 
ggplot (data = atm) +
  geom_bind(mapping = aes (x = temp_superficie, y = temperatura) 
#otra forma de hacerlo es dividiendo los datos en intervalos 
#y publicando con diagramas de cajas 
ggplot (data = atm, mapping = aes (x = temp_superficie, y = temperatura) +
          geom_boxplot (mapping = aes (group = cut_width(temperatura, 10)))
        
        