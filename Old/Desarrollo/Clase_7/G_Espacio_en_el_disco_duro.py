# -*- coding: utf-8 -*-
"""Importar líbreria psutil"""
import psutil
"""Indicar unidad a monitorear"""
disk_usage = psutil.disk_usage("C:\\")
def Convertir_Bytes_a_Gigas(bytes):  
    """Convertir a gigabytes."""    
    return bytes / 1024**3

if __name__ == "__main__": 
    print("Espacio total: {:.2f} GB."
          .format (Convertir_Bytes_a_Gigas(disk_usage.total)))
    print("Espacio disponible: {:.2f} GB."
          .format (Convertir_Bytes_a_Gigas(disk_usage.free)))
    print("Espacio usado: {:.2f} GB."
          .format (Convertir_Bytes_a_Gigas(disk_usage.used)))
    print("Porcentaje de espacio usado: {}%."
          .format (disk_usage.percent))

  

 