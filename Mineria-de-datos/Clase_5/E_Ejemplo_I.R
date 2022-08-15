#Interacción entre predictores 
#Construya el siguiente modelo (Variables independiente) 
Modelo_0 <- lm(z ~ x + y, data = datos::diamantes) 
summary (Modelo_0)
#Hay dos formas de establecer una relación entre variables 
#Modelo de interacción 1 
Modelo_1=lm(z ~ x + y + x:y, data = datos::diamantes) 
summary (Modelo_1) #Modelo de interacción 2 
Modelo_2=lm(z ~ x*y, data = datos::diamantes) 
summary (Modelo_2)
#Al ser un modelo con dos predictores continuos se puede representar en 3D 
#Determine el rango de valores para el predictor 1 
rango_x <- range (diamantes$x) 
#Cree un vector de 20 muestras entre el valor maximo y minimo de x 
nuevos_valores_x <- seq(from = rango_x[1], to = rango_x[2], length.out = 20) 
#Haga lo mismo para el segundo predictor 
rango_y <- range (diamantes$y) 
nuevos_valores_y <- seq(from = rango_y[1], to = rango_y[2], length.out = 20)
#Cree una variable que almacene el valor de las predicciones hechas 
#con los valores de los rangos 
predicciones <- outer(X = nuevos_valores_x, Y = nuevos_valores_y,
                      FUN = function(x, y) {
                        predict(object = Modelo_0, newdata = data.frame(x, y))
                        })
#Cree una superficie 
superficie <- persp(x = nuevos_valores_x, 
                    y = nuevos_valores_y, 
                    z = predicciones, 
                    theta = 18, 
                    phi = 20, 
                    col = "blue", 
                    shade = 0.1, 
                    xlab = "x", 
                    ylab = "y", 
                    zlab = "z",
                    main = "Variables independientes (z~x,y)") 
#Relacione las superficies y los datos 
observaciones <- trans3d(diamantes$x, diamantes$y, diamantes$z, superficie) 
#Halle el margen de error 
error <- trans3d(diamantes $x, diamantes$y, fitted (Modelo_0), superficie) 
#Dibuje un punto donde se encuentran los datos reales 
points (observaciones, col = "red", pch = 16) 
#trace una linea que presente la diferencia entre los datos 
#y el modelo 
segments (observaciones$x, observaciones$y, error$x, error$y)
