#Uso básico del archivo
import transaction
from persistent import Persistent
from ZODB import DB
from ZODB.FileStorage import FileStorage

# Definir una clase de objeto persistente
class Vehiculo(Persistent):
    def __init__(self, marca, modelo):
        self.marca = marca
        self.modelo = modelo

if __name__ == '__main__':
    # Configurar almacenamiento
    contenedor = FileStorage('data.fs')
    db = DB(contenedor)
    conexion = db.open()
    base = conexion.root()

    # Crear dos objetos
    if not base.get('Carros'):
        base['Carros'] = [Vehiculo('Mazda', 2023), Vehiculo('Renault', 2028)]
        transaction.commit()

    # Acceder y mostrar los objetos
    Carros = base['Carros']
    for Car in Carros:
        print(f'la marca es {Car.marca} y el modelo {Car.modelo}')

    # Cerrar la conexión y la base de datos
    conexion.close()
    db.close()