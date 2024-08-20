/*******************************************************************************
* File Name: M1.h  
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

#if !defined(CY_PINS_M1_H) /* Pins M1_H */
#define CY_PINS_M1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "M1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 M1__PORT == 15 && ((M1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    M1_Write(uint8 value);
void    M1_SetDriveMode(uint8 mode);
uint8   M1_ReadDataReg(void);
uint8   M1_Read(void);
void    M1_SetInterruptMode(uint16 position, uint16 mode);
uint8   M1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the M1_SetDriveMode() function.
     *  @{
     */
        #define M1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define M1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define M1_DM_RES_UP          PIN_DM_RES_UP
        #define M1_DM_RES_DWN         PIN_DM_RES_DWN
        #define M1_DM_OD_LO           PIN_DM_OD_LO
        #define M1_DM_OD_HI           PIN_DM_OD_HI
        #define M1_DM_STRONG          PIN_DM_STRONG
        #define M1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define M1_MASK               M1__MASK
#define M1_SHIFT              M1__SHIFT
#define M1_WIDTH              1u

/* Interrupt constants */
#if defined(M1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in M1_SetInterruptMode() function.
     *  @{
     */
        #define M1_INTR_NONE      (uint16)(0x0000u)
        #define M1_INTR_RISING    (uint16)(0x0001u)
        #define M1_INTR_FALLING   (uint16)(0x0002u)
        #define M1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define M1_INTR_MASK      (0x01u) 
#endif /* (M1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define M1_PS                     (* (reg8 *) M1__PS)
/* Data Register */
#define M1_DR                     (* (reg8 *) M1__DR)
/* Port Number */
#define M1_PRT_NUM                (* (reg8 *) M1__PRT) 
/* Connect to Analog Globals */                                                  
#define M1_AG                     (* (reg8 *) M1__AG)                       
/* Analog MUX bux enable */
#define M1_AMUX                   (* (reg8 *) M1__AMUX) 
/* Bidirectional Enable */                                                        
#define M1_BIE                    (* (reg8 *) M1__BIE)
/* Bit-mask for Aliased Register Access */
#define M1_BIT_MASK               (* (reg8 *) M1__BIT_MASK)
/* Bypass Enable */
#define M1_BYP                    (* (reg8 *) M1__BYP)
/* Port wide control signals */                                                   
#define M1_CTL                    (* (reg8 *) M1__CTL)
/* Drive Modes */
#define M1_DM0                    (* (reg8 *) M1__DM0) 
#define M1_DM1                    (* (reg8 *) M1__DM1)
#define M1_DM2                    (* (reg8 *) M1__DM2) 
/* Input Buffer Disable Override */
#define M1_INP_DIS                (* (reg8 *) M1__INP_DIS)
/* LCD Common or Segment Drive */
#define M1_LCD_COM_SEG            (* (reg8 *) M1__LCD_COM_SEG)
/* Enable Segment LCD */
#define M1_LCD_EN                 (* (reg8 *) M1__LCD_EN)
/* Slew Rate Control */
#define M1_SLW                    (* (reg8 *) M1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define M1_PRTDSI__CAPS_SEL       (* (reg8 *) M1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define M1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) M1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define M1_PRTDSI__OE_SEL0        (* (reg8 *) M1__PRTDSI__OE_SEL0) 
#define M1_PRTDSI__OE_SEL1        (* (reg8 *) M1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define M1_PRTDSI__OUT_SEL0       (* (reg8 *) M1__PRTDSI__OUT_SEL0) 
#define M1_PRTDSI__OUT_SEL1       (* (reg8 *) M1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define M1_PRTDSI__SYNC_OUT       (* (reg8 *) M1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(M1__SIO_CFG)
    #define M1_SIO_HYST_EN        (* (reg8 *) M1__SIO_HYST_EN)
    #define M1_SIO_REG_HIFREQ     (* (reg8 *) M1__SIO_REG_HIFREQ)
    #define M1_SIO_CFG            (* (reg8 *) M1__SIO_CFG)
    #define M1_SIO_DIFF           (* (reg8 *) M1__SIO_DIFF)
#endif /* (M1__SIO_CFG) */

/* Interrupt Registers */
#if defined(M1__INTSTAT)
    #define M1_INTSTAT            (* (reg8 *) M1__INTSTAT)
    #define M1_SNAP               (* (reg8 *) M1__SNAP)
    
	#define M1_0_INTTYPE_REG 		(* (reg8 *) M1__0__INTTYPE)
#endif /* (M1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_M1_H */


/* [] END OF FILE */
