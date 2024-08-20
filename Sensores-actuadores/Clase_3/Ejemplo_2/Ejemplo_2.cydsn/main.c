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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    //Variables del PWM
    // Iniciar PWM
    PWM_Start(); 
    uint8 niveldebillo = 0;
    
    //Variables localesdentro del void main
    uint8 contador = 0;
    for(;;)
    {
        /* Place your application code here. */
        //Ejemplo 1
        /*if(Pin_1_Read()){
            Pin_2_Write(1);
        }
        else{Pin_2_Write(0);}*/
        //Ejemplo 2
        /*Pin_2_Write(0);
        CyDelay(500);
        Pin_2_Write(1);
        CyDelay(500);*/
        
        //Ejemplo 3 "Contador binario con leds"
        /*if(Pin_1_Read() == 1){
            contador++;
            LED1_Write(contador & 0x01);
            //>> Desplazamiento hacia la derecha, Si contador vale 6 "0110"
            //y se deslaza 1 seria 0011
            LED2_Write((contador >> 1) & 0x01);
            LED3_Write((contador >> 2) & 0x01);
            LED4_Write((contador >> 3) & 0x01);   
            while(Pin_1_Read() == 0); // Anti-rebote
        }*/
        
        /*
        //Ejemplo 4 "Inversión de giro de un motor"
        if(Pin_1_Read() == 0)
        {
            M1_Write(1); // Adelante
            M2_Write(0);
        }
        else if(Pin_3_Read() == 0)
        {
            M1_Write(0); // Atrás
            M2_Write(1);
        }
        else
        {
            M1_Write(0); // Apagar motor
            M2_Write(0);
        }*/
        
        //Ejemplo 5 "PWM"
        /*if(Pin_1_Read() == 1)
        {
            niveldebillo = (niveldebillo + 1) % 5;
            switch(niveldebillo)
            {
                case 0: PWM_WriteCompare(0); break;   // Apagado
                case 1: PWM_WriteCompare(50); break;  // Brillo bajo
                case 2: PWM_WriteCompare(100); break;  // Brillo medio
                case 3: PWM_WriteCompare(125); break;  // Brillo alto
                case 4: PWM_WriteCompare(255); break; // Máximo brillo
            }
            
            while(Pin_1_Read() == 1); // Anti-rebote
        }*/
    }
}

/* [] END OF FILE */
