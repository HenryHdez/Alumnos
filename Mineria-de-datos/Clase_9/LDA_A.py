import numpy as np

# Generar datos de ejemplo para G1 y G2
np.random.seed(0)
G1 = np.random.randint(0, 10, size=(10, 2))
G2 = np.random.randint(0, 10, size=(10, 2))

# Paso 1: Calcular las medias de las variables para cada grupo
mu1 = np.mean(G1, axis=0)
mu2 = np.mean(G2, axis=0)

# Paso 2: Calcular la matriz de dispersión intra-grupo
S1 = np.cov(G1.T)
S2 = np.cov(G2.T)
Sw = S1 + S2

# Paso 3: Calcular la matriz de dispersión entre-grupos
Sb = np.outer(mu1 - mu2, mu1 - mu2)

# Paso 4: Calcular la función discriminante lineal
w = np.linalg.inv(Sw).dot(mu1 - mu2)

# Paso 5: Clasificar nuevas observaciones
x_new = np.array([-15, -4]) # Nueva observación
y = w.dot(x_new)
c = (w.dot(mu1) + w.dot(mu2)) / 2 # Umbral
if y >= c:
    print("La nueva observación pertenece a G1")
else:
    print("La nueva observación pertenece a G2")



