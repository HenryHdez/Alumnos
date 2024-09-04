/*******************************************************************************
* File Name: Termistor.h
* Version 1.20
*
* Description:
*  This header file provides registers and constants associated with the
*  ThermistorCalc component.
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

#if !defined(CY_THERMISTOR_CALC_Termistor_H)
#define CY_THERMISTOR_CALC_Termistor_H

#include "cyfitter.h"
#include "CyLib.h"

#define Termistor_IMPLEMENTATION         (0u)
#define Termistor_EQUATION_METHOD        (0u)
#define Termistor_LUT_METHOD             (1u)

#if (Termistor_IMPLEMENTATION == Termistor_EQUATION_METHOD)
    #include <math.h>
#endif /* (Termistor_IMPLEMENTATION == Termistor_EQUATION_METHOD) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define Termistor_REF_RESISTOR           (10000)
#define Termistor_REF_RES_SHIFT          (0u)
#define Termistor_ACCURACY               (10u)
#define Termistor_MIN_TEMP               (0 * Termistor_SCALE)


/***************************************
*        Function Prototypes
***************************************/

uint32 Termistor_GetResistance(int16 vReference, int16 vThermistor)
                                      ;
int16 Termistor_GetTemperature(uint32 resT) ;


/***************************************
*           API Constants
***************************************/

#define Termistor_K2C                    (273.15)
#define Termistor_SCALE                  (100)

#define Termistor_THA               (0.0009032679)
#define Termistor_THB               (0.000248772)
#define Termistor_THC               (2.041094E-07)


#endif /* CY_THERMISTOR_CALC_Termistor_H */


/* [] END OF FILE */
