# -*- coding: utf-8 -*-
from flask import Flask, request, render_template

pagina = Flask(__name__)

@pagina.route('/')
def FuncionForm():
    return render_template('Formulario.html',
                           varflask=str(100))
    
@pagina.route('/otrapag', methods = ['GET', 'POST'])
def Funcion2():
    if request.method== 'POST':
        Valores_pagina = request.form
        print(Valores_pagina)
        #La informacion llega en String y sale en String
        if Valores_pagina['Caja1']=='Ir': 
            #Ejecucion de un codigo de python
            #...
            return render_template('pagina2.html', 
                                variable=Valores_pagina['Caja1'],)
            #Este codigo no se ejecutara
        else:
            return render_template('pagina.html', 
                                variable='Variable desde el servidor',
                                variablec=10)            


if __name__ == '__main__':
    pagina.run(port=2500, debug=True)