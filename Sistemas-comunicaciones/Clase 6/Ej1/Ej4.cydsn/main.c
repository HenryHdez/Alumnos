#include <project.h>
//Manejo de arreglos
#include <stdio.h>

int main(void)
{
    uint16 Valor_ADC;
    float voltaje;
    char buffer[16]; 
    CyGlobalIntEnable;
    // Inicialización de periféricos
    ADC_Start();
    ADC_StartConvert();
    LCD_Start();
    PWM_Start();

    for(;;)
    {
        //Esperar y convertir
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);   
        Valor_ADC = ADC_GetResult16();              
        
        // Manejo de valores
        voltaje = (Valor_ADC * 5.0) / 4095.0;
        LCD_Position(0, 0);
        LCD_PrintString("ADC:         ");
        LCD_Position(0, 5);
        LCD_PrintDecUint16(Valor_ADC);
        //Valor del PWM
        PWM_WriteCompare(Valor_ADC/8); 
        
        //Llenar el buffer y poner 2 digitos
        sprintf(buffer, "V: %.2f V     ", voltaje); 
        LCD_Position(1, 0);
        LCD_PrintString(buffer);
        
        
        CyDelay(500); 
    }
}
