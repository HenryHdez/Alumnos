from tkinter import *
from PIL import Image, ImageTk

if __name__ == "__main__":
    Aplicacion =Tk()
    canvas = Canvas(Aplicacion, width=400, height=300, bg='white')
    Imagen = Image.open('./Bob.jpg')                      #Abrir imágen
    Imagen = Imagen.resize((400, 250))                    #Redimensionar
    Foto   = ImageTk.PhotoImage(Imagen)                   #Fotograma
    canvas.create_image(10, 10, image=Foto, anchor=NW)
    canvas.pack(expand=YES, fill=BOTH)
    mainloop()
    
    # Líneas
    canvas.create_line(10, 10, 80, 80)
    canvas.create_line(10, 80, 80, 10)
    # Ovalo o circulo
    canvas.create_oval(100, 10, 180, 80, width=2, fill='blue')
    # Arco
    canvas.create_arc(200, 10, 280, 100)
    # Rectangulo
    canvas.create_rectangle(10, 100, 200, 200, width=5, fill='red')
    # Texto
    canvas.create_text(100, 280, text='Hola Canvas', fill='green')
    