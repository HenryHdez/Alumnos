from flask import Flask, request, render_template


Pagina = Flask(__name__)


@Pagina.route('/', methods = ['GET', 'POST'])
def index():
    #Verifique el metodo usado por la pagina para responder
    if request.method== 'POST':
        #Con el comando request. form lea el valor de los
        #Campos de formulario.
        Valores_pagina = request.form

        print(Valores_pagina)
    

return render_template('Formulario.html')


if __name__ =='__main__':

   Pagina.run()