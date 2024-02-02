import sys
from PyQt6 import uic, QtWidgets

Formulario, Ventana = uic.loadUiType("Ej2.ui")
#Uso de los radiobuttom
class Aplicacion(QtWidgets.QMainWindow, Formulario):
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        Formulario.__init__(self)
        self.setupUi(self)
        self.radioButton.clicked.connect(self.RB)
        self.radioButton_2.clicked.connect(self.RB)
        self.radioButton_3.clicked.connect(self.RB)
        self.checkBox.clicked.connect(self.CB)
        self.checkBox_2.clicked.connect(self.CB)
        self.pushButton.clicked.connect(self.suma)
        
    def RB(self):
        self.plainTextEdit.clear()          #Borrar plainText
        if(self.radioButton.isChecked()):
            self.plainTextEdit.insertPlainText("Pulse el botón 1")
        elif(self.radioButton_2.isChecked()):
            self.plainTextEdit.insertPlainText("Pulse el botón 2")
        elif(self.radioButton_3.isChecked()):
            self.plainTextEdit.insertPlainText("Pulse el botón 3")
        else:
            self.plainTextEdit.insertPlainText("Ningun botón")

    def CB(self):
        if(self.checkBox.isChecked()):
            self.textEdit.setText("Pulse el check 1")
        elif(self.checkBox_2.isChecked()):
            self.textEdit.setText("Pulse el check 2")
        else:
            self.textEdit.setText("Ningun check")
            
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