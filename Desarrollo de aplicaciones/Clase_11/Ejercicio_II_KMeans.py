import math

# Datos: puntos de datos
datos = [(1, 1), (2, 1), (4, 3), (5, 4)]
# Número de clústeres
k = 2
# Inicializar centroides manualmente
centroides = [(1.5, 1), (4.5, 3.5)]

# Función para calcular la distancia euclidiana
def distancia_euclidiana(punto1, punto2):
    return math.sqrt((punto1[0] - punto2[0])**2 + (punto1[1] - punto2[1])**2)

# Asignar puntos a clústeres en función del centroide más cercano
def asignar_clusteres(datos, centroides):
    clústeres = {}
    for i in range(k):
        clústeres[i] = []
    
    for punto in datos:
        distancias = [distancia_euclidiana(punto, centroide) for centroide in centroides]
        id_clúster = distancias.index(min(distancias))
        clústeres[id_clúster].append(punto)
    
    return clústeres

# Recalcular los centroides
def recalcular_centroides(clusteres):
    nuevos_centroides = []
    for id_clúster, puntos in clusteres.items():
        if len(puntos) > 0:
            # Calcular el promedio para cada coordenada
            promedio_x = sum(punto[0] for punto in puntos) / len(puntos)
            promedio_y = sum(punto[1] for punto in puntos) / len(puntos)
            nuevos_centroides.append((promedio_x, promedio_y))
        else:
            # Si el clúster está vacío, mantener el mismo centroide
            nuevos_centroides.append(centroides[id_clúster])
    return nuevos_centroides

# K-Means 
def kmeans(datos, k, centroides, max_iteraciones=100, tolerancia=0.001):
    for iteracion in range(max_iteraciones):
        # Asignar puntos a clústeres
        clústeres = asignar_clusteres(datos, centroides)
        # Recalcular los centroides
        nuevos_centroides = recalcular_centroides(clústeres)
        # Calcular el cambio en los centroides
        cambios_centroides = [distancia_euclidiana(centroides[i], nuevos_centroides[i]) for i in range(k)]
        # Actualizar los centroides
        centroides = nuevos_centroides
        print(f"Iteración {iteracion + 1}:")
        print(f"Centroides: {centroides}")
        print(f"Clústeres: {clústeres}")
        # Detener si los centroides no cambian significativamente
        if max(cambios_centroides) < tolerancia:
            print("\nConvergencia alcanzada.")
            break
    return clústeres, centroides

# Ejecutar el algoritmo K-Means
clusteres, centroides_finales = kmeans(datos, k, centroides)

# Mostrar resultados finales
print("\nResultados Finales:")
print("Clústeres:")
for id_cluster, puntos in clusteres.items():
    print(f"Clúster {id_cluster+1}: {puntos}")
print("Centroides finales:")
print(centroides_finales)