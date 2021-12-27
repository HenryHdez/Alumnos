

"""Importe la l�breria"""


from flask import Flask
"""Inicializaci�n de la p�gina"""


pagina = Flask(__name__)




"""Flask requiere de un direccionamiento por funci�n.

Es decir cuando va a mostrar algo en la pagina se dirige

a la ruta asignada"""

"""En este caso / indica la ra�z del servidor
"""
"""Funci�n particular para mostrar algo en la p�gina"""
@pagina.route('/')

def Funcion(

):
    return 'Hola mundo'

 

 



"""Ejecuci�n del servidor de flask"""


if __name__ == '__main__':
    pagina.run()