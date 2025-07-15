/*******************************************************************************
* File Name: Interrupcion.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Interrupcion_H)
#define CY_ISR_Interrupcion_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Interrupcion_Start(void);
void Interrupcion_StartEx(cyisraddress address);
void Interrupcion_Stop(void);

CY_ISR_PROTO(Interrupcion_Interrupt);

void Interrupcion_SetVector(cyisraddress address);
cyisraddress Interrupcion_GetVector(void);

void Interrupcion_SetPriority(uint8 priority);
uint8 Interrupcion_GetPriority(void);

void Interrupcion_Enable(void);
uint8 Interrupcion_GetState(void);
void Interrupcion_Disable(void);

void Interrupcion_SetPending(void);
void Interrupcion_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Interrupcion ISR. */
#define Interrupcion_INTC_VECTOR            ((reg32 *) Interrupcion__INTC_VECT)

/* Address of the Interrupcion ISR priority. */
#define Interrupcion_INTC_PRIOR             ((reg8 *) Interrupcion__INTC_PRIOR_REG)

/* Priority of the Interrupcion interrupt. */
#define Interrupcion_INTC_PRIOR_NUMBER      Interrupcion__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Interrupcion interrupt. */
#define Interrupcion_INTC_SET_EN            ((reg32 *) Interrupcion__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Interrupcion interrupt. */
#define Interrupcion_INTC_CLR_EN            ((reg32 *) Interrupcion__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Interrupcion interrupt state to pending. */
#define Interrupcion_INTC_SET_PD            ((reg32 *) Interrupcion__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Interrupcion interrupt. */
#define Interrupcion_INTC_CLR_PD            ((reg32 *) Interrupcion__INTC_CLR_PD_REG)


#endif /* CY_ISR_Interrupcion_H */


/* [] END OF FILE */
