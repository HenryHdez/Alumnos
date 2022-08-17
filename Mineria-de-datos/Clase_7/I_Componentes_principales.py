#librería para el manejo de datos
import pandas as pd
#librería de procesamiento numérico
import numpy as np
#librería de graficos
import matplotlib.pyplot as plt
#librería de aprendizaje computacional
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler

""">>>>>>>>>>>>>>>>>>>>>>PASO 1 (Selección)<<<<<<<<<<<<<<<<<<<<<"""
#Ruta de acceso al directorio
ruta = "D:\GitHub\Alumnos\Mineria-de-datos\A_Datasets\Flores.csv"
#Crear un dataFrame usando pandas
df = pd.read_csv(ruta)
#Retorna las últimas filas del dataFrame
box = df.tail()
#Dividir el dataFrame en dos 
#Predictores (4 primeras columnas)
X = df.iloc[:, 0:4].values
#Datos a predecir (especies)
y = df.iloc[:, 4].values
print(X)
print(y)

""">>>>>>>>>>>>>>>>>>>>>PASO 2 (Normalización)<<<<<<<<<<<<<<<<<<<"""
#Realizar un cambio de escala de de los datos usando una transformación
#Normal o Gaussiana (z = (x - u) / s)
from sklearn.preprocessing import StandardScaler
X_z = StandardScaler().fit_transform(X)

""">>>>>>>>PASO 3 (Cálculo de autovectores y autovalores)<<<<<<<<"""
# Calcular la matriz de covarianza
M_cov = np.cov(X_z.T)
print(M_cov)

# Calcular los autovalores y autovectores de la matriz de covarianza
cov_mat = np.cov(X_z.T)
[auto_val, auto_vec] = np.linalg.eig(cov_mat)

#  Hacer una lista de parejas (autovector, autovalor) 
auto_parejas = [(np.abs(auto_val[i]), auto_vec[:,i]) for i in range(len(auto_val))]

# Ordenar las parejas en orden descendiente con la función sort
auto_parejas.sort(key=lambda x: x[0], reverse=True)

# Visualizar la lista de autovalores en orden desdenciente
print("Autovalores en orden descendiente:")
for i in auto_parejas:
    print(i[0])

""">>>>>>>>PASO 4 (Seleccionar los autovectores 
            correspondientes a los componentes principales)<<<<<<<<"""
#A partir de los autovalores, calculamos la varianza explicada
tot = sum(auto_val)
var_exp = [(i / tot)*100 for i in sorted(auto_val, reverse=True)]
cum_var_exp = np.cumsum(var_exp)

#Representamos en un diagrama de barras la varianza explicada por
#cada autovalor, y la acumulada
plt.figure(num = 1, figsize=(6, 4))
plt.bar(range(4), var_exp, alpha=0.5, align="center",
            label="Varianza individual explicada", color="g")
plt.step(range(4), cum_var_exp, where="mid", linestyle="--",
             label="Varianza explicada acumulada")
plt.ylabel("Radio de Varianza Explicada")
plt.xlabel("Componentes Principales")
plt.legend(loc="best")
plt.tight_layout()
plt.show()

""">>>>>>>>PASO 5 (Proyectamos los datos sobre
                    un espacio de dimensionalidad menor)<<<<<<<<"""
#Genere la matríz a partir de los pares auto valor-auto vector
matrix_w = np.hstack((auto_parejas[0][1].reshape(4,1),
                      auto_parejas[1][1].reshape(4,1)))
#Realice un producto punto de los valores normalizados con los
#componentes seleccionados
Y = X_z.dot(matrix_w)
print(Y)

#Tomar los resultados del producto punto
x_1 = Y[:, 0]
y_1 = Y[:, 1]
colores = []
for i in y:
    if(i=="Iris-setosa"):
        colores.append("magenta")
    elif(i=="Iris-versicolor"):
        colores.append("blue")
    else:
        colores.append("red")
plt.figure(num = 2, figsize=(6, 4))
plt.scatter(x_1,
            y_1,
            c=colores)
plt.xlabel("Componente principal 1")
plt.ylabel("Componente principal 2")
plt.legend(loc="lower center")
plt.tight_layout()
plt.show()

