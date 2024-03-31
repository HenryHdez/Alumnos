#Ejemplo de Subconsultas
import transaction
from persistent.list import PersistentList
from persistent import Persistent
from ZODB import DB
from ZODB.FileStorage import FileStorage

class Propietario(Persistent):
    def __init__(self, nombre, edad):
        self.nombre = nombre
        self.edad = edad

class Vehiculo(Persistent):
    def __init__(self, marca, modelo, ano, propietario):
        self.marca = marca
        self.modelo = modelo
        self.ano = ano
        self.propietario = propietario

if __name__ == '__main__':
    # Configuración de la base de datos y creación de objetos
    contenedor = FileStorage('data.fs')
    db = DB(contenedor)
    conexion = db.open()
    base = conexion.root()

    # Crear y añadir vehículos con propietarios si no existen
    base['Carros'] = PersistentList([
            Vehiculo('Mazda', 'CX-5', 2023, Propietario('Juan', 30)),
            Vehiculo('Renault', 'Kwid', 2028, Propietario('Ana', 25)),
            Vehiculo('Toyota', 'Corolla', 2021, Propietario('Pedro', 40)),
            Vehiculo('Ford', 'Mustang', 2020, Propietario('Maria', 35)),
            Vehiculo('Chevrolet', 'Camaro', 2022, Propietario('Jose', 45))
        ])
    transaction.commit()
    Carros = base['Carros']

    # Encontrar todos los vehículos de "Juan"
    vehiculos_juan = []
    for car in Carros:
        if car.propietario.nombre == 'Juan':
            vehiculos_juan.append(car)
    print("Vehículos de Juan:")
    for v in vehiculos_juan:
        print(f'{v.marca} {v.modelo}')

    # Encontrar vehículos cuyos propietarios tienen más de 30 años
    vehiculos_prop_mayores_30 = []
    for car in Carros:
        if car.propietario.edad > 30:
            vehiculos_prop_mayores_30.append(car)
    print("Vehículos cuyos propietarios tienen más de 30 años:")
    for v in vehiculos_prop_mayores_30:
        print(f'{v.marca} {v.modelo} - Propietario: {v.propietario.nombre}')

    # Contar vehículos cuyos propietarios tienen menos de 40 años
    cantidad_vehiculos_prop_menores_40 = len([car for car in Carros if car.propietario.edad < 40])
    print(f'Cantidad de vehículos cuyos propietarios tienen menos de 40 años: {cantidad_vehiculos_prop_menores_40}')

    # Inicializar un contador para los vehículos cuyos propietarios tienen menos de 40 años
    cantidad_vehiculos_prop_menores_40 = 0
    for car in Carros:
        if car.propietario.edad < 40:
            cantidad_vehiculos_prop_menores_40 += 1
    print(f'Cantidad de vehículos cuyos propietarios tienen menos de 40 años: {cantidad_vehiculos_prop_menores_40}')

    # Cerrar la conexión y la base de datos
    conexion.close()
    db.close()