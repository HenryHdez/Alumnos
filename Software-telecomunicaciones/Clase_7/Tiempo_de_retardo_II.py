from scapy.all import *
#Definir la cantidad de intentos que necesita (paquetes)
Cantidas_paquetes=4
#Definir la dirección IP
Direccion_IP="10.28.0.1"
#Construcción de la estructura para empaquetar la información
# /Medio/Dirección/Protocolo
paquete = Ether()/IP(dst=Direccion_IP)/ICMP()
# Variable tiempo
t=0.0
#Estructura para enviar cierta cantidad de paquetes
for i in range(Cantidas_paquetes):
    # la función SRP implementa el ARP ping y retorna la MAC del equipo de dst
    ans,unans=srp(paquete,iface="Ethernet", filter='icmp', verbose=0, timeout=2)
    if(ans):
     # Esta ubicación del arreglo contiene los campos relacionados con la
     # información que llega 
        rx = ans[0][1]
     # Esta ubicación del arreglo contiene los campos relacionados con la
     # información que se envía 
        tx = ans[0][0]
     # Cada variable de información (enviada y de llegada) tiene varios campos,
     # entre ellos el tiempo de ida y vuelta. 
        diferencia_de_tiempo = abs(rx.time-tx.sent_time)
        print ("Ping: "+srt(i)+" "+srt(diferenci_de_tiempo))
        t+=diferencia_de_tiempo
    else:
        print("No conectado")
print("tiempo total "+str(t))