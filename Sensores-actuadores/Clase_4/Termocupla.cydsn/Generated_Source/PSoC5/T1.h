/*******************************************************************************
* File Name: T1.h  
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

#if !defined(CY_PINS_T1_H) /* Pins T1_H */
#define CY_PINS_T1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "T1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 T1__PORT == 15 && ((T1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    T1_Write(uint8 value);
void    T1_SetDriveMode(uint8 mode);
uint8   T1_ReadDataReg(void);
uint8   T1_Read(void);
void    T1_SetInterruptMode(uint16 position, uint16 mode);
uint8   T1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the T1_SetDriveMode() function.
     *  @{
     */
        #define T1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define T1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define T1_DM_RES_UP          PIN_DM_RES_UP
        #define T1_DM_RES_DWN         PIN_DM_RES_DWN
        #define T1_DM_OD_LO           PIN_DM_OD_LO
        #define T1_DM_OD_HI           PIN_DM_OD_HI
        #define T1_DM_STRONG          PIN_DM_STRONG
        #define T1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define T1_MASK               T1__MASK
#define T1_SHIFT              T1__SHIFT
#define T1_WIDTH              1u

/* Interrupt constants */
#if defined(T1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in T1_SetInterruptMode() function.
     *  @{
     */
        #define T1_INTR_NONE      (uint16)(0x0000u)
        #define T1_INTR_RISING    (uint16)(0x0001u)
        #define T1_INTR_FALLING   (uint16)(0x0002u)
        #define T1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define T1_INTR_MASK      (0x01u) 
#endif /* (T1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define T1_PS                     (* (reg8 *) T1__PS)
/* Data Register */
#define T1_DR                     (* (reg8 *) T1__DR)
/* Port Number */
#define T1_PRT_NUM                (* (reg8 *) T1__PRT) 
/* Connect to Analog Globals */                                                  
#define T1_AG                     (* (reg8 *) T1__AG)                       
/* Analog MUX bux enable */
#define T1_AMUX                   (* (reg8 *) T1__AMUX) 
/* Bidirectional Enable */                                                        
#define T1_BIE                    (* (reg8 *) T1__BIE)
/* Bit-mask for Aliased Register Access */
#define T1_BIT_MASK               (* (reg8 *) T1__BIT_MASK)
/* Bypass Enable */
#define T1_BYP                    (* (reg8 *) T1__BYP)
/* Port wide control signals */                                                   
#define T1_CTL                    (* (reg8 *) T1__CTL)
/* Drive Modes */
#define T1_DM0                    (* (reg8 *) T1__DM0) 
#define T1_DM1                    (* (reg8 *) T1__DM1)
#define T1_DM2                    (* (reg8 *) T1__DM2) 
/* Input Buffer Disable Override */
#define T1_INP_DIS                (* (reg8 *) T1__INP_DIS)
/* LCD Common or Segment Drive */
#define T1_LCD_COM_SEG            (* (reg8 *) T1__LCD_COM_SEG)
/* Enable Segment LCD */
#define T1_LCD_EN                 (* (reg8 *) T1__LCD_EN)
/* Slew Rate Control */
#define T1_SLW                    (* (reg8 *) T1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define T1_PRTDSI__CAPS_SEL       (* (reg8 *) T1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define T1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) T1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define T1_PRTDSI__OE_SEL0        (* (reg8 *) T1__PRTDSI__OE_SEL0) 
#define T1_PRTDSI__OE_SEL1        (* (reg8 *) T1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define T1_PRTDSI__OUT_SEL0       (* (reg8 *) T1__PRTDSI__OUT_SEL0) 
#define T1_PRTDSI__OUT_SEL1       (* (reg8 *) T1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define T1_PRTDSI__SYNC_OUT       (* (reg8 *) T1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(T1__SIO_CFG)
    #define T1_SIO_HYST_EN        (* (reg8 *) T1__SIO_HYST_EN)
    #define T1_SIO_REG_HIFREQ     (* (reg8 *) T1__SIO_REG_HIFREQ)
    #define T1_SIO_CFG            (* (reg8 *) T1__SIO_CFG)
    #define T1_SIO_DIFF           (* (reg8 *) T1__SIO_DIFF)
#endif /* (T1__SIO_CFG) */

/* Interrupt Registers */
#if defined(T1__INTSTAT)
    #define T1_INTSTAT            (* (reg8 *) T1__INTSTAT)
    #define T1_SNAP               (* (reg8 *) T1__SNAP)
    
	#define T1_0_INTTYPE_REG 		(* (reg8 *) T1__0__INTTYPE)
#endif /* (T1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_T1_H */


/* [] END OF FILE */
