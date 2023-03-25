# -*- coding: utf-8 -*-
"""Ejemplo de detección de circulación de paquetes."""
from scapy.all import *
"""Define interface a traves de la cual se realiza en escane"""
interface1 = "Ethernet"
interface2 = "Wi-Fi"
"""Función para ejercutar el sniffer"""
def Imprimir_Informacion(paquete):
    """IP es un parámetro heredado de la red"""
    ip_layer = paquete.getlayer('10.28.48.116')
    print("Información del paquete de {src}: \n" 
          .format(src=ip_layer.src))
    if ip_layer.haslayer( Raw ):
        """Información del paquete"""
        Cabecera = ip_layer.getlayer( Raw ).load
        print(Cabecera.decode(errors='ignore'))

if __name__ == "__main__":
    print("Presione crtl+c para terminar.")
    """Llamar hilo de sniffer"""
    sniff(iface=interface1, filter="ip", prn=Imprimir_Informacion)
    print("Termino el sniffer.")