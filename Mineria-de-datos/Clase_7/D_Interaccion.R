#Función que selecciona los mejores predictores de y 
step (Modelo_lineal_5, direction = "both", trace = 0) 
#Construcción del modelo con los mejores predictores 
Modelo_lineal_6 = lm(y~quilate+ 
                       claridad+profundidad+tabla+x+z, 
                     data=Ejemplo_2_RG) 