/*******************************************************************************
* File Name: PUERTO_CAN_1_INT.c
* Version 3.0
*
* Description:
*  This file contains Interrupt Service Routine (ISR) for CAN Component.
*  The Interrupt handlers functions are generated accordingly to the PSoC
*  Creator Customizer inputs.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PUERTO_CAN_1.h"
#include "cyapicallbacks.h"

/* `#START CAN_INT_C_CODE_DEFINITION` */

/* `#END` */

#if (PUERTO_CAN_1_ARB_LOST)
    /*******************************************************************************
    * FUNCTION NAME:   PUERTO_CAN_1_ArbLostIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Arbitration Lost Interrupt. Clears
    *  Arbitration Lost interrupt flag. Only generated if Arbitration Lost
    *  Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void PUERTO_CAN_1_ArbLostIsr(void) 
    {
        /* Clear Arbitration Lost flag */
        PUERTO_CAN_1_INT_SR_REG.byte[0u] = PUERTO_CAN_1_ARBITRATION_LOST_MASK;

        /* `#START ARBITRATION_LOST_ISR` */

        /* `#END` */

        #ifdef PUERTO_CAN_1_ARB_LOST_ISR_CALLBACK
            PUERTO_CAN_1_ArbLostIsr_Callback();
        #endif /* PUERTO_CAN_1_ARB_LOST_ISR_CALLBACK */
    }
#endif /* PUERTO_CAN_1_ARB_LOST */


#if (PUERTO_CAN_1_OVERLOAD)
    /*******************************************************************************
    * FUNCTION NAME:   PUERTO_CAN_1_OvrLdErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Overload Error Interrupt. Clears Overload
    *  Error interrupt flag. Only generated if Overload Error Interrupt enable
    *  in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void PUERTO_CAN_1_OvrLdErrorIsr(void) 
    {
        /* Clear Overload Error flag */
        PUERTO_CAN_1_INT_SR_REG.byte[0u] = PUERTO_CAN_1_OVERLOAD_ERROR_MASK;

        /* `#START OVER_LOAD_ERROR_ISR` */

        /* `#END` */

        #ifdef PUERTO_CAN_1_OVR_LD_ERROR_ISR_CALLBACK
            PUERTO_CAN_1_OvrLdErrorIsr_Callback();
        #endif /* PUERTO_CAN_1_OVR_LD_ERROR_ISR_CALLBACK */
    }
#endif /* PUERTO_CAN_1_OVERLOAD */


#if (PUERTO_CAN_1_BIT_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   PUERTO_CAN_1_BitErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Bit Error Interrupt. Clears Bit Error
    *  interrupt flag. Only generated if Bit Error Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void PUERTO_CAN_1_BitErrorIsr(void) 
    {
        /* Clear Bit Error flag */
        PUERTO_CAN_1_INT_SR_REG.byte[0u] = PUERTO_CAN_1_BIT_ERROR_MASK;

        /* `#START BIT_ERROR_ISR` */

        /* `#END` */

        #ifdef PUERTO_CAN_1_BIT_ERROR_ISR_CALLBACK
            PUERTO_CAN_1_BitErrorIsr_Callback();
        #endif /* PUERTO_CAN_1_BIT_ERROR_ISR_CALLBACK */
    }
#endif /* PUERTO_CAN_1_BIT_ERR */


#if (PUERTO_CAN_1_STUFF_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   PUERTO_CAN_1_BitStuffErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Bit Stuff Error Interrupt. Clears Bit Stuff
    *  Error interrupt flag. Only generated if Bit Stuff Error Interrupt enable
    *  in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void PUERTO_CAN_1_BitStuffErrorIsr(void) 
    {
        /* Clear Stuff Error flag */
        PUERTO_CAN_1_INT_SR_REG.byte[0u] = PUERTO_CAN_1_STUFF_ERROR_MASK;

        /* `#START BIT_STUFF_ERROR_ISR` */

        /* `#END` */

        #ifdef PUERTO_CAN_1_BIT_STUFF_ERROR_ISR_CALLBACK
            PUERTO_CAN_1_BitStuffErrorIsr_Callback();
        #endif /* PUERTO_CAN_1_BIT_STUFF_ERROR_ISR_CALLBACK */
    }
