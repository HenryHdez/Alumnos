#Parámetros estadisticos con R base
#Tome un atributo de la base de datos
vector<-Flores$petal_length
#Frecuencias absolutas
F<-table(vector)
print(F)
#Frecuencias relativas
Fr<-prop.table(vector)
print(F)
#Porcentaje
P<-Fr*100
#Frecuencias acumuladas
Fa<-cumsum(Fa)
print(Fa)
#Ahora verifique la longitud de cada vector
length(F)
length(Fr)
length(P)
length(Fa)
#Construya la tabla de frecuencias
#Donde f, fr, Pocentaje y Acumulada son rotulos
tabla=cbind(f=F,fr=Fr,Porcentaje=P,Acumulada=Fa)
print(tabla)

#Otras formas de presentar la información son:
#histogramas
hist(Flores$sepal_width)
#Diagrama de cajas y bigotes
boxplot(Flores$sepal_length)