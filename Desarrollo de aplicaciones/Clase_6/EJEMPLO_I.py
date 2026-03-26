# -*- coding: utf-8 -*-
"""Importe la librería SMTP"""
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.application import MIMEApplication
import smtplib
"""Cree un objeto para almacenar el correo electrónico a enviar"""
MSG = MIMEMultipart()
"""Escriba el cuerpo del correo electrónico"""
Mensaje = "Bienvenido al curso"""
"""Establezca los parámetros del correo electrónico"""
Contrasena     = ""
MSG['From']    = "correopruebaclasesud@gmail.com"
MSG['To']      = ""
MSG['Subject'] = "Bienvenida"
"""Agregue el cuerpo del correo al objeto"""
MSG.attach(MIMEText (Mensaje, 'plain'))
    
# Adjuntar archivo
# Poner nombre de archivo
ruta_archivo = 'Ejemplo_II.sql'
with open(ruta_archivo, 'rb') as archivo:
    parte = MIMEApplication(archivo.read(), Name=ruta_archivo)
    parte['Content-Disposition'] = f'attachment; filename="{ruta_archivo}"'
    MSG.attach(parte)

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

