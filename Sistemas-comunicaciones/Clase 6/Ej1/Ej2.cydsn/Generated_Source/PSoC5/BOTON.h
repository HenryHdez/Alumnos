/*******************************************************************************
* File Name: BOTON.h  
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

#if !defined(CY_PINS_BOTON_H) /* Pins BOTON_H */
#define CY_PINS_BOTON_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BOTON_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BOTON__PORT == 15 && ((BOTON__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    BOTON_Write(uint8 value);
void    BOTON_SetDriveMode(uint8 mode);
uint8   BOTON_ReadDataReg(void);
uint8   BOTON_Read(void);
void    BOTON_SetInterruptMode(uint16 position, uint16 mode);
uint8   BOTON_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the BOTON_SetDriveMode() function.
     *  @{
     */
        #define BOTON_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define BOTON_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define BOTON_DM_RES_UP          PIN_DM_RES_UP
        #define BOTON_DM_RES_DWN         PIN_DM_RES_DWN
        #define BOTON_DM_OD_LO           PIN_DM_OD_LO
        #define BOTON_DM_OD_HI           PIN_DM_OD_HI
        #define BOTON_DM_STRONG          PIN_DM_STRONG
        #define BOTON_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define BOTON_MASK               BOTON__MASK
#define BOTON_SHIFT              BOTON__SHIFT
#define BOTON_WIDTH              1u

/* Interrupt constants */
#if defined(BOTON__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BOTON_SetInterruptMode() function.
     *  @{
     */
        #define BOTON_INTR_NONE      (uint16)(0x0000u)
        #define BOTON_INTR_RISING    (uint16)(0x0001u)
        #define BOTON_INTR_FALLING   (uint16)(0x0002u)
        #define BOTON_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define BOTON_INTR_MASK      (0x01u) 
#endif /* (BOTON__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BOTON_PS                     (* (reg8 *) BOTON__PS)
/* Data Register */
#define BOTON_DR                     (* (reg8 *) BOTON__DR)
/* Port Number */
#define BOTON_PRT_NUM                (* (reg8 *) BOTON__PRT) 
/* Connect to Analog Globals */                                                  
#define BOTON_AG                     (* (reg8 *) BOTON__AG)                       
/* Analog MUX bux enable */
#define BOTON_AMUX                   (* (reg8 *) BOTON__AMUX) 
/* Bidirectional Enable */                                                        
#define BOTON_BIE                    (* (reg8 *) BOTON__BIE)
/* Bit-mask for Aliased Register Access */
#define BOTON_BIT_MASK               (* (reg8 *) BOTON__BIT_MASK)
/* Bypass Enable */
#define BOTON_BYP                    (* (reg8 *) BOTON__BYP)
/* Port wide control signals */                                                   
#define BOTON_CTL                    (* (reg8 *) BOTON__CTL)
/* Drive Modes */
#define BOTON_DM0                    (* (reg8 *) BOTON__DM0) 
#define BOTON_DM1                    (* (reg8 *) BOTON__DM1)
#define BOTON_DM2                    (* (reg8 *) BOTON__DM2) 
/* Input Buffer Disable Override */
#define BOTON_INP_DIS                (* (reg8 *) BOTON__INP_DIS)
/* LCD Common or Segment Drive */
#define BOTON_LCD_COM_SEG            (* (reg8 *) BOTON__LCD_COM_SEG)
/* Enable Segment LCD */
#define BOTON_LCD_EN                 (* (reg8 *) BOTON__LCD_EN)
/* Slew Rate Control */
#define BOTON_SLW                    (* (reg8 *) BOTON__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BOTON_PRTDSI__CAPS_SEL       (* (reg8 *) BOTON__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BOTON_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BOTON__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BOTON_PRTDSI__OE_SEL0        (* (reg8 *) BOTON__PRTDSI__OE_SEL0) 
#define BOTON_PRTDSI__OE_SEL1        (* (reg8 *) BOTON__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BOTON_PRTDSI__OUT_SEL0       (* (reg8 *) BOTON__PRTDSI__OUT_SEL0) 
#define BOTON_PRTDSI__OUT_SEL1       (* (reg8 *) BOTON__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BOTON_PRTDSI__SYNC_OUT       (* (reg8 *) BOTON__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(BOTON__SIO_CFG)
    #define BOTON_SIO_HYST_EN        (* (reg8 *) BOTON__SIO_HYST_EN)
    #define BOTON_SIO_REG_HIFREQ     (* (reg8 *) BOTON__SIO_REG_HIFREQ)
    #define BOTON_SIO_CFG            (* (reg8 *) BOTON__SIO_CFG)
    #define BOTON_SIO_DIFF           (* (reg8 *) BOTON__SIO_DIFF)
#endif /* (BOTON__SIO_CFG) */

/* Interrupt Registers */
#if defined(BOTON__INTSTAT)
    #define BOTON_INTSTAT            (* (reg8 *) BOTON__INTSTAT)
    #define BOTON_SNAP               (* (reg8 *) BOTON__SNAP)
    
	#define BOTON_0_INTTYPE_REG 		(* (reg8 *) BOTON__0__INTTYPE)
#endif /* (BOTON__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BOTON_H */


/* [] END OF FILE */
