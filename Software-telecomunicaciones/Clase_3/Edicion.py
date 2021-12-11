"""Función principal"""
if __name__ == ""__main__":
    """Crear ventana vacia"""
    Aplicacion=Tk()
    """Ajustar dimensiones de la ventana (Ancho, Alto)"""    
    Aplicacion.geometry("500x600")
    Aplicacion.title("Caracteristicas")
    """Color de fondo y texto Alto, Ancho y ubicación del texto"""
    etiqueta=Label(Aplicacion,text=T_Etiqueta,bg='red', fg='blue')
    """Tamaño del boton"""
    boton=Button(Aplicacion,text="Pulse", width=20, height=10, anchor="ne")
    T_Salida=" "
    C_Entrada=Entry(Aplicacion, textvariable=T_Salida)
    """Poner objetos en la ventada (aparecen
    en el orden que se pongan en el codigo)"""
    etiqueta.pack()
    boton.pack()
    C_Entrada.pack()
    """Bucle infinito"""
    Aplicacion.mainloop()


    """Fija ubicación y tamaño""" 
    etiqueta.place(x=70, y=140, width=100, height=30)
    boton.place(x=60, y=40, width=100, height=30)
    C_Entrada.place(x=260, y=240, width=100, height=30)