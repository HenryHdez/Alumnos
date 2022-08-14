#Importe el dataset de especies de flores data(iris) 
#se seleccionan únicamente las variables numéricas 
datos <- iris[,c(1,2,3,4)] 
#El comando pairs las agrupa en parejas 
pairs(x = datos, lower.panel = NULL) 
#El comando cor estima la correlación y 
#publica la información en forma matricial 
cor (x = datos, method = "pearson") 
#Una forma de validar si los datos siguen una 
#distribución normal 
library (psych) 
multi.hist(x = datos, dcol = c("blue", "red"),
          dlty = c("dotted", "solid"), main = "") 
#otra forma de presentar la matriz de correlación 
#En la cual se descartan datos a partir del nivel 
#de correlación 
library (corrplot) 
corrplot(corr = cor (x = datos, method = "pearson"),
          method = "number")
