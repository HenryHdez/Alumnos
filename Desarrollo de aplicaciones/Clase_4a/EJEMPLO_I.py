# -*- coding: utf-8 -*-
"""Importe la librería SMTP"""
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
import smtplib
"""Cree un objeto para almacenar el correo electrónico a enviar"""
MSG = MIMEMultipart()
"""Escriba el cuerpo del correo electrónico"""
Mensaje = "Bienvenido al curso Automatica III"""
"""Establezca los parámetros del correo electrónico"""
Contrasena     = "pzpisvwkusurpkcs"
MSG['From']    = "correopruebaclasesud@gmail.com"
MSG['To']      = "heahernandezma@unal.edu.co"
MSG['Subject'] = "Bienvenida"
"""Agregue el cuerpo del correo al objeto"""
MSG.attach(MIMEText (Mensaje, 'plain'))
try:
    """Establezca la conexión con el servidor de gmail"""
    server = smtplib.SMTP('smtp.gmail.com',587)
    server.starttls()
    """Ingrese al servicio"""
    server.login(MSG['From'], Contrasena)
    """Envie el mensaje"""
    server.sendmail(MSG['From'], MSG['To'], MSG.as_string())
    server.quit()
    print ("Mensaje enviado a: %s" % (MSG['To']))
except:
    print("Error al enviar el correo")

