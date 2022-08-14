#Importe la librería 
library("readr")
# Especifique el directorio de trabajo
ruta <- "D:/GitHub/Alumnos/Mineria-de-datos/A_Datasets/Flores.csv"
# Lea el contenido
flores <- read_csv(ruta, col_names  <-  TRUE)
# Visualice
View(flores)

#Importar librerías(Nota: Importe el arreglo flores)
library(tidyverse)
library(funModeling)
library(Hmisc)

#Exploración del DataFrame
df_status(flores)
#Con respecto a cada atributo publica
#q_zeros Cantidad de ceros
#p_zeros es el porcentaje de ceros
#q_na cantidad de nulos
#p_na porcentaje de nulos
#q_inf cantidad de infinitos
#p_inf porcentaje de infinitos
#type o tipo de variable
#unique que le indica la cantidad de datos sin repetir
#Saber la cantidad de ceros es muy importante en el aprendizaje
#computacional por que puede influir dentro del modelo, ya que,
#si hay muchos ceros, puede que, la información no sea relevante.
#Unique es importante en algunos casos. Por ejemplo, el algoritmo
#random forest no acepta más de 53 datos únicos.

#plot_num permite imprimir las variables numéricas de forma exploratoria
plot_num(flores)
#Aplica criterios de estadística sobre cada atributo
summary(flores)
#Muestra la cantidad de datos únicos por atributo
describe(flores)
#Amplia la información de summary y solo aplica para variables numéricas
profiling_num(flores)
#Análisis descriptivo de cada variable categórica
freq(flores)
#Ordenar registros (Menor a mayor)
d <- arrange(flores, sepal_length)
view(d)
#Ordenar registros (Mayor a menor)
d <- arrange(flores, -sepal_length)
view(d)

#Antes de continuar agregue valores nulos a un atributo
flores$sepal_width[3] <- NA
flores$sepal_width[5] <- NA
view(flores)
df_status(flores)
#Existen varias funciones de reparación
#1-Reemplaza caracteres nulos por cero
v1 <- is.na(flores$sepal_width)
flores$sepal_width[v1] <- 0
df_status(flores)
#2-Reemplaza caracteres infinitos por cero
v1 <- is.infinite(flores$sepal_width)
flores$sepal_width[v1] <- 0
df_status(flores)

#Tenga cuidado al cambiar el valor nulo por que va a modificar
#el resultado del modelo

#Seleccionar 1 atributo (para n atributos separelos por , , ,)
d <- select(flores, sepal_width)
view(d)
#Desplazar una columna (everything toma las columnas no mencionadas antes)
d2 <- select(flores, species, everything())
view(d2)

#Joints (Articulación o tarea predefinida)
#Estos DataFrame los trae R por defecto
band_members
band_instruments
#Cosas en comun
inner_join(band_instruments, band_members)
#Cosas en comun y que variable no lo es en ambos
left_join(band_instruments, band_members)

#Cosas que no son comunes
anti_join(band_instruments, band_members)

#para exportar
write.csv(band_members, file <- "Nombre.csv")


