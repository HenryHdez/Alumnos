#Instale las librerías requridas
install.packages(c("moments", "psych", "corrplot", "ggplot2"))
#Importe las librerías señaladas
library(ggplot2)
library(moments)

#Opción 1 #Importe el conjunto de datos mtcars y superponga una curva
#con distribución normal teórica sobre los histogramas generados.
ggplot(data = mtcars, aes(x = mpg)) +
  geom_histogram(aes(y = ..density.., fill = ..count..)) +
  #Función de distribución normal
  stat_function(fun = dnorm, colour = "firebrick",
                args = list(mean = mean(mtcars $mpg),
                      sd = sd(mtcars$mpg))) +
  ggtitle("Histograma y curva normal teórica")

#opción 2
#Dibuje una línea que indique normalidad y verifique la cercania
#entre los puntos y la recta.
qqnorm(mtcars$mpg)
qqline(mtcars$mpg)

#Opción 3
#si el p-value es mayor a 0.05 significa que la distribución
#sigue un patrón de distribución normal.
agostino.test(mtcars$mpg)

