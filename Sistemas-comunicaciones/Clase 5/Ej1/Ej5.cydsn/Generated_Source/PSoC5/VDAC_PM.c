/*******************************************************************************
* File Name: VDAC_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "VDAC.h"

static VDAC_backupStruct VDAC_backup;


/*******************************************************************************
* Function Name: VDAC_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void VDAC_SaveConfig(void) 
{
    if (!((VDAC_CR1 & VDAC_SRC_MASK) == VDAC_SRC_UDB))
    {
        VDAC_backup.data_value = VDAC_Data;
    }
}


/*******************************************************************************
* Function Name: VDAC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void VDAC_RestoreConfig(void) 
{
    if (!((VDAC_CR1 & VDAC_SRC_MASK) == VDAC_SRC_UDB))
    {
        if((VDAC_Strobe & VDAC_STRB_MASK) == VDAC_STRB_EN)
        {
            VDAC_Strobe &= (uint8)(~VDAC_STRB_MASK);
            VDAC_Data = VDAC_backup.data_value;
            VDAC_Strobe |= VDAC_STRB_EN;
        }
        else
        {
            VDAC_Data = VDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: VDAC_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  VDAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void VDAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(VDAC_ACT_PWR_EN == (VDAC_PWRMGR & VDAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        VDAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        VDAC_backup.enableState = 0u;
    }
    
    VDAC_Stop();
    VDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: VDAC_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  VDAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void VDAC_Wakeup(void) 
{
    VDAC_RestoreConfig();
    
    if(VDAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        VDAC_Enable();

        /* Restore the data register */
        VDAC_SetValue(VDAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