#endif /* PUERTO_CAN_1_STUFF_ERR */


#if (PUERTO_CAN_1_ACK_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   PUERTO_CAN_1_AckErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Acknowledge Error Interrupt. Clears
    *  Acknowledge Error interrupt flag. Only generated if Acknowledge Error
    *  Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void PUERTO_CAN_1_AckErrorIsr(void) 
    {
        /* Clear Acknoledge Error flag */
        PUERTO_CAN_1_INT_SR_REG.byte[0u] = PUERTO_CAN_1_ACK_ERROR_MASK;

        /* `#START ACKNOWLEDGE_ERROR_ISR` */

        /* `#END` */

        #ifdef PUERTO_CAN_1_ACK_ERROR_ISR_CALLBACK
            PUERTO_CAN_1_AckErrorIsr_Callback();
        #endif /* PUERTO_CAN_1_ACK_ERROR_ISR_CALLBACK */
    }
#endif /* PUERTO_CAN_1_ACK_ERR */


#if (PUERTO_CAN_1_FORM_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   PUERTO_CAN_1_MsgErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Form Error Interrupt. Clears Form Error
    *  interrupt flag. Only generated if Form Error Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void PUERTO_CAN_1_MsgErrorIsr(void) 
    {
        /* Clear Form Error flag */
        PUERTO_CAN_1_INT_SR_REG.byte[0u] = PUERTO_CAN_1_FORM_ERROR_MASK;

        /* `#START MESSAGE_ERROR_ISR` */

        /* `#END` */

        #ifdef PUERTO_CAN_1_MSG_ERROR_ISR_CALLBACK
            PUERTO_CAN_1_MsgErrorIsr_Callback();
        #endif /* PUERTO_CAN_1_MSG_ERROR_ISR_CALLBACK */
    }
#endif /* PUERTO_CAN_1_FORM_ERR */


#if (PUERTO_CAN_1_CRC_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   PUERTO_CAN_1_CrcErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to CRC Error Interrupt. Clears CRC Error
    *  interrupt flag. Only generated if CRC Error Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void PUERTO_CAN_1_CrcErrorIsr(void) 
    {
        /* Clear CRC Error flag */
        PUERTO_CAN_1_INT_SR_REG.byte[1u] = PUERTO_CAN_1_CRC_ERROR_MASK;

        /* `#START CRC_ERROR_ISR` */

        /* `#END` */

        #ifdef PUERTO_CAN_1_CRC_ERROR_ISR_CALLBACK
            PUERTO_CAN_1_CrcErrorIsr_Callback();
        #endif /* PUERTO_CAN_1_CRC_ERROR_ISR_CALLBACK */
    }
#endif /* PUERTO_CAN_1_CRC_ERR */


#if (PUERTO_CAN_1_BUS_OFF)
    /*******************************************************************************
    * FUNCTION NAME:   PUERTO_CAN_1_BusOffIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Bus Off Interrupt. Places CAN Component
    *  to Stop mode. Only generated if Bus Off Interrupt enable in Customizer.
    *  Recommended setting to enable this interrupt.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Stops CAN component operation.
    *
    *******************************************************************************/
    void PUERTO_CAN_1_BusOffIsr(void) 
    {
        /* Clear Bus Off flag */
        PUERTO_CAN_1_INT_SR_REG.byte[1u] = PUERTO_CAN_1_BUS_OFF_MASK;
        (void) PUERTO_CAN_1_GlobalIntDisable();

        /* `#START BUS_OFF_ISR` */

        /* `#END` */

        #ifdef PUERTO_CAN_1_BUS_OFF_ISR_CALLBACK
            PUERTO_CAN_1_BusOffIsr_Callback();
        #endif /* PUERTO_CAN_1_BUS_OFF_ISR_CALLBACK */

        (void) PUERTO_CAN_1_Stop();
    }
