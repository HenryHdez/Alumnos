"""importe la libreria Tkinter"""
from tkinter import *
"""Matplotlib es una libreria para publicar graficas de tendencia."""
import matplotlin.pyplot as plt

def clic():
    lista=[1,2,3,4,5]
    plt.plot(lista)
    """Etiquetas"""
    plt.xlabel("Valores eje x")
    plt.ylabel("Valores eje y")
    plt.title("Titulo")
    """Activar grilla"""
    plt.grid(True)
    """Mostrar gráfico"""
    plt.show()

"""Función principal"""
if __name__ == ""__main__":
    Aplicacion=Tk()
    Aplicacion.title("Graficar")
    boton=Button(Aplicacion,text="Grafique",command=clic)
    boton.pack()
    Aplicacion.mainloop()