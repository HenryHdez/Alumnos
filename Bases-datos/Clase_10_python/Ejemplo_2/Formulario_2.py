import sys
from PyQt6 import uic, QtWidgets

Formulario, Ventana = uic.loadUiType("Ej2.ui")
#Uso de los checkbox
class Aplicacion(QtWidgets.QMainWindow, Formulario):
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Formulario.__init__(self)
        self.setupUi(self)
        self.checkBox.clicked.connect(self.CB)
        self.checkBox_2.clicked.connect(self.CB)
    def CB(self):
        if(self.checkBox.isChecked()):
            self.textEdit.setText("Pulse el check 1")
        elif(self.checkBox_2.isChecked()):
            self.textEdit.setText("Pulse el check 2")
        else:
            self.textEdit.setText("Ningun check")

if __name__=="__main__":
    app = QtWidgets.QApplication(sys.argv)
    Vent = Aplicacion()
    Vent.show()
    app.exec()