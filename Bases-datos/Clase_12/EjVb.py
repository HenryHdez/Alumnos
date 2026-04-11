import geopandas as gpd
import matplotlib.pyplot as plt
from shapely.geometry import Point

#Descarga un mapa de https://www.diva-gis.org/gdata

# Cargar el Shapefile del mapa de Colombia
mapa_colombia = gpd.read_file('MapaAdmin/COL_adm0.shp')
#mapa_colombia2 = gpd.read_file('MapaCarreteras/COL_roads.shp')

# Coordenadas de ejemplo de algunas capitales de Colombia
capitales_data = {
    'Ciudad': ['Bogotá', 'Medellín', 'Cali'],
    'Coordenadas': [Point(-74.08175, 4.60971), Point(-75.56359, 6.25184), Point(-76.5225, 3.43722)]
}

# Crear un GeoDataFrame para las capitales
capitales = gpd.GeoDataFrame(capitales_data, geometry='Coordenadas')

# Crear el plot
fig, ax = plt.subplots()

# Dibujar el mapa de Colombia
mapa_colombia.plot(ax=ax, color='lightgrey')

#Dibujar Carreteras
#mapa_colombia2.plot(ax=ax, color='green')

# Dibujar las capitales en el mapa
capitales.plot(ax=ax, marker='o', color='red', markersize=50)

# Añadir etiquetas de ciudad
for x, y, label in zip(capitales.geometry.x, capitales.geometry.y, capitales['Ciudad']):
    ax.annotate(label, xy=(x, y), xytext=(3, 3), textcoords="offset points")

plt.show()