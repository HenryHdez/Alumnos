"""importe la libreria Tkinter"""
from tkinter import *
"""sys contiene a try"""
import sys 

def clic():
    """Verifique si el recuerso u objeto está disponible"""
    try:
        """Leer desde el campo (String por defecto)"""
        Numero=int(C_Entrada.get())
        T_Etiqueta="El numero es: "+str(Numero)
        """Modificar el estado de etiqueta"""
        etiqueta.config(text=T_Etiqueta)
    except ValueError:
        """La excepción se activa si hay al menos un error en el
        dato del campo de entrada"""
        T_Etiqueta="Introduzca un dato"
        etiqueta.config(text=T_Etiqueta)
        
"""Función principal"""
if __name__ == "__main__":
    """Crear ventana vacia"""
    Aplicacion=Tk()
    """Definición de los objetos a usar"""    
    Aplicacion.title("Edición")
    """Crear etiqueta cpn variable de texto"""
    T_Etiqueta="Digite algo..."
    etiqueta=Label(Aplicacion,text=T_Etiqueta)
    """Crear Botón (clic=nombre de la función
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

