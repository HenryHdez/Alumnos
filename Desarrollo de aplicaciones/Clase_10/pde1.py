import numpy as np
import matplotlib.pyplot as plt

# Parámetros
L = 1.0       # Longitud del dominio
T = 1.0       # Tiempo total de simulación
Nx = 100      # Número de puntos espaciales
Nt = 1000     # Número de pasos de tiempo
Dx = L / Nx   # Paso espacial
Dt = T / Nt   # Paso de tiempo
chi = 1.0     # Sensibilidad quimiotáctica
mu = 1.0      # Coeficiente de difusión de v
gamma = 0.1   # Tasa de producción de v
delta = 0.1   # Tasa de degradación de v

# Inicialización
u = np.zeros((Nt, Nx))
v = np.zeros((Nt, Nx))
u[0, :] = np.sin(np.pi * np.linspace(0, L, Nx))**2  # Condición inicial para u
v[0, :] = np.cos(np.pi * np.linspace(0, L, Nx))**2  # Condición inicial para v

# Esquema de diferencias finitas
for n in range(0, Nt-1):
    for i in range(1, Nx-1):
        u[n+1, i] = u[n, i] + Dt * (
            (u[n, i+1] - 2*u[n, i] + u[n, i-1]) / Dx**2 -
            chi * u[n, i] * (1 - u[n, i]) * (v[n, i+1] - v[n, i-1]) / (2*Dx)
        )
        v[n+1, i] = v[n, i] + Dt * (
            mu * (v[n, i+1] - 2*v[n, i] + v[n, i-1]) / Dx**2 +
            gamma * u[n, i] - delta * v[n, i]
        )
    # Condiciones de contorno periódicas
    u[n+1, 0] = u[n+1, -2]
    u[n+1, -1] = u[n+1, 1]
    v[n+1, 0] = v[n+1, -2]
    v[n+1, -1] = v[n+1, 1]

# Visualización
plt.figure()
plt.plot(np.linspace(0, L, Nx), u[-1, :], label='u(t,x)')
plt.plot(np.linspace(0, L, Nx), v[-1, :], label='v(t,x)')
plt.legend()
plt.show()
