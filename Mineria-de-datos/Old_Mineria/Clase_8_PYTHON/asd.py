from tkinter import *

def clic():
    try:
        var=int(entrada1.get())
    except:
        var="Error"
    etiqueta.config(text=var)
    
    
if __name__ == "__main__":
    Aplicacion=Tk()
    Aplicacion.geometry("500x600")
    
    Aplicacion.title("Primer App")
    etiqueta=Label(Aplicacion,text="Saludos", bg="red", fg="blue")
    entrada1=Entry(Aplicacion,text="Saludos1", bg="yellow", fg="blue")
    entrada2=Entry(Aplicacion,text="Saludos2", bg="yellow", fg="blue")
    boton=Button(Aplicacion,text="OK", command=clic)

    etiqueta.place(x=70, y=140, width=100, height=30)
    entrada1.place(x=270, y=140, width=100, height=30)
    entrada2.place(x=170, y=140, width=100, height=30)
    boton.place(x=470, y=140, width=100, height=30)
    
    Aplicacion.mainloop()