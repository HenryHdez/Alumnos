#Regresi�n l�neal con una variable categ�rica. 
Temp=datos::diamantes 
# Las siguiente variable es categorica, por lo que, 
# se debe transformar en un factor.
factor(Temp$corte) 
#Construya un modelo de regresi�n 
Modelo_lineal_2 <- lm(profundidad ~ corte, data = Temp) 
predict (Modelo_lineal_2, data.frame(corte=c("Bueno", "Regular", "Premium")))
         