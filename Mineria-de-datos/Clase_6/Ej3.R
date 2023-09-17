#Filtrar fechas después de una fecha específica
library(dplyr)
data_filtered <- data_colombia_long %>%
  filter(as.Date(Fecha, format="%m/%d/%y") > as.Date("2020-03-01"))

#Eliminar filas donde los casos confirmados son cero
data_filtered <- data_colombia_long %>%
  filter(Casos_Confirmados > 0)

#Filtrar por una combinación de criterios
data_combined_criteria <- data_colombia_long %>%
  filter(
    as.Date(Fecha, format="%m/%d/%y") > as.Date("2020-03-01") & 
    Casos_Confirmados > 1000
  )

