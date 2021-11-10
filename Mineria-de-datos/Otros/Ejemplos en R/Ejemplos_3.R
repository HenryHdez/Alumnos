#Animaciones
#Suponga que tiene un vector con muestras
t=seq(-pi,pi,0.1)
y=sin(t)
#Use la estructura for
for(i in 1:length(y)){
  plot(t[i],y[i],
       xlim=c(-pi,pi),
       ylim=c(-1,1)
       )
  #Sys.sleep para el sistema e imprime la gráfica
  Sys.sleep(.09)
}

x=scan(dec=",") #dec indica que es decimal y la 
                #coma que los elementos del vector
                #van separados por coma
#Para leer caracteres
x <- scan(what = "")

