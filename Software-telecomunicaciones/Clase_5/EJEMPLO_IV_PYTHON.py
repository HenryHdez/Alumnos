"""Importe la l�breria"""
from flask import Flask, render_template
"""Inicializaci�n de la p�gina"
"""
pagina = Flask(__name__)



"""Funci�n particular"""
@pagina.route('/')
def Funcion():
    lista=["Henry","Hernandez","Docente"]
    """Las variables a mostrar en la p�gina vn
    separadas por comas"""
    return render_template('mi_primer_pagina.html',
                           Nombre_variable_mostrar=lista)