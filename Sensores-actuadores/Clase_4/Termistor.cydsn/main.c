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
    int16 Termistor_V;
    int16 Referencia;
    int32 Resistencia;
    int32 Temperatura; 
    //Iniciar perifericos LCD_Start();
    LCD_Position (0,0);
    LCD_PrintString("Ejemplo Termistor");
    ADC_Start();
    AMux_1_Start();
    CyGlobalIntEnable;
    for(;;)
    {
        //Fijar valor de referencia 
        AMux_1_FastSelect (0); 
        //Tomar valor del ADC
        ADC_StartConvert();
        ADC_IsEndConversion (ADC_WAIT_FOR_RESULT);
        ADC_StopConvert();
        Referencia = ADC_GetResult32();
        //Fijar valor del termistor
        AMux_1_FastSelect (1);
        //Tomar valor del ADC
        ADC_StartConvert();
        ADC_IsEndConversion (ADC_WAIT_FOR_RESULT);
        ADC_StopConvert();
        Termistor_V = ADC_GetResult32();
        //Obtener valor de resistencia a partir de la tensión del ADC 
        Resistencia=Termistor_GetResistance(Referencia, Termistor_V); 
        //Leer valor de temperatura a partir de la resistencia
        Temperatura=Termistor_GetTemperature(Resistencia);
        //Como el valor de temperatura es un entero largo (2 digitos de presición) 
        //se debe convertir a decimal con punto
        int32 entera = Temperatura/100;
        int32 decimal= Temperatura-(entera*100);
        //si la parte decimal es negativa hay que convertirla a positiva
        if (decimal<0) { decimal*=-1;}
        //Crear String
        sprintf (palabra, "Temp=%ld.%021d C", entera, decimal);
        //Borrar LCD
        LCD_Position (1,0);
        LCD_PrintString("                  ");
        LCD_Position (1,0);
        LCD_PrintString (palabra);
        CyDelay(100);
    }
}

/* [] END OF FILE */
