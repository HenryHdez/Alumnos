"""importe la libreria Tkinter"""
from tkinter import *
"""sys contiene a try"""
import sys 

def clic():
    """Verifique si el recuerso u objeto est� disponible"""
    try:
        """Leer desde el campo (String por defecto)"""
        Numero=int(C_Entrada.get())
        T_Etiqueta="El numero es: "+str(Numero)
        """Modificar el estado de etiqueta"""
        etiqueta.config(text=T_Etiqueta)
    except ValueError:
        """La excepci�n se activa si hay al menos un error en el
        dato del campo de entrada"""
        T_Etiqueta="Introduzca un dato"
        etiqueta.config(text=T_Etiqueta)
        
"""Funci�n principal"""
if __name__ == "__main__":
    """Crear ventana vacia"""
    Aplicacion=Tk()
    """Definici�n de los objetos a usar"""    
    Aplicacion.title("Edici�n")
    """Crear etiqueta cpn variable de texto"""
    T_Etiqueta="Digite algo..."
    etiqueta=Label(Aplicacion,text=T_Etiqueta)
    """Crear Bot�n (clic=nombre de la funci�n
    asociada)"""
    boton=Button(Aplicacion,text="Pulse",command=clic)
    """Crear campo de entrada y/o salida"""
    T_Salida=" "
    C_Entrada=Entry(Aplicacion, textvariable=T_Salida)
    """Poner objetos en la ventada (aparecen
    en el orden que se pongan en el codigo)"""
    etiqueta.pack()
    boton.pack()
    C_Entrada.pack()
    """Bucle infinito"""
    Aplicacion.mainloop()

