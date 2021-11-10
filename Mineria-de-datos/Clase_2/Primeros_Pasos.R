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