/*******************************************************************************
* File Name: Thermocouple_1.h
* Version 1.20
*
* Description:
*  This file provides constants and parameter values for the Thermocouple_1
*  component.
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

#if !defined(CY_THERMOCOUPLE_CALC_Thermocouple_1_H)
#define CY_THERMOCOUPLE_CALC_Thermocouple_1_H

#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/


/***************************************
*       Enum Types
***************************************/

/* ThermocoupleTypes constants  */
#define Thermocouple_1__B 0
#define Thermocouple_1__E 1
#define Thermocouple_1__J 2
#define Thermocouple_1__K 3
#define Thermocouple_1__N 4
#define Thermocouple_1__R 5
#define Thermocouple_1__S 6
#define Thermocouple_1__T 7
             

/* CalcErrorType constants  */
#define Thermocouple_1__ERR_0_1 0
#define Thermocouple_1__ERR_0_5 1
#define Thermocouple_1__ERR_1 2
                 

/* PolynomialOrderType constants  */
#define Thermocouple_1__NIST 0
#define Thermocouple_1__ORDER_7 1
#define Thermocouple_1__ORDER_5 2
           


/***************************************
*        Constants
***************************************/

#define     Thermocouple_1_INIT                       (0)
#define     Thermocouple_1_FIRST_EL_MAS               (0u)
#define     Thermocouple_1_RANGE_MAS_0                (0u)
#define     Thermocouple_1_RANGE_MAS_1                (1u)
#define     Thermocouple_1_RANGE_MAS_2                (2u)
#define     Thermocouple_1_RANGE_MAS_3                (3u)
#define     Thermocouple_1_THREE                      (3u)
#define     Thermocouple_1_IN_NORMALIZATION_VT        (24)
#define     Thermocouple_1_IN_NORMALIZATION_TV        (24u)
#define     Thermocouple_1_24BIT_SHIFTING             (24u)
#define     Thermocouple_1_16BIT_SHIFTING             (16u)
#define     Thermocouple_1_8BIT_SHIFTING              (8u)
#define     Thermocouple_1_24BIT_CUTTING              (0xFFFFFFlu)
#define     Thermocouple_1_16BIT_CUTTING              (0xFFFFu)
#define     Thermocouple_1_8BIT_CUTTING               (0xFFu)
#define     Thermocouple_1_V_IN_FLOAT_NORMALIZATION   (1000u)
#define     Thermocouple_1_V_OUT_FLOAT_NORMALIZATION  (100u)
#define     Thermocouple_1_T_IN_FLOAT_NORMALIZATION   (100u)
#define     Thermocouple_1_T_OUT_FLOAT_NORMALIZATION  (1000u)


/***************************************
*  Customizer Generated Defines
***************************************/

#define     Thermocouple_1_ORDER_TV   (0x09u)
#define     Thermocouple_1_ORDER_VT   (0x0Au)
#define     Thermocouple_1_VT_RANGE_LEN   (0x02u)
#define     Thermocouple_1_X_SCALE_TV   (0x0Fu)
#define     Thermocouple_1_COEF_SCALE_TV   (0x05u)


/***************************************
*        Function Prototypes
***************************************/

int32 Thermocouple_1_GetTemperature(int32 voltage) ;
int32 Thermocouple_1_GetVoltage(int32 temperature) ;

#if (!CY_PSOC3)
    int32 Thermocouple_1_MultShift24(int32 op1, int32 op2) ;
#endif /* (!CY_PSOC3) */

#endif /* CY_THERMOCOUPLE_CALC_Thermocouple_1_H */

/* [] END OF FILE */
