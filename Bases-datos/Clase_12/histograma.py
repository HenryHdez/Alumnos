import pandas as pd
import matplotlib.pyplot as plt

# Crear un DataFrame de ejemplo
data = {'columna1': [1, 2, 3, 4, 5], 'columna2': [2, 4, 6, 10, 10]}
df = pd.DataFrame(data)
# Crear un histograma de la columna1
df['columna1'].hist()
# Agregar etiquetas al gráfico
plt.title('Histograma de columna1')
plt.xlabel('Valor')
plt.ylabel('Frecuencia')
# Mostrar el gráfico
plt.show()

