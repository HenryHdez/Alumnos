# Ejemplo 2 "Herencia y polimorfismo"
class Auto:
    # Inicialización de la clase
    def __init__(self, marca, modelo, año):
        self.marca = marca
        self.modelo = modelo
        self.año = año
        self.encendido = False
    # Método para arrancar el auto
    def arrancar(self):
        if not self.encendido:
            self.encendido = True
            print(f"El {self.marca} {self.modelo} está arrancando.")
        else:
            print(f"El {self.marca} {self.modelo} ya está encendido.")

# Subclase Sedan que hereda de Auto
class Sedan(Auto):
    def arrancar(self):
        print(f"Arrancando el Sedan {self.marca} {self.modelo}.")
        #Super da el acceso a métodos de la clase padre
        super().arrancar()
    #Método no nativo de la clase (polimorfismo)
    def caracteristica(self):
        print(f"El Sedan {self.modelo} tiene un maletero espacioso.")

# Subclase Deportivo que hereda de Auto
class Deportivo(Auto):
    def arrancar(self):
        print(f"Arrancando el Deportivo {self.marca} {self.modelo}.")
        super().arrancar()

    def caracteristica(self):
        print(f"El Deportivo {self.modelo} tiene una aceleración rápida.")

if __name__ == '__main__':
    VehSedan = Sedan("Toyota", "Camry", 2022)
    VehSedan.arrancar()
    VehSedan.caracteristica()

    VehDepor = Deportivo("Ferrari", "488", 2020)
    VehDepor.arrancar()
    VehDepor.caracteristica()