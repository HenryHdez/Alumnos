import cv2
import numpy as np

# Configuración de la cámara
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

while True:
    # Captura de un cuadro del video
    ret, frame = cap.read()
    
    # Convertir la imagen de BGR (color) a HSV (escala de tonos)
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    # Definir el rango de colores verdes a detectar en HSV
    bajo = np.array([40, 40, 40])     #Verde oscuro
    alto = np.array([70, 255, 255])   #Verde claro
    # Aplicar una máscara para detectar sólo los colores verdes
    mascara = cv2.inRange(hsv, bajo, alto)
    
    # Aplicar una serie de operaciones morfológicas para 
    # eliminar el ruido de la máscara
    kernel = np.ones((5,5),np.uint8)
    mascara = cv2.erode(mascara, kernel, iterations=1)
    mascara = cv2.dilate(mascara, kernel, iterations=1)
    # Encontrar los contornos de la máscara
    contours, _ = cv2.findContours(mascara, cv2.RETR_EXTERNAL, 
                                   cv2.CHAIN_APPROX_SIMPLE)
    
    # Dibujar un rectángulo alrededor del objeto verde detectado
    for contour in contours:
        x,y,w,h = cv2.boundingRect(contour)
        cv2.rectangle(frame, (x,y), (x+w,y+h), (0,255,0), 2)
    
    # Mostrar la imagen original y la máscara en ventanas separadas
    cv2.imshow('Original', frame)
    cv2.imshow('Mask', mascara)
    
    # Salir del bucle si se presiona la tecla 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Liberar la cámara y cerrar las ventanas
cap.release()
cv2.destroyAllWindows()
