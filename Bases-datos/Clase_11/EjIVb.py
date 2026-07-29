#Ejemplo de agregación
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
    base['Carros'] = PersistentList()
    base['Carros'].extend([
        Vehiculo('Mazda', 'CX-5', 2023),
        Vehiculo('Renault', 'Kwid', 2028),
        Vehiculo('Toyota', 'Corolla', 2021),
        Vehiculo('Ford', 'Mustang', 2020),
        Vehiculo('Chevrolet', 'Camaro', 2022)
    ])
    transaction.commit()

    Carros = base['Carros']

    # Contar cuántos vehículos hay de cada marca
    marcas = {}
    for car in Carros:
        marcas[car.marca] = marcas.get(car.marca, 0) + 1
    print("Cantidad de vehículos por marca:")
    for marca, cantidad in marcas.items():
        print(f'{marca}: {cantidad}')

    # Encontrar el vehículo más antiguo
    if Carros:
        mas_antiguo = Carros[0]
        for car in Carros:
            if car.ano < mas_antiguo.ano:
                mas_antiguo = car
        print(f'El vehículo más antiguo es {mas_antiguo.marca} {mas_antiguo.modelo} del año {mas_antiguo.ano}')
    else:
        print('No hay vehículos en la lista.')

    # Encontrar el vehículo más nuevo
    if Carros:  # Verificar que la lista no esté vacía
        mas_nuevo = Carros[0] 
        for car in Carros:
            if car.ano > mas_nuevo.ano:
                mas_nuevo = car  
        print(f'El vehículo más nuevo es {mas_nuevo.marca} {mas_nuevo.modelo} del año {mas_nuevo.ano}')
    else:
        print('No hay vehículos en la lista.')

    #Calcular la diferencia de años entre el vehículo más nuevo y el más antiguo
    diferencia_anos = mas_nuevo.ano - mas_antiguo.ano
    print(f'La diferencia de años entre el vehículo más nuevo y el más antiguo es {diferencia_anos}')

    # Cerrar la conexión y la base de datos
    conexion.close()
    db.close()