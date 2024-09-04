/*******************************************************************************
* File Name: V_Nodo.h  
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

#if !defined(CY_PINS_V_Nodo_H) /* Pins V_Nodo_H */
#define CY_PINS_V_Nodo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "V_Nodo_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 V_Nodo__PORT == 15 && ((V_Nodo__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    V_Nodo_Write(uint8 value);
void    V_Nodo_SetDriveMode(uint8 mode);
uint8   V_Nodo_ReadDataReg(void);
uint8   V_Nodo_Read(void);
void    V_Nodo_SetInterruptMode(uint16 position, uint16 mode);
uint8   V_Nodo_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the V_Nodo_SetDriveMode() function.
     *  @{
     */
        #define V_Nodo_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define V_Nodo_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define V_Nodo_DM_RES_UP          PIN_DM_RES_UP
        #define V_Nodo_DM_RES_DWN         PIN_DM_RES_DWN
        #define V_Nodo_DM_OD_LO           PIN_DM_OD_LO
        #define V_Nodo_DM_OD_HI           PIN_DM_OD_HI
        #define V_Nodo_DM_STRONG          PIN_DM_STRONG
        #define V_Nodo_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define V_Nodo_MASK               V_Nodo__MASK
#define V_Nodo_SHIFT              V_Nodo__SHIFT
#define V_Nodo_WIDTH              1u

/* Interrupt constants */
#if defined(V_Nodo__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in V_Nodo_SetInterruptMode() function.
     *  @{
     */
        #define V_Nodo_INTR_NONE      (uint16)(0x0000u)
        #define V_Nodo_INTR_RISING    (uint16)(0x0001u)
        #define V_Nodo_INTR_FALLING   (uint16)(0x0002u)
        #define V_Nodo_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define V_Nodo_INTR_MASK      (0x01u) 
#endif /* (V_Nodo__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define V_Nodo_PS                     (* (reg8 *) V_Nodo__PS)
/* Data Register */
#define V_Nodo_DR                     (* (reg8 *) V_Nodo__DR)
/* Port Number */
#define V_Nodo_PRT_NUM                (* (reg8 *) V_Nodo__PRT) 
/* Connect to Analog Globals */                                                  
#define V_Nodo_AG                     (* (reg8 *) V_Nodo__AG)                       
/* Analog MUX bux enable */
#define V_Nodo_AMUX                   (* (reg8 *) V_Nodo__AMUX) 
/* Bidirectional Enable */                                                        
#define V_Nodo_BIE                    (* (reg8 *) V_Nodo__BIE)
/* Bit-mask for Aliased Register Access */
#define V_Nodo_BIT_MASK               (* (reg8 *) V_Nodo__BIT_MASK)
/* Bypass Enable */
#define V_Nodo_BYP                    (* (reg8 *) V_Nodo__BYP)
/* Port wide control signals */                                                   
#define V_Nodo_CTL                    (* (reg8 *) V_Nodo__CTL)
/* Drive Modes */
#define V_Nodo_DM0                    (* (reg8 *) V_Nodo__DM0) 
#define V_Nodo_DM1                    (* (reg8 *) V_Nodo__DM1)
#define V_Nodo_DM2                    (* (reg8 *) V_Nodo__DM2) 
/* Input Buffer Disable Override */
#define V_Nodo_INP_DIS                (* (reg8 *) V_Nodo__INP_DIS)
/* LCD Common or Segment Drive */
#define V_Nodo_LCD_COM_SEG            (* (reg8 *) V_Nodo__LCD_COM_SEG)
/* Enable Segment LCD */
#define V_Nodo_LCD_EN                 (* (reg8 *) V_Nodo__LCD_EN)
/* Slew Rate Control */
#define V_Nodo_SLW                    (* (reg8 *) V_Nodo__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define V_Nodo_PRTDSI__CAPS_SEL       (* (reg8 *) V_Nodo__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define V_Nodo_PRTDSI__DBL_SYNC_IN    (* (reg8 *) V_Nodo__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define V_Nodo_PRTDSI__OE_SEL0        (* (reg8 *) V_Nodo__PRTDSI__OE_SEL0) 
#define V_Nodo_PRTDSI__OE_SEL1        (* (reg8 *) V_Nodo__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define V_Nodo_PRTDSI__OUT_SEL0       (* (reg8 *) V_Nodo__PRTDSI__OUT_SEL0) 
#define V_Nodo_PRTDSI__OUT_SEL1       (* (reg8 *) V_Nodo__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define V_Nodo_PRTDSI__SYNC_OUT       (* (reg8 *) V_Nodo__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(V_Nodo__SIO_CFG)
    #define V_Nodo_SIO_HYST_EN        (* (reg8 *) V_Nodo__SIO_HYST_EN)
    #define V_Nodo_SIO_REG_HIFREQ     (* (reg8 *) V_Nodo__SIO_REG_HIFREQ)
    #define V_Nodo_SIO_CFG            (* (reg8 *) V_Nodo__SIO_CFG)
    #define V_Nodo_SIO_DIFF           (* (reg8 *) V_Nodo__SIO_DIFF)
#endif /* (V_Nodo__SIO_CFG) */

/* Interrupt Registers */
#if defined(V_Nodo__INTSTAT)
    #define V_Nodo_INTSTAT            (* (reg8 *) V_Nodo__INTSTAT)
    #define V_Nodo_SNAP               (* (reg8 *) V_Nodo__SNAP)
    
	#define V_Nodo_0_INTTYPE_REG 		(* (reg8 *) V_Nodo__0__INTTYPE)
#endif /* (V_Nodo__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_V_Nodo_H */


/* [] END OF FILE */
