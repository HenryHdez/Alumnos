/*******************************************************************************
* File Name: Termistor.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the ThermistorCalc
*  Component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Termistor.h"


/*******************************************************************************
* Function Name: Termistor_GetResistance
********************************************************************************
*
* Summary:
*  The digital values of the voltages across the reference resistor and the
*  thermistor are passed to this function as parameters. The function returns
*  the resistance, based on the voltage values.
*
* Parameters:
*  vReference: the voltage across the reference resistor;
*  vThermistor: the voltage across the thermistor.
*  The ratio of these two voltages is used by this function. Therefore, the
*  units for both parameters must be the same.
*
* Return:
*  The return value is the resistance across the thermistor. The value returned
*  is the resistance in Ohms.
*
*******************************************************************************/
uint32 Termistor_GetResistance(int16 vReference, int16 vThermistor)
                                      
{
    int32 resT;
    int16 temp;

    /* Calculate thermistor resistance from the voltages */
    resT = Termistor_REF_RESISTOR * ((int32)vThermistor);
    if (vReference < 0)
    {
        temp = -vReference;
        temp = (int16)((uint16)((uint16)temp >> 1u));
        temp = -temp;
    }
    else
    {
        temp = (int16)((uint16)((uint16)vReference >> 1u));
    }
    resT += temp;
    resT /= vReference;

    /* The ordering of Reference resistor value is specifically designed to keep the result from overflowing */
    return ((uint32)((uint32)resT << Termistor_REF_RES_SHIFT));
}


/*******************************************************************************
* Function Name: Termistor_GetTemperature
********************************************************************************
*
* Summary:
*  The value of the thermistor resistance is passed to this function as a
*  parameter. The function returns the temperature, based on the resistance
*  value. The method used to calculate the temperature is dependent on whether
*  Equation or LUT was selected in the Customizer.
*
* Parameters:
*  resT: the resistance across the thermistor in Ohms.
*
* Return:
*  The return value is the temperature in 1/100ths of degrees C. For example,
*  the return value is 2345, when the actual temperature is 23.45 degrees C.
*
*******************************************************************************/
int16 Termistor_GetTemperature(uint32 resT) 
{
    int16 tempTR;
    
    #if (Termistor_IMPLEMENTATION == Termistor_EQUATION_METHOD)

        float32 stEqn;
        float32 logrT;

        /* Calculate thermistor resistance from the voltages */
        #if(!CY_PSOC3)
            logrT = (float32)log((float64)resT);
        #else
            logrT = log((float32)resT);
        #endif  /* (!CY_PSOC3) */

        /* Calculate temperature from the resistance of thermistor using Steinhart-Hart Equation */
        #if(!CY_PSOC3)
            stEqn = (float32)(Termistor_THA + (Termistor_THB * logrT) + 
                             (Termistor_THC * pow((float64)logrT, (float32)3)));
        #else
            stEqn = (float32)(Termistor_THA + (Termistor_THB * logrT) + 
                             (Termistor_THC * pow(logrT, (float32)3)));
        #endif  /* (!CY_PSOC3) */

        tempTR = (int16)((float32)((((1.0 / stEqn) - Termistor_K2C) * (float32)Termistor_SCALE) + 0.5));

    #else /* Termistor_IMPLEMENTATION == Termistor_LUT_METHOD */

        uint16 mid;
        uint16 first = 0u;
        uint16 last = Termistor_LUT_SIZE - 1u;

        /* Calculate temperature from the resistance of thermistor by using the LUT */
        while (first < last)
        {
            mid = (first + last) >> 1u;

            if ((0u == mid) || ((Termistor_LUT_SIZE - 1u) == mid) || (resT == Termistor_LUT[mid]))
            {
                last = mid;
                break;
            }
            else if (Termistor_LUT[mid] > resT)
            {
                first = mid + 1u;
            }
            else /* (Termistor_LUT[mid] < resT) */
            {
                last = mid - 1u;
            }
        }

        /* Calculation the closest entry in the LUT */
        if ((Termistor_LUT[last] > resT) && (last < (Termistor_LUT_SIZE - 1u)) &&
           ((Termistor_LUT[last] - resT) > (resT - Termistor_LUT[last + 1u])))
        {
            last++;
        }
        else if ((Termistor_LUT[last] < resT) && (last > 0u) &&
                ((Termistor_LUT[last - 1u] - resT) < (resT - Termistor_LUT[last])))
        {
            last--;
        }
        else
        {
            /* Closest entry in the LUT already found */
        }

        tempTR = Termistor_MIN_TEMP + (int16)((uint16)(last * Termistor_ACCURACY));

    #endif /* (Termistor_IMPLEMENTATION == Termistor_EQUATION_METHOD) */

    return (tempTR);
}


/* [] END OF FILE */
