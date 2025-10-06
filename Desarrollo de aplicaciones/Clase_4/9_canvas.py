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
    