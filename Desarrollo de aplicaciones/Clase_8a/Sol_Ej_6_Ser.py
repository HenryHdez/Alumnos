import cv2
import socket
import struct

def main():
    # Configuración del socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('127.0.0.1', 5000))
    server_socket.listen(1)
    print("Esperando conexión del cliente...")
    conn, addr = server_socket.accept()
    print(f"Conectado a {addr}")

    cap = cv2.VideoCapture(0)
    
    try:
        while cap.isOpened():
            ret, frame = cap.read()
            if not ret:
                print("Error al capturar el frame")
                break
            
            # Comprimir la imagen
            _, buffer = cv2.imencode('.jpg', frame, [cv2.IMWRITE_JPEG_QUALITY, 80])
            data = buffer.tobytes()
            
            # Empaquetar los datos (Convertir los datos a bytes, Q=Formato) y enviarlos a través de la red
            msg = struct.pack('Q', len(data)) + data
            conn.sendall(msg)
    except Exception as e:
        print(f"Error durante la transmisión: {e}")
    finally:
        cap.release()
        conn.close()
        server_socket.close()

if __name__ == "__main__":
    main()
