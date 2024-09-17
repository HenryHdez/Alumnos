/*******************************************************************************
* File Name: Termocupla.h
* Version 1.20
*
* Description:
*  This file provides constants and parameter values for the Termocupla
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

#if !defined(CY_THERMOCOUPLE_CALC_Termocupla_H)
#define CY_THERMOCOUPLE_CALC_Termocupla_H

#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/


/***************************************
*       Enum Types
***************************************/

/* ThermocoupleTypes constants  */
#define Termocupla__B 0
#define Termocupla__E 1
#define Termocupla__J 2
#define Termocupla__K 3
#define Termocupla__N 4
#define Termocupla__R 5
#define Termocupla__S 6
#define Termocupla__T 7
             

/* CalcErrorType constants  */
#define Termocupla__ERR_0_1 0
#define Termocupla__ERR_0_5 1
#define Termocupla__ERR_1 2
                 

/* PolynomialOrderType constants  */
#define Termocupla__NIST 0
#define Termocupla__ORDER_7 1
#define Termocupla__ORDER_5 2
           


/***************************************
*        Constants
***************************************/

#define     Termocupla_INIT                       (0)
#define     Termocupla_FIRST_EL_MAS               (0u)
#define     Termocupla_RANGE_MAS_0                (0u)
#define     Termocupla_RANGE_MAS_1                (1u)
#define     Termocupla_RANGE_MAS_2                (2u)
#define     Termocupla_RANGE_MAS_3                (3u)
#define     Termocupla_THREE                      (3u)
#define     Termocupla_IN_NORMALIZATION_VT        (24)
#define     Termocupla_IN_NORMALIZATION_TV        (24u)
#define     Termocupla_24BIT_SHIFTING             (24u)
#define     Termocupla_16BIT_SHIFTING             (16u)
#define     Termocupla_8BIT_SHIFTING              (8u)
#define     Termocupla_24BIT_CUTTING              (0xFFFFFFlu)
#define     Termocupla_16BIT_CUTTING              (0xFFFFu)
#define     Termocupla_8BIT_CUTTING               (0xFFu)
#define     Termocupla_V_IN_FLOAT_NORMALIZATION   (1000u)
#define     Termocupla_V_OUT_FLOAT_NORMALIZATION  (100u)
#define     Termocupla_T_IN_FLOAT_NORMALIZATION   (100u)
#define     Termocupla_T_OUT_FLOAT_NORMALIZATION  (1000u)


/***************************************
*  Customizer Generated Defines
***************************************/

#define     Termocupla_ORDER_TV   (0x09u)
#define     Termocupla_ORDER_VT   (0x0Au)
#define     Termocupla_VT_RANGE_LEN   (0x02u)
#define     Termocupla_X_SCALE_TV   (0x0Fu)
#define     Termocupla_COEF_SCALE_TV   (0x05u)


/***************************************
*        Function Prototypes
***************************************/

int32 Termocupla_GetTemperature(int32 voltage) ;
int32 Termocupla_GetVoltage(int32 temperature) ;

#if (!CY_PSOC3)
    int32 Termocupla_MultShift24(int32 op1, int32 op2) ;
#endif /* (!CY_PSOC3) */

#endif /* CY_THERMOCOUPLE_CALC_Termocupla_H */

/* [] END OF FILE */
