/*******************************************************************************
* File Name: TX.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_TX_ALIASES_H) /* Pins TX_ALIASES_H */
#define CY_PINS_TX_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define TX_0			(TX__0__PC)
#define TX_0_INTR	((uint16)((uint16)0x0001u << TX__0__SHIFT))

#define TX_INTR_ALL	 ((uint16)(TX_0_INTR))

#endif /* End Pins TX_ALIASES_H */


/* [] END OF FILE */
