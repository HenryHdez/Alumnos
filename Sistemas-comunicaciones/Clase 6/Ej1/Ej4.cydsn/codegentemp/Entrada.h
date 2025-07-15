/*******************************************************************************
* File Name: Entrada.h  
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

#if !defined(CY_PINS_Entrada_H) /* Pins Entrada_H */
#define CY_PINS_Entrada_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Entrada_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Entrada__PORT == 15 && ((Entrada__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Entrada_Write(uint8 value);
void    Entrada_SetDriveMode(uint8 mode);
uint8   Entrada_ReadDataReg(void);
uint8   Entrada_Read(void);
void    Entrada_SetInterruptMode(uint16 position, uint16 mode);
uint8   Entrada_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Entrada_SetDriveMode() function.
     *  @{
     */
        #define Entrada_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Entrada_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Entrada_DM_RES_UP          PIN_DM_RES_UP
        #define Entrada_DM_RES_DWN         PIN_DM_RES_DWN
        #define Entrada_DM_OD_LO           PIN_DM_OD_LO
        #define Entrada_DM_OD_HI           PIN_DM_OD_HI
        #define Entrada_DM_STRONG          PIN_DM_STRONG
        #define Entrada_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Entrada_MASK               Entrada__MASK
#define Entrada_SHIFT              Entrada__SHIFT
#define Entrada_WIDTH              1u

/* Interrupt constants */
#if defined(Entrada__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Entrada_SetInterruptMode() function.
     *  @{
     */
        #define Entrada_INTR_NONE      (uint16)(0x0000u)
        #define Entrada_INTR_RISING    (uint16)(0x0001u)
        #define Entrada_INTR_FALLING   (uint16)(0x0002u)
        #define Entrada_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Entrada_INTR_MASK      (0x01u) 
#endif /* (Entrada__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Entrada_PS                     (* (reg8 *) Entrada__PS)
/* Data Register */
#define Entrada_DR                     (* (reg8 *) Entrada__DR)
/* Port Number */
#define Entrada_PRT_NUM                (* (reg8 *) Entrada__PRT) 
/* Connect to Analog Globals */                                                  
#define Entrada_AG                     (* (reg8 *) Entrada__AG)                       
/* Analog MUX bux enable */
#define Entrada_AMUX                   (* (reg8 *) Entrada__AMUX) 
/* Bidirectional Enable */                                                        
#define Entrada_BIE                    (* (reg8 *) Entrada__BIE)
/* Bit-mask for Aliased Register Access */
#define Entrada_BIT_MASK               (* (reg8 *) Entrada__BIT_MASK)
/* Bypass Enable */
#define Entrada_BYP                    (* (reg8 *) Entrada__BYP)
/* Port wide control signals */                                                   
#define Entrada_CTL                    (* (reg8 *) Entrada__CTL)
/* Drive Modes */
#define Entrada_DM0                    (* (reg8 *) Entrada__DM0) 
#define Entrada_DM1                    (* (reg8 *) Entrada__DM1)
#define Entrada_DM2                    (* (reg8 *) Entrada__DM2) 
/* Input Buffer Disable Override */
#define Entrada_INP_DIS                (* (reg8 *) Entrada__INP_DIS)
/* LCD Common or Segment Drive */
#define Entrada_LCD_COM_SEG            (* (reg8 *) Entrada__LCD_COM_SEG)
/* Enable Segment LCD */
#define Entrada_LCD_EN                 (* (reg8 *) Entrada__LCD_EN)
/* Slew Rate Control */
#define Entrada_SLW                    (* (reg8 *) Entrada__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Entrada_PRTDSI__CAPS_SEL       (* (reg8 *) Entrada__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Entrada_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Entrada__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Entrada_PRTDSI__OE_SEL0        (* (reg8 *) Entrada__PRTDSI__OE_SEL0) 
#define Entrada_PRTDSI__OE_SEL1        (* (reg8 *) Entrada__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Entrada_PRTDSI__OUT_SEL0       (* (reg8 *) Entrada__PRTDSI__OUT_SEL0) 
#define Entrada_PRTDSI__OUT_SEL1       (* (reg8 *) Entrada__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Entrada_PRTDSI__SYNC_OUT       (* (reg8 *) Entrada__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Entrada__SIO_CFG)
    #define Entrada_SIO_HYST_EN        (* (reg8 *) Entrada__SIO_HYST_EN)
    #define Entrada_SIO_REG_HIFREQ     (* (reg8 *) Entrada__SIO_REG_HIFREQ)
    #define Entrada_SIO_CFG            (* (reg8 *) Entrada__SIO_CFG)
    #define Entrada_SIO_DIFF           (* (reg8 *) Entrada__SIO_DIFF)
#endif /* (Entrada__SIO_CFG) */

/* Interrupt Registers */
#if defined(Entrada__INTSTAT)
    #define Entrada_INTSTAT            (* (reg8 *) Entrada__INTSTAT)
    #define Entrada_SNAP               (* (reg8 *) Entrada__SNAP)
    
	#define Entrada_0_INTTYPE_REG 		(* (reg8 *) Entrada__0__INTTYPE)
#endif /* (Entrada__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Entrada_H */


/* [] END OF FILE */
