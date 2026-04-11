# -*- coding: utf-8 -*-
"""Importe la líbreria"""
from flask import Flask, request ,render_template
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
    return render_template('Ej1.html', var2=a)

@pagina.route('/bienvenida', methods=['GET', 'POST'])
def Funcion2():
    respuesta=request.method
    if respuesta=='GET':
        return render_template('pagina1.html')
    else:
        valores_pagina=request.form
        print(valores_pagina)
        if valores_pagina['listanombres']=='HH':
            texto='Titulo'
            return texto+"<h1>Hola HH</h1>"
        else:
            return valores_pagina['Entrada']

@pagina.route('/otrpag2')
def Funcion3():
    return render_template('pagina2.html')

if __name__=="__main__":
    pagina.run(port=3000, debug=True)