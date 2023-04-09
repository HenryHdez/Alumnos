# -*- coding: utf-8 -*-
"""Importar libreria SIMP"""
from pysnmp.hlapi import *
"""Identificador del equipo"""
OID = "1.3.6.1.2.1.1.1.0"
IP = "192.168.1.6" 
Puerto = 161

if __name__ == "__main__":
    e1, e2, e3, vb = next (getCmd(SnmpEngine(),
                                  CommunityData('public', mpModel=0),
                                  UdpTransportTarget((IP, Puerto)),
                                  ContextData(),
                                  ObjectType(ObjectIdentity(OID))
                                  )
                           )
    """Imprimir errores de indicación"""
    if(e1):    
        print(e1)
    """Imprimir errores de estado""" 
    if(e2):
        print(e2) 
    """Imprimir errores de estado"""
    if(e3):   
        print(e3)
    """Imprimir información del dispositivo"""
    if(vb):  
        for i in vb:
            print(str(i))
        
"""if __name__ == "__main__":
    car=getCmd(SnmpEngine(),
                CommunityData('public'),
                UdpTransportTarget((IP, Puerto)),
                ContextData(),
                ObjectType(ObjectIdentity('SNMPv2-MIB', 'sysDescr', 0))
                )
    informacion=next(car)
    print(informacion)"""