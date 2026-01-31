import paramiko

host = "192.168.87.253"
user = "ubuntu"
password = "ubuntu" 

# Comando SNMP a ejecutar
command = "snmpwalk -v 2c -c public 192.168.87.253"

try:
    # Crear cliente ssh
    client = paramiko.SSHClient()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    # Conectar
    client.connect(host, username=user, password=password)
    # Ejecutar comando
    stdin, stdout, stderr = client.exec_command(command)
    # Leer salida
    output = stdout.read().decode()
    error = stderr.read().decode()
    print("SALIDA DEL COMANDO:")
    print(output)
    if error:
        print("ERRORES:")
        print(error)
finally:
    client.close()
