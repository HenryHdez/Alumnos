# -*- coding: utf-8 -*-
"""Importe la l�breria"""
from flask import Flask, render_template
"""Inicializaci�n de la p�gina"""
pagina = Flask(__name__)

"""Funci�n particular"""
@pagina.route('/')
def Funcion():
    lista=["Henry","Hernandez","Docente"]
    """Las variables a mostrar en la p�gina van
    separadas por comas"""
    return render_template('mi_primer_pagina.html',
                           Nombre_variable_mostrar=lista)

"""Ejecuci�n del servidor de flask"""
if __name__ == '__main__':
    pagina.run()