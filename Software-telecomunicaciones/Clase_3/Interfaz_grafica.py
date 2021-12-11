"""Mi primer aplicación con interfaz grafica"""
"""importe la libreria Tkinter"""
from tkinter import *

"""Función principal"""
if __name__ == ""__main__":
    """Crear ventana vacia"""
    Aplicacion=Tk()
    """Definición de los objetos a usar"""
    Aplicacion.title("Primer App")
    etiqueta=Label(Aplicacion,text="Saludos")
    boton=Button(Aplicacion,text="OK")
    """Poner objetos en la ventana"""
    etiqueta.pack()
    boton.pack()
    """La instrucción Mainloop manitene activa 
    la aplicación"""
    Aplicacion.mainloop()