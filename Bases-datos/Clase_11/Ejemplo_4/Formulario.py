import sys
import pandas as pd
from PyQt6 import uic, QtWidgets

Formulario, Ventana = uic.loadUiType("Ej4.ui")
class Aplicacion(QtWidgets.QMainWindow, Formulario):
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Formulario.__init__(self)
        self.setupUi(self)
        self.pushButton.clicked.connect(self.Mostrar_tabla)
    def Mostrar_tabla(self):
        datos = {'nombre': ['Miguel', 'Mario', 'Pedro', 'Lucy'],
                    'edad': [32, 45, 22, 38],
                    'ciudad': ['Bogotá', 'Cali', 'Medellín', 'Pasto']}
        df = pd.DataFrame(datos)
        tabla_html = df.to_html() #Crear versión HTML del df
        self.textBrowser.setHtml(tabla_html)

if __name__=="__main__":
    app = QtWidgets.QApplication(sys.argv)
    Vent = Aplicacion()
    Vent.show()
    app.exec()
    
    