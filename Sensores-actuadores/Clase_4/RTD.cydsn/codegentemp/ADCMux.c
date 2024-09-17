/*******************************************************************************
* File Name: ADCMux.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "ADCMux.h"

static uint8 ADCMux_lastChannel = ADCMux_NULL_CHANNEL;


/*******************************************************************************
* Function Name: ADCMux_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ADCMux_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < ADCMux_CHANNELS ; chan++)
    {
#if (ADCMux_MUXTYPE == ADCMux_MUX_SINGLE)
        ADCMux_Unset(chan);
#else
        ADCMux_CYAMUXSIDE_A_Unset(chan);
        ADCMux_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    ADCMux_lastChannel = ADCMux_NULL_CHANNEL;
}


#if (!ADCMux_ATMOSTONE)
/*******************************************************************************
* Function Name: ADCMux_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void ADCMux_Select(uint8 channel) 
{
    ADCMux_DisconnectAll();        /* Disconnect all previous connections */
    ADCMux_Connect(channel);       /* Make the given selection */
    ADCMux_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: ADCMux_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void ADCMux_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( ADCMux_lastChannel != ADCMux_NULL_CHANNEL)
    {
        ADCMux_Disconnect(ADCMux_lastChannel);
    }

    /* Make the new channel connection */
#if (ADCMux_MUXTYPE == ADCMux_MUX_SINGLE)
    ADCMux_Set(channel);
#else
    ADCMux_CYAMUXSIDE_A_Set(channel);
    ADCMux_CYAMUXSIDE_B_Set(channel);
#endif


    ADCMux_lastChannel = channel;   /* Update last channel */
}


#if (ADCMux_MUXTYPE == ADCMux_MUX_DIFF)
#if (!ADCMux_ATMOSTONE)
/*******************************************************************************
* Function Name: ADCMux_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void ADCMux_Connect(uint8 channel) 
{
    ADCMux_CYAMUXSIDE_A_Set(channel);
    ADCMux_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: ADCMux_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void ADCMux_Disconnect(uint8 channel) 
{
    ADCMux_CYAMUXSIDE_A_Unset(channel);
    ADCMux_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (ADCMux_ATMOSTONE)
/*******************************************************************************
* Function Name: ADCMux_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void ADCMux_DisconnectAll(void) 
{
    if(ADCMux_lastChannel != ADCMux_NULL_CHANNEL) 
    {
        ADCMux_Disconnect(ADCMux_lastChannel);
        ADCMux_lastChannel = ADCMux_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
