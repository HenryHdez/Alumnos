import cv2

# Abrir la cámara para capturar video
cap = cv2.VideoCapture(0)

while(True):
    # Capturar un cuadro (frame) del video
    ret, frame = cap.read()
    # Si la captura del cuadro es exitosa
    if ret == True:
        # Mostrar el cuadro en una ventana llamada "Video"
        cv2.imshow('Video', frame)
    # Salir del bucle si la tecla 'q' es presionada
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Liberar la cámara y cerrar la ventana
cap.release()
cv2.destroyAllWindows()

