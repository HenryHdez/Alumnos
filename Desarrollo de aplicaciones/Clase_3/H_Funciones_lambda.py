#Función con argumentos de entrada y salida
def suma1 (a,b):
    return a+b
#Función lambda 
#Argumentos : Expresión
#Ejemplo 1
suma2 = lambda a,b : a+b
#Ejemplo 2
resul = lambda a,b : True if (a<b) else False
#Función principal
if __name__=="__main__":
    print(suma1(3,2))
    print(suma2(3,2))
    print(resul(3,2))
    
    