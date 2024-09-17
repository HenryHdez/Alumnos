/*******************************************************************************
* File Name: RTD.h
* Version 1.20
*
* Description:
*  This header file provides registers and constants associated with the
*  RTDCalc component.
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

#if !defined(CY_RTD_CALC_RTD_H)
#define CY_RTD_CALC_RTD_H

#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define RTD_RTD_TYPE           (100u)


/***************************************
*  Customizer Generated Defines
***************************************/

#define     RTD_ORDER_POS   (0x3u)
#define     RTD_POS_INPUT_SCALE   (9)
#define     RTD_POS_COEFF_SCALE   (11)
#define     RTD_ORDER_NEG   (0x3u)
#define     RTD_NEG_INPUT_SCALE   (9)
#define     RTD_NEG_COEFF_SCALE   (11)


/***************************************
*        Function Prototypes
***************************************/

int32 RTD_GetTemperature(uint32 res) ;

#if(!CY_PSOC3)
    int32 RTD_MultShift24(int32 op1, uint32 op2) ;
#endif /* (!CY_PSOC3) */


/***************************************
*    Enumerated Types and Parameters
***************************************/

/* Enumerated Types RTDType, Used in parameter RTDType */

#define RTD__PT100 100
#define RTD__PT500 500
#define RTD__PT1000 1000



/***************************************
*           API Constants
***************************************/

/* Resistance value at 0 degrees C in milliohms */
#define RTD_ZERO_VAL_PT100             (100000lu)
#define RTD_ZERO_VAL_PT500             (500000lu)
#define RTD_ZERO_VAL_PT1000            (1000000lu)

#define RTD_FIRST_EL_MAS               (0u)
#define RTD_24BIT_SHIFTING             (24u)
#define RTD_16BIT_SHIFTING             (16u)
#define RTD_8BIT_SHIFTING              (8u)
#define RTD_24BIT_CUTTING              (0xFFFFFFu)
#define RTD_16BIT_CUTTING              (0xFFFFu)
#define RTD_8BIT_CUTTING               (0xFFu)
#define RTD_IN_NORMALIZATION           (14)
#define RTD_IN_FLOAT_NORMALIZATION     (1000u)
#define RTD_OUT_FLOAT_NORMALIZATION    (100u)

#endif /* CY_RTD_CALC_RTD_H */

/* [] END OF FILE */
