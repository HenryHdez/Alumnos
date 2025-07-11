//Define Librerias
#include "project.h"
#include "stdio.h"
//Tamaño del buffer
#define BUFFER_LEN     64u 

int main(void)
{
    //Variables para manejar el Buffer
    uint16 Cuenta;
    uint8 buffer[BUFFER_LEN];
    char8 Texto[20];

    //Habilita las interrupciones
    CyGlobalIntEnable;

    //Estos tres parámetros van en grupo
    //Se encargan de que el computador detecte el USB-Serial
    USB_Start(0u, USB_3V_OPERATION);
    while(!USB_GetConfiguration());
    USB_CDC_Init();

    /* Iniciar LCD */
    LCD_Start();
    LCD_Position(0,0);
    LCD_PrintString("Ejemplo USB");

    for(;;)
    {

        //Recibe Algo
        if(USB_DataIsReady() != 0u){
            Cuenta = USB_GetAll(buffer);
            sprintf(Texto,"%c Hecho",buffer[0]);
            USB_PutString(Texto);

            //Escribe en la LCD lo que se envia
            LCD_Position(1,0);
            LCD_PutChar(buffer[0]);
        }

        //Envia algo al Destino
        USB_PutString("Prueba");
        CyDelay(1000);
    }
}
