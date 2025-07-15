#include "project.h"

//Funcion Interrupcion
CY_ISR(Interrupcion){
    LCD_Position(1,0);
    LCD_PutChar(Receptor_GetChar());
}

int main(void)
{
    CyGlobalIntEnable;

    //Iniciar Puerto Serial
    Receptor_Start();
    LCD_Start();
    LCD_Position(0,0);
    LCD_PrintString("Valor Recibido");

    //Inicie la interrupción
    Interrupcion_Start();

    for(;;)
    {
        //Bucle infinito
    }
}
