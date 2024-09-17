/*******************************************************************************
* File Name: Thermocouple_1.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the Thermocouple_1
*  component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Thermocouple_1.h"

#if(!CY_PSOC3)

    /*******************************************************************************
    * Function Name: Thermocouple_1_MultShift24
    ********************************************************************************
    *
    * Summary:
    *  Performs the math function (op1 * op2) >> 24 using 64 bit arithmetic without
    *  any loss of precision and without overflow.
    *
    * Parameters:
    *  op1: Signed 32-bit operand
    *  op2: Signed 24-bit operand
    *
    * Return:
    *  Signed 32-bit result of the math calculation
    *
    *******************************************************************************/
    int32 Thermocouple_1_MultShift24(int32 op1, int32 op2) 
    {
        int64 result=0;

        result = (int64)op1 * (int64)op2;
        if (result < 0)
        {
            result = -result;
            result = (int32)((uint64)((uint64)result >> Thermocouple_1_24BIT_SHIFTING));
            result = -result;
        }
        else
        {
            result = (int32)((uint64)((uint64)result >> Thermocouple_1_24BIT_SHIFTING));
        }
        return (result);
    }        
#endif /* End (!CY_PSOC3) */


/*******************************************************************************
* Function Name: Thermocouple_1_GetTemperature
********************************************************************************
*
* Summary:
*  This function takes thermocouple voltage in microvolt as i/p and calculates
*  temperature corresponding to the thermocouple voltage. The order of the
*  polynomial and the polynomial coefficients used to convert voltage to
*  temperature are dependent on the type of thermocouple selected.
*
* Parameters:
*  int32 voltage : Thermocouple voltage measured in microvolts.
*
* Return:
*  int32 : Temperature in 1/100 degree C
*
*******************************************************************************/
int32 Thermocouple_1_GetTemperature(int32 voltage) 

