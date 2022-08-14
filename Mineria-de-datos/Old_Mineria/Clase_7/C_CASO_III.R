install.packages("car")
library(car)
#Regresión multilineal 
Ejemplo_2_RG=datos::diamantes 
# Dos predictores. 
Modelo_lineal_3 = lm(y~x+z, data=Ejemplo_2_RG) 
predict(Modelo_lineal_3, data.frame (x=c(4.61), z=c(4.67))) 
# Todos son predictores de y. 
Modelo_lineal_4 = lm(y~., data=Ejemplo_2_RG)
# Todos son predictores de y menos corte. 
Modelo_lineal_5 = lm(y~.-corte, data=Ejemplo_2_RG) 
summary(Modelo_lineal_5) 
#Función que selecciona los mejores predictores de y 
step (Modelo_lineal_5, direction = "both", trace = 0) 
#Construcción del modelo con los mejores predictores 
Modelo_lineal_6 = lm(y~quilate+ 
                       claridad+profundidad+tabla+x+z, 
                     data=Ejemplo_2_RG) 
summary(Modelo_lineal_6)
par(mfrow = c(2,2)) 
plot(Modelo_lineal_6) 
#Calculo del coeficiente del Factor de inflación de la varianza 
vif(Modelo_lineal_6)
