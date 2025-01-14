/*******************************************************************************
* File Name: CAN_INT.c
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

#include "CAN.h"
#include "cyapicallbacks.h"

/* `#START CAN_INT_C_CODE_DEFINITION` */

/* `#END` */

#if (CAN_ARB_LOST)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_ArbLostIsr
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
    void CAN_ArbLostIsr(void) 
    {
        /* Clear Arbitration Lost flag */
        CAN_INT_SR_REG.byte[0u] = CAN_ARBITRATION_LOST_MASK;

        /* `#START ARBITRATION_LOST_ISR` */

        /* `#END` */

        #ifdef CAN_ARB_LOST_ISR_CALLBACK
            CAN_ArbLostIsr_Callback();
        #endif /* CAN_ARB_LOST_ISR_CALLBACK */
    }
#endif /* CAN_ARB_LOST */


#if (CAN_OVERLOAD)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_OvrLdErrorIsr
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
    void CAN_OvrLdErrorIsr(void) 
    {
        /* Clear Overload Error flag */
        CAN_INT_SR_REG.byte[0u] = CAN_OVERLOAD_ERROR_MASK;

        /* `#START OVER_LOAD_ERROR_ISR` */

        /* `#END` */

        #ifdef CAN_OVR_LD_ERROR_ISR_CALLBACK
            CAN_OvrLdErrorIsr_Callback();
        #endif /* CAN_OVR_LD_ERROR_ISR_CALLBACK */
    }
#endif /* CAN_OVERLOAD */


#if (CAN_BIT_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_BitErrorIsr
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
    void CAN_BitErrorIsr(void) 
    {
        /* Clear Bit Error flag */
        CAN_INT_SR_REG.byte[0u] = CAN_BIT_ERROR_MASK;

        /* `#START BIT_ERROR_ISR` */

        /* `#END` */

        #ifdef CAN_BIT_ERROR_ISR_CALLBACK
            CAN_BitErrorIsr_Callback();
        #endif /* CAN_BIT_ERROR_ISR_CALLBACK */
    }
#endif /* CAN_BIT_ERR */


#if (CAN_STUFF_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_BitStuffErrorIsr
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
    void CAN_BitStuffErrorIsr(void) 
    {
        /* Clear Stuff Error flag */
        CAN_INT_SR_REG.byte[0u] = CAN_STUFF_ERROR_MASK;

        /* `#START BIT_STUFF_ERROR_ISR` */

        /* `#END` */

        #ifdef CAN_BIT_STUFF_ERROR_ISR_CALLBACK
            CAN_BitStuffErrorIsr_Callback();
        #endif /* CAN_BIT_STUFF_ERROR_ISR_CALLBACK */
    }
#endif /* CAN_STUFF_ERR */


#if (CAN_ACK_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_AckErrorIsr
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
    void CAN_AckErrorIsr(void) 
    {
        /* Clear Acknoledge Error flag */
        CAN_INT_SR_REG.byte[0u] = CAN_ACK_ERROR_MASK;

        /* `#START ACKNOWLEDGE_ERROR_ISR` */

        /* `#END` */

        #ifdef CAN_ACK_ERROR_ISR_CALLBACK
            CAN_AckErrorIsr_Callback();
        #endif /* CAN_ACK_ERROR_ISR_CALLBACK */
    }
#endif /* CAN_ACK_ERR */


#if (CAN_FORM_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_MsgErrorIsr
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
    void CAN_MsgErrorIsr(void) 
    {
        /* Clear Form Error flag */
        CAN_INT_SR_REG.byte[0u] = CAN_FORM_ERROR_MASK;

        /* `#START MESSAGE_ERROR_ISR` */

        /* `#END` */

        #ifdef CAN_MSG_ERROR_ISR_CALLBACK
            CAN_MsgErrorIsr_Callback();
        #endif /* CAN_MSG_ERROR_ISR_CALLBACK */
    }
#endif /* CAN_FORM_ERR */


#if (CAN_CRC_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_CrcErrorIsr
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
    void CAN_CrcErrorIsr(void) 
    {
        /* Clear CRC Error flag */
        CAN_INT_SR_REG.byte[1u] = CAN_CRC_ERROR_MASK;

        /* `#START CRC_ERROR_ISR` */

        /* `#END` */

        #ifdef CAN_CRC_ERROR_ISR_CALLBACK
            CAN_CrcErrorIsr_Callback();
        #endif /* CAN_CRC_ERROR_ISR_CALLBACK */
    }
