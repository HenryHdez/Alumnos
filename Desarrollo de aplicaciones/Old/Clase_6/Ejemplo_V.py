﻿# -*- coding: utf-8 -*-
from flask import Flask, request, render_template
Pagina = Flask(__name__)

@Pagina.route('/')
def index():
    #Pagina principal
    #Ahora accese desde Formulario2.html
    return render_template('Formulario.html')

@Pagina.route('/pagina', meethods = ['GET', 'POST'])
def Respuesta():
    #A esta pagina se remite desde la pagina principal
    #Usando la pagina web Formulario.html
    if request.method== 'POST':
        Valores_pagina = request.form       
        return render_template('Formulario_2.html',
                               Var=Valores_pagina['Caja1'])

if __name__ =='__main__':
    Pagina.run()