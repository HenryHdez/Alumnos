#Variables globales
z=10
w=20
#definir funciones en PYTHON
def Suma(a,b):
    global z,w
    w=0
    #Agregar codigo particular
    a*=3
    b-=2
    if a>b:
        print("a es mayor que b")
    return a+b

def Resta():
    global z,w
    #Agregar codigo particular
    z*=3
    w-=2
    print(z-w)

#Definir la funcion principal
if __name__=="__main__":
    w=32
    c= Suma(5,10)
    print(c)
    Resta()