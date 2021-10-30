import numpy as np
from sklearn import metrics
import matplotlib.pyplot as plt
#Suponga que estimo un valor de salida y precisión
#Valores aleatorios de y
datos_predecidos = np.array([1,1,2,2,3,3,4,4,2,3])
#Valores aleatorios de precisión
precision = np.array([0.3, 0.4, 0.95,0.78,0.8,0.64,0.86,0.81,0.9, 0.8])
#Calculo de la curva ROC y AUC
fpr, tpr, thresholds = metrics.roc_curve(datos_predecidos, precision, pos_label=2)
roc_auc = metrics.auc(fpr, tpr)
#Presentar resultado
plt.figure()
plt.plot(fpr, tpr, label='Curva ROC (area = %0.2f)' % roc_auc)
plt.plot([0, 1], [0, 1], 'k--')
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.xlabel('Falsos positivos')
plt.ylabel('Verdaderos positivos')
plt.title('Ejemplo de ROC')
plt.legend(loc="lower right")
plt.show()

