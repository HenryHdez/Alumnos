/*******************************************************************************
* File Name: RTD.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the RTDCalc Component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "RTD.h"

#if(!CY_PSOC3)


    /*******************************************************************************
    * Function Name: RTD_MultShift24
    ********************************************************************************
    *
    * Summary:
    *  Performs the math function (op1 * op2) >> 24 using 64 bit arithmetic without
    *  any loss of precision and without overflow.
    *
    * Parameters:
    *  op1: Signed 32-bit operand
    *  op2: Unsigned 24-bit operand
    *
    * Return:
    *  Signed 32-bit result of the math calculation
    *
    *******************************************************************************/
    int32 RTD_MultShift24(int32 op1, uint32 op2) 
    {
        int64 result=0;

        result = (int64)op1 * (int64)op2;
        
        if (result < 0)
        {
            result = -result;
            result = (int32)((uint32)((uint64)result >> RTD_24BIT_SHIFTING));
            result = -result;
        }
        else
        {
            result = (int32)((uint32)((uint64)result >> RTD_24BIT_SHIFTING));
        }
        return (result);
    }
#endif /* End (!CY_PSOC3) */


/*******************************************************************************
* Function Name: RTD_GetTemperature
********************************************************************************
*
* Summary:
*  Calculates the temperature from RTD resistance.
*
* Parameters:
*  res: Resistance in milliohms.
*
* Return:
*  Temperature in 1/100ths degrees C.
*
*******************************************************************************/
int32 RTD_GetTemperature(uint32 res) 

#if (CY_PSOC3)
{

    /***************************************
    *  Customizer Generated Coefficients
    ***************************************/
    const int32 CYCODE RTD_coeffPos[] = { -50250219, 252360369, 58213731 };
    const int32 CYCODE RTD_coeffNeg[] = { -50308256, 252728554, 57843218 };

    uint8 i=0u;
    float32 resNorm=0.0f;
    float32 temp=0.0f;

    resNorm = (float32)res;

    if (((RTD_RTD_TYPE == (uint32)RTD__PT100) && (res > RTD_ZERO_VAL_PT100)) ||
        ((RTD_RTD_TYPE == (uint32)RTD__PT500) && (res > RTD_ZERO_VAL_PT500)) ||
        ((RTD_RTD_TYPE == (uint32)RTD__PT1000) && (res > RTD_ZERO_VAL_PT1000)))
    {
         /* Temperature above 0 degrees C */
        for (i = RTD_ORDER_POS - 1u; i > 0u; i--)
        {
            temp = (RTD_coeffPos[i] + temp) * resNorm;
        }
        temp = temp + RTD_coeffPos[RTD_FIRST_EL_MAS];
    }
    else
    {
        /* Temperature below 0 degrees C */
        for (i = RTD_ORDER_NEG - 1u; i > 0u; i--)
        {
            temp = (RTD_coeffNeg[i] + temp) * resNorm;
        }
        temp = temp + RTD_coeffNeg[RTD_FIRST_EL_MAS];
    }
    return ((int32)(temp));
}
#else
{
    /***************************************
    *  Customizer Generated Coefficients
    ***************************************/
    const int32 CYCODE RTD_coeffPos[] = { -50250219, 252360369, 58213731 };
    const int32 CYCODE RTD_coeffNeg[] = { -50308256, 252728554, 57843218 };

    uint8 i;
    int32 temp=0;

    if (((RTD_RTD_TYPE == (uint32)RTD__PT100) && (res > RTD_ZERO_VAL_PT100)) ||
        ((RTD_RTD_TYPE == (uint32)RTD__PT500) && (res > RTD_ZERO_VAL_PT500)) ||
        ((RTD_RTD_TYPE == (uint32)RTD__PT1000) && (res > RTD_ZERO_VAL_PT1000)))
    {
         /* Temperature above 0 degrees C */
        res = res << (RTD_IN_NORMALIZATION - RTD_POS_INPUT_SCALE);

        for (i = RTD_ORDER_POS - 1u; i > 0u; i--)
        {
            temp = RTD_MultShift24((RTD_coeffPos[i] + temp), res);
        }
        temp = (int32)((uint32)((uint64)(int32)(temp + RTD_coeffPos[RTD_FIRST_EL_MAS]) >> 
                       RTD_POS_COEFF_SCALE));
    }

    else
    {
        /* Temperature below 0 degrees C */
        res = res << (RTD_IN_NORMALIZATION - RTD_NEG_INPUT_SCALE);

        for (i = RTD_ORDER_NEG - 1u; i > 0u; i--)
        {
            temp = RTD_MultShift24((RTD_coeffNeg[i] + temp), res);
        }

        temp = (int32)((uint32)((uint64)(int32)(temp + RTD_coeffNeg[RTD_FIRST_EL_MAS]) >> 
                       RTD_NEG_COEFF_SCALE));
    }
    return (temp);
}
#endif /* End PSoC3 */

/* [] END OF FILE */
