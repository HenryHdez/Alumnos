/*******************************************************************************
* File Name: Ref_pos.h  
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

#if !defined(CY_PINS_Ref_pos_H) /* Pins Ref_pos_H */
#define CY_PINS_Ref_pos_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Ref_pos_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Ref_pos__PORT == 15 && ((Ref_pos__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Ref_pos_Write(uint8 value);
void    Ref_pos_SetDriveMode(uint8 mode);
uint8   Ref_pos_ReadDataReg(void);
uint8   Ref_pos_Read(void);
void    Ref_pos_SetInterruptMode(uint16 position, uint16 mode);
uint8   Ref_pos_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Ref_pos_SetDriveMode() function.
     *  @{
     */
        #define Ref_pos_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Ref_pos_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Ref_pos_DM_RES_UP          PIN_DM_RES_UP
        #define Ref_pos_DM_RES_DWN         PIN_DM_RES_DWN
        #define Ref_pos_DM_OD_LO           PIN_DM_OD_LO
        #define Ref_pos_DM_OD_HI           PIN_DM_OD_HI
        #define Ref_pos_DM_STRONG          PIN_DM_STRONG
        #define Ref_pos_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Ref_pos_MASK               Ref_pos__MASK
#define Ref_pos_SHIFT              Ref_pos__SHIFT
#define Ref_pos_WIDTH              1u

/* Interrupt constants */
#if defined(Ref_pos__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Ref_pos_SetInterruptMode() function.
     *  @{
     */
        #define Ref_pos_INTR_NONE      (uint16)(0x0000u)
        #define Ref_pos_INTR_RISING    (uint16)(0x0001u)
        #define Ref_pos_INTR_FALLING   (uint16)(0x0002u)
        #define Ref_pos_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Ref_pos_INTR_MASK      (0x01u) 
#endif /* (Ref_pos__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ref_pos_PS                     (* (reg8 *) Ref_pos__PS)
/* Data Register */
#define Ref_pos_DR                     (* (reg8 *) Ref_pos__DR)
/* Port Number */
#define Ref_pos_PRT_NUM                (* (reg8 *) Ref_pos__PRT) 
/* Connect to Analog Globals */                                                  
#define Ref_pos_AG                     (* (reg8 *) Ref_pos__AG)                       
/* Analog MUX bux enable */
#define Ref_pos_AMUX                   (* (reg8 *) Ref_pos__AMUX) 
/* Bidirectional Enable */                                                        
#define Ref_pos_BIE                    (* (reg8 *) Ref_pos__BIE)
/* Bit-mask for Aliased Register Access */
#define Ref_pos_BIT_MASK               (* (reg8 *) Ref_pos__BIT_MASK)
/* Bypass Enable */
#define Ref_pos_BYP                    (* (reg8 *) Ref_pos__BYP)
/* Port wide control signals */                                                   
#define Ref_pos_CTL                    (* (reg8 *) Ref_pos__CTL)
/* Drive Modes */
#define Ref_pos_DM0                    (* (reg8 *) Ref_pos__DM0) 
#define Ref_pos_DM1                    (* (reg8 *) Ref_pos__DM1)
#define Ref_pos_DM2                    (* (reg8 *) Ref_pos__DM2) 
/* Input Buffer Disable Override */
#define Ref_pos_INP_DIS                (* (reg8 *) Ref_pos__INP_DIS)
/* LCD Common or Segment Drive */
#define Ref_pos_LCD_COM_SEG            (* (reg8 *) Ref_pos__LCD_COM_SEG)
/* Enable Segment LCD */
#define Ref_pos_LCD_EN                 (* (reg8 *) Ref_pos__LCD_EN)
/* Slew Rate Control */
#define Ref_pos_SLW                    (* (reg8 *) Ref_pos__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Ref_pos_PRTDSI__CAPS_SEL       (* (reg8 *) Ref_pos__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Ref_pos_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Ref_pos__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Ref_pos_PRTDSI__OE_SEL0        (* (reg8 *) Ref_pos__PRTDSI__OE_SEL0) 
#define Ref_pos_PRTDSI__OE_SEL1        (* (reg8 *) Ref_pos__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Ref_pos_PRTDSI__OUT_SEL0       (* (reg8 *) Ref_pos__PRTDSI__OUT_SEL0) 
#define Ref_pos_PRTDSI__OUT_SEL1       (* (reg8 *) Ref_pos__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Ref_pos_PRTDSI__SYNC_OUT       (* (reg8 *) Ref_pos__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Ref_pos__SIO_CFG)
    #define Ref_pos_SIO_HYST_EN        (* (reg8 *) Ref_pos__SIO_HYST_EN)
    #define Ref_pos_SIO_REG_HIFREQ     (* (reg8 *) Ref_pos__SIO_REG_HIFREQ)
    #define Ref_pos_SIO_CFG            (* (reg8 *) Ref_pos__SIO_CFG)
    #define Ref_pos_SIO_DIFF           (* (reg8 *) Ref_pos__SIO_DIFF)
#endif /* (Ref_pos__SIO_CFG) */

/* Interrupt Registers */
#if defined(Ref_pos__INTSTAT)
    #define Ref_pos_INTSTAT            (* (reg8 *) Ref_pos__INTSTAT)
    #define Ref_pos_SNAP               (* (reg8 *) Ref_pos__SNAP)
    
	#define Ref_pos_0_INTTYPE_REG 		(* (reg8 *) Ref_pos__0__INTTYPE)
#endif /* (Ref_pos__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Ref_pos_H */


/* [] END OF FILE */
