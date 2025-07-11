/*******************************************************************************
* File Name: ADC_PM.c
* Version 3.10
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

#include "ADC.h"


/***************************************
* Local data allocation
***************************************/

static ADC_BACKUP_STRUCT  ADC_backup =
{
    ADC_DISABLED
};


/*******************************************************************************
* Function Name: ADC_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The ADC_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ADC_Sleep(void)
{
    if((ADC_PWRMGR_SAR_REG  & ADC_ACT_PWR_SAR_EN) != 0u)
    {
        if((ADC_SAR_CSR0_REG & ADC_SAR_SOF_START_CONV) != 0u)
        {
            ADC_backup.enableState = ADC_ENABLED | ADC_STARTED;
        }
        else
        {
            ADC_backup.enableState = ADC_ENABLED;
        }
        ADC_Stop();
    }
    else
    {
        ADC_backup.enableState = ADC_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ADC_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  ADC_Sleep() was called. If the component was enabled before the
*  ADC_Sleep() function was called, the
*  ADC_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ADC_Wakeup(void)
{
    if(ADC_backup.enableState != ADC_DISABLED)
    {
        ADC_Enable();
        #if(ADC_DEFAULT_CONV_MODE != ADC__HARDWARE_TRIGGER)
            if((ADC_backup.enableState & ADC_STARTED) != 0u)
            {
                ADC_StartConvert();
            }
        #endif /* End ADC_DEFAULT_CONV_MODE != ADC__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
