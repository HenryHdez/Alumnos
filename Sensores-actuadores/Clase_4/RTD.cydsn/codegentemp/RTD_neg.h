/*******************************************************************************
* File Name: RTD_neg.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_RTD_neg_H) /* Pins RTD_neg_H */
#define CY_PINS_RTD_neg_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RTD_neg_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RTD_neg__PORT == 15 && ((RTD_neg__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RTD_neg_Write(uint8 value);
void    RTD_neg_SetDriveMode(uint8 mode);
uint8   RTD_neg_ReadDataReg(void);
uint8   RTD_neg_Read(void);
void    RTD_neg_SetInterruptMode(uint16 position, uint16 mode);
uint8   RTD_neg_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RTD_neg_SetDriveMode() function.
     *  @{
     */
        #define RTD_neg_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RTD_neg_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RTD_neg_DM_RES_UP          PIN_DM_RES_UP
        #define RTD_neg_DM_RES_DWN         PIN_DM_RES_DWN
        #define RTD_neg_DM_OD_LO           PIN_DM_OD_LO
        #define RTD_neg_DM_OD_HI           PIN_DM_OD_HI
        #define RTD_neg_DM_STRONG          PIN_DM_STRONG
        #define RTD_neg_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RTD_neg_MASK               RTD_neg__MASK
#define RTD_neg_SHIFT              RTD_neg__SHIFT
#define RTD_neg_WIDTH              1u

/* Interrupt constants */
#if defined(RTD_neg__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RTD_neg_SetInterruptMode() function.
     *  @{
     */
        #define RTD_neg_INTR_NONE      (uint16)(0x0000u)
        #define RTD_neg_INTR_RISING    (uint16)(0x0001u)
        #define RTD_neg_INTR_FALLING   (uint16)(0x0002u)
        #define RTD_neg_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RTD_neg_INTR_MASK      (0x01u) 
#endif /* (RTD_neg__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RTD_neg_PS                     (* (reg8 *) RTD_neg__PS)
/* Data Register */
#define RTD_neg_DR                     (* (reg8 *) RTD_neg__DR)
/* Port Number */
#define RTD_neg_PRT_NUM                (* (reg8 *) RTD_neg__PRT) 
/* Connect to Analog Globals */                                                  
#define RTD_neg_AG                     (* (reg8 *) RTD_neg__AG)                       
/* Analog MUX bux enable */
#define RTD_neg_AMUX                   (* (reg8 *) RTD_neg__AMUX) 
/* Bidirectional Enable */                                                        
#define RTD_neg_BIE                    (* (reg8 *) RTD_neg__BIE)
/* Bit-mask for Aliased Register Access */
#define RTD_neg_BIT_MASK               (* (reg8 *) RTD_neg__BIT_MASK)
/* Bypass Enable */
#define RTD_neg_BYP                    (* (reg8 *) RTD_neg__BYP)
/* Port wide control signals */                                                   
#define RTD_neg_CTL                    (* (reg8 *) RTD_neg__CTL)
/* Drive Modes */
#define RTD_neg_DM0                    (* (reg8 *) RTD_neg__DM0) 
#define RTD_neg_DM1                    (* (reg8 *) RTD_neg__DM1)
#define RTD_neg_DM2                    (* (reg8 *) RTD_neg__DM2) 
/* Input Buffer Disable Override */
#define RTD_neg_INP_DIS                (* (reg8 *) RTD_neg__INP_DIS)
/* LCD Common or Segment Drive */
#define RTD_neg_LCD_COM_SEG            (* (reg8 *) RTD_neg__LCD_COM_SEG)
/* Enable Segment LCD */
#define RTD_neg_LCD_EN                 (* (reg8 *) RTD_neg__LCD_EN)
/* Slew Rate Control */
#define RTD_neg_SLW                    (* (reg8 *) RTD_neg__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RTD_neg_PRTDSI__CAPS_SEL       (* (reg8 *) RTD_neg__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RTD_neg_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RTD_neg__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RTD_neg_PRTDSI__OE_SEL0        (* (reg8 *) RTD_neg__PRTDSI__OE_SEL0) 
#define RTD_neg_PRTDSI__OE_SEL1        (* (reg8 *) RTD_neg__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RTD_neg_PRTDSI__OUT_SEL0       (* (reg8 *) RTD_neg__PRTDSI__OUT_SEL0) 
#define RTD_neg_PRTDSI__OUT_SEL1       (* (reg8 *) RTD_neg__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RTD_neg_PRTDSI__SYNC_OUT       (* (reg8 *) RTD_neg__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RTD_neg__SIO_CFG)
    #define RTD_neg_SIO_HYST_EN        (* (reg8 *) RTD_neg__SIO_HYST_EN)
    #define RTD_neg_SIO_REG_HIFREQ     (* (reg8 *) RTD_neg__SIO_REG_HIFREQ)
    #define RTD_neg_SIO_CFG            (* (reg8 *) RTD_neg__SIO_CFG)
    #define RTD_neg_SIO_DIFF           (* (reg8 *) RTD_neg__SIO_DIFF)
#endif /* (RTD_neg__SIO_CFG) */

/* Interrupt Registers */
#if defined(RTD_neg__INTSTAT)
    #define RTD_neg_INTSTAT            (* (reg8 *) RTD_neg__INTSTAT)
    #define RTD_neg_SNAP               (* (reg8 *) RTD_neg__SNAP)
    
	#define RTD_neg_0_INTTYPE_REG 		(* (reg8 *) RTD_neg__0__INTTYPE)
#endif /* (RTD_neg__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RTD_neg_H */


/* [] END OF FILE */
