# -*- coding: utf-8 -*-
"""Importe la líbreria"""
from flask import Flask, render_template
"""Inicialización de la página"""
pagina = Flask(__name__)

"""En este caso se direcciona un archivo con formato HTML"""
@pagina.route('/')
def Funcion1():
    return render_template('pagina.html')

@pagina.route('/contacto')
def Funcion2():
    return "hola contcto"

"""Ejecución del servidor de flask"""
if __name__ == '__main__':
    pagina.run(port='3000', debug=True)

