# -*- coding: utf-8 -*-
"""Definici�n de funciones"""
"""Declaraci�n de variables"""
a=1
"""Est� funci�n tiene par�metros de entrada"""
def funcion1(Variable_Entrada):
    """C�digo particular"""  
    """Si desea usar una variable contenida definida en
       otro punto del codigo, use el comando global."""
    global a
    a=a*Variable_Entrada

"""Esta funci�n no tiene par�metros de entrada"""
"""pero si tiene un par�metro de salida"""
def funcion2():
    global a
    b=a+3
    return b

"""Definici�n de la funci�n principal"""
if __name__=="__main__":
    """Llamado a las distintas funciones"""
    funcion1(3)
    w=a*funcion2()
    print(w)
