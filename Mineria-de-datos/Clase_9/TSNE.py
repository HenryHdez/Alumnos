import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.manifold import TSNE

# Cargar el conjunto de datos Iris
iris = load_iris()
X = iris.data
y = iris.target

# Aplicar T-SNE a los datos
tsne = TSNE(n_components=2, random_state=42)
X_tsne = tsne.fit_transform(X)

# Visualizar los datos en el espacio de baja dimensión
df = pd.DataFrame({'x': X_tsne[:,0], 'y': X_tsne[:,1], 'label': y})
colors = ['red', 'green', 'blue']
for i, target_label in enumerate(iris.target_names):
    subset_df = df[df['label'] == i]
    plt.scatter(subset_df['x'], subset_df['y'], 
                c=colors[i], label=target_label)
plt.legend()
plt.show()

