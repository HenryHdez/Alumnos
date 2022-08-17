# -*- coding: utf-8 -*-
"""PYTHON tiene la capacidad de almacenar listas"""
Lista=["Sujeto 1", "Sujeto 2", "Sujeto 3"]
"""La forma más sencilla de publicar es:"""
print(Lista)
"""Sin embargo, puede usar una estructura"""
#El comando len se usa para conocer la longitud de la lista
for i in range(len(Lista)):
    print(Lista[i])
"""Las matrices son un caso particular de lista, ya que,
son una lista anidada."""
#Ejemplo
Matriz=[]
Numero_Filas=5
Numero_Columnas=10
for i in range(Numero_Filas):
    Matriz.append([])
    for j in range(Numero_Columnas):
        Matriz[i].append("Dato a asignar en la posición: "
              +str(i)+", "+str(j))
print(Matriz)

