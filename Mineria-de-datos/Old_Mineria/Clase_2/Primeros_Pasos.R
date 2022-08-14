#Comentario en R
#Tipos de datos en R
#Numericos
a <- 1
b <- 3.2
c <- a + b
#Cadenas
d <- "Hola"
# Lógicos (F_<- False,_T <- True)
e <- FALSE
#el comando print muestra el resultado en pantalla
print(d)
#ctrl+enter ejecuta la línea de codigo seleccionada

#Estructuras de datos
#vectores Nombre <- c(datos del vector separados por coma)
nombre_vector <- c(1, 2, 3, 4, 5)
#Tenga en cuenta que, el tipo de datos del vector es el mismo
#Es decir, si mezcla números con caracteres el vector se tornara
#Tipo carácter
ejemplo_vector <- c(1, 2, "Hola mundo")

#Funciones básicas con las estructuras de datos
is.vector(nombre_vector) #Retorna True si es estructura de datos
typeof(nombre_vector)    #Indica el tipo de variable

#Secuencias Enteras
inicio <- -1
fin <- 2
nombre_secuencia_1 <- inicio:fin
nombre_secuencia_1
#No nesesariamente debe tener variables
nombre_secuencia_2 <- -10:10
nombre_secuencia_2
#Secuencias Decimales
inicio <- -5
paso  <-  0.5
fin <- 5
secuencia_decimal <- seq(inicio, fin, by <- paso)
print(secuencia_decimal)
#o
secuencia_decimal <- seq(0, 1, by <- 0.1)
print(secuencia_decimal)


#La función rep o repetición crea una estructura y le asigna a todas
#las posiciones el mismo valor
valor <- 5
cantidad_valores <- 30
vector <- rep(valor, cantidad_valores)
print(vector)

#Matrices
filas <- 2
columnas <- 3
valor_inicial <- 1
matriz <- matrix(valor_inicial, filas, columnas)
print(matriz)
#Las matrices tambien pueden iniciarce con secuencias
matriz <- matrix(1:12, filas, columnas)
print(matriz)
#OJO Como la secuencia excede el tamaño de la matriz NO
#se publican todos los elementos, por lo tanto, modifique la
#cantidad de columnas
columnas <- 6
matriz <- matrix(1:12, filas, columnas)
print(matriz)
#El llenado convencional se realiza por columnas, pero al agregar
#el valor logico T o true se le indica que el llenado se hace por filas
matriz <- matrix(1:12, filas, columnas, TRUE)
print(matriz)

#Arrays
#Este tipo de estructura agrupa varias matrices.
n_dimensiones <- 2
my_array <- array(1:12, dim <- c(3, 4, n_dimensiones))
print(my_array)

#Acceder a un elemento de una matriz, vector o array
#Vector
posicion <- 1 #Inicia desde 0 como es habitual en otros lenguajes
elemento1 <- vector[posicion]
print(elemento1)
#Matriz
posicion_fila <- 1
posicion_colmuna <- 2
elemento2 <- matriz[posicion_fila, posicion_colmuna]
print(elemento2)
#Array
posicion_fila <- 1
posicion_colmuna <- 2
indice_matriz <- 2
elemento3 <- my_array[posicion_fila, posicion_colmuna, indice_matriz]
print(elemento3)

#Tomar todos los elementos de una fila
indice_fila <- 2
fila <- matriz[indice_fila, ]
print(fila)
indice_columna <- 3
columna <- matriz[, indice_columna]
print(columna)

#De manera similar se puede tomar un segmento fila 
#o columna de un array
fila_array <- my_array[2, , 2]
print(fila_array)

#Concatenar arreglos
ma <- matrix(1, 4, 4)
mb <- matrix(2, 4, 4)
#Unir por columnas
mc <- cbind(ma, mb)
print(mc)
#Unir por filas
md <- rbind(ma, mb)
print(md)
#Concatenar arrays (Nota: de esta forma se convierte
#un arreglo bidimensional)
a <- cbind(my_array, my_array)
print(a)