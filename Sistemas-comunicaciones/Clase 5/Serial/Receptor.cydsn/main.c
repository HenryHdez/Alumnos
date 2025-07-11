#include "project.h"    


int main(void)
{
    CyGlobalIntEnable;

    //Iniciar Puerto Serial
    Receptor_Start();
    LCD_Start();
    LCD_Position(0,0);
    LCD_PrintString("Valor Recibido");

    for(;;)
    {
        LCD_Position(1,0);
        LCD_PutChar(Receptor_GetChar());
    }
}