#endif /* PUERTO_CAN_1_BUS_OFF */


#if (PUERTO_CAN_1_RX_MSG_LOST)
    /*******************************************************************************
    * FUNCTION NAME:   PUERTO_CAN_1_MsgLostIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Message Lost Interrupt. Clears Message Lost
    *  interrupt flag. Only generated if Message Lost Interrupt enable in Customizer
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void PUERTO_CAN_1_MsgLostIsr(void) 
    {
        /* Clear Receive Message Lost flag */
        PUERTO_CAN_1_INT_SR_REG.byte[1u] = PUERTO_CAN_1_RX_MSG_LOST_MASK;

        /* `#START MESSAGE_LOST_ISR` */

        /* `#END` */

        #ifdef PUERTO_CAN_1_MSG_LOST_ISR_CALLBACK
            PUERTO_CAN_1_MsgLostIsr_Callback();
        #endif /* PUERTO_CAN_1_MSG_LOST_ISR_CALLBACK */
    }
#endif /* PUERTO_CAN_1_RX_MSG_LOST */


#if (PUERTO_CAN_1_TX_MESSAGE)
    /*******************************************************************************
    * FUNCTION NAME:   PUERTO_CAN_1_MsgTXIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Transmit Message Interrupt. Clears Transmit
    *  Message interrupt flag. Only generated if Transmit Message Interrupt enable
    *  in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void PUERTO_CAN_1_MsgTXIsr(void) 
    {
        /* Clear Transmit Message flag */
        PUERTO_CAN_1_INT_SR_REG.byte[1u] = PUERTO_CAN_1_TX_MESSAGE_MASK;

        /* `#START MESSAGE_TRANSMITTED_ISR` */

        /* `#END` */

        #ifdef PUERTO_CAN_1_MSG_TX_ISR_CALLBACK
            PUERTO_CAN_1_MsgTXIsr_Callback();
        #endif /* PUERTO_CAN_1_MSG_TX_ISR_CALLBACK */
    }
#endif /* PUERTO_CAN_1_TX_MESSAGE */


#if (PUERTO_CAN_1_RX_MESSAGE)
    /*******************************************************************************
    * FUNCTION NAME:   PUERTO_CAN_1_MsgRXIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Receive Message Interrupt. Clears Receive
    *  Message interrupt flag and call appropriate handlers for Basic and Full
    *  interrupt based mailboxes. Only generated if Receive Message Interrupt
    *  enable in Customizer. Recommended setting to enable this interrupt.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void PUERTO_CAN_1_MsgRXIsr(void) 
    {
        uint8 mailboxNumber;
        uint16 shift = 0x01u;

        /* Clear Receive Message flag */
        PUERTO_CAN_1_INT_SR_REG.byte[1u] = PUERTO_CAN_1_RX_MESSAGE_MASK;

        /* `#START MESSAGE_RECEIVE_ISR` */

        /* `#END` */

        #ifdef PUERTO_CAN_1_MSG_RX_ISR_CALLBACK
            PUERTO_CAN_1_MsgRXIsr_Callback();
        #endif /* PUERTO_CAN_1_MSG_RX_ISR_CALLBACK */

        for (mailboxNumber = 0u; mailboxNumber < PUERTO_CAN_1_NUMBER_OF_RX_MAILBOXES; mailboxNumber++)
        {
            if ((CY_GET_REG16((reg16 *) &PUERTO_CAN_1_BUF_SR_REG.byte[0u]) & shift) != 0u)
            {
                if ((PUERTO_CAN_1_RX[mailboxNumber].rxcmd.byte[0u] & PUERTO_CAN_1_RX_INT_ENABLE_MASK) != 0u)
                {
                    if ((PUERTO_CAN_1_RX_MAILBOX_TYPE & shift) != 0u)
                    {
                        /* RX Full mailboxes handler */
                        switch(mailboxNumber)
                        {
                            case 0u : PUERTO_CAN_1_ReceiveMsg0();
                            break;
                            default:
                            break;
                        }
                    }
                    else
                    {
                        /* RX Basic mailbox handler */
                        PUERTO_CAN_1_ReceiveMsg(mailboxNumber);
                    }
                }
            }
            shift <<= 1u;
        }
    }
