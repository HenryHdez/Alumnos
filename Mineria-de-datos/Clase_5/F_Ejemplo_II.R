#Regresión polinomial
install.packages("ISLR")
library(ISLR)
#Importe el dataFrame Auto
ejemplo_2 <- ISLR::Auto
#Cree un modelo que relacione la variable mencionada
modelo_lineal <- lm(mpg ~ horsepower, ejemplo_2)
#Verifique que cumple con los criterios para realizar
#una regresión lineal summary(modelo_lineal)
#Grafique los puntos y la recta obtenida
plot(ejemplo_2$horsepower, ejemplo_2$mpg,
     main = "Consumo vs potencia motor", col = "grey")
abline(modelo_lineal, lwd = 3, col = "red")
#La función poly construye un polinomio de grado n (en este caso n=2)
modelo_cuadratico <- lm(mpg ~ poly(horsepower, 2), ejemplo_2)
#Grafique nuevamente los datos
plot(ejemplo_2$horsepower, ejemplo_2$mpg,
     main = "Consumo vs potencia motor", col = "grey")
#Construya un vector para asignar valores al modelo creado
puntos_interpolados <- seq(from = min(ejemplo_2$horsepower),
                           to = max(ejemplo_2$horsepower), by = 1)
#Prediga usando el comando
prediccion <- predict(object = modelo_cuadratico,
                      newdata = data.frame(horsepower=ejemplo_2$horsepower))
#Trace la línea sobre el plano ordenando los valores de salida del polinomio
lines(sort(ejemplo_2$horsepower),
       prediccion[order(ejemplo_2$horsepower)],
       col = "red", lwd = 3)

#Otras funciones para construir polinomios
library(ggplot2)
ggplot(ejemplo_2, aes(x = ejemplo_2$horsepower, y = ejemplo_2$mpg)) +
geom_point(colour = "grey") +
stat_smooth(method = "lm", formula = y ~ poly(x, 2),
            colour = "red", se = FALSE) +
stat_smooth(method = "lm", formula = y ~ poly(x, 5),
            colour = "blue", se = FALSE) +
stat_smooth(method = "lm", formula = y ~ poly(x, 10),
            colour = "green", se = FALSE) +
labs(title = "Polinomios de grado 2, 5, 10") +
theme_bw()

