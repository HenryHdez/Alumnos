install.packages("car") #Dispone de la función vif
library(car)
library(datos)
#Regresión multilineal
ejemplo_2_rg <- datos::diamantes
#Dos predictores.
modelo_lineal_3 <- lm(y ~ x + z, data = ejemplo_2_rg)
predict(modelo_lineal_3, data.frame(x = c(4.61), z = c(4.67)))
#Todos son predictores de y.
modelo_lineal_4 <- lm(y ~ ., data = ejemplo_2_rg)
#Todos son predictores de y menos corte.
modelo_lineal_5 <- lm(y ~ . - corte, data = ejemplo_2_rg)
summary(modelo_lineal_5)
#Función que selecciona los mejores predictores de y
step(modelo_lineal_5, direction = "both", trace = 0)
#Construcción del modelo con los mejores predictores
modelo_lineal_6 <- lm(y ~ quilate +
                      claridad + profundidad + tabla + x + z,
                      data = ejemplo_2_rg)
summary(modelo_lineal_6)
par(mfrow = c(2, 2))
plot(modelo_lineal_6)
#Calculo del coeficiente del factor de inflación de la varianza
vif(modelo_lineal_6)
