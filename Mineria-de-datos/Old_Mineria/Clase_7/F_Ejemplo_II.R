#Regresión polinomial 
install.packages("ISLR")
library(ISLR) 
#Importe el dataFrame Auto 
Ejemplo_2=ISLR:: Auto 
#Cree un modelo que relacione la variable mencionada 
modelo_lineal <- lm(mpg ~ horsepower, Ejemplo_2) 
#Verifique que cumple con los criterios para realizar 
#una regresión linal summary(modelo_lineal) 
#Grafique los puntos y la recta obtenida 
plot(Ejemplo_2$horsepower, Ejemplo_2$mpg, main = "Consumo vs potencia motor", col = "grey") 
abline (modelo_lineal, lwd = 3, col = "red")
#La función poly construye un polinomio de grado n (en este caso n=2) 
modelo_cuadratico <- lm(mpg ~ poly(horsepower, 2), Ejemplo_2) 
#Grafique nuevamente los datos 
plot(Ejemplo_2$horsepower, Ejemplo_2$mpg, main = "Consumo vs potencia motor", col = "grey") 
#Construya un vector para asignar valores al modelo creado 
puntos_interpolados <- seq(from = min(Ejemplo_2$horsepower), to = max(Ejemplo_2$horsepower), by = 1) 
#Prediga usando el comando 
prediccion <- predict(object = modelo_cuadratico, newdata = data.frame(horsepower=Ejemplo_2$horsepower)) 
#Trace la línea sobre el plano ordenando los valores de salida del polinomio 
lines (sort (Ejemplo_2$horsepower),
       prediccion[order (Ejemplo_2$horsepower)], 
       col = "red", lwd = 3)
