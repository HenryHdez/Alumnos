# -*- coding: utf-8 -*-
"""Importe la l�breria"""
from flask import Flask, render_template
"""Inicializaci�n de la p�gina"""
pagina = Flask(__name__)
"""En este caso se direcciona un archivo con formato HTML"""
@pagina.route('/')
def Funcion():
    return render_template('mi_primer_pagina.html')

"""Ejecuci�n del servidor de flask"""
if __name__ == '__main__':
    pagina.run()
