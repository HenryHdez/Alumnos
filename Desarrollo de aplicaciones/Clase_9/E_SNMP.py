# -*- coding: utf-8 -*-
"""Importar libreria SIMP"""
from pysnmp.hlapi import *
"""Identificador del equipo"""
OID = "1.3.6.1.2.1.1.1.0"
IP = "192.168.1.7" 
Puerto = 161

if __name__ == "__main__":
    car=getCmd(SnmpEngine(),
                CommunityData('public'),
                UdpTransportTarget((IP, Puerto)),
                ContextData(),
                ObjectType(ObjectIdentity('SNMPv2-MIB', 'sysDescr', 0))
                )
    informacion=next(car)
    print(informacion)