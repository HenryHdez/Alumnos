# -*- coding: utf-8 -*-
from scapy.all import sr1, IP, ICMP
import time

def medir_latencia(destino, timeout):
   paquete = IP(dst=destino)/ICMP()
   tiempo_inicio = time.time()
   respuesta = sr1(paquete, timeout=timeout, verbose=0)
   tiempo_fin = time.time()
   if respuesta:
      #Convertir a ms
      rtt = (tiempo_fin - tiempo_inicio) * 1000
      print(f"Latencia hacia {destino}: {rtt:.2f} ms")
   else:
      print(f"No hay respuesta desde {destino} (timeout de {timeout}s)")

medir_latencia("192.168.1.7", 2)


