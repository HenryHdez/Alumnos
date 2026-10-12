from sklearn.datasets import load_iris
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt

# Cargar el conjunto de datos iris
iris = load_iris()

# Seleccionar dos características
X = iris.data[:, :2]

# Entrenar el modelo de clustering con KMeans
kmeans = KMeans(n_clusters=10, random_state=42)
kmeans.fit(X)

# Obtener los centroides y las etiquetas de cada punto
centroides = kmeans.cluster_centers_
labels = kmeans.labels_

# Visualizar los resultados
plt.scatter(X[:, 0], X[:, 1], c=labels)
plt.scatter(centroides[:, 0], centroides[:, 1], marker='*', s=300, c='r')
plt.title('KMeans Clustering - Dataset Iris')
plt.xlabel('longitud de tallo')
plt.ylabel('ancho de tallo')
plt.show()

# Evaluar los modelos con los datos de prueba
print("Resultados de KMeans:")
print(kmeans.predict(X))

