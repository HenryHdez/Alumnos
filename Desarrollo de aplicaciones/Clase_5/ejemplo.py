from tkinter import *
from time import sleep

x= 0
destino = (0,0)
Diccionario={"pos1":(10,10),"pos2":(10,20), "pos3":(20,20)}
llaves=list(Diccionario.keys())
print(llaves)
pos_llave=0
llave_actual=llaves[pos_llave]
print(llave_actual)

def mover():
    global x
    global Diccionario
    global pos_llave
    x=x+40
    try: #Si no esta llave haga tal cosa
        llave_actual=llaves[pos_llave]
        destino=Diccionario[llave_actual]
        print(destino)
        if(pos_llave<len(llaves)):
            pos_llave=pos_llave+1
        else:
            pos_llave=0
    except:
        print('Error')
    #Borrar el canvas
    canvas.delete("all")
    #Crear el circulo
    canvas.create_oval(x, 10, x+80, 80, width=2, fill='blue')
    #Actualizar el canvas cada segundo
    Aplicacion.after(1000, mover)
    
if __name__ == "__main__":

    Aplicacion =Tk()
    canvas = Canvas(Aplicacion, width=400, height=300, bg='white')  
    #mover()
    canvas.pack(expand=YES, fill=BOTH)
    #mainloop()
    
    #Archivos JSON
    #JSON - Diccionario
    import json
    # Ejemplo de archivo JSON
    x2 = '{ "Nombre":[10,10], "Edad":[20,30], "Ciudad":[10,20]}'
    # Decodificar JSON en diccionario:
    y1 = json.loads(x2)
    print(y1["Edad"]) 

    #Diccionario - JSON
    #import json
    # Codificar diccionario a JSON:
    #y2 = json.dumps(y1)
    # Presentar String:
    #print(y2) 

    #Salida archivo
    with open('salida.json', 'w') as archivo:
        json.dump(y1, archivo, indent=4)

    #Leer archivo
    with open('salida.json') as archivo:
        datos = json.load(archivo)
        print(datos)

