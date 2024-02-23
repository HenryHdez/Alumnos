# -*- coding: utf-8 -*-
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
