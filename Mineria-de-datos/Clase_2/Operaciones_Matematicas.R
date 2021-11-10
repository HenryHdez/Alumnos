
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