"""Funci�n principal"""
if __name__ == ""__main__":
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

