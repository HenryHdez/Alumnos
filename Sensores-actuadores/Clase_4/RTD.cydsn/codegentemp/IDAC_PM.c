/*******************************************************************************
* File Name: IDAC.c
* Version 2.0
*
* Description:
*  This file provides the power management source code to API for the
*  IDAC8.
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


#include "IDAC.h"

static IDAC_backupStruct IDAC_backup;


/*******************************************************************************
* Function Name: IDAC_SaveConfig
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
void IDAC_SaveConfig(void) 
{
    if (!((IDAC_CR1 & IDAC_SRC_MASK) == IDAC_SRC_UDB))
    {
        IDAC_backup.data_value = IDAC_Data;
    }
}


/*******************************************************************************
* Function Name: IDAC_RestoreConfig
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
void IDAC_RestoreConfig(void) 
{
    if (!((IDAC_CR1 & IDAC_SRC_MASK) == IDAC_SRC_UDB))
    {
        if((IDAC_Strobe & IDAC_STRB_MASK) == IDAC_STRB_EN)
        {
            IDAC_Strobe &= (uint8)(~IDAC_STRB_MASK);
            IDAC_Data = IDAC_backup.data_value;
            IDAC_Strobe |= IDAC_STRB_EN;
        }
        else
        {
            IDAC_Data = IDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: IDAC_Sleep
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
*  IDAC_backup.enableState: Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void IDAC_Sleep(void) 
{
    if(IDAC_ACT_PWR_EN == (IDAC_PWRMGR & IDAC_ACT_PWR_EN))
    {
        /* IDAC8 is enabled */
        IDAC_backup.enableState = 1u;
    }
    else
    {
        /* IDAC8 is disabled */
        IDAC_backup.enableState = 0u;
    }

    IDAC_Stop();
    IDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: IDAC_Wakeup
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
*  IDAC_backup.enableState: Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void IDAC_Wakeup(void) 
{
    IDAC_RestoreConfig();
    
    if(IDAC_backup.enableState == 1u)
    {
        /* Enable IDAC8's operation */
        IDAC_Enable();
        
        /* Set the data register */
        IDAC_SetValue(IDAC_Data);
    } /* Do nothing if IDAC8 was disabled before */    
}


/* [] END OF FILE */