#if(CY_PSOC3)
{

    /***************************************
    *  Customizer Generated Coefficients
    ***************************************/
    const int32 CYCODE Thermocouple_1_coeffVT[][3] = {{0, 0, -1687114},
                                                  {2639629, 164388, 40518839},
                                                  {-1001834, 16879, -90491511},
                                                  {-7623495, -1761422, 196887684},
                                                  {-51750922, 19173707, -227871065},
                                                  {-176344390, -92787626, 136207339},
                                                  {-335143805, 242736174, -31547361},
                                                  {-331192671, -358027528, 0},
                                                  {-134793524, 281193929, 0},
                                                  {0, -91707895, 0}};

const int32 CYCODE Thermocouple_1_voltRange[2] = {0, 20644};

const int8 CYCODE Thermocouple_1_xScaleVT[3] = {13, 15, 16};
const int8 CYCODE Thermocouple_1_coefScaleVT[3] = {7, 1, 7};

    /* Variable to store temperature */
    float32 temp=0.0f;
    float32 voltageNorm=0.0f;
    uint8 i=0u;

    #if (Thermocouple_1_VT_RANGE_LEN == Thermocouple_1_THREE)
    {
        voltageNorm = (float32)voltage;

        if(voltage < Thermocouple_1_voltRange[Thermocouple_1_RANGE_MAS_0] )
        {
            for (i=Thermocouple_1_ORDER_VT - 1u; i > 0u; i--)
            {
                temp = (temp + Thermocouple_1_coeffVT[i][Thermocouple_1_RANGE_MAS_0]) * voltageNorm;
            }
            temp = (temp + Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_0]);
        }

        else if(voltage <= Thermocouple_1_voltRange[Thermocouple_1_RANGE_MAS_1] )
        {
            for (i=Thermocouple_1_ORDER_VT - 1u; i > 0u; i--)
            {
                temp = (temp + Thermocouple_1_coeffVT[i][Thermocouple_1_RANGE_MAS_1]) * voltageNorm;
            }
            temp = (temp + Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_1]);
        }

        else if(voltage <= Thermocouple_1_voltRange[Thermocouple_1_RANGE_MAS_2] )
        {
            for (i=Thermocouple_1_ORDER_VT - 1u; i > 0u; i--)
            {
                temp = (temp + Thermocouple_1_coeffVT[i][Thermocouple_1_RANGE_MAS_2]) * voltageNorm;
            }
            temp = (temp + Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_2]);
        }

        else
        {
            for (i=Thermocouple_1_ORDER_VT - 1u; i > 0u; i--)
            {
                temp = (temp + Thermocouple_1_coeffVT[i][Thermocouple_1_RANGE_MAS_3]) * voltageNorm;
            }
            temp = (temp + Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_3]);
        }
    }

    #else
    {
        voltageNorm = (float32)voltage;

        if(voltage < Thermocouple_1_voltRange[Thermocouple_1_RANGE_MAS_0] )
        {
            for (i=Thermocouple_1_ORDER_VT - 1u; i > 0u; i--)
            {
                temp = (temp + Thermocouple_1_coeffVT[i][Thermocouple_1_RANGE_MAS_0]) * voltageNorm;
            }
            temp = (temp + Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_0]);
        }

        else if(voltage <= Thermocouple_1_voltRange[Thermocouple_1_RANGE_MAS_1] )
        {
            for (i=Thermocouple_1_ORDER_VT - 1u; i > 0u; i--)
            {
                temp = (temp + Thermocouple_1_coeffVT[i][Thermocouple_1_RANGE_MAS_1]) * voltageNorm;
            }
            temp = (temp + Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_1]);
        }

        else
        {
            for (i=Thermocouple_1_ORDER_VT - 1u; i > 0u; i--)
            {
                temp = (temp + Thermocouple_1_coeffVT[i][Thermocouple_1_RANGE_MAS_2]) * voltageNorm;
            }
            temp = (temp + Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_2]);
        }
    }

    #endif /* End  Thermocouple_1_VT_RANGE_LEN == Thermocouple_1_THREE */

    return ((int32)(temp));
}
#else
{

    /***************************************
    *  Customizer Generated Coefficients
    ***************************************/
    const int32 CYCODE Thermocouple_1_coeffVT[][3] = {{0, 0, -1687114},
                                                  {2639629, 164388, 40518839},
                                                  {-1001834, 16879, -90491511},
                                                  {-7623495, -1761422, 196887684},
                                                  {-51750922, 19173707, -227871065},
                                                  {-176344390, -92787626, 136207339},
                                                  {-335143805, 242736174, -31547361},
                                                  {-331192671, -358027528, 0},
                                                  {-134793524, 281193929, 0},
                                                  {0, -91707895, 0}};

const int32 CYCODE Thermocouple_1_voltRange[2] = {0, 20644};

const int8 CYCODE Thermocouple_1_xScaleVT[3] = {13, 15, 16};
const int8 CYCODE Thermocouple_1_coefScaleVT[3] = {7, 1, 7};

    /* Variable to store temperature */
    int32 temp=0;
    uint8 i=0u;

    #if (Thermocouple_1_VT_RANGE_LEN == Thermocouple_1_THREE)
    {
        if(voltage < Thermocouple_1_voltRange[Thermocouple_1_RANGE_MAS_0] )
        {
            if (voltage < 0)
            {
                voltage = -voltage;
                voltage = (int32)((uint64)((uint64)voltage << 
                                               (Thermocouple_1_IN_NORMALIZATION_VT - 
                                                Thermocouple_1_xScaleVT[Thermocouple_1_RANGE_MAS_0])));
                voltage = -voltage;
            }
            else
            {
                voltage = (int32)((uint64)((uint64)voltage << 
                                               (Thermocouple_1_IN_NORMALIZATION_VT - 
                                                Thermocouple_1_xScaleVT[Thermocouple_1_RANGE_MAS_0])));
            }            

            for (i=Thermocouple_1_ORDER_VT - 1u; i > 0u; i--)
            {
                temp = Thermocouple_1_MultShift24((Thermocouple_1_coeffVT[i][Thermocouple_1_RANGE_MAS_0] +
                       temp), voltage);
            }

            if(Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_0] < 0)
            {
                temp = (int32)((uint64)((uint64)(int32)(temp + 
                        Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_0]) << 
                        Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_0]));
            }

            else
            {
                temp = (int32)((uint32)((uint64)(int32)(temp + 
                        Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_0]) >> 
                        Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_0]));
            }
        }

        else if(voltage <= Thermocouple_1_voltRange[Thermocouple_1_RANGE_MAS_1] )
        {
            if (voltage < 0)
            {
                voltage = -voltage;
                voltage = (int32)((uint64)((uint64)voltage << 
                                               (Thermocouple_1_IN_NORMALIZATION_VT - 
                                                Thermocouple_1_xScaleVT[Thermocouple_1_RANGE_MAS_1])));
                voltage = -voltage;
            }
            else
            {
                voltage = (int32)((uint64)((uint64)voltage << 
                                               (Thermocouple_1_IN_NORMALIZATION_VT - 
                                                Thermocouple_1_xScaleVT[Thermocouple_1_RANGE_MAS_1])));
            }              
            
            for (i=Thermocouple_1_ORDER_VT - 1u; i > 0u; i--)
            {
                temp = Thermocouple_1_MultShift24((Thermocouple_1_coeffVT[i][Thermocouple_1_RANGE_MAS_1] +
                       temp), voltage);
            }

            if(Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_1] < 0)
            {
                temp = (int32)((uint64)((uint64)(int32)(temp + 
                        Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_1]) << 
                        Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_1]));
            }

            else
            {
                temp = (int32)((uint32)((uint64)(int32)(temp + 
                        Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_1]) >> 
                        Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_1]));
            }

        }

        else if(voltage <= Thermocouple_1_voltRange[Thermocouple_1_RANGE_MAS_2] )
        {
            if (voltage < 0)
            {
                voltage = -voltage;
                voltage = (int32)((uint64)((uint64)voltage << 
                                               (Thermocouple_1_IN_NORMALIZATION_VT - 
                                                Thermocouple_1_xScaleVT[Thermocouple_1_RANGE_MAS_2])));
                voltage = -voltage;
            }
            else
            {
                voltage = (int32)((uint64)((uint64)voltage << 
                                               (Thermocouple_1_IN_NORMALIZATION_VT - 
                                                Thermocouple_1_xScaleVT[Thermocouple_1_RANGE_MAS_2])));
            }              

            for (i=Thermocouple_1_ORDER_VT - 1u; i > 0u; i--)
            {
                temp = Thermocouple_1_MultShift24((Thermocouple_1_coeffVT[i][Thermocouple_1_RANGE_MAS_2] +
                       temp), voltage);
            }

            if(Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_2] < 0)
            {
                temp = (int32)((uint64)((uint64)(int32)(temp + 
                        Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_2]) << 
                        Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_2]));
            }

            else
            {
                temp = (int32)((uint32)((uint64)(int32)(temp + 
                        Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_2]) >> 
                        Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_2]));
            }
        }

        else
        {
            if (voltage < 0)
            {
                voltage = -voltage;
                voltage = (int32)((uint64)((uint64)voltage << 
                                               (Thermocouple_1_IN_NORMALIZATION_VT - 
                                                Thermocouple_1_xScaleVT[Thermocouple_1_RANGE_MAS_3])));
                voltage = -voltage;
            }
            else
            {
                voltage = (int32)((uint64)((uint64)voltage << 
                                               (Thermocouple_1_IN_NORMALIZATION_VT - 
                                                Thermocouple_1_xScaleVT[Thermocouple_1_RANGE_MAS_3])));
            }              

            for (i=Thermocouple_1_ORDER_VT - 1u; i > 0u; i--)
            {
                temp = Thermocouple_1_MultShift24((Thermocouple_1_coeffVT[i][Thermocouple_1_RANGE_MAS_3] +
                       temp), voltage);
            }

            if(Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_3] < 0)
            {
                temp = (int32)((uint64)((uint64)(int32)(temp + 
                        Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_3]) << 
                        Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_3]));
            }

            else
            {
                temp = (int32)((uint32)((uint64)(int32)(temp + 
                        Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_3]) >> 
                        Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_3]));
            }
        }
    }

    #else
    {
        if(voltage < Thermocouple_1_voltRange[Thermocouple_1_RANGE_MAS_0] )
        {
            if (voltage < 0)
            {
                voltage = -voltage;
                voltage = (int32)((uint64)((uint64)voltage << 
                                               (Thermocouple_1_IN_NORMALIZATION_VT - 
                                                Thermocouple_1_xScaleVT[Thermocouple_1_RANGE_MAS_0])));
                voltage = -voltage;
            }
            else
            {
                voltage = (int32)((uint64)((uint64)voltage << 
                                               (Thermocouple_1_IN_NORMALIZATION_VT - 
                                                Thermocouple_1_xScaleVT[Thermocouple_1_RANGE_MAS_0])));
            }            

            for (i=Thermocouple_1_ORDER_VT - 1u; i > 0u; i--)
            {
                temp = Thermocouple_1_MultShift24((Thermocouple_1_coeffVT[i][Thermocouple_1_RANGE_MAS_0] +
                       temp), voltage);
            }

            if(Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_0] < 0)
            {
                temp = (int32)((uint64)((uint64)(int32)(temp + 
                        Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_0]) << 
                        Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_0]));
            }

            else
            {
                temp = (int32)((uint32)((uint64)(int32)(temp + 
                        Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_0]) >> 
                        Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_0]));
            }
        }

        else if(voltage <= Thermocouple_1_voltRange[Thermocouple_1_RANGE_MAS_1] )
        {
            if (voltage < 0)
            {
                voltage = -voltage;
                voltage = (int32)((uint64)((uint64)voltage << 
                                               (Thermocouple_1_IN_NORMALIZATION_VT - 
                                                Thermocouple_1_xScaleVT[Thermocouple_1_RANGE_MAS_1])));
                voltage = -voltage;
            }
            else
            {
                voltage = (int32)((uint64)((uint64)voltage << 
                                               (Thermocouple_1_IN_NORMALIZATION_VT - 
                                                Thermocouple_1_xScaleVT[Thermocouple_1_RANGE_MAS_1])));
            }              
            
            for (i=Thermocouple_1_ORDER_VT - 1u; i > 0u; i--)
            {
                temp = Thermocouple_1_MultShift24((Thermocouple_1_coeffVT[i][Thermocouple_1_RANGE_MAS_1] +
                       temp), voltage);
            }

            if(Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_1] < 0)
            {
                temp = (int32)((uint64)((uint64)(int32)(temp + 
                        Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_1]) << 
                        Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_1]));
            }

            else
            {
                temp = (int32)((uint32)((uint64)(int32)(temp + 
                        Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_1]) >> 
                        Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_1]));
            }
        }

        else
        {
            if (voltage < 0)
            {
                voltage = -voltage;
                voltage = (int32)((uint64)((uint64)voltage << 
                                               (Thermocouple_1_IN_NORMALIZATION_VT - 
                                                Thermocouple_1_xScaleVT[Thermocouple_1_RANGE_MAS_2])));
                voltage = -voltage;
            }
            else
            {
                voltage = (int32)((uint64)((uint64)voltage << 
                                               (Thermocouple_1_IN_NORMALIZATION_VT - 
                                                Thermocouple_1_xScaleVT[Thermocouple_1_RANGE_MAS_2])));
            }              

            for (i=Thermocouple_1_ORDER_VT - 1u; i > 0u; i--)
            {
                temp = Thermocouple_1_MultShift24((Thermocouple_1_coeffVT[i][Thermocouple_1_RANGE_MAS_2] +
                       temp), voltage);
            }

            if(Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_2] < 0)
            {
                temp = (int32)((uint64)((uint64)(int32)(temp + 
                        Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_2]) << 
                        Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_2]));
            }

            else
            {
                temp = (int32)((uint32)((uint64)(int32)(temp + 
                        Thermocouple_1_coeffVT[Thermocouple_1_FIRST_EL_MAS][Thermocouple_1_RANGE_MAS_2]) >> 
                        Thermocouple_1_coefScaleVT[Thermocouple_1_RANGE_MAS_2]));
            }
        }
    }

    #endif /* End Thermocouple_1_VT_RANGE_LEN == Thermocouple_1_THREE */

    return (temp);
}
#endif /* End CY_PSOC3 */


