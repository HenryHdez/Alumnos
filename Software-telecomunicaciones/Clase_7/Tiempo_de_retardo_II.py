from scapy.all import *
#Definir la cantidad de intentos que necesita (paquetes)
Cantidas_paquetes=4
#Definir la direcci�n IP
Direccion_IP="10.28.0.1"
#Construcci�n de la estructura para empaquetar la informaci�n
# /Medio/Direcci�n/Protocolo
paquete = Ether()/IP(dst=Direccion_IP)/ICMP()
# Variable tiempo
t=0.0
#Estructura para enviar cierta cantidad de paquetes
for i in range(Cantidas_paquetes):
    # la funci�n SRP implementa el ARP ping y retorna la MAC del equipo de dst
    ans,unans=srp(paquete,iface="Ethernet", filter='icmp', verbose=0, timeout=2)
    if(ans):
     # Esta ubicaci�n del arreglo contiene los campos relacionados con la
     # informaci�n que llega 
        rx = ans[0][1]
     # Esta ubicaci�n del arreglo contiene los campos relacionados con la
     # informaci�n que se env�a 
        tx = ans[0][0]
     # Cada variable de informaci�n (enviada y de llegada) tiene varios campos,
     # entre ellos el tiempo de ida y vuelta. 
        diferencia_de_tiempo = abs(rx.time-tx.sent_time)
        print ("Ping: "+srt(i)+" "+srt(diferenci_de_tiempo))
        t+=diferencia_de_tiempo
    else:
        print("No conectado")
print("tiempo total "+str(t))