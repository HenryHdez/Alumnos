/*******************************************************************************
* File Name: RELOJ.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_RELOJ_H)
#define CY_CLOCK_RELOJ_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void RELOJ_Start(void) ;
void RELOJ_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void RELOJ_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void RELOJ_StandbyPower(uint8 state) ;
void RELOJ_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 RELOJ_GetDividerRegister(void) ;
void RELOJ_SetModeRegister(uint8 modeBitMask) ;
void RELOJ_ClearModeRegister(uint8 modeBitMask) ;
uint8 RELOJ_GetModeRegister(void) ;
void RELOJ_SetSourceRegister(uint8 clkSource) ;
uint8 RELOJ_GetSourceRegister(void) ;
#if defined(RELOJ__CFG3)
void RELOJ_SetPhaseRegister(uint8 clkPhase) ;
uint8 RELOJ_GetPhaseRegister(void) ;
#endif /* defined(RELOJ__CFG3) */

#define RELOJ_Enable()                       RELOJ_Start()
#define RELOJ_Disable()                      RELOJ_Stop()
#define RELOJ_SetDivider(clkDivider)         RELOJ_SetDividerRegister(clkDivider, 1u)
#define RELOJ_SetDividerValue(clkDivider)    RELOJ_SetDividerRegister((clkDivider) - 1u, 1u)
#define RELOJ_SetMode(clkMode)               RELOJ_SetModeRegister(clkMode)
#define RELOJ_SetSource(clkSource)           RELOJ_SetSourceRegister(clkSource)
#if defined(RELOJ__CFG3)
#define RELOJ_SetPhase(clkPhase)             RELOJ_SetPhaseRegister(clkPhase)
#define RELOJ_SetPhaseValue(clkPhase)        RELOJ_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(RELOJ__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define RELOJ_CLKEN              (* (reg8 *) RELOJ__PM_ACT_CFG)
#define RELOJ_CLKEN_PTR          ((reg8 *) RELOJ__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define RELOJ_CLKSTBY            (* (reg8 *) RELOJ__PM_STBY_CFG)
#define RELOJ_CLKSTBY_PTR        ((reg8 *) RELOJ__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define RELOJ_DIV_LSB            (* (reg8 *) RELOJ__CFG0)
#define RELOJ_DIV_LSB_PTR        ((reg8 *) RELOJ__CFG0)
#define RELOJ_DIV_PTR            ((reg16 *) RELOJ__CFG0)

/* Clock MSB divider configuration register. */
#define RELOJ_DIV_MSB            (* (reg8 *) RELOJ__CFG1)
#define RELOJ_DIV_MSB_PTR        ((reg8 *) RELOJ__CFG1)

/* Mode and source configuration register */
#define RELOJ_MOD_SRC            (* (reg8 *) RELOJ__CFG2)
#define RELOJ_MOD_SRC_PTR        ((reg8 *) RELOJ__CFG2)

#if defined(RELOJ__CFG3)
/* Analog clock phase configuration register */
#define RELOJ_PHASE              (* (reg8 *) RELOJ__CFG3)
#define RELOJ_PHASE_PTR          ((reg8 *) RELOJ__CFG3)
#endif /* defined(RELOJ__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define RELOJ_CLKEN_MASK         RELOJ__PM_ACT_MSK
#define RELOJ_CLKSTBY_MASK       RELOJ__PM_STBY_MSK

/* CFG2 field masks */
#define RELOJ_SRC_SEL_MSK        RELOJ__CFG2_SRC_SEL_MASK
#define RELOJ_MODE_MASK          (~(RELOJ_SRC_SEL_MSK))

#if defined(RELOJ__CFG3)
/* CFG3 phase mask */
#define RELOJ_PHASE_MASK         RELOJ__CFG3_PHASE_DLY_MASK
#endif /* defined(RELOJ__CFG3) */

#endif /* CY_CLOCK_RELOJ_H */


/* [] END OF FILE */
