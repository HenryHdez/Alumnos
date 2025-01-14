/*******************************************************************************
* File Name: PUERTO_CAN_1.c
* Version 3.0
*
* Description:
*  The CAN Component provides functionality of Control Area Network.
*  The two types of mailbox configuration available are "Full" and "Basic".
*
* Note:
*  The CAN configuration is put as constant to ROM and can be changed
*  only directly by the registers written by the user.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PUERTO_CAN_1.h"

uint8 PUERTO_CAN_1_initVar = 0u;


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_RxTxBuffersConfig
********************************************************************************
*
* Summary:
*  Inits/Restores default CAN Rx and Tx Buffers control registers configuration
*  provided by the customizer.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the configuration has been accepted or rejected.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
* Side Effects:
*  All the Rx and Tx Buffers control registers will be reset to their initial
*  values.
*
*******************************************************************************/
uint8 PUERTO_CAN_1_RxTxBuffersConfig(void) 
{
    /* Initial values of CAN RX and TX registers */
    static const PUERTO_CAN_1_RX_CFG CYCODE PUERTO_CAN_1_RXConfigStruct[] =
    {
        { 0u, 0x28u, 0x1FFFF9u, 0x200000u },
        { 1u, 0x0u, 0x0u, 0x0u },
        { 2u, 0x0u, 0x0u, 0x0u },
        { 3u, 0x0u, 0x0u, 0x0u },
        { 4u, 0x0u, 0x0u, 0x0u },
        { 5u, 0x0u, 0x0u, 0x0u },
        { 6u, 0x0u, 0x0u, 0x0u },
        { 7u, 0x0u, 0x0u, 0x0u },
        { 8u, 0x0u, 0x0u, 0x0u },
        { 9u, 0x0u, 0x0u, 0x0u },
        { 10u, 0x0u, 0x0u, 0x0u },
        { 11u, 0x0u, 0x0u, 0x0u },
        { 12u, 0x0u, 0x0u, 0x0u },
        { 13u, 0x0u, 0x0u, 0x0u },
        { 14u, 0x0u, 0x0u, 0x0u },
        { 15u, 0x0u, 0x0u, 0x0u }
    };

    static const PUERTO_CAN_1_TX_CFG CYCODE PUERTO_CAN_1_TXConfigStruct[] =
    {
        { 0u, 0x80000u, 0x400000u },
        { 1u, 0x880008u, 0x0u },
        { 2u, 0x880008u, 0x0u },
        { 3u, 0x880008u, 0x0u },
        { 4u, 0x880008u, 0x0u },
        { 5u, 0x880008u, 0x0u },
        { 6u, 0x880008u, 0x0u },
        { 7u, 0x880008u, 0x0u }
    };

    uint8 result = CYRET_SUCCESS;
    uint8 i;

    /* Initialize TX mailboxes */
    for (i = 0u; i < PUERTO_CAN_1_NUMBER_OF_TX_MAILBOXES; i++)
    {
        if (PUERTO_CAN_1_TxBufConfig((const PUERTO_CAN_1_TX_CFG *)
            (&PUERTO_CAN_1_TXConfigStruct[i])) != CYRET_SUCCESS)
        {
            result = PUERTO_CAN_1_FAIL;
            break;
        }
    }

    if (result == CYRET_SUCCESS)
    {
        /* Initialize RX mailboxes */
        for (i = 0u; i < PUERTO_CAN_1_NUMBER_OF_RX_MAILBOXES; i++)
        {
            if (PUERTO_CAN_1_RxBufConfig((const PUERTO_CAN_1_RX_CFG *)
                (&PUERTO_CAN_1_RXConfigStruct[i])) != CYRET_SUCCESS)
            {
                result = PUERTO_CAN_1_FAIL;
                break;
            }
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default CAN configuration provided by the customizer.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the configuration has been accepted or rejected.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
* Side Effects:
*  All the registers will be reset to their initial values. This will
*  re-initialize the component with the following exceptions - it will not clear
*  data from the mailboxes.
*  Enable power to the CAN Core.
*
*******************************************************************************/
uint8 PUERTO_CAN_1_Init(void) 
{
    uint32 timeout = PUERTO_CAN_1_MODE_STATE_STOP_TIMEOUT;
    uint8 result = PUERTO_CAN_1_FAIL;
    uint8 localResult = PUERTO_CAN_1_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Enable CAN block in Active mode */
        PUERTO_CAN_1_PM_ACT_CFG_REG |= PUERTO_CAN_1_ACT_PWR_EN;
        /* Enable CAN block in Alternate Active (Standby) mode */
        PUERTO_CAN_1_PM_STBY_CFG_REG |= PUERTO_CAN_1_STBY_PWR_EN;
        CyExitCriticalSection(enableInterrupts);

        /* Sets CAN controller to stop mode */
        PUERTO_CAN_1_CMD_REG.byte[0u] &= (uint8) (~PUERTO_CAN_1_MODE_MASK);

        /* Timeout for CAN state machine to switch mode to Stop */
        while ((timeout != 0u) && ((PUERTO_CAN_1_CMD_REG.byte[0u] & PUERTO_CAN_1_MODE_MASK) != 0u))
        {
            timeout--;
        }
    #else  /* CY_PSOC4 */
        /* Enable CAN IP Block */
        PUERTO_CAN_1_CNTL_REG = PUERTO_CAN_1_IP_ENABLE;

        /* Sets CAN controller to stop mode */
        PUERTO_CAN_1_CMD_REG &= (uint32) (~((uint32) PUERTO_CAN_1_MODE_MASK));

        /* Timeout for CAN state machine to switch mode to Stop */
        while ((timeout != 0u) && ((PUERTO_CAN_1_CMD_REG & PUERTO_CAN_1_MODE_MASK) != 0u))
        {
            timeout--;
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */
        if (timeout != 0u)
        {
            /* Disable Interrupt. */
        CyIntDisable(PUERTO_CAN_1_ISR_NUMBER);

        /* Set the ISR to point to the PUERTO_CAN_1_ISR Interrupt. */
        (void) CyIntSetVector(PUERTO_CAN_1_ISR_NUMBER, & PUERTO_CAN_1_ISR);

        /* Set the priority. */
        CyIntSetPriority(PUERTO_CAN_1_ISR_NUMBER, PUERTO_CAN_1_ISR_PRIORITY);

            if (PUERTO_CAN_1_SetPreScaler(PUERTO_CAN_1_BITRATE) == CYRET_SUCCESS)
            {
                if (PUERTO_CAN_1_SetArbiter(PUERTO_CAN_1_ARBITER) == CYRET_SUCCESS)
                {
                    #if (!(CY_PSOC3 || CY_PSOC5))
                        if (PUERTO_CAN_1_SetSwapDataEndianness(PUERTO_CAN_1_SWAP_DATA_END) == CYRET_SUCCESS)
                    #endif /* (!(CY_PSOC3 || CY_PSOC5)) */
                        {
                            if (PUERTO_CAN_1_SetTsegSample(PUERTO_CAN_1_CFG_REG_TSEG1,
                                PUERTO_CAN_1_CFG_REG_TSEG2, PUERTO_CAN_1_CFG_REG_SJW,
                                PUERTO_CAN_1_SAMPLING_MODE) == CYRET_SUCCESS)
                            {
                                if (PUERTO_CAN_1_SetRestartType(PUERTO_CAN_1_RESET_TYPE) == CYRET_SUCCESS)
                                {
                                    if (PUERTO_CAN_1_SetEdgeMode(PUERTO_CAN_1_SYNC_EDGE) == CYRET_SUCCESS)
                                    {
                                        localResult = CYRET_SUCCESS;
                                    }
                                }
                            }
                        }
                }
            }

            if (localResult == CYRET_SUCCESS)
            {
                if (PUERTO_CAN_1_RxTxBuffersConfig() == CYRET_SUCCESS)
                {
                    /* Write IRQ Mask */
                    if (PUERTO_CAN_1_SetIrqMask(PUERTO_CAN_1_INIT_INTERRUPT_MASK) ==
                        CYRET_SUCCESS)
                    {
                        /* Set CAN Operation Mode to Active mode always */
                        #if (CY_PSOC3 || CY_PSOC5)
                            PUERTO_CAN_1_CMD_REG.byte[0u] = PUERTO_CAN_1_INITIAL_MODE;
                            if ((PUERTO_CAN_1_CMD_REG.byte[0u] & PUERTO_CAN_1_MODE_MASK) == 0u)
                        #else  /* CY_PSOC4 */
                            PUERTO_CAN_1_CMD_REG &= (uint32) (~((uint32) PUERTO_CAN_1_OPMODE_FIELD_MASK));
                            if ((PUERTO_CAN_1_CMD_REG & PUERTO_CAN_1_OPMODE_FIELD_MASK) == 0u)
                        #endif /* CY_PSOC3 || CY_PSOC5 */
                            {
                                result = CYRET_SUCCESS;
                            }
                    }
                }
            }
        }

    return (result);
}


/*******************************************************************************
* Function Name: PUERTO_CAN_1_Enable
********************************************************************************
*
* Summary:
*  This function enables the CAN Component and ISR of CAN Component.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
*******************************************************************************/
uint8 PUERTO_CAN_1_Enable(void) 
{
    uint32 timeout = PUERTO_CAN_1_MODE_STATE_RUN_TIMEOUT;
    uint8 result = PUERTO_CAN_1_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();

        /* Enable CAN block in Active mode */
        PUERTO_CAN_1_PM_ACT_CFG_REG |= PUERTO_CAN_1_ACT_PWR_EN;

        /* Enable CAN block in Alternate Active (Standby) mode */
        PUERTO_CAN_1_PM_STBY_CFG_REG |= PUERTO_CAN_1_STBY_PWR_EN;

        CyExitCriticalSection(enableInterrupts);
    #endif /* CY_PSOC3 || CY_PSOC5 */

    /* Clear interrupts status */
    CY_SET_REG32(PUERTO_CAN_1_INT_SR_PTR, PUERTO_CAN_1_INIT_INTERRUPT_MASK);
    (void) PUERTO_CAN_1_GlobalIntEnable();

    /* Enable isr */
    CyIntEnable(PUERTO_CAN_1_ISR_NUMBER);

    /* Sets CAN controller to run mode */
    CY_SET_REG32(PUERTO_CAN_1_CMD_PTR, CY_GET_REG32(PUERTO_CAN_1_CMD_PTR) | PUERTO_CAN_1_MODE_MASK);

    /* Timeout for CAN state machine to switch mode to Run */
    while ((timeout != 0u) && ((CY_GET_REG32(PUERTO_CAN_1_CMD_PTR) & PUERTO_CAN_1_MODE_MASK) == 0u))
    {
        timeout--;
    }

    if (timeout != 0u)
    {
        result = CYRET_SUCCESS;
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_Start
********************************************************************************
*
* Summary:
*  This function sets CAN Component into the Run mode. Starts Rate Counter if
*  polling mailboxes are available.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
* Global variables:
*  PUERTO_CAN_1_initVar - used to check the initial configuration, modified
*  on the first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint8 PUERTO_CAN_1_Start(void) 
{
    uint8 result = CYRET_SUCCESS;

    if (PUERTO_CAN_1_initVar == 0u)
    {
        result = PUERTO_CAN_1_Init();
    }

    if (result == CYRET_SUCCESS)
    {
        PUERTO_CAN_1_initVar = 1u;
        result = PUERTO_CAN_1_Enable();
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_Stop
********************************************************************************
*
* Summary:
*  This function sets CAN Component into the Stop mode.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
* Side Effects:
*  Disable power to CAN Core in case of PSoC 3/5.
*  Pending message in the Tx buffer of PSoC 3/5 will not be aborted on calling
*  the PUERTO_CAN_1_Stop() API. User has to abort all pending messages
*  before calling the PUERTO_CAN_1_Stop() function to make sure that the
*  block stops all the message transmission immediately.
*
*******************************************************************************/
uint8 PUERTO_CAN_1_Stop(void) 
{
    uint32 timeout = PUERTO_CAN_1_MODE_STATE_STOP_TIMEOUT;
    uint8 result = PUERTO_CAN_1_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        uint8 enableInterrupts;
    #endif /* CY_PSOC3 || CY_PSOC5 */

    /* Set CAN controller to stop mode */
    CY_SET_REG32(PUERTO_CAN_1_CMD_PTR, (CY_GET_REG32(PUERTO_CAN_1_CMD_PTR) &
                                            ((uint32) (~((uint32)PUERTO_CAN_1_MODE_MASK)))));

    /* Timeout for CAN state machine to switch mode to Stop */
    while ((timeout != 0u) && ((CY_GET_REG32(PUERTO_CAN_1_CMD_PTR) & PUERTO_CAN_1_MODE_MASK) != 0u))
    {
        timeout--;
    }

    /* Verify that bit is cleared */
    if (timeout != 0u)
    {
        result = CYRET_SUCCESS;

        /* Disable isr */
    CyIntDisable(PUERTO_CAN_1_ISR_NUMBER);

        #if (CY_PSOC3 || CY_PSOC5)
            enableInterrupts = CyEnterCriticalSection();

            /* Disable CAN block in Active mode */
            PUERTO_CAN_1_PM_ACT_CFG_REG &= (uint8) (~PUERTO_CAN_1_ACT_PWR_EN);

            /* Disable CAN block in Alternate Active (Standby) mode template */
            PUERTO_CAN_1_PM_STBY_CFG_REG &= (uint8) (~PUERTO_CAN_1_STBY_PWR_EN);

            CyExitCriticalSection(enableInterrupts);
        #endif /* CY_PSOC3 || CY_PSOC5 */
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_GlobalIntEnable
********************************************************************************
*
* Summary:
*  This function enables Global Interrupts from CAN Core.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
*******************************************************************************/
uint8 PUERTO_CAN_1_GlobalIntEnable(void) 
{
    uint8 result = PUERTO_CAN_1_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        PUERTO_CAN_1_INT_EN_REG.byte[0u] |= PUERTO_CAN_1_GLOBAL_INT_MASK;

        /* Verify that bit is set */
        if ((PUERTO_CAN_1_INT_EN_REG.byte[0u] & PUERTO_CAN_1_GLOBAL_INT_MASK) != 0u)
        {
            result = CYRET_SUCCESS;
        }
    #else  /* CY_PSOC4 */
        PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_GLOBAL_INT_MASK;
        /* Verify that bit is set */
        if ((PUERTO_CAN_1_INT_EN_REG & PUERTO_CAN_1_GLOBAL_INT_MASK) != 0u)
        {
            result = CYRET_SUCCESS;
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_GlobalIntDisable
********************************************************************************
*
* Summary:
*  This function disables Global Interrupts from CAN Core.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
*******************************************************************************/
uint8 PUERTO_CAN_1_GlobalIntDisable(void) 
{
    uint8 result = PUERTO_CAN_1_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        PUERTO_CAN_1_INT_EN_REG.byte[0u] &= (uint8) (~PUERTO_CAN_1_GLOBAL_INT_MASK);

        /* Verify that bit is cleared */
        if ((PUERTO_CAN_1_INT_EN_REG.byte[0u] & PUERTO_CAN_1_GLOBAL_INT_MASK) == 0u)
        {
            result = CYRET_SUCCESS;
        }
    #else  /* CY_PSOC4 */
        PUERTO_CAN_1_INT_EN_REG &= (uint32) (~((uint32) PUERTO_CAN_1_GLOBAL_INT_MASK));

        /* Verify that bit is cleared */
        if ((PUERTO_CAN_1_INT_EN_REG & PUERTO_CAN_1_GLOBAL_INT_MASK) == 0u)
        {
            result = CYRET_SUCCESS;
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_SetPreScaler
********************************************************************************
*
* Summary:
*  This function sets PreScaler for generating the time quantum which defines
*  the time quanta. The values between 0x0 and 0x7FFF are valid.
*
* Parameters:
*  bitrate: PreScaler value.
*   Value           Description
*    0               One time quantum equals 1 clock cycle
*    1               One time quantum equals 2 clock cycles
*    ...             ...
*    32767           One time quantum equals 32768 clock cycles
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*    PUERTO_CAN_1_OUT_OF_RANGE      The function parameter is out of range
*
*******************************************************************************/
uint8 PUERTO_CAN_1_SetPreScaler(uint16 bitrate) 
{
    uint8 result = PUERTO_CAN_1_OUT_OF_RANGE;

    if (bitrate <= PUERTO_CAN_1_BITRATE_MASK)
    {
        result = PUERTO_CAN_1_FAIL;

        #if (CY_PSOC3 || CY_PSOC5)
            /* Set prescaler */
            CY_SET_REG16((reg16 *) (&PUERTO_CAN_1_CFG_REG.byte[2u]), bitrate);

            /* Verify that prescaler is set */
            if (CY_GET_REG16((reg16 *) (&PUERTO_CAN_1_CFG_REG.byte[2u])) == bitrate)
            {
                result = CYRET_SUCCESS;
            }
        #else  /* CY_PSOC4 */
            /* Set prescaler */
            PUERTO_CAN_1_CFG_REG = (PUERTO_CAN_1_CFG_REG & (uint32) (~PUERTO_CAN_1_BITRATE_MASK_SHIFTED)) |
            (uint32) ((uint32) bitrate << PUERTO_CAN_1_BITRATE_SHIFT);

            /* Verify that prescaler is set */
            if ((PUERTO_CAN_1_CFG_REG & PUERTO_CAN_1_BITRATE_MASK_SHIFTED) ==
               ((uint32) ((uint32) bitrate << PUERTO_CAN_1_BITRATE_SHIFT)))
            {
                result = CYRET_SUCCESS;
            }
        #endif /* CY_PSOC3 || CY_PSOC5 */
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_SetArbiter
********************************************************************************
*
* Summary:
*  This function sets the arbitration type for transmit mailboxes. The types of
*  the arbiters are Round Robin and Fixed Priority. Values 0 and 1 are valid.
*
* Parameters:
*  arbiter: The arbitration type for transmit mailboxes.
*   Value                              Description
*    PUERTO_CAN_1_ROUND_ROBIN       The Round Robin arbitration
*    PUERTO_CAN_1_FIXED_PRIORITY    The Fixed Priority arbitration.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
*******************************************************************************/
uint8 PUERTO_CAN_1_SetArbiter(uint8 arbiter) 
{
    uint8 result = PUERTO_CAN_1_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        if (arbiter == PUERTO_CAN_1_ROUND_ROBIN)
        {
            PUERTO_CAN_1_CFG_REG.byte[1u] &= (uint8) (~PUERTO_CAN_1_ARBITRATION_MASK);

            /* Verify that bit is cleared */
            if ((PUERTO_CAN_1_CFG_REG.byte[1u] & PUERTO_CAN_1_ARBITRATION_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else    /* Fixed Priority */
        {
            PUERTO_CAN_1_CFG_REG.byte[1u] |= PUERTO_CAN_1_ARBITRATION_MASK;

            /* Verify that bit is set */
            if ((PUERTO_CAN_1_CFG_REG.byte[1u] & PUERTO_CAN_1_ARBITRATION_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #else  /* CY_PSOC4 */
        if (arbiter == PUERTO_CAN_1_ROUND_ROBIN)
        {
            PUERTO_CAN_1_CFG_REG &= (uint32) (~PUERTO_CAN_1_ARBITRATION_MASK);

            /* Verify that bit is cleared */
            if ((PUERTO_CAN_1_CFG_REG & PUERTO_CAN_1_ARBITRATION_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else    /* Fixed priority */
        {
            PUERTO_CAN_1_CFG_REG |= PUERTO_CAN_1_ARBITRATION_MASK;

            /* Verify that bit is set */
            if ((PUERTO_CAN_1_CFG_REG & PUERTO_CAN_1_ARBITRATION_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME: PUERTO_CAN_1_SetTsegSample
********************************************************************************
*
* Summary:
*  This function configures: Time segment 1, Time segment 2, Sampling Mode
*  and Synchronization Jump Width.
*
* Parameters:
*  cfgTseg1: The length of time segment 1, values between 0x2 and 0xF are valid;
*  cfgTseg2: The length of time segment 2, values between 0x1 and 0x7 are valid;
*  sjw: Synchronization Jump Width, value between 0x0 and 0x3 are valid;
*  sm: Sampling Mode.
*   Define                               Description
*   PUERTO_CAN_1_ONE_SAMPLE_POINT     One sampling point is used
*   PUERTO_CAN_1_THREE_SAMPLE_POINTS  Three sampling points are used
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*    PUERTO_CAN_1_OUT_OF_RANGE      The function parameter is out of range
*
*******************************************************************************/
uint8 PUERTO_CAN_1_SetTsegSample(uint8 cfgTseg1, uint8 cfgTseg2, uint8 sjw, uint8 sm)
                                     
{
    uint8 result = PUERTO_CAN_1_OUT_OF_RANGE;
    uint8 cfgTemp;

    if ((cfgTseg1 >= PUERTO_CAN_1_CFG_REG_TSEG1_LOWER_LIMIT) && (cfgTseg1 <=
         PUERTO_CAN_1_CFG_REG_TSEG1_UPPER_LIMIT))
    {
        if (((cfgTseg2 >= PUERTO_CAN_1_CFG_REG_TSEG2_LOWER_LIMIT) &&
             (cfgTseg2 <= PUERTO_CAN_1_CFG_REG_TSEG2_UPPER_LIMIT)) || ((sm == PUERTO_CAN_1_ONE_SAMPLE_POINT) &&
             (cfgTseg2 == PUERTO_CAN_1_CFG_REG_TSEG2_EXCEPTION)))
        {
            if ((sjw <= PUERTO_CAN_1_CFG_REG_SJW_LOWER_LIMIT) && (sjw <= cfgTseg1) && (sjw <= cfgTseg2))
            {
                result = PUERTO_CAN_1_FAIL;

                #if (CY_PSOC3 || CY_PSOC5)
                    cfgTemp = PUERTO_CAN_1_CFG_REG.byte[1];
                    cfgTemp &= (uint8) (~PUERTO_CAN_1_CFG_REG_TSEG1_MASK);
                    cfgTemp |= cfgTseg1;

                    /* Write register byte 1 */
                    PUERTO_CAN_1_CFG_REG.byte[1u] = cfgTemp;

                    /* Verify 1st byte of PUERTO_CAN_1_CFG_REG register */
                    if (PUERTO_CAN_1_CFG_REG.byte[1u] == cfgTemp)
                    {
                        cfgTemp = 0u;
                        /* Set appropriate bits */
                        if (sm != PUERTO_CAN_1_ONE_SAMPLE_POINT)
                        {
                            cfgTemp = PUERTO_CAN_1_SAMPLE_MODE_MASK;
                        }
                        cfgTemp |= ((uint8) (cfgTseg2 << PUERTO_CAN_1_CFG_REG_TSEG2_SHIFT)) |
                                   ((uint8) (sjw << PUERTO_CAN_1_CFG_REG_SJW_SHIFT));

                        /* Write register byte 0 */
                        PUERTO_CAN_1_CFG_REG.byte[0u] = cfgTemp;

                        /* Verify 1st byte of PUERTO_CAN_1_CFG_REG register */
                        if (PUERTO_CAN_1_CFG_REG.byte[0u] == cfgTemp)
                        {
                            result = CYRET_SUCCESS;
                        }
                    }
                #else  /* CY_PSOC4 */
                    cfgTemp = (uint8) (PUERTO_CAN_1_CFG_REG >> PUERTO_CAN_1_CFG_REG_TSEG1_SHIFT);
                    cfgTemp &= (uint8) (~PUERTO_CAN_1_CFG_REG_TSEG1_MASK);
                    cfgTemp |= cfgTseg1;

                    /* Write register byte 1 */
                    PUERTO_CAN_1_CFG_REG =
                    (PUERTO_CAN_1_CFG_REG & (uint32) (~((uint32) ((uint32) PUERTO_CAN_1_CFG_REG_TSEG1_MASK <<
                    PUERTO_CAN_1_CFG_REG_TSEG1_SHIFT)))) |
                    (uint32) ((uint32) cfgTemp << PUERTO_CAN_1_CFG_REG_TSEG1_SHIFT);

                    /* Verify 1st byte of PUERTO_CAN_1_CFG_REG register */
                    if ((PUERTO_CAN_1_CFG_REG & (uint32) ((uint32) PUERTO_CAN_1_CFG_REG_TSEG1_MASK <<
                       PUERTO_CAN_1_CFG_REG_TSEG1_SHIFT)) == (uint32) ((uint32) ((uint32) cfgTemp &
                       PUERTO_CAN_1_CFG_REG_TSEG1_MASK) << PUERTO_CAN_1_CFG_REG_TSEG1_SHIFT))
                    {
                        cfgTemp = 0u;
                        /* Set appropriate bits */
                        if (sm != PUERTO_CAN_1_ONE_SAMPLE_POINT)
                        {
                            cfgTemp = PUERTO_CAN_1_SAMPLE_MODE_MASK;
                        }
                        cfgTemp |= ((uint8) (cfgTseg2 << PUERTO_CAN_1_CFG_REG_TSEG2_SHIFT)) |
                                   ((uint8) (sjw << PUERTO_CAN_1_CFG_REG_SJW_SHIFT));

                        /* Write register byte 0 */
                        PUERTO_CAN_1_CFG_REG = (PUERTO_CAN_1_CFG_REG &
                        (uint32) (~((uint32) (PUERTO_CAN_1_CFG_REG_TSEG2_MASK | PUERTO_CAN_1_CFG_REG_SJW_MASK |
                        PUERTO_CAN_1_SAMPLE_MODE_MASK)))) | cfgTemp;

                        /* Verify 1st byte of PUERTO_CAN_1_CFG_REG register */
                        if ((PUERTO_CAN_1_CFG_REG & (PUERTO_CAN_1_CFG_REG_TSEG2_MASK |
                           PUERTO_CAN_1_CFG_REG_SJW_MASK | PUERTO_CAN_1_SAMPLE_MODE_MASK)) == cfgTemp)
                        {
                            result = CYRET_SUCCESS;
                        }
                    }
                #endif /* CY_PSOC3 || CY_PSOC5 */
            }
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_SetRestartType
********************************************************************************
*
* Summary:
*  This function sets the Reset type. The types of Reset are Automatic and
*  Manual. Manual Reset is the recommended setting.
*
* Parameters:
*  reset: Reset Type.
*   Define                             Description
*    PUERTO_CAN_1_MANUAL_RESTART    After Bus-Off, CAN must be restarted
*                                       manually. This is the recommended
*                                       setting.
*    PUERTO_CAN_1_AUTO_RESTART      After Bus-Off, CAN restarts
*                                       automatically after 128 groups of 11
*                                       recessive bits.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
*******************************************************************************/
uint8 PUERTO_CAN_1_SetRestartType(uint8 reset) 
{
    uint8 result = PUERTO_CAN_1_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        if (reset == PUERTO_CAN_1_MANUAL_RESTART)
        {
            PUERTO_CAN_1_CFG_REG.byte[0u] &= (uint8) (~PUERTO_CAN_1_RESET_MASK);

            /* Verify that bit is cleared */
            if ((PUERTO_CAN_1_CFG_REG.byte[0u] & PUERTO_CAN_1_RESET_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else    /* Automatic restart */
        {
            PUERTO_CAN_1_CFG_REG.byte[0u] |= PUERTO_CAN_1_RESET_MASK;

            /* Verify that bit is set */
            if ((PUERTO_CAN_1_CFG_REG.byte[0u] & PUERTO_CAN_1_RESET_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #else  /* CY_PSOC4 */
        if (reset == PUERTO_CAN_1_MANUAL_RESTART)
        {
            PUERTO_CAN_1_CFG_REG &= (uint32) (~((uint32) PUERTO_CAN_1_RESET_MASK));

            /* Verify that bit is cleared */
            if ((PUERTO_CAN_1_CFG_REG & PUERTO_CAN_1_RESET_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else    /* Automatic restart */
        {
            PUERTO_CAN_1_CFG_REG |= PUERTO_CAN_1_RESET_MASK;

            /* Verify that bit is set */
            if ((PUERTO_CAN_1_CFG_REG & PUERTO_CAN_1_RESET_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_SetEdgeMode
********************************************************************************
*
* Summary:
*  This function sets Edge Mode. The modes are 'R' to 'D'(Recessive to Dominant)
*  and Both edges are used.
*
* Parameters:
*  edge: Edge Mode.
*   Define                             Description
*    PUERTO_CAN_1_EDGE_R_TO_D       The edge from R to D is used for
*                                       synchronization
*    PUERTO_CAN_1_BOTH_EDGES        Both edges are used
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
*******************************************************************************/
uint8 PUERTO_CAN_1_SetEdgeMode(uint8 edge) 
{
    uint8 result = PUERTO_CAN_1_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        if (edge == PUERTO_CAN_1_EDGE_R_TO_D)
        {
            /* Recessive to Dominant is used for synchronization */
            PUERTO_CAN_1_CFG_REG.byte[0u] &= (uint8) (~PUERTO_CAN_1_EDGE_MODE_MASK);

            /* Verify that bit is cleared */
            if ((PUERTO_CAN_1_CFG_REG.byte[0u] & PUERTO_CAN_1_EDGE_MODE_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else
        {
            /* Both edges to be used */
            PUERTO_CAN_1_CFG_REG.byte[0u] |= PUERTO_CAN_1_EDGE_MODE_MASK;

            /* Verify that bit is set */
            if ((PUERTO_CAN_1_CFG_REG.byte[0u] & PUERTO_CAN_1_EDGE_MODE_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #else  /* CY_PSOC4 */
        if (edge == PUERTO_CAN_1_EDGE_R_TO_D)
        {
            /* Recessive to Dominant is used for synchronization */
            PUERTO_CAN_1_CFG_REG &= (uint32) (~((uint32) PUERTO_CAN_1_EDGE_MODE_MASK));

            /* Verify that bit is cleared */
            if ((PUERTO_CAN_1_CFG_REG & PUERTO_CAN_1_EDGE_MODE_MASK) == 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
        else
        {
            /* Both edges to be used */
            PUERTO_CAN_1_CFG_REG |= PUERTO_CAN_1_EDGE_MODE_MASK;

            /* Verify that bit is set */
            if ((PUERTO_CAN_1_CFG_REG & PUERTO_CAN_1_EDGE_MODE_MASK) != 0u)
            {
                result = CYRET_SUCCESS;
            }
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_SetOpMode
********************************************************************************
*
* Summary:
*  This function sets Operation Mode.
*
* Parameters:
*  opMode: Operation Mode value.
*   Define                              Description
*    PUERTO_CAN_1_STOP_MODE          The CAN controller is in the Stop mode
*    PUERTO_CAN_1_ACTIVE_RUN_MODE    The CAN controller is in the Active
*                                        mode
*    PUERTO_CAN_1_LISTEN_ONLY_MODE   The CAN controller is in the Listen
*                                        Only mode: The output is held at the
*                                        'R' level.
*    PUERTO_CAN_1_INTERNAL_LOOP_BACK The CAN controller is in the Internal
*                                        Loopback mode. This mode is used for
*                                        the testing purpose and the transmitted
*                                        transactions are internally routed
*                                        back to the receiver logic and
*                                        processed by the controller in this
*                                        mode. Not available for PSoC3/5.
*    PUERTO_CAN_1_EXTERNAL_LOOP_BACK This mode is used for the testing
*                                        purpose by connecting Tx and Rx lines
*                                        externally. The transmitted messages
*                                        are received back and processed by the
*                                        CAN controller in this mode.
*                                        Not available for PSoC3/5.
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
* Side Effects:
*  For PSoC 4 device family the function re-initializes the CAN registers.
*
*******************************************************************************/
uint8 PUERTO_CAN_1_SetOpMode(uint8 opMode) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        uint32 timeout;
    #endif /* CY_PSOC3 || CY_PSOC5 */
    uint8 result = PUERTO_CAN_1_FAIL;
    uint8 runState = PUERTO_CAN_1_STOP_MODE;

    #if (CY_PSOC3 || CY_PSOC5)
        if (((PUERTO_CAN_1_CMD_REG.byte[0u] & PUERTO_CAN_1_ACTIVE_RUN_MODE) != 0u) ||
            (opMode == PUERTO_CAN_1_ACTIVE_RUN_MODE))
        {
            runState = PUERTO_CAN_1_ACTIVE_RUN_MODE;
        }

        /* Set CAN to the Stop Mode */
        PUERTO_CAN_1_CMD_REG.byte[0u] = PUERTO_CAN_1_STOP_MODE;

        /* Timeout for CAN state machine to switch mode to Stop */
        for (timeout = PUERTO_CAN_1_MODE_STATE_STOP_TIMEOUT;
            (timeout != 0u) && ((PUERTO_CAN_1_CMD_REG.byte[0u] & PUERTO_CAN_1_ACTIVE_RUN_MODE) != 0u);
             timeout--)
        {
        }

        if (timeout != 0u)
        {
            result = CYRET_SUCCESS;
        }

        if ((result == CYRET_SUCCESS) && (opMode != PUERTO_CAN_1_STOP_MODE))
        {
            if (opMode == PUERTO_CAN_1_LISTEN_ONLY_MODE)
            {
                PUERTO_CAN_1_CMD_REG.byte[0u] = PUERTO_CAN_1_LISTEN_ONLY_MODE;
            }

            if (runState == PUERTO_CAN_1_ACTIVE_RUN_MODE)
            {
                PUERTO_CAN_1_CMD_REG.byte[0u] |= PUERTO_CAN_1_ACTIVE_RUN_MODE;

                /* Timeout for CAN state machine to switch mode to Run */
                for (timeout = PUERTO_CAN_1_MODE_STATE_RUN_TIMEOUT;
                    (timeout != 0u) && ((PUERTO_CAN_1_CMD_REG.byte[0u] & PUERTO_CAN_1_MODE_MASK) == 0u);
                     timeout--)
                {
                }

                if (timeout == 0u)
                {
                    result = PUERTO_CAN_1_FAIL;
                }
            }
        }
    #else  /* CY_PSOC4 */
        if (((PUERTO_CAN_1_CMD_REG & PUERTO_CAN_1_MODE_MASK) != 0u) ||
            (opMode == PUERTO_CAN_1_ACTIVE_RUN_MODE))
        {
            runState = PUERTO_CAN_1_ACTIVE_RUN_MODE;
        }

        /* Sets CAN Component into the Stop mode */
        if (PUERTO_CAN_1_Stop() == CYRET_SUCCESS)
        {
            /* Disable CAN IP Block to reset configuration before sets Operation Mode */
            PUERTO_CAN_1_CNTL_REG = (uint32) (~PUERTO_CAN_1_IP_ENABLE);

            /* Enable CAN IP Block */
            PUERTO_CAN_1_CNTL_REG = PUERTO_CAN_1_IP_ENABLE;

            result = PUERTO_CAN_1_Init();

            if ((result == CYRET_SUCCESS) && (opMode != PUERTO_CAN_1_STOP_MODE))
            {
                if (opMode != PUERTO_CAN_1_ACTIVE_RUN_MODE)
                {
                    /* Set CAN Operation Mode */
                    PUERTO_CAN_1_CMD_REG |= opMode;
                }

                if (runState == PUERTO_CAN_1_ACTIVE_RUN_MODE)
                {
                    /* Enable component's operation */
                    result = PUERTO_CAN_1_Enable();
                }
            }
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_RXRegisterInit
********************************************************************************
*
* Summary:
*  This function writes only receive CAN registers.
*
* Parameters:
*  regAddr: The pointer to a CAN receive register;
*  config:  The value that will be written in the register.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*    PUERTO_CAN_1_OUT_OF_RANGE      The function parameter is out of range
*
*******************************************************************************/
uint8 PUERTO_CAN_1_RXRegisterInit(reg32 *regAddr, uint32 config)
                                      
{
    uint8 result = PUERTO_CAN_1_OUT_OF_RANGE;

    if ((((uint32) regAddr & PUERTO_CAN_1_REG_ADDR_MASK) >=
        ((uint32) PUERTO_CAN_1_RX_FIRST_REGISTER_PTR & PUERTO_CAN_1_REG_ADDR_MASK)) &&
        ((((uint32) regAddr & PUERTO_CAN_1_REG_ADDR_MASK)) <=
        ((uint32) PUERTO_CAN_1_RX_LAST_REGISTER_PTR & PUERTO_CAN_1_REG_ADDR_MASK)))
    {
        result = PUERTO_CAN_1_FAIL;

        if ((((uint32) regAddr & PUERTO_CAN_1_REG_ADDR_MASK) % PUERTO_CAN_1_RX_CMD_REG_WIDTH) == 0u)
        {
            config |= PUERTO_CAN_1_RX_WPN_SET;

    /* Disable isr */
    CyIntDisable(PUERTO_CAN_1_ISR_NUMBER);

            /* Write defined RX CMD registers */
            CY_SET_REG32(regAddr, config);

    /* Enable isr */
    CyIntEnable(PUERTO_CAN_1_ISR_NUMBER);

            /* Verify register */
            if ((CY_GET_REG32(regAddr) & PUERTO_CAN_1_RX_READ_BACK_MASK) ==
                (config & PUERTO_CAN_1_RX_READ_BACK_MASK))
            {
                result = CYRET_SUCCESS;
            }
        }
        /* All registers except RX CMD*/
        else
        {
    /* Disable isr */
    CyIntDisable(PUERTO_CAN_1_ISR_NUMBER);

            /* Write defined CAN receive register */
            CY_SET_REG32(regAddr, config);

    /* Enable isr */
    CyIntEnable(PUERTO_CAN_1_ISR_NUMBER);

            /* Verify register */
            if (CY_GET_REG32(regAddr) == config)
            {
                result = CYRET_SUCCESS;
            }
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_SetIrqMask
********************************************************************************
*
* Summary:
*  This function sets to enable/disable particular interrupt sources. Interrupt
*  Mask directly write to the CAN Interrupt Enable register. A particular
*  interrupt source is enabled by setting its respective flag to 1.
*
* Parameters:
*  mask: Interrupt enable/disable request. 1 bit per interrupt source.
*   Define                                    Description
*    PUERTO_CAN_1_GLOBAL_INT_ENABLE        Global Interrupt Enable Flag
*    PUERTO_CAN_1_ARBITRATION_LOST_ENABLE  Arbitration Loss Interrupt Enable
*    PUERTO_CAN_1_OVERLOAD_ERROR_ENABLE    Overload Interrupt Enable
*    PUERTO_CAN_1_BIT_ERROR_ENABLE         Bit Error Interrupt Enable
*    PUERTO_CAN_1_STUFF_ERROR_ENABLE       Stuff Error Interrupt Enable
*    PUERTO_CAN_1_ACK_ERROR_ENABLE         Ack Error Interrupt Enable
*    PUERTO_CAN_1_FORM_ERROR_ENABLE        Form Error Interrupt Enable
*    PUERTO_CAN_1_CRC_ERROR_ENABLE         CRC Error Interrupt Enable
*    PUERTO_CAN_1_BUS_OFF_ENABLE           Bus-Off State Interrupt Enable
*    PUERTO_CAN_1_RX_MSG_LOST_ENABLE       Rx Msg Loss Interrupt Enable
*    PUERTO_CAN_1_TX_MESSAGE_ENABLE        Tx Msg Sent Interrupt Enable
*    PUERTO_CAN_1_RX_MESSAGE_ENABLE        Msg Received Interrupt Enable
*    PUERTO_CAN_1_RTR_MESSAGE_ENABLE       RTR Auto-reply Interrupt Enable
*    PUERTO_CAN_1_STUCK_AT_ZERO_ENABLE     Stuck at dominant error Interrupt
*                                              Enable
*    PUERTO_CAN_1_SST_FAILURE_ENABLE       SST failure Interrupt Enable
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
*******************************************************************************/
uint8 PUERTO_CAN_1_SetIrqMask(uint16 mask) 
{
    uint8 result = PUERTO_CAN_1_FAIL;

    #if (CY_PSOC3 || CY_PSOC5)
        /* Write byte 0 and 1 of PUERTO_CAN_1_INT_EN_REG register */
        CY_SET_REG16((reg16 *) (&PUERTO_CAN_1_INT_EN_REG), mask);

        /* Verify PUERTO_CAN_1_INT_EN_REG register */
        if (CY_GET_REG16((reg16 *) (&PUERTO_CAN_1_INT_EN_REG)) == mask)
        {
            result = CYRET_SUCCESS;
        }
    #else  /* CY_PSOC4 */
        /* Write byte 0 and 1 of PUERTO_CAN_1_INT_EN_REG register */
        PUERTO_CAN_1_INT_EN_REG = mask;

        /* Verify PUERTO_CAN_1_INT_EN_REG register */
        if ((PUERTO_CAN_1_INT_EN_REG & PUERTO_CAN_1_REG_ADDR_MASK) == mask)
        {
            result = CYRET_SUCCESS;
        }
    #endif /* CY_PSOC3 || CY_PSOC5 */

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_GetTXErrorFlag
********************************************************************************
*
* Summary:
*  This function returns the bit that indicates if the number of TX errors
*  exceeds 0x60.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the number of TX errors exceeds 0x60.
*
*******************************************************************************/
uint8 PUERTO_CAN_1_GetTXErrorFlag(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get state of transmit error flag */
        return (((PUERTO_CAN_1_ERR_SR_REG.byte[2u] & PUERTO_CAN_1_TX_ERROR_FLAG_MASK) ==
                  PUERTO_CAN_1_TX_ERROR_FLAG_MASK) ? 1u : 0u);
    #else  /* CY_PSOC4 */
        /* Get state of transmit error flag */
        return (((PUERTO_CAN_1_ERR_SR_REG & PUERTO_CAN_1_TX_ERROR_FLAG_MASK) ==
                  PUERTO_CAN_1_TX_ERROR_FLAG_MASK) ? 1u : 0u);
    #endif /* CY_PSOC3 || CY_PSOC5 */

}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_GetRXErrorFlag
********************************************************************************
*
* Summary:
*  This function returns the bit that indicates if the number of RX errors
*  exceeds 0x60.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the number of TX errors exceeds 0x60.
*
*******************************************************************************/
uint8 PUERTO_CAN_1_GetRXErrorFlag(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get state of receive error flag */
        return (((PUERTO_CAN_1_ERR_SR_REG.byte[2u] & PUERTO_CAN_1_RX_ERROR_FLAG_MASK) ==
                  PUERTO_CAN_1_RX_ERROR_FLAG_MASK) ? 1u : 0u);
    #else  /* CY_PSOC4 */
        /* Get state of receive error flag */
        return (((PUERTO_CAN_1_ERR_SR_REG & PUERTO_CAN_1_RX_ERROR_FLAG_MASK) ==
                  PUERTO_CAN_1_RX_ERROR_FLAG_MASK) ? 1u : 0u);
    #endif /* CY_PSOC3 || CY_PSOC5 */

}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_GetTXErrorCount
********************************************************************************
*
* Summary:
*  This function returns the number of Transmit Errors.
*
* Parameters:
*  None.
*
* Return:
*  The number of Transmit Errors.
*
*******************************************************************************/
uint8 PUERTO_CAN_1_GetTXErrorCount(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get state of transmit error count */
        return (PUERTO_CAN_1_ERR_SR_REG.byte[0u]);    /* bits 7-0 */
    #else  /* CY_PSOC4 */
        /* Get state of transmit error count */
        return ((uint8) PUERTO_CAN_1_ERR_SR_REG);    /* bits 7-0 */
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_GetRXErrorCount
********************************************************************************
*
* Summary:
*  This function returns the number of Receive Errors.
*
* Parameters:
*  None.
*
* Return:
*  The number of Receive Errors.
*
*******************************************************************************/
uint8 PUERTO_CAN_1_GetRXErrorCount(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get state of receive error count */
        return (PUERTO_CAN_1_ERR_SR_REG.byte[1u]);    /* bits 15-8 */
    #else  /* CY_PSOC4 */
        /* Get state of receive error count (bits 15-8) */
        return ((uint8) (PUERTO_CAN_1_ERR_SR_REG >> PUERTO_CAN_1_ONE_BYTE_OFFSET));
    #endif /* CY_PSOC3 || CY_PSOC5 */

}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_GetErrorState
********************************************************************************
*
* Summary:
*  This function returns the error status of CAN Component.
*
* Parameters:
*  None.
*
* Return:
*  The error status.
*
*******************************************************************************/
uint8 PUERTO_CAN_1_GetErrorState(void) 
{
    #if (CY_PSOC3 || CY_PSOC5)
        /* Get error state of receiver */
        return (PUERTO_CAN_1_ERR_SR_REG.byte[2u] & PUERTO_CAN_1_ERROR_STATE_MASK);
    #else  /* CY_PSOC4 */
        /* Get error state of receiver */
        return ((uint8) ((PUERTO_CAN_1_ERR_SR_REG >> PUERTO_CAN_1_TWO_BYTE_OFFSET) &
                PUERTO_CAN_1_ERROR_STATE_MASK));
    #endif /* CY_PSOC3 || CY_PSOC5 */
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_RxBufConfig
********************************************************************************
*
* Summary:
*  This function configures all receive registers for a particular mailbox.
*
* Parameters:
*  rxConfig: The pointer to a structure that contain all required values to
*  configure all receive registers for a particular mailbox.
*
* Return:
*  The indication if particular configuration has been accepted or rejected.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
*******************************************************************************/
uint8 PUERTO_CAN_1_RxBufConfig(const PUERTO_CAN_1_RX_CFG *rxConfig)
                                   
{
    uint8 result = PUERTO_CAN_1_FAIL;

    /* Write RX CMD Register */
    CY_SET_REG32((reg32 *) (&PUERTO_CAN_1_RX[rxConfig->rxmailbox].rxcmd), (rxConfig->rxcmd |
                 PUERTO_CAN_1_RX_WPN_SET));
    if ((CY_GET_REG32((reg32 *) (&PUERTO_CAN_1_RX[rxConfig->rxmailbox].rxcmd)) &
         PUERTO_CAN_1_RX_READ_BACK_MASK) == (rxConfig->rxcmd & PUERTO_CAN_1_RX_WPN_CLEAR))
    {
        /* Write RX AMR Register */
        CY_SET_REG32((reg32 *) (&PUERTO_CAN_1_RX[rxConfig->rxmailbox].rxamr), rxConfig->rxamr);
        if (CY_GET_REG32((reg32 *) (&PUERTO_CAN_1_RX[rxConfig->rxmailbox].rxamr)) == rxConfig->rxamr)
        {
            /* Write RX ACR Register */
            CY_SET_REG32((reg32 *) (&PUERTO_CAN_1_RX[rxConfig->rxmailbox].rxacr), rxConfig->rxacr);
            if (CY_GET_REG32((reg32 *) (&PUERTO_CAN_1_RX[rxConfig->rxmailbox].rxacr)) == rxConfig->rxacr)
            {
                /* Write RX AMRD Register */
                CY_SET_REG32((reg32 *) (&PUERTO_CAN_1_RX[rxConfig->rxmailbox].rxamrd), 0xFFFFFFFFu);
                if (CY_GET_REG32((reg32 *) (&PUERTO_CAN_1_RX[rxConfig->rxmailbox].rxamrd)) == 0xFFFFFFFFu)
                {
                    /* Write RX ACRD Register */
                    CY_SET_REG32((reg32 *) (&PUERTO_CAN_1_RX[rxConfig->rxmailbox].rxacrd), 0x00000000u);
                    if (CY_GET_REG32((reg32 *) (&PUERTO_CAN_1_RX[rxConfig->rxmailbox].rxacrd)) == 0x00000000u)
                    {
                        result = CYRET_SUCCESS;
                    }
                }
            }
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_TxBufConfig
********************************************************************************
*
* Summary:
*  This function configures all transmit registers for a particular mailbox.
*  Mailbox number contains PUERTO_CAN_1_TX_CFG structure.
*
* Parameters:
*  txConfig: The pointer to structure that contain all required values to
*  configure all transmit registers for a particular mailbox.
*
* Return:
*  The indication if particular configuration has been accepted or rejected.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
*******************************************************************************/
uint8 PUERTO_CAN_1_TxBufConfig(const PUERTO_CAN_1_TX_CFG *txConfig)
                                   
{
    uint8 result = PUERTO_CAN_1_FAIL;

    /* Write TX CMD Register */
    CY_SET_REG32(PUERTO_CAN_1_TX_CMD_PTR(txConfig->txmailbox), (txConfig->txcmd | PUERTO_CAN_1_TX_WPN_SET));
    if ((CY_GET_REG32(PUERTO_CAN_1_TX_CMD_PTR(txConfig->txmailbox)) &
        PUERTO_CAN_1_TX_READ_BACK_MASK) == (txConfig->txcmd & PUERTO_CAN_1_TX_WPN_CLEAR))
    {
        /* Write TX ID Register */
        CY_SET_REG32(PUERTO_CAN_1_TX_ID_PTR(txConfig->txmailbox), txConfig->txid);
        if (CY_GET_REG32(PUERTO_CAN_1_TX_ID_PTR(txConfig->txmailbox)) == txConfig->txid)
        {
            result = CYRET_SUCCESS;
        }
    }

    return (result);
}


#if (!(CY_PSOC3 || CY_PSOC5))

/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_SetSwapDataEndianness
********************************************************************************
*
* Summary:
*  This function selects whether the data byte endianness of the CAN receive and
*  transmit data fields has to be swapped or not swapped. This is useful to
*  match the data byte endianness to the endian setting of the processor or the
*  used CAN protocol.
*
* Parameters:
*  swap: Swap Enable/Disable setting.
*   Define                                   Description
*   PUERTO_CAN_1_SWAP_ENDIANNESS_ENABLE   The endianness of transmitted/
*                                             received data byte fields (Big
*                                             endian) is not swapped during
*                                             multibyte data transmission.
*   PUERTO_CAN_1_SWAP_ENDIANNESS_DISABLE  The endianness of transmitted/
*                                             received data byte fields is
*                                             swapped (Little endian) during
*                                             multi byte data transmission.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
*******************************************************************************/
uint8 PUERTO_CAN_1_SetSwapDataEndianness(uint8 swap)
{
    uint8 result = PUERTO_CAN_1_FAIL;

    if (swap == PUERTO_CAN_1_SWAP_ENDIANNESS_DISABLE)    /* Big endian */
    {
        PUERTO_CAN_1_CFG_REG &= (uint32) (~PUERTO_CAN_1_ENDIANNESS_MASK);

        /* Verify that bit is cleared */
        if ((PUERTO_CAN_1_CFG_REG & PUERTO_CAN_1_ENDIANNESS_MASK) == 0u)
        {
            result = CYRET_SUCCESS;
        }
    }
    else    /* Little endian */
    {
        PUERTO_CAN_1_CFG_REG |= PUERTO_CAN_1_ENDIANNESS_MASK;

        /* Verify that bit is set */
        if ((PUERTO_CAN_1_CFG_REG & PUERTO_CAN_1_ENDIANNESS_MASK) != 0u)
        {
            result = CYRET_SUCCESS;
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_SetErrorCaptureRegisterMode
********************************************************************************
*
* Summary:
*  This function sets the Error Capture register mode. The two modes are
*  possible: Free Running and Error Capture.
*
* Parameters:
*  ecrMode: The Error Capture register mode setting.
*   Define                               Description
*   PUERTO_CAN_1_ECR_FREE_RUNNING     The ECR captures the field and bit
*                                         position within the current CAN frame.
*   PUERTO_CAN_1_ECR_ERROR_CAPTURE    In this mode the ECR register only
*                                         captures an error event. For
*                                         successive error captures, the ECR
*                                         needs to be armed again by writing
*                                         to the ECR register.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
*******************************************************************************/
uint8 PUERTO_CAN_1_SetErrorCaptureRegisterMode(uint8 ecrMode)
{
    uint8 result = PUERTO_CAN_1_FAIL;

    if (ecrMode == PUERTO_CAN_1_ECR_FREE_RUNNING)
    {
        PUERTO_CAN_1_CFG_REG &= (uint32) (~PUERTO_CAN_1_ECR_MODE_MASK);

        /* Verify that bit is cleared */
        if ((PUERTO_CAN_1_CFG_REG & PUERTO_CAN_1_ECR_MODE_MASK) == 0u)
        {
            result = CYRET_SUCCESS;
        }
    }
    else    /* Capture mode */
    {
        PUERTO_CAN_1_CFG_REG |= PUERTO_CAN_1_ECR_MODE_MASK;

        /* Verify that bit is set */
        if ((PUERTO_CAN_1_CFG_REG & PUERTO_CAN_1_ECR_MODE_MASK) != 0u)
        {
            result = CYRET_SUCCESS;
        }
    }

    return (result);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_ReadErrorCaptureRegister
********************************************************************************
*
* Summary:
*  This function returns the value of the Error Capture register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the Error Capture register.
*   Bit  Name          Values
*    0    ECR_STATUS    0: The ECR register captured an error or it is a free
*                          running mode
*                       1: The ECR register is armed
*   3:1   ERROR_TYPE    000 : Arbitration loss
*                       001 : Bit Error
*                       010 : Bit Stuffing Error
*                       011 : Acknowledge Error
*                       100 : Form Error
*                       101 : CRC Error
*                       Others : N/A
*    4    TX_MODE       0: No status
*                       1: CAN Controller is the transmitter
*    5    RX_MODE       0: No status
*                       1: CAN Controller is the receiver
*  11:6   BIT           Bit number inside of Field
*  12:16  Field         0x00 : Stopped
*                       0x01 : Synchronize
*                       0x05 : Interframe
*                       0x06 : Bus Idle
*                       0x07 : Start of Frame
*                       0x08 : Arbitration
*                       0x09 : Control
*                       0x0A : Data
*                       0x0B : CRC
*                       0x0C : ACK
*                       0x0D : End of frame
*                       0x10 : Error flag
*                       0x11 : Error echo
*                       0x12 : Error delimiter
*                       0x18 : Overload flag
*                       0x19 : Overload echo
*                       0x1A : Overload delimiter
*                       Others : N/A
*
*******************************************************************************/
uint32 PUERTO_CAN_1_ReadErrorCaptureRegister(void)
{
    return (PUERTO_CAN_1_ECR_REG);
}


/*******************************************************************************
* FUNCTION NAME:   PUERTO_CAN_1_ArmErrorCaptureRegister
********************************************************************************
*
* Summary:
*  This function arms the Error Capture register when the ECR is in the Error
*  Capture mode, by setting the ECR_STATUS bit in the ECR register.
*
* Parameters:
*  None.
*
* Return:
*  The indication whether the register is written and verified.
*   Define                             Description
*    CYRET_SUCCESS                      The function passed successfully
*    PUERTO_CAN_1_FAIL              The function failed
*
*******************************************************************************/
uint8 PUERTO_CAN_1_ArmErrorCaptureRegister(void)
{
    uint8 result = PUERTO_CAN_1_FAIL;

    PUERTO_CAN_1_ECR_REG |= PUERTO_CAN_1_ECR_STATUS_ARM;

    /* Verify that bit is set */
    if ((PUERTO_CAN_1_ECR_REG & PUERTO_CAN_1_ECR_STATUS_ARM) != 0u)
    {
        result = CYRET_SUCCESS;
    }

    return (result);
}

#endif /* (!(CY_PSOC3 || CY_PSOC5)) */


/* [] END OF FILE */
