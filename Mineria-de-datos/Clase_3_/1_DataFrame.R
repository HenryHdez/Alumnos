#Dataframe
#Suponga que tiene los siguientes listados
A=c(3,4,5,6,7)
B=c('Banano','Piña','Sandia','Mora','Coco')
C=c(T,T,F,F,F)
Datos=data.frame(Cantidades=A,Nombres=B,Disponible=C)
print(Datos)
#Al imprimir aparece un listado con los atributos escritos
#al definir la estructura.

#Al tener el archivo como una variable
View(Flores)
#1-Acceda a los atributos con su nombre
a<-Flores['species']
print(a)
#2-Tome un registro como si fuera una fila
a<-Flores[1,]
print(a)
#3-De la misma forma tome un atributo
a<-Flores[,2]
print(a)
#4-El simbolo $ tambien le permite tomar un atributo
print(a$sepal_width[1])