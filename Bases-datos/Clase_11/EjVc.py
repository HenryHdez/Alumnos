import geopandas as gpd
import matplotlib.pyplot as plt
from shapely.geometry import LineString

# Cargar el mapa de Colombia
mapa_colombia = gpd.read_file('MapaAdmin/COL_adm0.shp')  # Asegúrate de tener el archivo correcto

# Coordenadas de Bogotá y Medellín
coord_bogota = (-74.08175, 4.60971)
coord_medellin = (-75.56359, 6.25184)

# Crear una línea entre Bogotá y Medellín
linea = LineString([coord_bogota, coord_medellin])

# Crear un GeoDataFrame para la línea
linea_gdf = gpd.GeoDataFrame(geometry=[linea])

# Crear la figura y los ejes
fig, ax = plt.subplots()

# Dibujar el mapa de Colombia
mapa_colombia.plot(ax=ax, color='lightgrey')

# Dibujar la línea entre las capitales
linea_gdf.plot(ax=ax, linewidth=2, color='blue')

# Marcar las capitales
plt.plot(*coord_bogota, marker='o', color='red')
plt.plot(*coord_medellin, marker='o', color='red')

# Etiquetas para las ciudades
plt.text(coord_bogota[0], coord_bogota[1], 'Bogotá', fontsize=12, ha='right')
plt.text(coord_medellin[0], coord_medellin[1], 'Medellín', fontsize=12, ha='right')

# Mostrar el mapa
plt.show()
