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



#Importar librerías
library(tidyverse)
library(funModeling)
library(Hmisc)

#Exploración del dataFrame
df_status(Flores)
#Con respecto a cada atributo publica
#q_zeros Cantidad de ceros
#p_zeros es el porcentaje de ceros
#q_na cantidad de nulos
#p_na porcentaje de nulos
#q_inf cantidad de infinitos
#p_inf porcentaje de infinitos
#type o tipo de variable
#unique que le indica la cantidad de datos sin repetir
#Saber la cantidad de ceros es muy importante en el aprendizaje
#computacional por que puede influir dentro del modelo, ya que,
#si hay muchos ceros, puede que, la información no sea relevante.
#Unique es importante en algunos casos, por ejemplo el algoritmo 
#random forest no acepta mas de 53 datos unicos 

#plot_num permite imprimir las variables numericas de forma exploratoria
plot_num(Flores)
#Aplica criterios de estadistica sobre cada atributo
summary(Flores)
#Muestra la cantidad de datos unicos por atributo
describe(Flores)
#Amplia la información de summary y solo aplica para variables numéricas
profiling_num(Flores)
#Análisis descriptivo de cada variable categorica
freq(Flores)
#Ordenar registros (Menor a mayor)
d=arrange(Flores, sepal_length)
view(d)
#Ordenar registros (Mayor a menor)
d=arrange(Flores, -sepal_length)
view(d)

#Antes de continuar agregue valores nulos a un atributo
Flores$sepal_width[3]=NA
Flores$sepal_width[5]=NA
view(Flores)
df_status(Flores)
#Existen varias funciones de reparación
#1-Reemplaza caracteres nulos por cero
v1=is.na(Flores$sepal_width)
Flores$sepal_width[v1]=0
df_status(Flores)
#2-Reemplaza caracteres infinitos por cero
v1=is.infinite(Flores$sepal_width)
Flores$sepal_width[v1]=0
df_status(Flores)

#Tenga cuidado al cambiar el valor nulo por que va a modificar
#el resultado del modelo

#Seleccionar 1 atributo (para n atributos separelos por , , ,)
d=select(Flores, sepal_width)
view(d)
#Desplazar una columna (everything toma las columnas no mencionadas antes)
d2=select(Flores, species, everything())
view(d2)

#Joints (Articulación o tarea predefinida)
#Estos DataFrame los trae R por defecto
band_members
band_instruments
#Cosas en comun
inner_join(band_instruments,band_members)
#Cosas en comun y que variable no lo es en ambos
left_join(band_instruments,band_members)

#Cosas que no son comunes
anti_join(band_instruments,band_members)

#para exportar
write.csv(band_members,file='Nombre.csv')

