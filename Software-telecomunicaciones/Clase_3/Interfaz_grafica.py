"""Mi primer aplicaci�n con interfaz grafica"""
"""importe la libreria Tkinter"""
from tkinter import *

"""Funci�n principal"""
if __name__ == ""__main__":
    """Crear ventana vacia"""
    Aplicacion=Tk()
    """Definici�n de los objetos a usar"""
    Aplicacion.title("Primer App")
    etiqueta=Label(Aplicacion,text="Saludos")
    boton=Button(Aplicacion,text="OK")
    """Poner objetos en la ventana"""
    etiqueta.pack()
    boton.pack()
    """La instrucci�n Mainloop manitene activa 
    la aplicaci�n"""
    Aplicacion.mainloop()