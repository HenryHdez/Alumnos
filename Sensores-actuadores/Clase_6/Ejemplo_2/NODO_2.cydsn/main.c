#include "project.h"

// Declaración de variables para los datos enviados y recibidos
char mensaje_enviado[] = "Aqui Estoy";  // Mensaje a enviar
char mensaje_recibido[20];             // Buffer para almacenar el mensaje recibido
uint8 indice_enviar = 0;               // Índice del carácter actual a enviar
uint8 indice_recibir = 0;              // Índice del carácter actual recibido
char buffer_rec='\0';
char buffer_env='\0';

int main(void)
{
    CyGlobalIntEnable; /* Habilita las interrupciones globales */
    CAN_Start();       // Inicializa el módulo CAN
    LCD_Start();       // Inicializa la pantalla LCD

    // Configuración inicial
    LCD_Position(0, 0);
    LCD_PrintString("NODO_2");

    for (;;)
    {
        /* Enviar carácter actual */
        if (mensaje_enviado[indice_enviar] != '\0')  // Mientras queden caracteres por enviar
        {
            buffer_env = mensaje_enviado[indice_enviar];
            CAN_TX_DATA_BYTE1(0) = buffer_env;  // Cargar el carácter actual
            CAN_SendMsg0();  // Enviar el mensaje
            indice_enviar++; // Incrementar el índice para el próximo carácter
        }
        else
        {
            indice_enviar = 0;  // Reiniciar el índice cuando termine el mensaje
        }

        /* Recibir carácter */
            mensaje_recibido[indice_recibir] = CAN_RX_DATA_BYTE1(0); // Leer el carácter recibido
            CAN_RX[0u].rxcmd.byte[0u] |= CAN_RX_ACK_MSG;            // Acknowledge del mensaje
            LCD_Position(1, indice_recibir);                        // Mostrar el carácter en la posición actual
            LCD_PutChar(mensaje_recibido[indice_recibir]);          // Mostrar el carácter en la LCD
            indice_recibir++;                                       // Incrementar el índice

            // Reiniciar el índice al final del mensaje
            if (mensaje_recibido[indice_recibir - 1] == '\0' || indice_recibir >= sizeof(mensaje_recibido))
            {
                indice_recibir = 0;  // Reiniciar el índice
                LCD_Position(1, 0); // Mover el cursor al inicio de la fila
                LCD_PrintString("                "); // Limpiar la fila
            }

        CyDelay(500);  // Pequeña pausa para evitar saturar el bus
    }
}
