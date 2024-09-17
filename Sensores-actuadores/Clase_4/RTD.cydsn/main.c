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
#define CONV_MILIOHM        100000

//Función para leer el offset que pueda tener el sensor
int32 Leer_Offset(){
    int32 offset = 0;
    //Fijar DAC en OmA
    IDAC_SetValue(0);
    //Iniciar conversión y lectura del ADC.
    ADC_StartConvert();
    ADC_IsEndConversion (ADC_WAIT_FOR_RESULT); 
    offset = ADC_GetResult32();
    return offset;
}

int32 Tension_referencia ()
{
    int32 ref = 0;
    //Seleccionar canal de la resistencia de referencia con el multiplexor 
    ADCMux_FastSelect(0);
    //Fija la salida del DAC en 1mA aproximadamente como valor
    //de referencia (1mA*100ohm=0.1V)
    IDAC_SetValue(125);
    //Iniciar conversión y lectura del ADC.
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT); 
    ref= ADC_GetResult32 ();
    return ref;
}

int32 valor_RTD ()
{
    int32 rtd_V = 0;
    //Variable para almacenar el valor de la RTD en mili-ohm 
    int32 rtdRes= 0;
    //Variable para realizar un ajuste del cero (0)
    int32 Cero_Corriente = 0;
    //Seleccionar canal de la RTD con el multiplexor 
    ADCMux_FastSelect(1);
    //Fija la salida del DAC en 1mA
    IDAC_SetValue(125);
    //Leer la tensión que cae sobre la RTD ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    rtd_V = ADC_GetResult32();
    //Leer offset del circuito
    Cero_Corriente = Leer_Offset();
    //Eliminar el offset
    rtd_V = rtd_V - Cero_Corriente;
    //Se encuentra una relación entre la tensión de la RTD y la de //referencia, luego se multiplica por 10000, para almacenar un valor de //precisión tomando 5 cifras del valor decimal
    rtdRes = (int32) ((float) rtd_V/Tension_referencia () * CONV_MILIOHM); 
    CyDelay(1000);
    return rtdRes;
}


int main(void)
{
    //Habilitar interrupciones 
    CyGlobalIntEnable;
    //Iniciar perifericos
    LCD_Start();
    LCD_Position (0,0);
    LCD_PrintString("Ejemplo RTD");
    IDAC_Start();
    ADC_Start();
    ADCMux_Start();
    //Bucle infinito

    for(;;)
    {
        /* Place your application code here. */
        LCD_Position (0,0);
        int x=valor_RTD();
        //Buscar el valor de temperatura usando la calculadora de PSOC5
        int32 rtdTemp=RTD_GetTemperature (x);
        //Se divide en dos partes para separar la parte entera y decimal //del termino dado por la calculadora
        int32 entera = rtdTemp/100;
        int32 decimal= rtdTemp-(entera*100);
        /*si la parte decimal es negativa hay que convertirla a positiva*/ 
        if (decimal<0) { decimal*=-1; }
        char printBuf[16]={'\0'};
        sprintf (printBuf, "Temp=%ld.%021d C", entera, decimal);
        LCD_Position (1, 0);
        LCD_PrintString (printBuf);
    }
}

/* [] END OF FILE */
