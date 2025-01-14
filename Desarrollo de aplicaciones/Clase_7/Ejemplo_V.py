# -*- coding: utf-8 -*-
from flask import Flask, request, render_template

Pagina = Flask(__name__)

@Pagina.route('/', methods = ['GET', 'POST'])
def index():
    #Verbo usado para enviar la información
    if request.method== 'POST':
        #request.form lee valores que recolectados en el formulario
        Valores_pagina = request.form
        print(Valores_pagina['Caja1'])
    return render_template('Formulario.html')

if __name__ =='__main__':
    Pagina.run()
    
    