/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"

#define BUFFER_SIZE 64

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();
    /*Variables globales*/
    char txData[BUFFER_SIZE];   // Buffer para enviar datos
    char rxData;                // Variable para recibir un carácter
    char buffer[BUFFER_SIZE];   // Buffer para almacenar y enviar los datos recibidos
    for(;;)
    {
        /* Place your application code here. */
        /*Ejemplo 1
        UART_1_PutChar('0');
        UART_1_PutChar('\n');
        CyDelay(1000);
        UART_1_PutChar('5');
        UART_1_PutChar('\n');
        CyDelay(1000);
        */
        /* Ejemplo 2 */
        if (UART_1_GetRxBufferSize() > 0)
        {
            //Enviar y recibir
            // Leer el dato recibido
            rxData = UART_1_GetChar();
            // Enviar el dato recibido a la terminal
            UART_1_PutChar(rxData);
            //Guardar en el buffer
            sprintf(buffer, "Recibido: %c\r\n", rxData);
            UART_1_PutString(buffer);
            
            // Enviar repuesta si recibo 'a'
            if(rxData == 'a')  
            {
                sprintf(txData, "Hola desde alumnos\r\n");
                UART_1_PutString(txData);
            }
        }        
        
    }
}