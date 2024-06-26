#Instale las librer�as requridas 
install.packages ("moments") 
install.packages ("psych") 
install.packages ("corrplot") 
install.packages ("ggplot2") 

library(ggplot2)
library (moments) 
#Opci�n 1 #Importe un dataFrame en este caso mt cars y superponga 
#una distribuci�n normal con la misma media desvicaci�n estandar. 
#del conjunto a evaluar. 
ggplot (data = mtcars, aes (x = mpg)) +
  geom_histogram(aes (y = ..density.., fill = ..count..)) + 
  #Funci�n de distribuci�n normal 
  stat_function(fun = dnorm, colour = "firebrick",
                args = list (mean = mean(mtcars $mpg),
                      sd = sd(mtcars$mpg))) + 
  ggtitle("Histograma y curva normal te�rica") 
#opci�n 2 
#Dibuje una l�nea que indique normalidad y verifique la cercania
#entre los puntos y la recta. 
qqnorm(mtcars$mpg) 
qqline (mtcars$mpg) 
#Opci�n 3 
#si el p-value es mayor a 0.05 significa que la distribuci�n 
#sigue un patr�n de distribuci�n normal. 
agostino.test(mtcars$mpg)
