/*******************************************************************************
* File Name: Ref_neg.h  
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

#if !defined(CY_PINS_Ref_neg_H) /* Pins Ref_neg_H */
#define CY_PINS_Ref_neg_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Ref_neg_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Ref_neg__PORT == 15 && ((Ref_neg__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Ref_neg_Write(uint8 value);
void    Ref_neg_SetDriveMode(uint8 mode);
uint8   Ref_neg_ReadDataReg(void);
uint8   Ref_neg_Read(void);
void    Ref_neg_SetInterruptMode(uint16 position, uint16 mode);
uint8   Ref_neg_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Ref_neg_SetDriveMode() function.
     *  @{
     */
        #define Ref_neg_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Ref_neg_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Ref_neg_DM_RES_UP          PIN_DM_RES_UP
        #define Ref_neg_DM_RES_DWN         PIN_DM_RES_DWN
        #define Ref_neg_DM_OD_LO           PIN_DM_OD_LO
        #define Ref_neg_DM_OD_HI           PIN_DM_OD_HI
        #define Ref_neg_DM_STRONG          PIN_DM_STRONG
        #define Ref_neg_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Ref_neg_MASK               Ref_neg__MASK
#define Ref_neg_SHIFT              Ref_neg__SHIFT
#define Ref_neg_WIDTH              1u

/* Interrupt constants */
#if defined(Ref_neg__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Ref_neg_SetInterruptMode() function.
     *  @{
     */
        #define Ref_neg_INTR_NONE      (uint16)(0x0000u)
        #define Ref_neg_INTR_RISING    (uint16)(0x0001u)
        #define Ref_neg_INTR_FALLING   (uint16)(0x0002u)
        #define Ref_neg_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Ref_neg_INTR_MASK      (0x01u) 
#endif /* (Ref_neg__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ref_neg_PS                     (* (reg8 *) Ref_neg__PS)
/* Data Register */
#define Ref_neg_DR                     (* (reg8 *) Ref_neg__DR)
/* Port Number */
#define Ref_neg_PRT_NUM                (* (reg8 *) Ref_neg__PRT) 
/* Connect to Analog Globals */                                                  
#define Ref_neg_AG                     (* (reg8 *) Ref_neg__AG)                       
/* Analog MUX bux enable */
#define Ref_neg_AMUX                   (* (reg8 *) Ref_neg__AMUX) 
/* Bidirectional Enable */                                                        
#define Ref_neg_BIE                    (* (reg8 *) Ref_neg__BIE)
/* Bit-mask for Aliased Register Access */
#define Ref_neg_BIT_MASK               (* (reg8 *) Ref_neg__BIT_MASK)
/* Bypass Enable */
#define Ref_neg_BYP                    (* (reg8 *) Ref_neg__BYP)
/* Port wide control signals */                                                   
#define Ref_neg_CTL                    (* (reg8 *) Ref_neg__CTL)
/* Drive Modes */
#define Ref_neg_DM0                    (* (reg8 *) Ref_neg__DM0) 
#define Ref_neg_DM1                    (* (reg8 *) Ref_neg__DM1)
#define Ref_neg_DM2                    (* (reg8 *) Ref_neg__DM2) 
/* Input Buffer Disable Override */
#define Ref_neg_INP_DIS                (* (reg8 *) Ref_neg__INP_DIS)
/* LCD Common or Segment Drive */
#define Ref_neg_LCD_COM_SEG            (* (reg8 *) Ref_neg__LCD_COM_SEG)
/* Enable Segment LCD */
#define Ref_neg_LCD_EN                 (* (reg8 *) Ref_neg__LCD_EN)
/* Slew Rate Control */
#define Ref_neg_SLW                    (* (reg8 *) Ref_neg__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Ref_neg_PRTDSI__CAPS_SEL       (* (reg8 *) Ref_neg__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Ref_neg_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Ref_neg__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Ref_neg_PRTDSI__OE_SEL0        (* (reg8 *) Ref_neg__PRTDSI__OE_SEL0) 
#define Ref_neg_PRTDSI__OE_SEL1        (* (reg8 *) Ref_neg__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Ref_neg_PRTDSI__OUT_SEL0       (* (reg8 *) Ref_neg__PRTDSI__OUT_SEL0) 
#define Ref_neg_PRTDSI__OUT_SEL1       (* (reg8 *) Ref_neg__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Ref_neg_PRTDSI__SYNC_OUT       (* (reg8 *) Ref_neg__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Ref_neg__SIO_CFG)
    #define Ref_neg_SIO_HYST_EN        (* (reg8 *) Ref_neg__SIO_HYST_EN)
    #define Ref_neg_SIO_REG_HIFREQ     (* (reg8 *) Ref_neg__SIO_REG_HIFREQ)
    #define Ref_neg_SIO_CFG            (* (reg8 *) Ref_neg__SIO_CFG)
    #define Ref_neg_SIO_DIFF           (* (reg8 *) Ref_neg__SIO_DIFF)
#endif /* (Ref_neg__SIO_CFG) */

/* Interrupt Registers */
#if defined(Ref_neg__INTSTAT)
    #define Ref_neg_INTSTAT            (* (reg8 *) Ref_neg__INTSTAT)
    #define Ref_neg_SNAP               (* (reg8 *) Ref_neg__SNAP)
    
	#define Ref_neg_0_INTTYPE_REG 		(* (reg8 *) Ref_neg__0__INTTYPE)
#endif /* (Ref_neg__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Ref_neg_H */


/* [] END OF FILE */
