/*******************************************************************************
* File Name: ADCMux.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_ADCMux_H)
#define CY_AMUX_ADCMux_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void ADCMux_Start(void) ;
#define ADCMux_Init() ADCMux_Start()
void ADCMux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void ADCMux_Stop(void); */
/* void ADCMux_Select(uint8 channel); */
/* void ADCMux_Connect(uint8 channel); */
/* void ADCMux_Disconnect(uint8 channel); */
/* void ADCMux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define ADCMux_CHANNELS  2u
#define ADCMux_MUXTYPE   2
#define ADCMux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define ADCMux_NULL_CHANNEL 0xFFu
#define ADCMux_MUX_SINGLE   1
#define ADCMux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if ADCMux_MUXTYPE == ADCMux_MUX_SINGLE
# if !ADCMux_ATMOSTONE
#  define ADCMux_Connect(channel) ADCMux_Set(channel)
# endif
# define ADCMux_Disconnect(channel) ADCMux_Unset(channel)
#else
# if !ADCMux_ATMOSTONE
void ADCMux_Connect(uint8 channel) ;
# endif
void ADCMux_Disconnect(uint8 channel) ;
#endif

#if ADCMux_ATMOSTONE
# define ADCMux_Stop() ADCMux_DisconnectAll()
# define ADCMux_Select(channel) ADCMux_FastSelect(channel)
void ADCMux_DisconnectAll(void) ;
#else
# define ADCMux_Stop() ADCMux_Start()
void ADCMux_Select(uint8 channel) ;
# define ADCMux_DisconnectAll() ADCMux_Start()
#endif

#endif /* CY_AMUX_ADCMux_H */


/* [] END OF FILE */
