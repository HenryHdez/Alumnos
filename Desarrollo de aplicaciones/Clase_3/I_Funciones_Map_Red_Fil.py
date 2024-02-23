#Ejemplo 3
import functools
#Lista de ejemplo
lis = [1, 3, 5, 6, 2]
#Lamda + Reduce
print("La sumatoria es : ", end="")
print(functools.reduce(lambda a, b: a+b, lis))

#Ejemplo 2
def Det_pares(numero):   # Función
    if numero % 2 == 0:  # Condicional
        return True      # Devolución

if __name__=="__main__":
    #Lista de números
    numeros = [2, 5, 10, 23, 50, 33]
    Rta=filter(Det_pares, numeros)
    print(Rta) #¿Que pasa?
    #>>>>>>>>>----------<<<<<<<<<<<<
    print(list(filter(Det_pares, numeros)))
    

    
    
    
#Ejemplo 1
def cuadrados(x):
    y = []
    for e in x:
        y.append(e ** 2)
    return y

    #lista de números
    numeros = [1, 2, 4, 7]
    print(cuadrados(numeros))
    #Función map()
    cuadrados = list(map(lambda x : x ** 2, numeros))
    print(cuadrados)




