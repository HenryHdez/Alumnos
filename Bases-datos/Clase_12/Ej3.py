import sys
from PyQt6 import uic, QtWidgets
from PyQt6.QtGui import QPixmap
import matplotlib.pyplot as plt

Formulario, Ventana = uic.loadUiType("Ej2.ui")

class Aplicacion(QtWidgets.QMainWindow, Formulario):
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Formulario.__init__(self)
        self.setupUi(self)
        self.pushButton.clicked.connect(self.imagen)
    def imagen(self):
        plt.plot([1, 2, 3], [1, 4, 9])
        plt.savefig('Grafica.png')
        pixmap = QPixmap('Grafica.png')
        self.label.setPixmap(pixmap)
        

if __name__=="__main__":
    app = QtWidgets.QApplication(sys.argv)
    Vent = Aplicacion()
    Vent.show()
    app.exec()