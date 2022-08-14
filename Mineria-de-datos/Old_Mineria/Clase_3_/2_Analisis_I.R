#Importe la librería
library("readr")
# Especifique el directorio de trabajo
ruta <- "D:/GitHub/Alumnos/Mineria-de-datos/A_Datasets/Flores.csv"
# Lea el contenido
flores <- read_csv(ruta, col_names = TRUE)
# Visualice
View(flores)

#-----Parámetros estadísticos con R base------
#Nota: Importe flores previamente
#Tome un atributo de la base de datos
vector <- flores$petal_length
#Frecuencias absolutas
f <- table(vector)
print(f)
#Frecuencias relativas
fr <- prop.table(vector)
print(fr)
#Porcentaje
p <- fr * 100
print(p)
#Frecuencias acumuladas
fa <- cumsum(f)
print(fa)
#Ahora verifique la longitud de cada vector
length(f)
length(fr)
length(p)
length(fa)

#Construya la tabla de frecuencias
#Donde f, fr, Pocentaje y Acumulada son rotulos
tabla <- cbind(f <- f, fr <- fr, porcentaje <- p, acumulada <- fa)
print(tabla)
View(tabla)
#Otras formas de presentar la información son:
#histogramas
hist(flores$sepal_width)
#Diagrama de cajas y bigotes
boxplot(flores$sepal_length)

