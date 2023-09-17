# Importar las librerías necesarias
from sklearn import datasets
from sklearn.decomposition import PCA
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns


# Cargar el conjunto de datos Iris
iris = datasets.load_iris()
X = iris.data
y = iris.target

# Aplicar PCA con dos componentes principales
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X)

# Crear un DataFrame para visualizar los resultados
df = pd.DataFrame(data=X_pca, columns=['PC1', 'PC2'])
df['Target'] = y

# Visualizar los resultados
sns.scatterplot(data=df, x='PC1', y='PC2', hue='Target')
plt.show()

