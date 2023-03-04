import sys
from PyQt6 import uic, QtWidgets

Formulario, Ventana = uic.loadUiType("Ej1.ui")

class Aplicacion(QtWidgets.QMainWindow, Formulario):
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Formulario.__init__(self)
        self.setupUi(self)
        self.Boton.clicked.connect(self.aviso)
    def aviso(self):
        self.Campo_entrada.setText("Hola mundo")

if __name__=="__main__":
    app = QtWidgets.QApplication(sys.argv)
    Vent = Aplicacion()
    Vent.show()
    app.exec()