#endif /* PUERTO_CAN_1_RX_MESSAGE */


/*******************************************************************************
* Function Name: PUERTO_CAN_1_ISR
********************************************************************************
*
* Summary:
*  This ISR is executed when CAN Core generates and interrupt on one of events:
*  Arb_lost, Overload, Bit_err, Stuff_err, Ack_err, Form_err, Crc_err,
*  Buss_off, Rx_msg_lost, Tx_msg or Rx_msg. The interrupt sources depends
*  on the Customizer inputs.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(PUERTO_CAN_1_ISR)
{
    #ifdef PUERTO_CAN_1_ISR_INTERRUPT_CALLBACK
        PUERTO_CAN_1_ISR_InterruptCallback();
    #endif /* PUERTO_CAN_1_ISR_INTERRUPT_CALLBACK */
    
    /* Place your Interrupt code here. */
    /* `#START CAN_ISR` */

    /* `#END` */
    
    /* Arbitration */
    #if (PUERTO_CAN_1_ARB_LOST && (PUERTO_CAN_1_ARB_LOST_USE_HELPER || \
        (!PUERTO_CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((PUERTO_CAN_1_INT_SR_REG.byte[0u] & PUERTO_CAN_1_ARBITRATION_LOST_MASK) != 0u)
        {
            PUERTO_CAN_1_ArbLostIsr();
        }
    #endif /* PUERTO_CAN_1_ARB_LOST && PUERTO_CAN_1_ARB_LOST_USE_HELPER */

    /* Overload Error */
    #if (PUERTO_CAN_1_OVERLOAD && (PUERTO_CAN_1_OVERLOAD_USE_HELPER || \
        (!PUERTO_CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((PUERTO_CAN_1_INT_SR_REG.byte[0u] & PUERTO_CAN_1_OVERLOAD_ERROR_MASK) != 0u)
        {
            PUERTO_CAN_1_OvrLdErrorIsr();
        }
    #endif /* PUERTO_CAN_1_OVERLOAD && PUERTO_CAN_1_OVERLOAD_USE_HELPER */

    /* Bit Error */
    #if (PUERTO_CAN_1_BIT_ERR && (PUERTO_CAN_1_BIT_ERR_USE_HELPER || \
        (!PUERTO_CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((PUERTO_CAN_1_INT_SR_REG.byte[0u] & PUERTO_CAN_1_BIT_ERROR_MASK) != 0u)
        {
            PUERTO_CAN_1_BitErrorIsr();
        }
    #endif /* PUERTO_CAN_1_BIT_ERR && PUERTO_CAN_1_BIT_ERR_USE_HELPER */

    /* Bit Staff Error */
    #if (PUERTO_CAN_1_STUFF_ERR && (PUERTO_CAN_1_STUFF_ERR_USE_HELPER || \
        (!PUERTO_CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((PUERTO_CAN_1_INT_SR_REG.byte[0u] & PUERTO_CAN_1_STUFF_ERROR_MASK) != 0u)
        {
            PUERTO_CAN_1_BitStuffErrorIsr();
        }
    #endif /* PUERTO_CAN_1_STUFF_ERR && PUERTO_CAN_1_STUFF_ERR_USE_HELPER */

    /* ACK Error */
    #if (PUERTO_CAN_1_ACK_ERR && (PUERTO_CAN_1_ACK_ERR_USE_HELPER || \
        (!PUERTO_CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((PUERTO_CAN_1_INT_SR_REG.byte[0u] & PUERTO_CAN_1_ACK_ERROR_MASK) != 0u)
        {
            PUERTO_CAN_1_AckErrorIsr();
        }
    #endif /* PUERTO_CAN_1_ACK_ERR && PUERTO_CAN_1_ACK_ERR_USE_HELPER */

    /* Form(msg) Error */
    #if (PUERTO_CAN_1_FORM_ERR && (PUERTO_CAN_1_FORM_ERR_USE_HELPER || \
        (!PUERTO_CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((PUERTO_CAN_1_INT_SR_REG.byte[0u] & PUERTO_CAN_1_FORM_ERROR_MASK) != 0u)
        {
            PUERTO_CAN_1_MsgErrorIsr();
        }
    #endif /* PUERTO_CAN_1_FORM_ERR && PUERTO_CAN_1_FORM_ERR_USE_HELPER */

    /* CRC Error */
    #if (PUERTO_CAN_1_CRC_ERR && (PUERTO_CAN_1_CRC_ERR_USE_HELPER || \
        (!PUERTO_CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((PUERTO_CAN_1_INT_SR_REG.byte[1u] & PUERTO_CAN_1_CRC_ERROR_MASK) != 0u)
        {
            PUERTO_CAN_1_CrcErrorIsr();
        }
    #endif /* PUERTO_CAN_1_CRC_ERR && PUERTO_CAN_1_CRC_ERR_USE_HELPER */

    /* Bus Off state */
    #if (PUERTO_CAN_1_BUS_OFF && (PUERTO_CAN_1_BUS_OFF_USE_HELPER || \
        (!PUERTO_CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((PUERTO_CAN_1_INT_SR_REG.byte[1u] & PUERTO_CAN_1_BUS_OFF_MASK) != 0u)
        {
            PUERTO_CAN_1_BusOffIsr();
        }
    #endif /* PUERTO_CAN_1_BUS_OFF && PUERTO_CAN_1_BUS_OFF_USE_HELPER */

    /* Message Lost */
    #if (PUERTO_CAN_1_RX_MSG_LOST && (PUERTO_CAN_1_RX_MSG_LOST_USE_HELPER || \
        (!PUERTO_CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((PUERTO_CAN_1_INT_SR_REG.byte[1u] & PUERTO_CAN_1_RX_MSG_LOST_MASK) != 0u)
        {
            PUERTO_CAN_1_MsgLostIsr();
        }
    #endif /* PUERTO_CAN_1_RX_MSG_LOST && PUERTO_CAN_1_RX_MSG_LOST_USE_HELPER */

    /* TX Message Send */
    #if (PUERTO_CAN_1_TX_MESSAGE && (PUERTO_CAN_1_TX_MESSAGE_USE_HELPER || \
        (!PUERTO_CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((PUERTO_CAN_1_INT_SR_REG.byte[1u] & PUERTO_CAN_1_TX_MESSAGE_MASK) != 0u)
        {
            PUERTO_CAN_1_MsgTXIsr();
        }
    #endif /* PUERTO_CAN_1_TX_MESSAGE && PUERTO_CAN_1_TX_MESSAGE_USE_HELPER */

    /* RX Message Available */
    #if (PUERTO_CAN_1_RX_MESSAGE && (PUERTO_CAN_1_RX_MESSAGE_USE_HELPER || \
        (!PUERTO_CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((PUERTO_CAN_1_INT_SR_REG.byte[1u] & PUERTO_CAN_1_RX_MESSAGE_MASK) != 0u)
        {
            PUERTO_CAN_1_MsgRXIsr();
        }
    #endif /* PUERTO_CAN_1_RX_MESSAGE && PUERTO_CAN_1_RX_MESSAGE_USE_HELPER */
}


/* [] END OF FILE */
