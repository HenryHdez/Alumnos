# lista = Agrupación de datos (mutables)
lista = [1, 2, 3, 8, 9]
# tupla = Grupo de datos (inmutable)
tupla = (1, 4, 8, 0, 5)
# Es decir, el contenido de la tupla no cambia
# durante la ejecución del programa
# Conjunto = Grupo de datos sin repetir
conjunto = set([1, 3, 1, 4])
# Colección de pares Clave:Valor
diccionario = {'a': 1, 'b': 3, 'z': 8}
print(lista)
print(tupla)
print(conjunto)
print(diccionario)

# Funciones para manejo de listas
# Agregar .append
lista.append(6)
# Eliminar .pop(index)
lista.pop(2)
# Insertar .insert(index, dato)
lista.insert(1,12)
#Funciones para manejo de tuplas
#Leer parámetro [index]
print(tupla[3])
#Convertir lista a tupla
tupla2=tuple(lista)
#Convertir tupla a lista
lista2=list(tupla)
print(tupla2)
print(lista2)

#Operaciones entre conjuntos
ConjA = set([1, 3, 4, 9])
ConjB = set([2, 6, 8, 9])
#Unión
ConjC = ConjA | ConjB
#Intersección
ConjC = ConjA & ConjB
#Diferencia
ConjC = ConjA - ConjB
#Agregar elemento
ConjC.add(10)
#Actualizar elementos
ConjC.update([1,2,6,7])
#Eliminar elemento
ConjC.remove(2)

#Manejo de diccionarios
diccionario = {'a': 1, 'b': 3, 'z': 8}
#Actualizar registro
diccionario['a'] = 10
#Leer claves y/o valores
lista_llaves=diccionario.keys()
lista_valores=diccionario.values()
#Agregar elemento
diccionario['Nueva_clave'] = 'valor'
#Registros de una clave
resul=diccionario.get('a')
#Eliminar
diccionario.pop('a')

#Archivos JSON
#JSON - Diccionario
import json
# Ejemplo de archivo JSON
x = '{ "Nombre":"Miguel", "Edad":40, "Ciudad":"Palmira"}'
# Decodificar JSON en diccionario:
y1 = json.loads(x)
print(y1["Edad"]) 

#Diccionario - JSON
import json
# Codificar diccionario a JSON:
y2 = json.dumps(y1)
# Presentar String:
print(y2) 

#Salida archivo
with open('salida.json', 'w') as archivo:
    json.dump(y2, archivo, indent=4)

#Leer archivo
with open('salida.json') as archivo:
    datos = json.load(archivo)
    print(datos)

