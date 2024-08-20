/*******************************************************************************
* File Name: B3.h  
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

#if !defined(CY_PINS_B3_H) /* Pins B3_H */
#define CY_PINS_B3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "B3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 B3__PORT == 15 && ((B3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    B3_Write(uint8 value);
void    B3_SetDriveMode(uint8 mode);
uint8   B3_ReadDataReg(void);
uint8   B3_Read(void);
void    B3_SetInterruptMode(uint16 position, uint16 mode);
uint8   B3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the B3_SetDriveMode() function.
     *  @{
     */
        #define B3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define B3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define B3_DM_RES_UP          PIN_DM_RES_UP
        #define B3_DM_RES_DWN         PIN_DM_RES_DWN
        #define B3_DM_OD_LO           PIN_DM_OD_LO
        #define B3_DM_OD_HI           PIN_DM_OD_HI
        #define B3_DM_STRONG          PIN_DM_STRONG
        #define B3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define B3_MASK               B3__MASK
#define B3_SHIFT              B3__SHIFT
#define B3_WIDTH              1u

/* Interrupt constants */
#if defined(B3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in B3_SetInterruptMode() function.
     *  @{
     */
        #define B3_INTR_NONE      (uint16)(0x0000u)
        #define B3_INTR_RISING    (uint16)(0x0001u)
        #define B3_INTR_FALLING   (uint16)(0x0002u)
        #define B3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define B3_INTR_MASK      (0x01u) 
#endif /* (B3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define B3_PS                     (* (reg8 *) B3__PS)
/* Data Register */
#define B3_DR                     (* (reg8 *) B3__DR)
/* Port Number */
#define B3_PRT_NUM                (* (reg8 *) B3__PRT) 
/* Connect to Analog Globals */                                                  
#define B3_AG                     (* (reg8 *) B3__AG)                       
/* Analog MUX bux enable */
#define B3_AMUX                   (* (reg8 *) B3__AMUX) 
/* Bidirectional Enable */                                                        
#define B3_BIE                    (* (reg8 *) B3__BIE)
/* Bit-mask for Aliased Register Access */
#define B3_BIT_MASK               (* (reg8 *) B3__BIT_MASK)
/* Bypass Enable */
#define B3_BYP                    (* (reg8 *) B3__BYP)
/* Port wide control signals */                                                   
#define B3_CTL                    (* (reg8 *) B3__CTL)
/* Drive Modes */
#define B3_DM0                    (* (reg8 *) B3__DM0) 
#define B3_DM1                    (* (reg8 *) B3__DM1)
#define B3_DM2                    (* (reg8 *) B3__DM2) 
/* Input Buffer Disable Override */
#define B3_INP_DIS                (* (reg8 *) B3__INP_DIS)
/* LCD Common or Segment Drive */
#define B3_LCD_COM_SEG            (* (reg8 *) B3__LCD_COM_SEG)
/* Enable Segment LCD */
#define B3_LCD_EN                 (* (reg8 *) B3__LCD_EN)
/* Slew Rate Control */
#define B3_SLW                    (* (reg8 *) B3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define B3_PRTDSI__CAPS_SEL       (* (reg8 *) B3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define B3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) B3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define B3_PRTDSI__OE_SEL0        (* (reg8 *) B3__PRTDSI__OE_SEL0) 
#define B3_PRTDSI__OE_SEL1        (* (reg8 *) B3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define B3_PRTDSI__OUT_SEL0       (* (reg8 *) B3__PRTDSI__OUT_SEL0) 
#define B3_PRTDSI__OUT_SEL1       (* (reg8 *) B3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define B3_PRTDSI__SYNC_OUT       (* (reg8 *) B3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(B3__SIO_CFG)
    #define B3_SIO_HYST_EN        (* (reg8 *) B3__SIO_HYST_EN)
    #define B3_SIO_REG_HIFREQ     (* (reg8 *) B3__SIO_REG_HIFREQ)
    #define B3_SIO_CFG            (* (reg8 *) B3__SIO_CFG)
    #define B3_SIO_DIFF           (* (reg8 *) B3__SIO_DIFF)
#endif /* (B3__SIO_CFG) */

/* Interrupt Registers */
#if defined(B3__INTSTAT)
    #define B3_INTSTAT            (* (reg8 *) B3__INTSTAT)
    #define B3_SNAP               (* (reg8 *) B3__SNAP)
    
	#define B3_0_INTTYPE_REG 		(* (reg8 *) B3__0__INTTYPE)
#endif /* (B3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_B3_H */


/* [] END OF FILE */
