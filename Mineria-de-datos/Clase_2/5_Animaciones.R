#instale el paquete httpgd así: install.packages("httpgd")
#Animaciones
#Suponga que tiene un vector con muestras
t <- seq(-pi, pi, 0.1)
y <- sin(t)
l <- length(y)
#Use la estructura for
windows()
for (i in 1:l){
  plot(t[i], y[i],
       xlim = c(-pi, pi),
       ylim = c(-1, 1)
       )
  #Sys.sleep para el sistema e imprime la gráfica
  Sys.sleep(0.2)
}

