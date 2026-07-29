import transaction
from ZODB import DB
from ZODB.FileStorage import FileStorage
from persistent.mapping import PersistentMapping

# Coordenadas de las capitales colombianas
capitales = {
    'Bogotá': {'lat': 4.6097100, 'lon': -74.0817500},
    'Medellín': {'lat': 6.2518400, 'lon': -75.5635900},
    'Cali': {'lat': 3.4372200, 'lon': -76.5225000},
}

# Configuración de ZODB
storage = FileStorage('capitales.db')
db = DB(storage)
connection = db.open()
root = connection.root()

# Almacenar los datos en ZODB
root['capitales'] = PersistentMapping(capitales)
transaction.commit()

# Cerrar la conexión
connection.close()
db.close()