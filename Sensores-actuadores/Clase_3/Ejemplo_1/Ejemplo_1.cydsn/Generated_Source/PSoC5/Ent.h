/*******************************************************************************
* File Name: Ent.h  
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

#if !defined(CY_PINS_Ent_H) /* Pins Ent_H */
#define CY_PINS_Ent_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Ent_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Ent__PORT == 15 && ((Ent__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Ent_Write(uint8 value);
void    Ent_SetDriveMode(uint8 mode);
uint8   Ent_ReadDataReg(void);
uint8   Ent_Read(void);
void    Ent_SetInterruptMode(uint16 position, uint16 mode);
uint8   Ent_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Ent_SetDriveMode() function.
     *  @{
     */
        #define Ent_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Ent_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Ent_DM_RES_UP          PIN_DM_RES_UP
        #define Ent_DM_RES_DWN         PIN_DM_RES_DWN
        #define Ent_DM_OD_LO           PIN_DM_OD_LO
        #define Ent_DM_OD_HI           PIN_DM_OD_HI
        #define Ent_DM_STRONG          PIN_DM_STRONG
        #define Ent_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Ent_MASK               Ent__MASK
#define Ent_SHIFT              Ent__SHIFT
#define Ent_WIDTH              1u

/* Interrupt constants */
#if defined(Ent__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Ent_SetInterruptMode() function.
     *  @{
     */
        #define Ent_INTR_NONE      (uint16)(0x0000u)
        #define Ent_INTR_RISING    (uint16)(0x0001u)
        #define Ent_INTR_FALLING   (uint16)(0x0002u)
        #define Ent_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Ent_INTR_MASK      (0x01u) 
#endif /* (Ent__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ent_PS                     (* (reg8 *) Ent__PS)
/* Data Register */
#define Ent_DR                     (* (reg8 *) Ent__DR)
/* Port Number */
#define Ent_PRT_NUM                (* (reg8 *) Ent__PRT) 
/* Connect to Analog Globals */                                                  
#define Ent_AG                     (* (reg8 *) Ent__AG)                       
/* Analog MUX bux enable */
#define Ent_AMUX                   (* (reg8 *) Ent__AMUX) 
/* Bidirectional Enable */                                                        
#define Ent_BIE                    (* (reg8 *) Ent__BIE)
/* Bit-mask for Aliased Register Access */
#define Ent_BIT_MASK               (* (reg8 *) Ent__BIT_MASK)
/* Bypass Enable */
#define Ent_BYP                    (* (reg8 *) Ent__BYP)
/* Port wide control signals */                                                   
#define Ent_CTL                    (* (reg8 *) Ent__CTL)
/* Drive Modes */
#define Ent_DM0                    (* (reg8 *) Ent__DM0) 
#define Ent_DM1                    (* (reg8 *) Ent__DM1)
#define Ent_DM2                    (* (reg8 *) Ent__DM2) 
/* Input Buffer Disable Override */
#define Ent_INP_DIS                (* (reg8 *) Ent__INP_DIS)
/* LCD Common or Segment Drive */
#define Ent_LCD_COM_SEG            (* (reg8 *) Ent__LCD_COM_SEG)
/* Enable Segment LCD */
#define Ent_LCD_EN                 (* (reg8 *) Ent__LCD_EN)
/* Slew Rate Control */
#define Ent_SLW                    (* (reg8 *) Ent__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Ent_PRTDSI__CAPS_SEL       (* (reg8 *) Ent__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Ent_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Ent__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Ent_PRTDSI__OE_SEL0        (* (reg8 *) Ent__PRTDSI__OE_SEL0) 
#define Ent_PRTDSI__OE_SEL1        (* (reg8 *) Ent__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Ent_PRTDSI__OUT_SEL0       (* (reg8 *) Ent__PRTDSI__OUT_SEL0) 
#define Ent_PRTDSI__OUT_SEL1       (* (reg8 *) Ent__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Ent_PRTDSI__SYNC_OUT       (* (reg8 *) Ent__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Ent__SIO_CFG)
    #define Ent_SIO_HYST_EN        (* (reg8 *) Ent__SIO_HYST_EN)
    #define Ent_SIO_REG_HIFREQ     (* (reg8 *) Ent__SIO_REG_HIFREQ)
    #define Ent_SIO_CFG            (* (reg8 *) Ent__SIO_CFG)
    #define Ent_SIO_DIFF           (* (reg8 *) Ent__SIO_DIFF)
#endif /* (Ent__SIO_CFG) */

/* Interrupt Registers */
#if defined(Ent__INTSTAT)
    #define Ent_INTSTAT            (* (reg8 *) Ent__INTSTAT)
    #define Ent_SNAP               (* (reg8 *) Ent__SNAP)
    
	#define Ent_0_INTTYPE_REG 		(* (reg8 *) Ent__0__INTTYPE)
#endif /* (Ent__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Ent_H */


/* [] END OF FILE */
