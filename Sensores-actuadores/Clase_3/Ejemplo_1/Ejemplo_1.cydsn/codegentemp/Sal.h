/*******************************************************************************
* File Name: Sal.h  
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

#if !defined(CY_PINS_Sal_H) /* Pins Sal_H */
#define CY_PINS_Sal_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Sal_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Sal__PORT == 15 && ((Sal__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Sal_Write(uint8 value);
void    Sal_SetDriveMode(uint8 mode);
uint8   Sal_ReadDataReg(void);
uint8   Sal_Read(void);
void    Sal_SetInterruptMode(uint16 position, uint16 mode);
uint8   Sal_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Sal_SetDriveMode() function.
     *  @{
     */
        #define Sal_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Sal_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Sal_DM_RES_UP          PIN_DM_RES_UP
        #define Sal_DM_RES_DWN         PIN_DM_RES_DWN
        #define Sal_DM_OD_LO           PIN_DM_OD_LO
        #define Sal_DM_OD_HI           PIN_DM_OD_HI
        #define Sal_DM_STRONG          PIN_DM_STRONG
        #define Sal_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Sal_MASK               Sal__MASK
#define Sal_SHIFT              Sal__SHIFT
#define Sal_WIDTH              1u

/* Interrupt constants */
#if defined(Sal__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Sal_SetInterruptMode() function.
     *  @{
     */
        #define Sal_INTR_NONE      (uint16)(0x0000u)
        #define Sal_INTR_RISING    (uint16)(0x0001u)
        #define Sal_INTR_FALLING   (uint16)(0x0002u)
        #define Sal_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Sal_INTR_MASK      (0x01u) 
#endif /* (Sal__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Sal_PS                     (* (reg8 *) Sal__PS)
/* Data Register */
#define Sal_DR                     (* (reg8 *) Sal__DR)
/* Port Number */
#define Sal_PRT_NUM                (* (reg8 *) Sal__PRT) 
/* Connect to Analog Globals */                                                  
#define Sal_AG                     (* (reg8 *) Sal__AG)                       
/* Analog MUX bux enable */
#define Sal_AMUX                   (* (reg8 *) Sal__AMUX) 
/* Bidirectional Enable */                                                        
#define Sal_BIE                    (* (reg8 *) Sal__BIE)
/* Bit-mask for Aliased Register Access */
#define Sal_BIT_MASK               (* (reg8 *) Sal__BIT_MASK)
/* Bypass Enable */
#define Sal_BYP                    (* (reg8 *) Sal__BYP)
/* Port wide control signals */                                                   
#define Sal_CTL                    (* (reg8 *) Sal__CTL)
/* Drive Modes */
#define Sal_DM0                    (* (reg8 *) Sal__DM0) 
#define Sal_DM1                    (* (reg8 *) Sal__DM1)
#define Sal_DM2                    (* (reg8 *) Sal__DM2) 
/* Input Buffer Disable Override */
#define Sal_INP_DIS                (* (reg8 *) Sal__INP_DIS)
/* LCD Common or Segment Drive */
#define Sal_LCD_COM_SEG            (* (reg8 *) Sal__LCD_COM_SEG)
/* Enable Segment LCD */
#define Sal_LCD_EN                 (* (reg8 *) Sal__LCD_EN)
/* Slew Rate Control */
#define Sal_SLW                    (* (reg8 *) Sal__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Sal_PRTDSI__CAPS_SEL       (* (reg8 *) Sal__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Sal_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Sal__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Sal_PRTDSI__OE_SEL0        (* (reg8 *) Sal__PRTDSI__OE_SEL0) 
#define Sal_PRTDSI__OE_SEL1        (* (reg8 *) Sal__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Sal_PRTDSI__OUT_SEL0       (* (reg8 *) Sal__PRTDSI__OUT_SEL0) 
#define Sal_PRTDSI__OUT_SEL1       (* (reg8 *) Sal__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Sal_PRTDSI__SYNC_OUT       (* (reg8 *) Sal__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Sal__SIO_CFG)
    #define Sal_SIO_HYST_EN        (* (reg8 *) Sal__SIO_HYST_EN)
    #define Sal_SIO_REG_HIFREQ     (* (reg8 *) Sal__SIO_REG_HIFREQ)
    #define Sal_SIO_CFG            (* (reg8 *) Sal__SIO_CFG)
    #define Sal_SIO_DIFF           (* (reg8 *) Sal__SIO_DIFF)
#endif /* (Sal__SIO_CFG) */

/* Interrupt Registers */
#if defined(Sal__INTSTAT)
    #define Sal_INTSTAT            (* (reg8 *) Sal__INTSTAT)
    #define Sal_SNAP               (* (reg8 *) Sal__SNAP)
    
	#define Sal_0_INTTYPE_REG 		(* (reg8 *) Sal__0__INTTYPE)
#endif /* (Sal__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Sal_H */


/* [] END OF FILE */
