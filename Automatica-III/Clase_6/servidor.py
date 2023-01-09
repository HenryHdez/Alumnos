# -*- coding: utf-8 -*-
from flask import Flask, request, render_template
Pagina = Flask(__name__)
#Dirección principal
@Pagina.route('/')
def index():
    return render_template('Formulario.html')
#Dirección particular
@Pagina.route('/pagina', methods = ['GET', 'POST'])
def Respuesta():
    if request.method== 'POST':
        Valores_pagina = request.form
        return render_template('Formulario_2.html',
                               Var=Valores_pagina['Caja1'])
#Dirección particular 2
@Pagina.route('/pagina2', methods = ['GET', 'POST'])
def Respuesta_1():
    return render_template('Formulario_3.html',
                               Var="9")

if __name__ =='__main__':
   Pagina.run()
   
   