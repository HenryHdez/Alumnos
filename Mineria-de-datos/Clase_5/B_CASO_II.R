#Regresión líneal con una variable categórica.
library(datos)
temp <- datos::diamantes
#La variable es categorica, por lo que,
#se debe transformar en un factor.
factor(temp$corte)
#Construya un modelo de regresión
modelo_lineal_2 <- lm(profundidad ~ corte, data = temp)
predict(modelo_lineal_2,
    data.frame(corte = c("Bueno", "Regular", "Premium")))
