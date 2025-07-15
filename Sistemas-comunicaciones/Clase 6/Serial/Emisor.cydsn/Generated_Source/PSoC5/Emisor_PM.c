/*******************************************************************************
* File Name: Emisor_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Emisor.h"


/***************************************
* Local data allocation
***************************************/

static Emisor_BACKUP_STRUCT  Emisor_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: Emisor_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the Emisor_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Emisor_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Emisor_SaveConfig(void)
{
    #if(Emisor_CONTROL_REG_REMOVED == 0u)
        Emisor_backup.cr = Emisor_CONTROL_REG;
    #endif /* End Emisor_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: Emisor_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Emisor_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling Emisor_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void Emisor_RestoreConfig(void)
{
    #if(Emisor_CONTROL_REG_REMOVED == 0u)
        Emisor_CONTROL_REG = Emisor_backup.cr;
    #endif /* End Emisor_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: Emisor_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The Emisor_Sleep() API saves the current component state. Then it
*  calls the Emisor_Stop() function and calls 
*  Emisor_SaveConfig() to save the hardware configuration.
*  Call the Emisor_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Emisor_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Emisor_Sleep(void)
{
    #if(Emisor_RX_ENABLED || Emisor_HD_ENABLED)
        if((Emisor_RXSTATUS_ACTL_REG  & Emisor_INT_ENABLE) != 0u)
        {
            Emisor_backup.enableState = 1u;
        }
        else
        {
            Emisor_backup.enableState = 0u;
        }
    #else
        if((Emisor_TXSTATUS_ACTL_REG  & Emisor_INT_ENABLE) !=0u)
        {
            Emisor_backup.enableState = 1u;
        }
        else
        {
            Emisor_backup.enableState = 0u;
        }
    #endif /* End Emisor_RX_ENABLED || Emisor_HD_ENABLED*/

    Emisor_Stop();
    Emisor_SaveConfig();
}


/*******************************************************************************
* Function Name: Emisor_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  Emisor_Sleep() was called. The Emisor_Wakeup() function
*  calls the Emisor_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  Emisor_Sleep() function was called, the Emisor_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Emisor_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Emisor_Wakeup(void)
{
    Emisor_RestoreConfig();
    #if( (Emisor_RX_ENABLED) || (Emisor_HD_ENABLED) )
        Emisor_ClearRxBuffer();
    #endif /* End (Emisor_RX_ENABLED) || (Emisor_HD_ENABLED) */
    #if(Emisor_TX_ENABLED || Emisor_HD_ENABLED)
        Emisor_ClearTxBuffer();
    #endif /* End Emisor_TX_ENABLED || Emisor_HD_ENABLED */

    if(Emisor_backup.enableState != 0u)
    {
        Emisor_Enable();
    }
}


/* [] END OF FILE */
