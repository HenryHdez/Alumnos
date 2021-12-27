"""Importe la líbreria"""
from flask import Flask, render_template
"""Inicialización de la página"
"""
pagina = Flask(__name__)



"""Función particular"""
@pagina.route('/')
def Funcion():
    lista=["Henry","Hernandez","Docente"]
    """Las variables a mostrar en la página vn
    separadas por comas"""
    return render_template('mi_primer_pagina.html',
                           Nombre_variable_mostrar=lista)