/*******************************************************************************
* File Name: Salida.h  
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

#if !defined(CY_PINS_Salida_H) /* Pins Salida_H */
#define CY_PINS_Salida_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Salida_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Salida__PORT == 15 && ((Salida__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Salida_Write(uint8 value);
void    Salida_SetDriveMode(uint8 mode);
uint8   Salida_ReadDataReg(void);
uint8   Salida_Read(void);
void    Salida_SetInterruptMode(uint16 position, uint16 mode);
uint8   Salida_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Salida_SetDriveMode() function.
     *  @{
     */
        #define Salida_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Salida_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Salida_DM_RES_UP          PIN_DM_RES_UP
        #define Salida_DM_RES_DWN         PIN_DM_RES_DWN
        #define Salida_DM_OD_LO           PIN_DM_OD_LO
        #define Salida_DM_OD_HI           PIN_DM_OD_HI
        #define Salida_DM_STRONG          PIN_DM_STRONG
        #define Salida_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Salida_MASK               Salida__MASK
#define Salida_SHIFT              Salida__SHIFT
#define Salida_WIDTH              1u

/* Interrupt constants */
#if defined(Salida__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Salida_SetInterruptMode() function.
     *  @{
     */
        #define Salida_INTR_NONE      (uint16)(0x0000u)
        #define Salida_INTR_RISING    (uint16)(0x0001u)
        #define Salida_INTR_FALLING   (uint16)(0x0002u)
        #define Salida_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Salida_INTR_MASK      (0x01u) 
#endif /* (Salida__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Salida_PS                     (* (reg8 *) Salida__PS)
/* Data Register */
#define Salida_DR                     (* (reg8 *) Salida__DR)
/* Port Number */
#define Salida_PRT_NUM                (* (reg8 *) Salida__PRT) 
/* Connect to Analog Globals */                                                  
#define Salida_AG                     (* (reg8 *) Salida__AG)                       
/* Analog MUX bux enable */
#define Salida_AMUX                   (* (reg8 *) Salida__AMUX) 
/* Bidirectional Enable */                                                        
#define Salida_BIE                    (* (reg8 *) Salida__BIE)
/* Bit-mask for Aliased Register Access */
#define Salida_BIT_MASK               (* (reg8 *) Salida__BIT_MASK)
/* Bypass Enable */
#define Salida_BYP                    (* (reg8 *) Salida__BYP)
/* Port wide control signals */                                                   
#define Salida_CTL                    (* (reg8 *) Salida__CTL)
/* Drive Modes */
#define Salida_DM0                    (* (reg8 *) Salida__DM0) 
#define Salida_DM1                    (* (reg8 *) Salida__DM1)
#define Salida_DM2                    (* (reg8 *) Salida__DM2) 
/* Input Buffer Disable Override */
#define Salida_INP_DIS                (* (reg8 *) Salida__INP_DIS)
/* LCD Common or Segment Drive */
#define Salida_LCD_COM_SEG            (* (reg8 *) Salida__LCD_COM_SEG)
/* Enable Segment LCD */
#define Salida_LCD_EN                 (* (reg8 *) Salida__LCD_EN)
/* Slew Rate Control */
#define Salida_SLW                    (* (reg8 *) Salida__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Salida_PRTDSI__CAPS_SEL       (* (reg8 *) Salida__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Salida_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Salida__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Salida_PRTDSI__OE_SEL0        (* (reg8 *) Salida__PRTDSI__OE_SEL0) 
#define Salida_PRTDSI__OE_SEL1        (* (reg8 *) Salida__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Salida_PRTDSI__OUT_SEL0       (* (reg8 *) Salida__PRTDSI__OUT_SEL0) 
#define Salida_PRTDSI__OUT_SEL1       (* (reg8 *) Salida__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Salida_PRTDSI__SYNC_OUT       (* (reg8 *) Salida__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Salida__SIO_CFG)
    #define Salida_SIO_HYST_EN        (* (reg8 *) Salida__SIO_HYST_EN)
    #define Salida_SIO_REG_HIFREQ     (* (reg8 *) Salida__SIO_REG_HIFREQ)
    #define Salida_SIO_CFG            (* (reg8 *) Salida__SIO_CFG)
    #define Salida_SIO_DIFF           (* (reg8 *) Salida__SIO_DIFF)
#endif /* (Salida__SIO_CFG) */

/* Interrupt Registers */
#if defined(Salida__INTSTAT)
    #define Salida_INTSTAT            (* (reg8 *) Salida__INTSTAT)
    #define Salida_SNAP               (* (reg8 *) Salida__SNAP)
    
	#define Salida_0_INTTYPE_REG 		(* (reg8 *) Salida__0__INTTYPE)
#endif /* (Salida__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Salida_H */


/* [] END OF FILE */
