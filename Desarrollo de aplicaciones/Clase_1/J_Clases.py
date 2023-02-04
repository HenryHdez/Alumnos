class Carro:                #Definición de la clase
    Marca = ''              #Datos
    Modelo = ''             #Datos
    def Mostrar_marca(self):#Atributo 1
        print(self.Marca)
    def Mostrar_Model(self):#Atributo 2
        print(self.Modelo)
     
Vehiculo = Carro()           #Llamado a la clase
Vehiculo.Marca  = 'Ferrari'
Vehiculo.Modelo = '2050'
Vehiculo.Mostrar_marca()
Vehiculo.Mostrar_Model()

