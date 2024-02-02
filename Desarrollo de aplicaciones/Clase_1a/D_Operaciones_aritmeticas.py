# -*- coding: utf-8 -*-
"""PYTHON no tiene un tipo de variable especifico"""
Entero=4
Decimal=2.4
Caracter='b'
Cadena="Hola"
Vector=[1,2,3,4,5]
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

"""Operaciones matemáticas báscias"""
Suma=5+2
Resta=5-3
Multiplicacion=2*3
Division=3/1
print(Suma)

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