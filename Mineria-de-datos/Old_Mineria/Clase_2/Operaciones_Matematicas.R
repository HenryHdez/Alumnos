#Algunas operaciones se realizan componente a componente.
#cree las siguientes variables
a <- 1
b <- 2.5
h <- c(1, 2, 3)
j <- c(5, 6, 7)
#aritmeticas
c <- a + b
print(c)
c <- a - b
print(c)
c <- a * b
print(c)
c <- a / b
print(c)
i <- j * h
print(i)
i <- j + h
print(i)
i <- b * j
print(i)
#algebraicas
i <- log(h)
print(i)
i <- sqrt(h)
print(i)
i <- exp(h)
print(i)
#Entre matrices
#transpuesta
z <- t(h)
print(h)
print(z)
#inversa
ma <- matrix(1:12, 2, 2)
z <- solve(ma)
print(z)
#multiplicación de matrices
m <- i %*% h
print(m)
#determinante
d <- det(ma)
print(d)

#Solución de ecuaciones lineales
#Suponga que tiene el siguiente sistema de ecuaciones
#5  <- 4a+3b+3c
#8  <- 4a+2b+3c
#10 <- 2a+3b+4c
#Una matriz puede verse como un grupo de listas, por lo tanto.
ma <- matrix(c(4, 4, 2, 3, 2, 3, 3, 3, 4), 3, 3)
print(ma)
#ahora ingrese el vector de respuestas
r <- matrix(c(5, 8, 10), 3, 1)
print(r)
#solve tambien permite resolver sistemas de ecuaciones
mc <- solve(ma, r)
print(mc)

