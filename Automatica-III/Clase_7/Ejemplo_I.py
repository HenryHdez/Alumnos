# -*- coding: utf-8 -*-
"""Importe la líbreria"""
from flask import Flask
"""Inicialización de la página"""
pagina = Flask(__name__)

@pagina.route('/')
def Funcion():
    return 'Hola mundo'

"""Ejecución del servidor de flask"""
if __name__ == '__main__':
    pagina.run(port=5000)

