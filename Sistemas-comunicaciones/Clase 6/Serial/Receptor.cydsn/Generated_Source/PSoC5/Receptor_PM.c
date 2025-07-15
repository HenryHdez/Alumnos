/*******************************************************************************
* File Name: Receptor_PM.c
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

#include "Receptor.h"


/***************************************
* Local data allocation
***************************************/

static Receptor_BACKUP_STRUCT  Receptor_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: Receptor_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the Receptor_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Receptor_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Receptor_SaveConfig(void)
{
    #if(Receptor_CONTROL_REG_REMOVED == 0u)
        Receptor_backup.cr = Receptor_CONTROL_REG;
    #endif /* End Receptor_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: Receptor_RestoreConfig
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
*  Receptor_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling Receptor_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void Receptor_RestoreConfig(void)
{
    #if(Receptor_CONTROL_REG_REMOVED == 0u)
        Receptor_CONTROL_REG = Receptor_backup.cr;
    #endif /* End Receptor_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: Receptor_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The Receptor_Sleep() API saves the current component state. Then it
*  calls the Receptor_Stop() function and calls 
*  Receptor_SaveConfig() to save the hardware configuration.
*  Call the Receptor_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Receptor_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Receptor_Sleep(void)
{
    #if(Receptor_RX_ENABLED || Receptor_HD_ENABLED)
        if((Receptor_RXSTATUS_ACTL_REG  & Receptor_INT_ENABLE) != 0u)
        {
            Receptor_backup.enableState = 1u;
        }
        else
        {
            Receptor_backup.enableState = 0u;
        }
    #else
        if((Receptor_TXSTATUS_ACTL_REG  & Receptor_INT_ENABLE) !=0u)
        {
            Receptor_backup.enableState = 1u;
        }
        else
        {
            Receptor_backup.enableState = 0u;
        }
    #endif /* End Receptor_RX_ENABLED || Receptor_HD_ENABLED*/

    Receptor_Stop();
    Receptor_SaveConfig();
}


/*******************************************************************************
* Function Name: Receptor_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  Receptor_Sleep() was called. The Receptor_Wakeup() function
*  calls the Receptor_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  Receptor_Sleep() function was called, the Receptor_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Receptor_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Receptor_Wakeup(void)
{
    Receptor_RestoreConfig();
    #if( (Receptor_RX_ENABLED) || (Receptor_HD_ENABLED) )
        Receptor_ClearRxBuffer();
    #endif /* End (Receptor_RX_ENABLED) || (Receptor_HD_ENABLED) */
    #if(Receptor_TX_ENABLED || Receptor_HD_ENABLED)
        Receptor_ClearTxBuffer();
    #endif /* End Receptor_TX_ENABLED || Receptor_HD_ENABLED */

    if(Receptor_backup.enableState != 0u)
    {
        Receptor_Enable();
    }
}


/* [] END OF FILE */