#endif /* CAN_CRC_ERR */


#if (CAN_BUS_OFF)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_BusOffIsr
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
    void CAN_BusOffIsr(void) 
    {
        /* Clear Bus Off flag */
        CAN_INT_SR_REG.byte[1u] = CAN_BUS_OFF_MASK;
        (void) CAN_GlobalIntDisable();

        /* `#START BUS_OFF_ISR` */

        /* `#END` */

        #ifdef CAN_BUS_OFF_ISR_CALLBACK
            CAN_BusOffIsr_Callback();
        #endif /* CAN_BUS_OFF_ISR_CALLBACK */

        (void) CAN_Stop();
    }
#endif /* CAN_BUS_OFF */


#if (CAN_RX_MSG_LOST)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_MsgLostIsr
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
    void CAN_MsgLostIsr(void) 
    {
        /* Clear Receive Message Lost flag */
        CAN_INT_SR_REG.byte[1u] = CAN_RX_MSG_LOST_MASK;

        /* `#START MESSAGE_LOST_ISR` */

        /* `#END` */

        #ifdef CAN_MSG_LOST_ISR_CALLBACK
            CAN_MsgLostIsr_Callback();
        #endif /* CAN_MSG_LOST_ISR_CALLBACK */
    }
#endif /* CAN_RX_MSG_LOST */


#if (CAN_TX_MESSAGE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_MsgTXIsr
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
    void CAN_MsgTXIsr(void) 
    {
        /* Clear Transmit Message flag */
        CAN_INT_SR_REG.byte[1u] = CAN_TX_MESSAGE_MASK;

        /* `#START MESSAGE_TRANSMITTED_ISR` */

        /* `#END` */

        #ifdef CAN_MSG_TX_ISR_CALLBACK
            CAN_MsgTXIsr_Callback();
        #endif /* CAN_MSG_TX_ISR_CALLBACK */
    }
#endif /* CAN_TX_MESSAGE */


#if (CAN_RX_MESSAGE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_MsgRXIsr
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
    void CAN_MsgRXIsr(void) 
    {
        uint8 mailboxNumber;
        uint16 shift = 0x01u;

        /* Clear Receive Message flag */
        CAN_INT_SR_REG.byte[1u] = CAN_RX_MESSAGE_MASK;

        /* `#START MESSAGE_RECEIVE_ISR` */

        /* `#END` */

        #ifdef CAN_MSG_RX_ISR_CALLBACK
            CAN_MsgRXIsr_Callback();
        #endif /* CAN_MSG_RX_ISR_CALLBACK */

        for (mailboxNumber = 0u; mailboxNumber < CAN_NUMBER_OF_RX_MAILBOXES; mailboxNumber++)
        {
            if ((CY_GET_REG16((reg16 *) &CAN_BUF_SR_REG.byte[0u]) & shift) != 0u)
            {
                if ((CAN_RX[mailboxNumber].rxcmd.byte[0u] & CAN_RX_INT_ENABLE_MASK) != 0u)
                {
                    if ((CAN_RX_MAILBOX_TYPE & shift) != 0u)
                    {
                        /* RX Full mailboxes handler */
                        switch(mailboxNumber)
                        {
                            case 0u : CAN_ReceiveMsg0();
                            break;
                            default:
                            break;
                        }
                    }
                    else
                    {
                        /* RX Basic mailbox handler */
                        CAN_ReceiveMsg(mailboxNumber);
                    }
                }
            }
            shift <<= 1u;
        }
    }
#endif /* CAN_RX_MESSAGE */


