"""PYTHON tiene dos estructuras de control de 
entrada y salida por pantalla"""
#Entrada
numero=input("Digite un n�mero:")
#Salida
print("El n�mero es: ",numero)

"""La estructura condicional asume que lo que esta
adelante un espacio tabular(tab) pertenece a ella."""
#Ejemplo
if(int(numero)==3):
    print("Numero Correcto")
else:
    print("Numero Incorrecto")
print("Continua la ejecuci�n de la aplicaci�n")

""En PYTHON funcionan las formas de comparaci�n convencionales como"""
"""x!=y             x No es igual a y"""
"""x==y             x Es igual a y"""
"""x>y              x Es mayor a y"""
"""x<y              x Es menor a y"""
"""and              Comparaci�n l�gica and"""
"""or               Comparaci�n l�gica or"""
#Ejemplo de implementaci�n con un elif
Selector=int(input("Digite una opci�n: "))
if(Selector==0):
    print("El n�mero es cero")
elif(Selector==1):
    print("El n�mero es uno")
elif(Selector<0 or Selector>2):
    print("El n�mero est� fuera de rango")


"""Nota: la estructura SWITCH en PYTHON no existe"""


"""Estructuras de Bucle"""
#Ejemplos
contador=0
iteraciones=int(input("Digite la cantidad de iteaciones"))
"""For incremental"""
for i in range(0,iteraciones):
    print(i)
"""For decremental"""
for i in range(-iteraciones,0):
    print(i)
"""While"""
while (contador<iteraciones):
    print(contador)
    contador=contador+1


