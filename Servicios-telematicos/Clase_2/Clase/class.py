matriz = [
    [1, 3, 5],
    [7, 9, 11],
    [13, 15, 17]
]

for lista in matriz:
    for elemento in lista:
        publicar = lambda x: x
        print(publicar(elemento))













for lista in matriz:
    list(map(lambda x: print(x), lista))