/*******************************************************************************
* Function Name: CAN_ISR
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
CY_ISR(CAN_ISR)
{
    #ifdef CAN_ISR_INTERRUPT_CALLBACK
        CAN_ISR_InterruptCallback();
    #endif /* CAN_ISR_INTERRUPT_CALLBACK */
    
    /* Place your Interrupt code here. */
    /* `#START CAN_ISR` */

    /* `#END` */
    
    /* Arbitration */
    #if (CAN_ARB_LOST && (CAN_ARB_LOST_USE_HELPER || \
        (!CAN_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_INT_SR_REG.byte[0u] & CAN_ARBITRATION_LOST_MASK) != 0u)
        {
            CAN_ArbLostIsr();
        }
    #endif /* CAN_ARB_LOST && CAN_ARB_LOST_USE_HELPER */

    /* Overload Error */
    #if (CAN_OVERLOAD && (CAN_OVERLOAD_USE_HELPER || \
        (!CAN_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_INT_SR_REG.byte[0u] & CAN_OVERLOAD_ERROR_MASK) != 0u)
        {
            CAN_OvrLdErrorIsr();
        }
    #endif /* CAN_OVERLOAD && CAN_OVERLOAD_USE_HELPER */

    /* Bit Error */
    #if (CAN_BIT_ERR && (CAN_BIT_ERR_USE_HELPER || \
        (!CAN_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_INT_SR_REG.byte[0u] & CAN_BIT_ERROR_MASK) != 0u)
        {
            CAN_BitErrorIsr();
        }
    #endif /* CAN_BIT_ERR && CAN_BIT_ERR_USE_HELPER */

    /* Bit Staff Error */
    #if (CAN_STUFF_ERR && (CAN_STUFF_ERR_USE_HELPER || \
        (!CAN_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_INT_SR_REG.byte[0u] & CAN_STUFF_ERROR_MASK) != 0u)
        {
            CAN_BitStuffErrorIsr();
        }
    #endif /* CAN_STUFF_ERR && CAN_STUFF_ERR_USE_HELPER */

    /* ACK Error */
    #if (CAN_ACK_ERR && (CAN_ACK_ERR_USE_HELPER || \
        (!CAN_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_INT_SR_REG.byte[0u] & CAN_ACK_ERROR_MASK) != 0u)
        {
            CAN_AckErrorIsr();
        }
    #endif /* CAN_ACK_ERR && CAN_ACK_ERR_USE_HELPER */

    /* Form(msg) Error */
    #if (CAN_FORM_ERR && (CAN_FORM_ERR_USE_HELPER || \
        (!CAN_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_INT_SR_REG.byte[0u] & CAN_FORM_ERROR_MASK) != 0u)
        {
            CAN_MsgErrorIsr();
        }
    #endif /* CAN_FORM_ERR && CAN_FORM_ERR_USE_HELPER */

    /* CRC Error */
    #if (CAN_CRC_ERR && (CAN_CRC_ERR_USE_HELPER || \
        (!CAN_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_INT_SR_REG.byte[1u] & CAN_CRC_ERROR_MASK) != 0u)
        {
            CAN_CrcErrorIsr();
        }
    #endif /* CAN_CRC_ERR && CAN_CRC_ERR_USE_HELPER */

    /* Bus Off state */
    #if (CAN_BUS_OFF && (CAN_BUS_OFF_USE_HELPER || \
        (!CAN_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_INT_SR_REG.byte[1u] & CAN_BUS_OFF_MASK) != 0u)
        {
            CAN_BusOffIsr();
        }
    #endif /* CAN_BUS_OFF && CAN_BUS_OFF_USE_HELPER */

    /* Message Lost */
    #if (CAN_RX_MSG_LOST && (CAN_RX_MSG_LOST_USE_HELPER || \
        (!CAN_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_INT_SR_REG.byte[1u] & CAN_RX_MSG_LOST_MASK) != 0u)
        {
            CAN_MsgLostIsr();
        }
    #endif /* CAN_RX_MSG_LOST && CAN_RX_MSG_LOST_USE_HELPER */

    /* TX Message Send */
    #if (CAN_TX_MESSAGE && (CAN_TX_MESSAGE_USE_HELPER || \
        (!CAN_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_INT_SR_REG.byte[1u] & CAN_TX_MESSAGE_MASK) != 0u)
        {
            CAN_MsgTXIsr();
        }
    #endif /* CAN_TX_MESSAGE && CAN_TX_MESSAGE_USE_HELPER */

    /* RX Message Available */
    #if (CAN_RX_MESSAGE && (CAN_RX_MESSAGE_USE_HELPER || \
        (!CAN_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_INT_SR_REG.byte[1u] & CAN_RX_MESSAGE_MASK) != 0u)
        {
            CAN_MsgRXIsr();
        }
    #endif /* CAN_RX_MESSAGE && CAN_RX_MESSAGE_USE_HELPER */
}


/* [] END OF FILE */
