#include "project.h"

uint8 dato_enviado = 0;   // Contador para los datos enviados
uint8 dato_recibido = 0;  // Contador para los datos recibidos

int main(void)
{
    CyGlobalIntEnable; /* Habilita las interrupciones globales */
    CAN_Start();       // Inicializa el módulo CAN
    LCD_Start();       // Inicializa la pantalla LCD
    LCD_Position(0, 0);
    LCD_PrintString("NODO_2");
    for (;;)
    {       
        dato_enviado++;             // Incrementa el contador de datos enviados
        CAN_SendMsg0();             // Envía un mensaje CAN utilizando el buffer 0
        CyDelay(500);               // Espera 500 ms (medio segundo)
        CAN_ReceiveMsg0();          // Recibe un mensaje CAN desde el buffer 0
        
        // Muestra el valor de 'dato_enviado' en la fila 1, columna 0 de la LCD
        LCD_Position(1, 0);
        LCD_PrintNumber(dato_enviado);
        
        // Muestra el valor de 'dato_recibido' en la fila 1, columna 8 de la LCD
        LCD_Position(1, 8);
        LCD_PrintNumber(dato_recibido);
    }
}
