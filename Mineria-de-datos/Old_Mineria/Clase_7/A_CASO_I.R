#Tome el dataFrame diamantes. 
library(datos) 
library(psych) 
Ejemplo_1_RG=datos::diamantes 
View(Ejemplo_1_RG) 
# Diamantes es un dataFrame con 53.940 filas y 10 columnas 
# precio= valor en d�lares americanos ($326-$18,823) 
# quilate = Peso del diamante (0.2-5.01)
# corte = Calidad del corte (Regular, Bueno, Muy bueno, Premium, Ideal) 
# color = Color del diamante, de 3 (peor) a D (mejor) 
# claridad = Medida de que tan claro es el diamante 
# (11 (peor), SII, SI2, 151, 152, W51, W52, IF (mejor)) 
# profundidad = Porcentaje de la profundidad 
# total = z / mean(x, y) = 2 * Z(x + y) (43-79) 
# tabla = Ancho de la parte superior del diamante 
# con relaci�n a su punto m�s ancho (43-95) 
# x = Largo en mil�metros 
# y = Ancho en mil�metros 
# Z = Profundidad en mil�metros 
# Modelo de regresi�n lineal (y predecido x) 
Modelo_lineal_1 = lm(y~x, data=Ejemplo_1_RG) 
#Ampliaci�n de la informaci�n de salida 
#Muestra los nombres de los atributos disponibles del modelo. 
names(Modelo_lineal_1) 
#Muestra m�s detalles de la salida. 
summary(Modelo_lineal_1)
#Muestra los coeficientes del moodelo 
coef(Modelo_lineal_1) 
#Muestra los coeficientes que puede tener el modelo en un 
#intervalo de confianza. 
confint(Modelo_lineal_1) 
#Evalua la funci�n asignando valores al predictor del modelo. 
predict(Modelo_lineal_1, data.frame(x <- c(5, 10, 15))) 
x=Ejemplo_1_RG$x 
y=Ejemplo_1_RG$y 
plot(x, y)
# Graficar datos
# Graficar l�nea de tendencia
#lwd = ancho de l�nea, col = color abline (Modelo lineal 1, lwd=3, col="red")
#par en una funci�n que permite construir 
#graficos de una distribuci�n en una matriz (Ej. 2*2) 
par(mfrow=c(2,2)) 
plot(Modelo_lineal_1)