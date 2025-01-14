# -*- coding: utf-8 -*-
from scapy.all import *
import time 

def sniff_packets(packet):
    # muestra información sobre cada paquete capturado
    packet.show()
    # carga util del paquete
    print(packet.payload)
    time.sleep(5)

# Filtro para capturar solo paquetes ARP (Address Resolution Protocol)
#Filtrar por la MAC 
arp_filter = "http" #tcp, http

# Filtro para capturar solo paquetes que provengan de la dirección IP 192.168.1.6
ip_filter = "src host 172.24.32.1"

# Captura paquetes ARP (Ruta)
#sniff(filter=arp_filter, prn=sniff_packets)

# Captura paquetes de la dirección IP 192.168.0.1
sniff(filter=ip_filter, prn=sniff_packets)

