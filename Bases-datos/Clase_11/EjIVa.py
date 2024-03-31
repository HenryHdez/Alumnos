#Básico uso de ZODB
import transaction
from persistent.list import PersistentList
from persistent import Persistent
from ZODB import DB
from ZODB.FileStorage import FileStorage

class Vehiculo(Persistent):
    def __init__(self, marca, modelo, ano):
        self.marca = marca
        self.modelo = modelo
        self.ano = ano

if __name__ == '__main__':
    # Configuración de la base de datos
    contenedor = FileStorage('data.fs')
    db = DB(contenedor)
    conexion = db.open()
    base = conexion.root()
    # Refrescar la lista de la BD
    base['Carros'] = PersistentList()
    # Agregar objetos a la BD
    base['Carros'].extend([
        Vehiculo('Mazda', 'CX-5', 2023),
        Vehiculo('Renault', 'Kwid', 2028),
        Vehiculo('Toyota', 'Corolla', 2021),
        Vehiculo('Ford', 'Mustang', 2020),
        Vehiculo('Chevrolet', 'Camaro', 2022)
    ])
    transaction.commit()

    # Mostrar todos los vehículos
    Carros = base['Carros']
    for Car in Carros:
        marca = Car.marca
        modelo = Car.modelo
        ano = Car.ano
        print(f'La marca es {marca}, el modelo es {modelo} y el año es {ano}')

    # Encontrar todos los vehículos de una marca específica (Consulta)
    Parametroaencont = 'Toyota'
    toyota_vehiculos = []
    for car in Carros:
        if car.marca == Parametroaencont:
            toyota_vehiculos.append(car)

    # Calcular el año promedio de los vehículos (Agregación)
    total_anos = 0
    for car in Carros:
        total_anos += car.ano
    if Carros:
        prom_ano = total_anos / len(Carros)
    else:
        prom_ano = 0
    print(f'El año promedio de los vehículos es {prom_ano:.2f}')

    # Cerrar la conexión y la base de datos
    conexion.close()
    db.close()