import sys
from PyQt6 import uic, QtWidgets
from PyQt6.QtGui import QPixmap

Formulario, Ventana = uic.loadUiType("Ej2.ui")

class Aplicacion(QtWidgets.QMainWindow, Formulario):
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Formulario.__init__(self)
        self.setupUi(self)
        self.pushButton.clicked.connect(self.imagen)
    def imagen(self):
        pixmap = QPixmap('Prueba.jpg')
        self.label.setPixmap(pixmap)
        

if __name__=="__main__":
    app = QtWidgets.QApplication(sys.argv)
    Vent = Aplicacion()
    Vent.show()
    app.exec()