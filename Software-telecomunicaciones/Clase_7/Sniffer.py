"""Ejemplo de detección de circulación de paquetes."""
from scapy.all import *
"""Define interface a traves de la cual se realiza en escane"""
interface1 = "Ethernet"
interface1 = "Wi-Fi"
"""Función para ejercutar el sniffer"""
def Imprimir_Informacion(paquete):
    """IP es un parámetro heredado de la red"""
    ip_layer = paquete.getlayer(IP)
    print("Información del paquete de {src}: \n" 
          .format(scr=ip_layer.scr))
    if ip_layer.haslayer( Raw):
       """Informacón del paquete"""
       Cabecera = ip_layer.getlayer( Raw ).load
       print(Cabecera.decode(errors='ignore'))

if __name__ == "__main__":
    print("Presione crtl+c para terminar.")
    """Llamar hilo de sniffer"""
    sniff(iface=interface2, filter="ip", prn=Imprimir_Informacion)
    print("Termino el sniffer.")