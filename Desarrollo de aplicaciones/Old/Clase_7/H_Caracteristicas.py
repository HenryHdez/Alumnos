import psutil

"""Frecuencia del procesador"""
print(psutil.cpu_freq())
"""Porcentaje de uso del procesador"""
print(psutil.cpu_percent())
""" Devuelve varias estadisticas de CPU como una tupla con nombre:
    ctx_switches: número de cambios de contexto (voluntario + involuntario)
    desde el arranque.
    interrupciones: número de interrupciones desde el arranque.
    soft_interrupts: número de interrupciones de software desde el arranque.
    syscalls: número de llamadas al sistema desde el inicio.
    """
print(psutil.cpu_stats())
"""Segunos que ha pasado la CPU en ejecución"""
print(psutil.cpu_times())
"""Promedio de carga de la CPU en los ultimos 15 minutos"""
print(psutil.getloadavg())
"""Uso de la memoria RAM"""
print(psutil.virtual_memory())
"""Uso de la memoria de intercambio"""
print(psutil.swap_memory())
"""Particiones del disco duro"""
print(psutil.disk_partitions())

"""Redes"""
"""Medidor de cantidad de paquetes de llegada y envio."""
print(psutil.net_io_counters())
"""Cantidad de conexiones disponibles"""
print(psutil.net_connections(kind='tcp'))
"""kind es un filtro que puede configurarse como:'all', 'tcp', 'tcp4',
'udp', 'udp4', 'inet', 'inet4', 'inet6', 'tcp6', 'udp6'"""
print( psutil.net_if_addrs())
"""Leer caracteristicas de la tarjeta de red"""
print(psutil.net_if_stats())

"""Sensores"""
"""Medir uso de la batería del computador (si la hay)"""
print(psutil.sensors_battery())
"""Uso de los ventiladores (Si los hay)"""
#print(psutil.sensors_fans())
"""Medir temperatura (si hay sensor)"""
#print(psutil.sensors_temperatures())
"""Usuarios del CPU"""
print(psutil.users())