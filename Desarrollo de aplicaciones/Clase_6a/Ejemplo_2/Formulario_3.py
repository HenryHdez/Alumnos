import sys
from PyQt6 import uic, QtWidgets

Formulario, Ventana = uic.loadUiType("Ej2.ui")
#Uso de los slider y dial
class Aplicacion(QtWidgets.QMainWindow, Formulario):
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Formulario.__init__(self)
        self.setupUi(self)
        self.pushButton.clicked.connect(self.suma)
    def suma(self):
        x1 = int(self.dial.value())
        x2 = int(self.horizontalSlider_2.value())
        self.textEdit_2.setText(str(x1+x2))
        self.dial.setValue(20)
        self.horizontalSlider_2.setValue(40)

if __name__=="__main__":
    app = QtWidgets.QApplication(sys.argv)
    Vent = Aplicacion()
    Vent.show()
    app.exec()