#include "project.h"    

int Contador = 0;

int main(void)
{
    CyGlobalIntEnable;
    //Iniciar Puerto Serial
    Emisor_Start();
    LCD_Start();
    LCD_Position(0,0);
    LCD_PrintString("Dato Enviado");

    for(;;)
    {
        //Bucle infinito para realizar la ejecución de la aplicación
        //Escribir Valor en Pantalla
        LCD_Position(1,0);
        LCD_PrintDecUint16(Contador);
        
        //Enviar Dato
        Emisor_PutChar(Contador);
        Contador++;
        CyDelay(1000);
    }
}

