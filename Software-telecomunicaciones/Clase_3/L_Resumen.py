"""
Editor de Spyder

Este archivo es temporal.
"""

print("Hola mundo")

"""Esta es una forma de crear un 
comentario de varias líneas"""
#Una librería se importa con el comando import.
#Por ejemplo
import numpy 
numpy.abs(-9)


----------TIPOS DE VARIABLE------------
"""PYTHON no tiene un tipo de variable especifico"""
Entero=4
Decimal=2.4
Caracter='b'
Cadena="Hola"
Vector=[1,2,3,4,5]

---------CONTATENACIÓN------------------
"""Formas de anidar e imprimir variables"""
#Imprimir la variable directamente
print(Entero)
#Convertir las variables a caracter
Texto1=Cadena+" "+str(Entero)+" "+str(Decimal)
print(Texto1)
#Anidar caracteres directamente
Texto2="El caracter es: "+Caracter
print(Texto2)
#Crear una lista
Texto3=[Texto1, Texto2]
print(Texto3)

-------------OPERACIONES MATEMATICAS BASICAS----
"""Operaciones matemáticas báscias"""
Suma=5+2
Resta=5-3
Multiplicacion=2*3
Division=3/1
print(Suma)

--------------OPERACIONES ARITMÉTICAS-----------
"""Otras operaciones matemáticas"""
Cociente=3//1
Residuo=4%2
base=2
exponente=3
Potenciacion=pow(base,exponente)
Redondear=round(2.55)
lista=[-1,4,5]
Maximo=max(lista)
Minimo=min(lista)

"""Operaciones con números complejos"""
a=1+2j
b=2.2-5j
print([a+b, b*a])

"""Algunas operaciones requieren de la liberia math, 
por su complejidad."""
import math as matematicas
#Número PI
pi=matematicas.pi
#Ejemplo funciones trigonométricas
print(matematicas.sin(pi/2))
print(matematicas.cos(pi/2))
print(matematicas.tan(pi/2))
#Funciones trigonométricas inversas
print(matematicas.asin(0.37))
print(matematicas.acos(1))
print(matematicas.atan(0.4))
#Conversiones
#De radianes a grados sexagesimales
print(matematicas.degrees(0.5))
#De grados sexagesimales a radianes
print(matematicas.radians(90))

------------ESTRUCTURAS DE CONTROL------
"""PYTHON tiene dos estructuras de control de 
entrada y salida por pantalla"""
#Entrada
numero=input("Digite un número:")
#Salida
print("El número es: ",numero)

"""La estructura condicional asume que lo que esta
adelante un espacio tabular(tab) pertenece a ella."""
#Ejemplo
if(int(numero)==3):
    print("Numero Correcto")
else:
    print("Numero Incorrecto")
print("Continua la ejecución de la aplicación")

