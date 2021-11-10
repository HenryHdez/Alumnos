#Comentario en R
#Tipos de datos en R
#Numericos
a=1
b=3.2
c=a+b
#Cadenas
d='Hola'
#Lógicos (F=false, T=true)
e=F 
#el comando print muestra el resultado en pantalla
print(d)
#ctrl+enter ejecuta la línea de codigo seleccionada

#Estructuras de datos
#vectores Nombre=c(datos del vector separados por coma)
Nombre_vector=c(1,2,3,4,5)
#Tenga en cuenta que, el tipo de datos del vector es el mismo
#Es decir, si mezcla números con caracteres el vector se tornará
#Tipo carácter
Ejemplo_vector=c(1,2,'Hola mundo')

#Funciones básicas con las estructuras de datos
is.vector(Nombre_vector) #Retorna True si es estructura de datos
typeof(Nombre_vector)    #Indica el tipo de variable
#Secuencias Enteras
Inicio=-1
Fin=2
Nombre_secuencia_1=Inicio:Fin;Nombre_secuencia_1
#No nesesariamente debe tener variables
Nombre_secuencia_2=-10:10;Nombre_secuencia_2
#Secuencias Decimales
Inicio=-5
Paso = 0.5
Fin=5
Secuencia_decimal=seq(Inicio, Fin, by=Paso) 
print(Secuencia_decimal)
#o
Secuencia_decimal=seq(0, 1000, by=0.1)
print(Secuencia_decimal)
#La función rep o repetición crea una estructura y le asigna a todas 
#las posiciones el mismo valor
valor=5
cantidad_valores=30
vector=rep(valor,cantidad_valores)
print(vector)

#Matrices
Filas=2
Columnas=3
Valor_inicial=1
Matriz=matrix(Valor_inicial,Filas,Columnas)
print(Matriz)
#Las matrices tambien pueden iniciarce con secuencias
Matriz=matrix(1:12,Filas,Columnas)
print(Matriz)
#OJO Como la secuencia excede el tamaño de la matriz NO
#se publican todos los elementos, por lo tanto, modifique la
#cantidad de columnas
Columnas=6
Matriz=matrix(1:12,Filas,Columnas)
print(Matriz)
#El llenado convencional se realiza por columnas, pero al agregar
#el valor logico T o true se le indica que el llenado se hace por filas
Matriz=matrix(1:12,Filas,Columnas,T)
print(Matriz)

#Arrays
#Este tipo de estructura agrupa varias matrices.
n_dimensiones=2
My_array=array(1:12,dim=c(3,4,n_dimensiones))
print(My_array)

#Acceder a un elemento de una matriz, vector o array
#Vector
posicion=1 #Inicia desde 0 como es habitual en otros lenguajes
elemento1=vector[posicion]
print(elemento1)
#Matriz
Posicion_fila=1
Posicion_colmuna=2
elemento2=Matriz[Posicion_fila,Posicion_colmuna]
print(elemento2)
#Array
Posicion_fila=1
Posicion_colmuna=2
Indice_Matriz=2
elemento3=My_array[Posicion_fila,Posicion_colmuna,Indice_Matriz]
print(elemento3)

#Tomar todos los elementos de una fila
Indice_Fila=2
Fila=Matriz[Indice_Fila,]
print(Fila)
Indice_Columna=3
columna=Matriz[,Indice_Columna]
print(columna)

#De manera similar se puede tomar un segmento fila 
#o columna de un array
Fila_Array=My_array[2,,2]
print(Fila_Array)

#Concatenar arreglos
MA=matrix(1,4,4)
MB=matrix(2,4,4)
#Unir por columnas
MC=cbind(MA,MB)
print(MC)
#Unir por filas
MD=rbind(MA,MB)
print(MD)
#Concatenar arrays (Nota: de esta forma se convierte
#un arreglo bidimensional)
A=cbind(My_array,My_array)
print(A)


#Se realizan componente a componente.
#el simbolo <- es asignación asi como el igual (=)
#Cree las siguientes variables
A<-1
B<-2.5
H<-c(1,2,3)
J<-c(5,6,7)
#Aritmeticas
C<-A+B
print(C)
C<-A-B
print(C)
C<-A*B
print(C)
C<-A/B
print(C)
I<-J*H
print(I)
I<-J+H
print(I)
I<-B*J
print(I)
#Algebraicas
I<-log(H)
print(I)
I<-sqrt(H)
print(I)
I<-exp(H)
print(I)
#Entre matrices
#transpuesta
Z=t(H)
print(H)
print(Z)
#inversa
MA=matrix(1:12,2,2)
Z=solve(MA)
print(Z)
#Multiplicación de matrices
M=I%*%H
print(M)
#Determinante
D=det(MA)
print(D)

#Solución de ecuaciones lineales
#Suponga que tiene el siguiente sistema de ecuaciones
#5 =4a+3b+3c
#8 =4a+2b+3c
#10=2a+3b+4c
#Una matriz puede verse como un grupo de listas, por lo tanto.
MA=matrix(c(4,4,2,3,2,3,3,3,4),3,3)
print(MA)
#Ahora ingrese el vector de respuestas
R=matrix(c(5,8,10),3,1)
print(R)
#solve tambien permite resolver sistemas de ecuaciones
MC=solve(MA,R)
print(MC)

#Graficos en R
#Defina la variable a graficar.
t<-seq(-pi,pi,0.1)
y=tan(t)
#El comando plot se encarga
plot(t,y)
#Si desea asignar rotulos use las palabras main, ylab y xlab
plot(t,y,
     main='titulo',
     ylab='Amplitud',
     xlab='tiempo')

#Hay varios tipos de linea (type) y se designan con letras
#l=línea continua, p=puntos, b=puntos y lineas, o=subrayar circulos
#s=escalonado, h=lineas verticales
#lwd= ancho de la linea
#col=color en ingles
plot(t,y,
     main='titulo',
     ylab='Amplitud',
     xlab='tiempo',
     type='l',
     col='red',
     lwd='2'
     )

#R también imprime grupos de datos alfanumericos clasificandolos
Frutas=c('Banano','Fresa','Coco','Fresa','Coco','Coco')
#El comando factor los agrupa
F=factor(Frutas)
plot(F) #En este caso se imprime un histograma
#Level me indica cuales son las eqtiquetas disponibles 
#dentro del vector
print(levels(F))
#str le indica que nivel ocupa cada etiqueta dentro del 
#arreglo. Ej. Banano es el 1, Fresa es el 3 y Coco el 2
str(F)
#Es decir convierte un dato categorico a número










