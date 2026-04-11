import transaction
from ZODB import DB
from ZODB.FileStorage import FileStorage
from persistent import Persistent

#Almacena de en el objeto persistent las instacias del objeto
class Objeto(Persistent):
    def __init__(self, nombre):
        self.nombre = nombre

if __name__ == '__main__':
    # Configurar el almacenamiento y base de datos
    storage = FileStorage('miarchivo.fs')
    db = DB(storage)
    connection = db.open()

    try:
        root = connection.root()
        root['obj'] = Objeto('Mi objeto')
        #Guardar los cambios
        transaction.commit()  
    finally:
        connection.close()
        db.close()
