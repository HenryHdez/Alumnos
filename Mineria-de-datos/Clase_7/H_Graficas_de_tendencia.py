# -*- coding: utf-8 -*-
"""Matplotlib es una libreria para publicar graficas de tendencia."""
import matplotlib.pyplot as plt

lista=[1,2,3,4,5]
plt.plot(lista)
"""Etiquetas"""
plt.xlabel("Valores eje x")
plt.ylabel("Valores eje y")
plt.title("Titulo")
"""Activar grilla"""
plt.grid(True)
"""Mostrar gráfico"""
plt.show()
