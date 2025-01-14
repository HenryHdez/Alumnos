# -*- coding: utf-8 -*-
"""Importe la librería SMTP"""
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
import smtplib

"""Cree un objeto para almacenar el correo electrónico a enviar"""
MSG = MIMEMultipart()
"""Escriba el cuerpo del correo electrónico"""
Mensaje = "Bienvenido al módulo de administración de redes"
"""Establezca los parámetros del correo electrónico"""
Contrasena     = "12345"
MSG['From']    = "Profesor@AdministradorRed.com"
MSG['To']      = "Profesor@AdministradorRed.com"
MSG['Subject'] = "Bienvenida"
"""Agregue el cuerpo del correo al objeto"""
MSG.attach(MIMEText (Mensaje, 'plain'))
"""Cree un servidor temporal"""
server = smtplib.SMTP(host='192.168.0.22', port=25)
"""Ingrese al servicio"""
server.login(MSG['From'], Contrasena)
"""Envie el mensaje"""
server.sendmail(MSG['From'], MSG['To'], MSG.as_string())
server.quit()
print("Mensaje enviado a: %s" % (MSG['To']))
