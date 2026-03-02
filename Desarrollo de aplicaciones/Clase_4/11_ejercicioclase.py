from tkinter import *
x=0

def clic():
    """Función que se ejecuta al hacer clic en el botón"""
    global x
    canvas.create_rectangle(50+x, 50, 150+x, 150, fill='white', outline='white')
    x=x+10
    canvas.create_oval(50+x, 50, 150+x, 150, fill='blue', outline='black')
    
if __name__ == "__main__":
    Aplicacion=Tk()
    Aplicacion.title("Primer App")
    Aplicacion.geometry("500x600")
    canvas= Canvas(Aplicacion, width=400, height=300, bg='white')
    canvas.create_oval(50, 50, 150, 150, fill='blue', outline='black')
    canvas.pack(expand=YES, fill=BOTH)
    boton=Button(Aplicacion,text="+",command=clic)
    boton2=Button(Aplicacion,text="Cerrar", command=Aplicacion.destroy)
    boton.pack()
    boton2.pack()
    Aplicacion.mainloop()