import numpy as np
from sklearn import svm
#Suponga que tiene dos grupos de datos
#Tupla
x0, x1 = np.random.randn(10, 2), np.random.randn(10, 2)
print(x0)
print(x1)
#Concatene los grupos de datos
x = np.vstack((x0, x1))
print(x)
#Genere etiquetas para las imagenes x0 y x1
#Diez ceros para x0 y diez unos para x1
y = [0] * 10 + [1] * 10
print(y)
#Cree un clasificador lineal
svm.SVC(kernel='linear').fit(x, y)
#Verifique la predicción
print(svm.SVC(kernel='linear').fit(x, y).predict([[0.5, 1]]))
#Verifique el tipo de regresión usada
print(svm.SVR(kernel='linear').fit(x, y))

