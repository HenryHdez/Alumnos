# -*- coding: utf-8 -*-
from tkinter import *
from tkinter import Tk
from tkinter import ttk

def seleccion(event):
    selection = Combo.get()           #Leer del combobox
    T_Salida.set(str(selection))      #Modificar StringVar
    print(Spin.get())                 #con Spin funciona set y get
    
if __name__ == "__main__":
    Aplicacion=Tk()
    Aplicacion.geometry("500x600")
    Aplicacion.title("Caracteristicas")
    Etiqu = Label(Aplicacion,text="Lista")
    #Combobox
    Combo = ttk.Combobox(Aplicacion,
                         state="readonly",
                         values=["Op1", "Op2", "Op3", "Op4"])
    Combo.set("Op3")
    Combo.bind("<<ComboboxSelected>>", seleccion)
    #Spinbox
    Spin= ttk.Spinbox(Aplicacion, from_ = 0, to = 10, increment = 1)
    #Variable string
    T_Salida=StringVar(Aplicacion)
    Entra = Entry(Aplicacion, textvariable=T_Salida)
    
    #Publicar
    Spin.pack()
    Etiqu.pack()
    Combo.pack()
    Entra.pack()
    Aplicacion.mainloop()
