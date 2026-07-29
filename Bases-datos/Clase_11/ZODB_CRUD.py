#CRUD en ZODB
from persistent import Persistent
#----------Crear--------------
class Miobjeto(Persistent):
    def __init__(self, name):
        self.name = name
#db es una conexión a la DB
base = db.open().root()
base['NombreObj'] = Miobjeto('NombreObj')
transaction.commit()

#----------Leer--------------
#db es una conexión a la DB
base = db.open().root()
Objeto = base['NombreObj']
print(Objeto.name)

#----------Actualizar--------------
Objeto = base['NombreObj']
Objeto.name = 'Nuevo nombre'
transaction.commit()

#----------Borrar--------------
del base['NombreObj']
transaction.commit()

#----------Agregación--------------
conteo = len(root.keys())
print(f'Número de objetos en la BD: {conteo}')