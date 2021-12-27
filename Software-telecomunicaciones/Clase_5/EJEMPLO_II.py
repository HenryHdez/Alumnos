# -*- coding: utf-8 -*-
"""Importe la librer�a SMTP"""
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
import smtplib

"""Cree un objeto para almacenar el correo electr�nico a enviar"""
MSG = MIMEMultipart()
"""Escriba el cuerpo del correo electr�nico"""
Mensaje = "Bienvenido al m�dulo de administraci�n de redes"
"""Establezca los par�metros del correo electr�nico"""
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
