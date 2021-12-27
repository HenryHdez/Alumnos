

"""Importe la líbreria"""


from flask import Flask
"""Inicialización de la página"""


pagina = Flask(__name__)




"""Flask requiere de un direccionamiento por función.

Es decir cuando va a mostrar algo en la pagina se dirige

a la ruta asignada"""

"""En este caso / indica la raíz del servidor
"""
"""Función particular para mostrar algo en la página"""
@pagina.route('/')

def Funcion(

):
    return 'Hola mundo'

 

 



"""Ejecución del servidor de flask"""


if __name__ == '__main__':
    pagina.run()