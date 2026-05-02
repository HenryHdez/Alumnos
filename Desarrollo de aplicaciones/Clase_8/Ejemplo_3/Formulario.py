import sys
from PyQt6 import uic, QtWidgets
import pandas as pd

Formulario, Ventana = uic.loadUiType("Ej3.ui")
#HTML
class Aplicacion(QtWidgets.QMainWindow, Formulario):
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Formulario.__init__(self)
        self.setupUi(self)
        self.radioButton.clicked.connect(self.HTML1)
    def HTML1(self):
        #self.plainTextEdit.appendHtml("<font color='red' size='6'><red>Hola <br> Mundo</font>")
        

        datos = {'nombre': ['Miguel', 'Mario', 'Pedro', 'Lucy'],
                'edad': [32, 45, 38, 43],
                'ciudad': ['Medellín','Bogotá','San Andrés','Pasto']}
        df=pd.DataFrame(datos) 
        print(df.to_html())
        self.plainTextEdit.appendHtml(df.to_html())        

if __name__=="__main__":
    app = QtWidgets.QApplication(sys.argv)
    Vent = Aplicacion()
    Vent.show()
    app.exec()