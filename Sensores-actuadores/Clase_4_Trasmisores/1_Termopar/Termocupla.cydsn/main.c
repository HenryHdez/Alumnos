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

//Variable globales
char palabra [12]={'\0'};

int main(void)
{
    int32 Temperatura;
    int32 Referencia;
    //Iniciar perifericos
    LCD_Start();
    LCD_Position (0,0);
    LCD_PrintString("Ejemplo TC K");
    ADC_Start();
    CyGlobalIntEnable;
    //Tomar un valor de referencia a 25 °C (puede ser otro valor de temperatura)
    int temp_ref=25;
    int escala=100;
    Referencia = Termocupla_GetVoltage (temp_ref*escala);

    for(;;)
    {
        //Tomar valor del ADC
        ADC_StartConvert();
        ADC_IsEndConversion (ADC_WAIT_FOR_RESULT);
        ADC_StopConvert();
        Temperatura = ADC_GetResult32();
        //Usar libreria para valor de temperatura teniendo en cuenta el
        //valor de referencia
        Temperatura=Termocupla_GetTemperature (Temperatura+Referencia);
        //Como el valor de temperatura es un entero largo (2 digitos de presición) 
        //se debe convertir a decimal con punto
        int32 entera  = Temperatura/escala;
        int32 decimal = Temperatura-(entera*escala);
        //si la parte decimal es negativa hay que convertirla a positiva
        if (decimal<0) { decimal*=-1; }
        //Crear String
        sprintf (palabra, "Temp=%ld.%021d C", entera, decimal);
        //Borrar LCD
        LCD_Position (1,0);
        LCD_PrintString("                   ");
        LCD_Position (1, 0);
        LCD_PrintString (palabra);
        CyDelay(100);
    }
}

/* [] END OF FILE */
