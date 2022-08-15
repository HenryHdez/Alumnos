#Función que selecciona los mejores predictores de y
step(modelo_lineal_5, direction = "both", trace = 0)
#Construcción del modelo con los mejores predictores
modelo_lineal_6 <- lm(y ~ quilate +
                     claridad + profundidad + tabla + x + z,
                     data = ejemplo_2_rg)

