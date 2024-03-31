#Ejemplo 1 "Definición de la clase"
class Auto:
    #Inicialización de la clase o método constructor
    def __init__(self, marca, modelo, año):
        self.marca = marca
        self.modelo = modelo
        self.año = año
        self.encendido = False
    #Atributo o método 1
    def arrancar(self):
        if not self.encendido:
            self.encendido = True
            print(f"El {self.marca} {self.modelo} está arrancando.")
        else:
            print(f"El {self.marca} {self.modelo} ya está encendido.")
    #Atributo o método 2
    def detener(self):
        if self.encendido:
            self.encendido = False
            print(f"El {self.marca} {self.modelo} se ha detenido.")
        else:
            print(f"El {self.marca} {self.modelo} ya está detenido.")

if __name__ == '__main__':
    #Uso de la clase
    mi_auto = Auto("Toyota", "Corolla", 2020)
    mi_auto.arrancar()
    mi_auto.detener()