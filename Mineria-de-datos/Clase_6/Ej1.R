install.packages("RMySQL")
library(RMySQL)

conn <- dbConnect(MySQL(), user='root', password='mi_contrasena', dbname='covid_colombia', host='localhost', port=3307)
url <- "https://raw.githubusercontent.com/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_time_series/time_series_covid19_confirmed_global.csv"

data_covid <- read.csv(url)

# Filtrar los datos por Colombia
data_colombia <- data_covid[data_covid$Country.Region == "Colombia",]
dbWriteTable(conn, "covid_data", data_colombia, overwrite=TRUE)
dbDisconnect(conn)

install.packages("tidyverse")
library(tidyverse)

data_colombia_long <- data_colombia %>%
gather(key = "Fecha", value = "Casos_Confirmados")

data_colombia_long[1,]
data_colombia_long

conn <- dbConnect(MySQL(), 
user='root', password='mi_contrasena', dbname='covid_colombia', host='localhost', port=3307, client.flag = CLIENT_LOCAL_FILES)
dbWriteTable(conn, "covid_data_colombia", data_colombia_long, overwrite=TRUE)
dbDisconnect(conn)

install.packages(c("plumber", "ggplot2", "png"));
install.packages("plumber")
library(plumber)

r <- plumb("Ej2a.R")
r$run(port=8000)

# Crear un conjunto de datos
datos <- data.frame(
  Año = c(2020, 2021),
  Enero = c(10, 15),
  Febrero = c(20, 25),
  Marzo = c(30, 35)
)
# Mostrar el conjunto de datos
print(datos)

library(tidyr)
datos_largos <- gather(datos, Mes, Valor, Enero:Marzo)
print(datos_largos)

library(tidyr)
datos_largos <- pivot_longer(datos, cols = Enero:Marzo, 
                    names_to = "Mes", values_to = "Valor")
print(datos_largos)

datos_ancho <- spread(datos_largos,
                       key = Mes, value = Valor)
print(datos_ancho)

datos_ancho <- datos_largos %>% 
              pivot_wider(names_from = Mes, values_from = Valor)
print(datos_ancho)

library(magrittr)
#Sin pipe
sqrt(sum(c(1:10)))

#Con pipe
c(1:10) %>% sum() %>% sqrt()