""En PYTHON funcionan las formas de comparación convencionales como"""
"""x!=y             x No es igual a y"""
"""x==y             x Es igual a y"""
"""x>y              x Es mayor a y"""
"""x<y              x Es menor a y"""
"""and              Comparación lógica and"""
"""or               Comparación lógica or"""
#Ejemplo de implementación con un elif
Selector=int(input("Digite una opción: "))
if(Selector==0):
    print("El número es cero")
elif(Selector==1):
    print("El número es uno")
elif(Selector<0 or Selector>2):
    print("El número está fuera de rango")


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





-----------------LISTAS----------------
"""PYTHON tiene la capacidad de almacenar listas"""
Lista=["Sujeto 1", "Sujeto 2", "Sujeto 3"]
"""La forma más sencilla de publicar es:"""
print(Lista)
"""Sin embargo, puede usar una estructura"""
#El comando len se usa para conocer la longitud de la lista
for i in range(len(Lista)):
    print(Lista[i])
"""Las matrices son un caso particular de lista, ya que,
son una lista anidada."""
#Ejemplo
Matriz=[]
Numero_Columnas=10
for i in range(Numero_Filas):
    Matriz.append([])
    for j in range(Numero_Columnas):
        Matriz[i].append("Dato a asignar en la posición: "
              +str(i)+", "+str(j))
print(Matriz)

-------------Definir funciones--------------------------
"""Definición de funciones"""
"""Declaración de variables"""
a=1
"""Está función tiene parámetros de entrada"""
def funcion1(Variable_Entrada):
    """Código particular"""  
    """Si desea usar una variable contenida definida en
       otro punto del codigo, use el comando global."""
    global a
    a=a*Variable_Entrada

"""Esta función no tiene parámetros de entrada"""
"""pero si tiene un parámetro de salida"""
def funcion2():
    global a
    b=a+3
    return b

"""Definición de la función principal"""
if __name__=="__main__":
    """Llamado a las distintas funciones"""
    funcion1(3)
    w=a*funcion2()
    print(w)


------------INTERFAZ GRAFICA------------
"""Mi primer aplicación con interfaz grafica"""
"""importe la libreria Tkinter"""
from tkinter import *

"""Función principal"""
if __name__ == ""__main__":
    """Crear ventana vacia"""
    Aplicacion=Tk()
    """Definición de los objetos a usar"""
    Aplicacion.title("Primer App")
    etiqueta=Label(Aplicacion,text="Saludos")
    boton=Button(Aplicacion,text="OK")
    """Poner objetos en la ventana"""
    etiqueta.pack()
    boton.pack()
    """La instrucción Mainloop manitene activa 
    la aplicación"""
    Aplicacion.mainloop()



---------------CREAR EVENTOS-----------------------
"""Función principal"""
if __name__ == ""__main__":
    """Crear ventana vacia"""
    Aplicacion=Tk()
    """Definición de los objetos a usar"""    
    Aplicacion.title("Edición")
    """Crear etiqueta cpn variable de texto"""
    T_Etiqueta="Digite algo..."
    etiqueta=Label(Aplicacion,text=T_Etiqueta)
    """Crear Botón (clic=nombre de la función
    asociada)"""
    boton=Button(Aplicacion,text="Pulse",command=clic)
    """Crear campo de entrada y/o salida"""
    T_Salida=" "
    C_Entrada=Entry(Aplicacion, textvariable=T_Salida)
    """Poner objetos en la ventada (aparecen
    en el orden que se pongan en el codigo)"""
    etiqueta.pack()
    boton.pack()
    C_Entrada.pack()
    """Bucle infinito"""
    Aplicacion.mainloop()



-----------------CREAR EVENTOS-------------------------
"""importe la libreria Tkinter"""
from tkinter import *
"""sys contiene a try"""
import sys 

def clic():
    """Verifique si el recuerso u objeto está disponible"""
    try:
        """Leer desde el campo (String por defecto)"""
        Numero=int(C_Entrada.get())
        T_Etiqueta="El numero es: "+str(Numero)
        """Modificar el estado de etiqueta"""
        etiqueta.config(text=T_Etiqueta)
    except ValueError:
        """La excepción se activa si hay al menos un error en el
        dato del campo de entrada"""
        T_Etiqueta="Introduzca un dato"
        etiqueta.config(text=T_Etiqueta)


-------------EDICION DE CARACTERÍSTICAS---------
"""Función principal"""
if __name__ == ""__main__":
    """Crear ventana vacia"""
    Aplicacion=Tk()
    """Ajustar dimensiones de la ventana (Ancho, Alto)"""    
    Aplicacion.geometry("500x600")
    Aplicacion.title("Caracteristicas")
    """Color de fondo y texto Alto, Ancho y ubicación del texto"""
    etiqueta=Label(Aplicacion,text=T_Etiqueta,bg='red', fg='blue')
    """Tamaño del boton"""
    boton=Button(Aplicacion,text="Pulse", width=20, height=10, anchor="ne")
    T_Salida=" "
    C_Entrada=Entry(Aplicacion, textvariable=T_Salida)
    """Poner objetos en la ventada (aparecen
    en el orden que se pongan en el codigo)"""
    etiqueta.pack()
    boton.pack()
    C_Entrada.pack()
    """Bucle infinito"""
    Aplicacion.mainloop()


    """Fija ubicación y tamaño""" 
    etiqueta.place(x=70, y=140, width=100, height=30)
    boton.place(x=60, y=40, width=100, height=30)
    C_Entrada.place(x=260, y=240, width=100, height=30)


-----------GRAFICAS DE TENDENCIA-------
"""importe la libreria Tkinter"""
from tkinter import *
"""Matplotlib es una libreria para publicar graficas de tendencia."""
import matplotlin.pyplot as plt

def clic():
    lista=[1,2,3,4,5]
    plt.plot(lista)
    """Etiquetas"""
    plt.xlabel("Valores eje x")
    plt.ylabel("Valores eje y")
    plt.title("Titulo")
    """Activar grilla"""
    plt.grid(True)
    """Mostrar gráfico"""
    plt.show()

"""Función principal"""
if __name__ == ""__main__":
    Aplicacion=Tk()
    Aplicacion.title("Graficar")
    boton=Button(Aplicacion,text="Grafique",command=clic)
    boton.pack()
    Aplicacion.mainloop()