/*******************************************************************************
* Function Name: Thermocouple_1_GetVoltage
********************************************************************************
*
* Summary:
*  This function takes the temperature as input and provides the expected
*  voltage for that temperature.
*
* Parameters:
*  int32 temperature : Temperature of the cold junction in 1/100 degree C
*
* Return:
*  int32 : Expected voltage output of the thermocouple in microvolts
*
*******************************************************************************/
int32 Thermocouple_1_GetVoltage(int32 temperature) 

#if (CY_PSOC3)
{

    /***************************************
    *  Customizer Generated Coefficients
    ***************************************/
    const int32 CYCODE Thermocouple_1_coeffTV[9] = {0, 
                                                413735, 
                                                83372, 
                                                -137607, 
                                                1089544, 
                                                -9978037, 
                                                43567176, 
                                                -95708775, 
                                                84037362};

    /* Variable to store calculated voltage */
    uint8 i=0u;
    float32 voltage=0.0f;
    float32 temperatureNorm=0.0f;

    temperatureNorm  = (float32)temperature;

    for (i = Thermocouple_1_ORDER_TV - 1u; i > 0u; i--)
    {
        voltage = (Thermocouple_1_coeffTV[i] + voltage) * temperatureNorm;
    }
    voltage = (voltage + Thermocouple_1_coeffTV[Thermocouple_1_FIRST_EL_MAS]);

    return ((int32) (voltage));
}
#else
{

    /***************************************
    *  Customizer Generated Coefficients
    ***************************************/
    const int32 CYCODE Thermocouple_1_coeffTV[9] = {0, 
                                                413735, 
                                                83372, 
                                                -137607, 
                                                1089544, 
                                                -9978037, 
                                                43567176, 
                                                -95708775, 
                                                84037362};

    /* Variable to store calculated voltage */
    uint8 i=0u;
    int32 voltage=0;

    if (temperature < 0)
    {
        temperature = -temperature;
        temperature = (int32)((uint64)((uint64)temperature << 
                                       (Thermocouple_1_IN_NORMALIZATION_TV - Thermocouple_1_X_SCALE_TV)));
        temperature = -temperature;
    }
    else
    {
        temperature = (int32)((uint64)((uint64)temperature << 
                                       (Thermocouple_1_IN_NORMALIZATION_TV - Thermocouple_1_X_SCALE_TV)));
    }
    
    for (i = Thermocouple_1_ORDER_TV - 1u; i > 0u; i--)
    {
        voltage = Thermocouple_1_MultShift24((Thermocouple_1_coeffTV[i] + voltage), temperature);
    }

    voltage = (int32)((uint32)((uint64)(int32)(voltage + Thermocouple_1_coeffTV[Thermocouple_1_FIRST_EL_MAS]) >> 
                                        Thermocouple_1_COEF_SCALE_TV));

    return (voltage);
}
#endif /* End CY_PSOC3 */

/* [] END OF FILE */
