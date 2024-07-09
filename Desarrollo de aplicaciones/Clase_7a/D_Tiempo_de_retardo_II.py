# -*- coding: utf-8 -*-
from scapy.all import srp,IP,ICMP
#Definir la cantidad de intentos que necesita (paquetes)
Cantidas_paquetes=4
#Definir la dirección IP
Direccion_IP="192.168.130.54"
# Variable tiempo
t=0.0
#Estructura para enviar cierta cantidad de paquetes
for i in range(Cantidas_paquetes):
    # SRP retorna entre otras cosas la MAC del equipo
    ans, unans=srp(IP(dst=Direccion_IP)/ICMP(), iface="Ethernet", 
                   filter='icmp', verbose=0, timeout=1)
    if(ans):
     # Información que llega 
        rx = ans[0][1]
     # Información que se envía 
        tx = ans[0][0]
     # Este es el calculo de tiempo de ida y vuelta del paquete
        diferencia_de_tiempo = abs(rx.time-tx.sent_time)
        print ("Ping: "+str(i)+" "+str(diferencia_de_tiempo))
        t+=diferencia_de_tiempo
    else:
        print("No conectado")
print("tiempo total "+str(t))


