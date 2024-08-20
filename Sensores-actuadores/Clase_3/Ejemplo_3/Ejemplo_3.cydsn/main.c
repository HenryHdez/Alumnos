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
//Importar librería
#include "stdio.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    int Var_Entera=0;
    float Var_flotante=0.0;
    char Caracter='a';
    char Cadena[15]="Hola Mundo";
    CyDelay(100); //Retardo en milisegundos
    CyDelayUs(100); //Retardo en microsegundos
    
    //Inicializar componentes
    LCD_Start();
    ADC_SAR_Start();
    ADC_SAR_StartConvert();
    //Fila,Columna
    LCD_Position(0,0);
    LCD_PrintString("Hola Mundo");
    CyDelay(1000);
    //Borrar
    LCD_ClearDisplay();
    for(;;)
    {
        //ADC
        //Leer pin 6_5 que es el potenciometro
        ADC_SAR_IsEndConversion(ADC_SAR_WAIT_FOR_RESULT);
        Var_Entera = ADC_SAR_GetResult16(); 
        //Print entero
        LCD_Position(0,0);
        LCD_PrintString("INT: ");
        LCD_Position(0,6);
        LCD_PrintNumber(Var_Entera);
        //Print flotante
        //Project>> Build Settings>>ARM XX>>Linker>>Command Line
        //Digite: -u_printf_float
        //Modifique Design Wide Resources>>System 
        //Head Size = 0X0400
        //Stack Size = 0X1000
        Var_flotante=(Var_Entera/4096.0)*5;
        char Letrero[15] = {'\0'};
        sprintf(Letrero,"%0.3f",Var_flotante); 
        LCD_Position(1,0);
        LCD_PrintString("FLO: ");
        LCD_Position(1,6);
        LCD_PrintString(Letrero);
        
        //DAC 0-4Vdc
        //Minimo
        VDAC_SetValue(0);
        //Maximo
        VDAC_SetValue(255); 
    }
}

/* [] END OF FILE */
