import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split

# Cargar datos de iris
iris = load_iris()
X = iris.data
y = iris.target
# Dividir datos en entrenamiento y prueba
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3)
# Crear modelo de regresión logística
logreg = LogisticRegression()
# Entrenar el modelo con los datos de entrenamiento
logreg.fit(X_train, y_train)
# Hacer predicciones con los datos de prueba
y_pred = logreg.predict(X_test)
# Calcular la precisión del modelo
accuracy = np.mean(y_pred == y_test)
print(f"Precisión del modelo: {accuracy:.2f}")


# Graficar los puntos de prueba con colores según la clase predicha
colors = ['red', 'green', 'blue']
markers = ['o', '^', 's']

for i in range(3):
    plt.scatter(X_test[y_pred == i, 0], X_test[y_pred == i, 1], 
                color=colors[i], marker=markers[i], label=f'Clase {i}')

# Graficar los datos reales y predichos
plt.figure(figsize=(10, 6))
plt.scatter(X_train[:, 0], X_train[:, 1], c=y_train, marker='o')
plt.scatter(X_test[:, 0], X_test[:, 1], c=y_pred, marker='s', alpha=0.4)
plt.xlabel('Longitud del tallo')
plt.ylabel('Ancho del tallo')
plt.title('Datos reales (círculos) y predichos (cuadros)')
plt.show()


