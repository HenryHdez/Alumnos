# -*- coding: utf-8 -*-
"""Importe la líbreria"""
from flask import Flask, render_template
"""Inicialización de la página"""
pagina = Flask(__name__)

"""En este caso se direcciona un archivo con formato HTML"""
@pagina.route('/')
def Funcion():
    lista_color=["red", "pink", "black", "blue", "yellow"]
    return render_template('holamundo.html', lista=lista_color)

"""Ejecución del servidor de flask"""
if __name__ == '__main__':
    pagina.run(port='3000', debug=True)