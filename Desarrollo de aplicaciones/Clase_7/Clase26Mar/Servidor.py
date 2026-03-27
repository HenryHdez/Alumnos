# -*- coding: utf-8 -*-
"""Importe la líbreria"""
from flask import Flask, render_template
"""Inicialización de la página"""
pagina = Flask(__name__)

"""En este caso se direcciona un archivo con formato HTML"""
@pagina.route('/')
def Funcion1():
    #Procesamiento
    a=1
    b=4
    c=a+b
    lista=["Hola","Alumnos","desarrollo de aplicaciones"]
    #del lado del cliente{{Variable}}
    return render_template('index.html',resultado=c,listaHTML=lista)

@pagina.route('/otrpag')
def Funcion2():
    return render_template('pagina1.html')

@pagina.route('/otrpag2')
def Funcion3():
    return render_template('pagina2.html')

if __name__=="__main__":
    pagina.run(port=3000, debug=True)