#Instalación de librerías

#Una solita
install.packages("readr")
install.packages("tidyverse")
#Varias
install.packages(c("funModeling", "Hmisc"))
#En caso de que funModeling no este disponible
library(remotes)
install_github("cran/remotes")

#Importar una librería
library("tidyverse")

#Dataframe
#Suponga que tiene los siguientes listados
a <- c(3, 4, 5, 6, 7)
b <- c("Banano", "Piña", "Sandia", "Mora", "Coco")
c <- c(TRUE, TRUE, FALSE, FALSE, FALSE)
datos <- data.frame(cantidades <- a, nombres <- b, disponible <- c)
print(datos)
#Al visualizar aparece un listado como se muestra a continuación

#Comando alterno para visualizar conjuntos de datos
View(datos)

#Metodología para importar archivo de excel

#instale readr así: install.packages("readr")
#Importe la librería
library("readr")
# Especifique el directorio de trabajo
ruta <- "D:/GitHub/Alumnos/Mineria-de-datos/A_Datasets/Flores.csv"
# Lea el contenido
flores <- read_csv(ruta, col_names = TRUE)
# Visualice
View(flores)

#1-Acceda a los Satributos con su nombre
a <- flores["species"]
print(a)
#2-Tome un registro como si fuera una fila
a <- flores[1, ]
print(a)
#3-De la misma forma tome un atributo
a <- flores[, 2]
print(a)
#4-El simbolo $ tambien le permite tomar un atributo
print(a$sepal_width[1])
