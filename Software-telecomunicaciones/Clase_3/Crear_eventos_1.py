"""Función principal"""
if __name__ == ""__main__":
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

