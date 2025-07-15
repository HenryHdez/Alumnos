/*******************************************************************************
* File Name: Emisor.c
* Version 2.50
*
* Description:
*  This file provides all API functionality of the UART component
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
#if (Emisor_INTERNAL_CLOCK_USED)
    #include "Emisor_IntClock.h"
#endif /* End Emisor_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 Emisor_initVar = 0u;

#if (Emisor_TX_INTERRUPT_ENABLED && Emisor_TX_ENABLED)
    volatile uint8 Emisor_txBuffer[Emisor_TX_BUFFER_SIZE];
    volatile uint8 Emisor_txBufferRead = 0u;
    uint8 Emisor_txBufferWrite = 0u;
#endif /* (Emisor_TX_INTERRUPT_ENABLED && Emisor_TX_ENABLED) */

#if (Emisor_RX_INTERRUPT_ENABLED && (Emisor_RX_ENABLED || Emisor_HD_ENABLED))
    uint8 Emisor_errorStatus = 0u;
    volatile uint8 Emisor_rxBuffer[Emisor_RX_BUFFER_SIZE];
    volatile uint8 Emisor_rxBufferRead  = 0u;
    volatile uint8 Emisor_rxBufferWrite = 0u;
    volatile uint8 Emisor_rxBufferLoopDetect = 0u;
    volatile uint8 Emisor_rxBufferOverflow   = 0u;
    #if (Emisor_RXHW_ADDRESS_ENABLED)
        volatile uint8 Emisor_rxAddressMode = Emisor_RX_ADDRESS_MODE;
        volatile uint8 Emisor_rxAddressDetected = 0u;
    #endif /* (Emisor_RXHW_ADDRESS_ENABLED) */
#endif /* (Emisor_RX_INTERRUPT_ENABLED && (Emisor_RX_ENABLED || Emisor_HD_ENABLED)) */


/*******************************************************************************
* Function Name: Emisor_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  Emisor_Start() sets the initVar variable, calls the
*  Emisor_Init() function, and then calls the
*  Emisor_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The Emisor_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time Emisor_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the Emisor_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Emisor_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(Emisor_initVar == 0u)
    {
        Emisor_Init();
        Emisor_initVar = 1u;
    }

    Emisor_Enable();
}


/*******************************************************************************
* Function Name: Emisor_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call Emisor_Init() because
*  the Emisor_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Emisor_Init(void) 
{
    #if(Emisor_RX_ENABLED || Emisor_HD_ENABLED)

        #if (Emisor_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(Emisor_RX_VECT_NUM, &Emisor_RXISR);
            CyIntSetPriority(Emisor_RX_VECT_NUM, Emisor_RX_PRIOR_NUM);
            Emisor_errorStatus = 0u;
        #endif /* (Emisor_RX_INTERRUPT_ENABLED) */

        #if (Emisor_RXHW_ADDRESS_ENABLED)
            Emisor_SetRxAddressMode(Emisor_RX_ADDRESS_MODE);
            Emisor_SetRxAddress1(Emisor_RX_HW_ADDRESS1);
            Emisor_SetRxAddress2(Emisor_RX_HW_ADDRESS2);
        #endif /* End Emisor_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        Emisor_RXBITCTR_PERIOD_REG = Emisor_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        Emisor_RXSTATUS_MASK_REG  = Emisor_INIT_RX_INTERRUPTS_MASK;
    #endif /* End Emisor_RX_ENABLED || Emisor_HD_ENABLED*/

    #if(Emisor_TX_ENABLED)
        #if (Emisor_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(Emisor_TX_VECT_NUM, &Emisor_TXISR);
            CyIntSetPriority(Emisor_TX_VECT_NUM, Emisor_TX_PRIOR_NUM);
        #endif /* (Emisor_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (Emisor_TXCLKGEN_DP)
            Emisor_TXBITCLKGEN_CTR_REG = Emisor_BIT_CENTER;
            Emisor_TXBITCLKTX_COMPLETE_REG = ((Emisor_NUMBER_OF_DATA_BITS +
                        Emisor_NUMBER_OF_START_BIT) * Emisor_OVER_SAMPLE_COUNT) - 1u;
        #else
            Emisor_TXBITCTR_PERIOD_REG = ((Emisor_NUMBER_OF_DATA_BITS +
                        Emisor_NUMBER_OF_START_BIT) * Emisor_OVER_SAMPLE_8) - 1u;
        #endif /* End Emisor_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (Emisor_TX_INTERRUPT_ENABLED)
            Emisor_TXSTATUS_MASK_REG = Emisor_TX_STS_FIFO_EMPTY;
        #else
            Emisor_TXSTATUS_MASK_REG = Emisor_INIT_TX_INTERRUPTS_MASK;
        #endif /*End Emisor_TX_INTERRUPT_ENABLED*/

    #endif /* End Emisor_TX_ENABLED */

    #if(Emisor_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        Emisor_WriteControlRegister( \
            (Emisor_ReadControlRegister() & (uint8)~Emisor_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(Emisor_PARITY_TYPE << Emisor_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End Emisor_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: Emisor_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call Emisor_Enable() because the Emisor_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Emisor_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void Emisor_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (Emisor_RX_ENABLED || Emisor_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        Emisor_RXBITCTR_CONTROL_REG |= Emisor_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        Emisor_RXSTATUS_ACTL_REG  |= Emisor_INT_ENABLE;

        #if (Emisor_RX_INTERRUPT_ENABLED)
            Emisor_EnableRxInt();

            #if (Emisor_RXHW_ADDRESS_ENABLED)
                Emisor_rxAddressDetected = 0u;
            #endif /* (Emisor_RXHW_ADDRESS_ENABLED) */
        #endif /* (Emisor_RX_INTERRUPT_ENABLED) */
    #endif /* (Emisor_RX_ENABLED || Emisor_HD_ENABLED) */

    #if(Emisor_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!Emisor_TXCLKGEN_DP)
            Emisor_TXBITCTR_CONTROL_REG |= Emisor_CNTR_ENABLE;
        #endif /* End Emisor_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        Emisor_TXSTATUS_ACTL_REG |= Emisor_INT_ENABLE;
        #if (Emisor_TX_INTERRUPT_ENABLED)
            Emisor_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            Emisor_EnableTxInt();
        #endif /* (Emisor_TX_INTERRUPT_ENABLED) */
     #endif /* (Emisor_TX_INTERRUPT_ENABLED) */

    #if (Emisor_INTERNAL_CLOCK_USED)
        Emisor_IntClock_Start();  /* Enable the clock */
    #endif /* (Emisor_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Emisor_Stop
********************************************************************************
*
* Summary:
*  Disables the UART operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Emisor_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (Emisor_RX_ENABLED || Emisor_HD_ENABLED)
        Emisor_RXBITCTR_CONTROL_REG &= (uint8) ~Emisor_CNTR_ENABLE;
    #endif /* (Emisor_RX_ENABLED || Emisor_HD_ENABLED) */

    #if (Emisor_TX_ENABLED)
        #if(!Emisor_TXCLKGEN_DP)
            Emisor_TXBITCTR_CONTROL_REG &= (uint8) ~Emisor_CNTR_ENABLE;
        #endif /* (!Emisor_TXCLKGEN_DP) */
    #endif /* (Emisor_TX_ENABLED) */

    #if (Emisor_INTERNAL_CLOCK_USED)
        Emisor_IntClock_Stop();   /* Disable the clock */
    #endif /* (Emisor_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (Emisor_RX_ENABLED || Emisor_HD_ENABLED)
        Emisor_RXSTATUS_ACTL_REG  &= (uint8) ~Emisor_INT_ENABLE;

        #if (Emisor_RX_INTERRUPT_ENABLED)
            Emisor_DisableRxInt();
        #endif /* (Emisor_RX_INTERRUPT_ENABLED) */
    #endif /* (Emisor_RX_ENABLED || Emisor_HD_ENABLED) */

    #if (Emisor_TX_ENABLED)
        Emisor_TXSTATUS_ACTL_REG &= (uint8) ~Emisor_INT_ENABLE;

        #if (Emisor_TX_INTERRUPT_ENABLED)
            Emisor_DisableTxInt();
        #endif /* (Emisor_TX_INTERRUPT_ENABLED) */
    #endif /* (Emisor_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Emisor_ReadControlRegister
********************************************************************************
*
* Summary:
*  Returns the current value of the control register.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the control register.
*
*******************************************************************************/
uint8 Emisor_ReadControlRegister(void) 
{
    #if (Emisor_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(Emisor_CONTROL_REG);
    #endif /* (Emisor_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: Emisor_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  Emisor_WriteControlRegister(uint8 control) 
{
    #if (Emisor_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       Emisor_CONTROL_REG = control;
    #endif /* (Emisor_CONTROL_REG_REMOVED) */
}


#if(Emisor_RX_ENABLED || Emisor_HD_ENABLED)
    /*******************************************************************************
    * Function Name: Emisor_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      Emisor_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      Emisor_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      Emisor_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      Emisor_RX_STS_BREAK            Interrupt on break.
    *      Emisor_RX_STS_OVERRUN          Interrupt on overrun error.
    *      Emisor_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      Emisor_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void Emisor_SetRxInterruptMode(uint8 intSrc) 
    {
        Emisor_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: Emisor_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns the next byte of received data. This function returns data without
    *  checking the status. You must check the status separately.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  Emisor_rxBuffer - RAM buffer pointer for save received data.
    *  Emisor_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  Emisor_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  Emisor_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 Emisor_ReadRxData(void) 
    {
        uint8 rxData;

    #if (Emisor_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        Emisor_DisableRxInt();

        locRxBufferRead  = Emisor_rxBufferRead;
        locRxBufferWrite = Emisor_rxBufferWrite;

        if( (Emisor_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = Emisor_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= Emisor_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            Emisor_rxBufferRead = locRxBufferRead;

            if(Emisor_rxBufferLoopDetect != 0u)
            {
                Emisor_rxBufferLoopDetect = 0u;
                #if ((Emisor_RX_INTERRUPT_ENABLED) && (Emisor_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( Emisor_HD_ENABLED )
                        if((Emisor_CONTROL_REG & Emisor_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            Emisor_RXSTATUS_MASK_REG  |= Emisor_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        Emisor_RXSTATUS_MASK_REG  |= Emisor_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end Emisor_HD_ENABLED */
                #endif /* ((Emisor_RX_INTERRUPT_ENABLED) && (Emisor_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = Emisor_RXDATA_REG;
        }

        Emisor_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = Emisor_RXDATA_REG;

    #endif /* (Emisor_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: Emisor_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the receiver status register and the software
    *  buffer overflow status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Side Effect:
    *  All status register bits are clear-on-read except
    *  Emisor_RX_STS_FIFO_NOTEMPTY.
    *  Emisor_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  Emisor_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   Emisor_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   Emisor_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 Emisor_ReadRxStatus(void) 
    {
        uint8 status;

        status = Emisor_RXSTATUS_REG & Emisor_RX_HW_MASK;

    #if (Emisor_RX_INTERRUPT_ENABLED)
        if(Emisor_rxBufferOverflow != 0u)
        {
            status |= Emisor_RX_STS_SOFT_BUFF_OVER;
            Emisor_rxBufferOverflow = 0u;
        }
    #endif /* (Emisor_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: Emisor_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. Emisor_GetChar() is
    *  designed for ASCII characters and returns a uint8 where 1 to 255 are values
    *  for valid characters and 0 indicates an error occurred or no data is present.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  Emisor_rxBuffer - RAM buffer pointer for save received data.
    *  Emisor_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  Emisor_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  Emisor_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 Emisor_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (Emisor_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        Emisor_DisableRxInt();

        locRxBufferRead  = Emisor_rxBufferRead;
        locRxBufferWrite = Emisor_rxBufferWrite;

        if( (Emisor_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = Emisor_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= Emisor_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            Emisor_rxBufferRead = locRxBufferRead;

            if(Emisor_rxBufferLoopDetect != 0u)
            {
                Emisor_rxBufferLoopDetect = 0u;
                #if( (Emisor_RX_INTERRUPT_ENABLED) && (Emisor_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( Emisor_HD_ENABLED )
                        if((Emisor_CONTROL_REG & Emisor_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            Emisor_RXSTATUS_MASK_REG |= Emisor_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        Emisor_RXSTATUS_MASK_REG |= Emisor_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end Emisor_HD_ENABLED */
                #endif /* Emisor_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = Emisor_RXSTATUS_REG;
            if((rxStatus & Emisor_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = Emisor_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (Emisor_RX_STS_BREAK | Emisor_RX_STS_PAR_ERROR |
                                Emisor_RX_STS_STOP_ERROR | Emisor_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        Emisor_EnableRxInt();

    #else

        rxStatus =Emisor_RXSTATUS_REG;
        if((rxStatus & Emisor_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = Emisor_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (Emisor_RX_STS_BREAK | Emisor_RX_STS_PAR_ERROR |
                            Emisor_RX_STS_STOP_ERROR | Emisor_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (Emisor_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: Emisor_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, returns received character and error
    *  condition.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains status and LSB contains UART RX data. If the MSB is nonzero,
    *  an error has occurred.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 Emisor_GetByte(void) 
    {
        
    #if (Emisor_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        Emisor_DisableRxInt();
        locErrorStatus = (uint16)Emisor_errorStatus;
        Emisor_errorStatus = 0u;
        Emisor_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | Emisor_ReadRxData() );
    #else
        return ( ((uint16)Emisor_ReadRxStatus() << 8u) | Emisor_ReadRxData() );
    #endif /* Emisor_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: Emisor_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received bytes available in the RX buffer.
    *  * RX software buffer is disabled (RX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty RX FIFO or 1 for not empty RX FIFO.
    *  * RX software buffer is enabled: returns the number of bytes available in 
    *    the RX software buffer. Bytes available in the RX FIFO do not take to 
    *    account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Number of bytes in the RX buffer. 
    *    Return value type depends on RX Buffer Size parameter.
    *
    * Global Variables:
    *  Emisor_rxBufferWrite - used to calculate left bytes.
    *  Emisor_rxBufferRead - used to calculate left bytes.
    *  Emisor_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 Emisor_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (Emisor_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        Emisor_DisableRxInt();

        if(Emisor_rxBufferRead == Emisor_rxBufferWrite)
        {
            if(Emisor_rxBufferLoopDetect != 0u)
            {
                size = Emisor_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(Emisor_rxBufferRead < Emisor_rxBufferWrite)
        {
            size = (Emisor_rxBufferWrite - Emisor_rxBufferRead);
        }
        else
        {
            size = (Emisor_RX_BUFFER_SIZE - Emisor_rxBufferRead) + Emisor_rxBufferWrite;
        }

        Emisor_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((Emisor_RXSTATUS_REG & Emisor_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (Emisor_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: Emisor_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receiver memory buffer and hardware RX FIFO of all received data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Emisor_rxBufferWrite - cleared to zero.
    *  Emisor_rxBufferRead - cleared to zero.
    *  Emisor_rxBufferLoopDetect - cleared to zero.
    *  Emisor_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *
    *******************************************************************************/
    void Emisor_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        Emisor_RXDATA_AUX_CTL_REG |= (uint8)  Emisor_RX_FIFO_CLR;
        Emisor_RXDATA_AUX_CTL_REG &= (uint8) ~Emisor_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (Emisor_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        Emisor_DisableRxInt();

        Emisor_rxBufferRead = 0u;
        Emisor_rxBufferWrite = 0u;
        Emisor_rxBufferLoopDetect = 0u;
        Emisor_rxBufferOverflow = 0u;

        Emisor_EnableRxInt();

    #endif /* (Emisor_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: Emisor_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  Emisor__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  Emisor__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  Emisor__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  Emisor__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  Emisor__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Emisor_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  Emisor_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void Emisor_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(Emisor_RXHW_ADDRESS_ENABLED)
            #if(Emisor_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* Emisor_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = Emisor_CONTROL_REG & (uint8)~Emisor_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << Emisor_CTRL_RXADDR_MODE0_SHIFT);
                Emisor_CONTROL_REG = tmpCtrl;

                #if(Emisor_RX_INTERRUPT_ENABLED && \
                   (Emisor_RXBUFFERSIZE > Emisor_FIFO_LENGTH) )
                    Emisor_rxAddressMode = addressMode;
                    Emisor_rxAddressDetected = 0u;
                #endif /* End Emisor_RXBUFFERSIZE > Emisor_FIFO_LENGTH*/
            #endif /* End Emisor_CONTROL_REG_REMOVED */
        #else /* Emisor_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End Emisor_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: Emisor_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Sets the first of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #1 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void Emisor_SetRxAddress1(uint8 address) 
    {
        Emisor_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: Emisor_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the second of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #2 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void Emisor_SetRxAddress2(uint8 address) 
    {
        Emisor_RXADDRESS2_REG = address;
    }

#endif  /* Emisor_RX_ENABLED || Emisor_HD_ENABLED*/


#if( (Emisor_TX_ENABLED) || (Emisor_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: Emisor_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   Emisor_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   Emisor_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   Emisor_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   Emisor_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void Emisor_SetTxInterruptMode(uint8 intSrc) 
    {
        Emisor_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: Emisor_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data into the transmit buffer to be sent when the bus is
    *  available without checking the TX status register. You must check status
    *  separately.
    *
    * Parameters:
    *  txDataByte: data byte
    *
    * Return:
    * None.
    *
    * Global Variables:
    *  Emisor_txBuffer - RAM buffer pointer for save data for transmission
    *  Emisor_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  Emisor_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  Emisor_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void Emisor_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(Emisor_initVar != 0u)
        {
        #if (Emisor_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            Emisor_DisableTxInt();

            if( (Emisor_txBufferRead == Emisor_txBufferWrite) &&
                ((Emisor_TXSTATUS_REG & Emisor_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                Emisor_TXDATA_REG = txDataByte;
            }
            else
            {
                if(Emisor_txBufferWrite >= Emisor_TX_BUFFER_SIZE)
                {
                    Emisor_txBufferWrite = 0u;
                }

                Emisor_txBuffer[Emisor_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                Emisor_txBufferWrite++;
            }

            Emisor_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            Emisor_TXDATA_REG = txDataByte;

        #endif /*(Emisor_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: Emisor_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the status register for the TX portion of the UART.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the TX status register, which is cleared on read.
    *  It is up to the user to handle all bits in this return value accordingly,
    *  even if the bit was not enabled as an interrupt source the event happened
    *  and must be handled accordingly.
    *
    *******************************************************************************/
    uint8 Emisor_ReadTxStatus(void) 
    {
        return(Emisor_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: Emisor_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Puts a byte of data into the transmit buffer to be sent when the bus is
    *  available. This is a blocking API that waits until the TX buffer has room to
    *  hold the data.
    *
    * Parameters:
    *  txDataByte: Byte containing the data to transmit
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Emisor_txBuffer - RAM buffer pointer for save data for transmission
    *  Emisor_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  Emisor_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  Emisor_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void Emisor_PutChar(uint8 txDataByte) 
    {
    #if (Emisor_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((Emisor_TX_BUFFER_SIZE > Emisor_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            Emisor_DisableTxInt();
        #endif /* (Emisor_TX_BUFFER_SIZE > Emisor_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = Emisor_txBufferWrite;
            locTxBufferRead  = Emisor_txBufferRead;

        #if ((Emisor_TX_BUFFER_SIZE > Emisor_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            Emisor_EnableTxInt();
        #endif /* (Emisor_TX_BUFFER_SIZE > Emisor_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(Emisor_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((Emisor_TXSTATUS_REG & Emisor_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            Emisor_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= Emisor_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            Emisor_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((Emisor_TX_BUFFER_SIZE > Emisor_MAX_BYTE_VALUE) && (CY_PSOC3))
            Emisor_DisableTxInt();
        #endif /* (Emisor_TX_BUFFER_SIZE > Emisor_MAX_BYTE_VALUE) && (CY_PSOC3) */

            Emisor_txBufferWrite = locTxBufferWrite;

        #if ((Emisor_TX_BUFFER_SIZE > Emisor_MAX_BYTE_VALUE) && (CY_PSOC3))
            Emisor_EnableTxInt();
        #endif /* (Emisor_TX_BUFFER_SIZE > Emisor_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (Emisor_TXSTATUS_REG & Emisor_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                Emisor_SetPendingTxInt();
            }
        }

    #else

        while((Emisor_TXSTATUS_REG & Emisor_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        Emisor_TXDATA_REG = txDataByte;

    #endif /* Emisor_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: Emisor_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a NULL terminated string to the TX buffer for transmission.
    *
    * Parameters:
    *  string[]: Pointer to the null terminated string array residing in RAM or ROM
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Emisor_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void Emisor_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(Emisor_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                Emisor_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: Emisor_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Places N bytes of data from a memory array into the TX buffer for
    *  transmission.
    *
    * Parameters:
    *  string[]: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of bytes to be transmitted. The type depends on TX Buffer
    *             Size parameter.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Emisor_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void Emisor_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(Emisor_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                Emisor_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: Emisor_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Writes a byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) to the transmit buffer.
    *
    * Parameters:
    *  txDataByte: Data byte to transmit before the carriage return and line feed.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Emisor_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void Emisor_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(Emisor_initVar != 0u)
        {
            Emisor_PutChar(txDataByte);
            Emisor_PutChar(0x0Du);
            Emisor_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: Emisor_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of bytes in the TX buffer which are waiting to be 
    *  transmitted.
    *  * TX software buffer is disabled (TX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty TX FIFO, 1 for not full TX FIFO or 4 for full TX FIFO.
    *  * TX software buffer is enabled: returns the number of bytes in the TX 
    *    software buffer which are waiting to be transmitted. Bytes available in the
    *    TX FIFO do not count.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Number of bytes used in the TX buffer. Return value type depends on the TX 
    *  Buffer Size parameter.
    *
    * Global Variables:
    *  Emisor_txBufferWrite - used to calculate left space.
    *  Emisor_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 Emisor_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (Emisor_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        Emisor_DisableTxInt();

        if(Emisor_txBufferRead == Emisor_txBufferWrite)
        {
            size = 0u;
        }
        else if(Emisor_txBufferRead < Emisor_txBufferWrite)
        {
            size = (Emisor_txBufferWrite - Emisor_txBufferRead);
        }
        else
        {
            size = (Emisor_TX_BUFFER_SIZE - Emisor_txBufferRead) +
                    Emisor_txBufferWrite;
        }

        Emisor_EnableTxInt();

    #else

        size = Emisor_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & Emisor_TX_STS_FIFO_FULL) != 0u)
        {
            size = Emisor_FIFO_LENGTH;
        }
        else if((size & Emisor_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (Emisor_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: Emisor_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears all data from the TX buffer and hardware TX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Emisor_txBufferWrite - cleared to zero.
    *  Emisor_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Data waiting in the transmit buffer is not sent; a byte that is currently
    *  transmitting finishes transmitting.
    *
    *******************************************************************************/
    void Emisor_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        Emisor_TXDATA_AUX_CTL_REG |= (uint8)  Emisor_TX_FIFO_CLR;
        Emisor_TXDATA_AUX_CTL_REG &= (uint8) ~Emisor_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (Emisor_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        Emisor_DisableTxInt();

        Emisor_txBufferRead = 0u;
        Emisor_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        Emisor_EnableTxInt();

    #endif /* (Emisor_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: Emisor_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   Emisor_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   Emisor_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   Emisor_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   Emisor_SEND_WAIT_REINIT - Performs both options: 
    *      Emisor_SEND_BREAK and Emisor_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Emisor_initVar - checked to identify that the component has been
    *     initialized.
    *  txPeriod - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  There are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Function will block CPU until transmission
    *     complete.
    *  2) User may want to use blocking time if UART configured to the low speed
    *     operation
    *     Example for this case:
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to initialize and use the interrupt to
    *     complete break operation.
    *     Example for this case:
    *     Initialize TX interrupt with "TX - On TX Complete" parameter
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     When interrupt appear with Emisor_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The Emisor_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void Emisor_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(Emisor_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(Emisor_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == Emisor_SEND_BREAK) ||
                (retMode == Emisor_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                Emisor_WriteControlRegister(Emisor_ReadControlRegister() |
                                                      Emisor_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                Emisor_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = Emisor_TXSTATUS_REG;
                }
                while((tmpStat & Emisor_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == Emisor_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Emisor_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = Emisor_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & Emisor_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == Emisor_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Emisor_REINIT) ||
                (retMode == Emisor_SEND_WAIT_REINIT) )
            {
                Emisor_WriteControlRegister(Emisor_ReadControlRegister() &
                                              (uint8)~Emisor_CTRL_HD_SEND_BREAK);
            }

        #else /* Emisor_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == Emisor_SEND_BREAK) ||
                (retMode == Emisor_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (Emisor_PARITY_TYPE != Emisor__B_UART__NONE_REVB) || \
                                    (Emisor_PARITY_TYPE_SW != 0u) )
                    Emisor_WriteControlRegister(Emisor_ReadControlRegister() |
                                                          Emisor_CTRL_HD_SEND_BREAK);
                #endif /* End Emisor_PARITY_TYPE != Emisor__B_UART__NONE_REVB  */

                #if(Emisor_TXCLKGEN_DP)
                    txPeriod = Emisor_TXBITCLKTX_COMPLETE_REG;
                    Emisor_TXBITCLKTX_COMPLETE_REG = Emisor_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = Emisor_TXBITCTR_PERIOD_REG;
                    Emisor_TXBITCTR_PERIOD_REG = Emisor_TXBITCTR_BREAKBITS8X;
                #endif /* End Emisor_TXCLKGEN_DP */

                /* Send zeros */
                Emisor_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = Emisor_TXSTATUS_REG;
                }
                while((tmpStat & Emisor_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == Emisor_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Emisor_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = Emisor_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & Emisor_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == Emisor_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Emisor_REINIT) ||
                (retMode == Emisor_SEND_WAIT_REINIT) )
            {

            #if(Emisor_TXCLKGEN_DP)
                Emisor_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                Emisor_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End Emisor_TXCLKGEN_DP */

            #if( (Emisor_PARITY_TYPE != Emisor__B_UART__NONE_REVB) || \
                 (Emisor_PARITY_TYPE_SW != 0u) )
                Emisor_WriteControlRegister(Emisor_ReadControlRegister() &
                                                      (uint8) ~Emisor_CTRL_HD_SEND_BREAK);
            #endif /* End Emisor_PARITY_TYPE != NONE */
            }
        #endif    /* End Emisor_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: Emisor_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       Emisor_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       Emisor_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears Emisor_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void Emisor_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( Emisor_CONTROL_REG_REMOVED == 0u )
            Emisor_WriteControlRegister(Emisor_ReadControlRegister() |
                                                  Emisor_CTRL_MARK);
        #endif /* End Emisor_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( Emisor_CONTROL_REG_REMOVED == 0u )
            Emisor_WriteControlRegister(Emisor_ReadControlRegister() &
                                                  (uint8) ~Emisor_CTRL_MARK);
        #endif /* End Emisor_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndEmisor_TX_ENABLED */

#if(Emisor_HD_ENABLED)


    /*******************************************************************************
    * Function Name: Emisor_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the receiver configuration in half duplex mode. After calling this
    *  function, the UART is ready to receive data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the transmitter
    *  configuration.
    *
    *******************************************************************************/
    void Emisor_LoadRxConfig(void) 
    {
        Emisor_WriteControlRegister(Emisor_ReadControlRegister() &
                                                (uint8)~Emisor_CTRL_HD_SEND);
        Emisor_RXBITCTR_PERIOD_REG = Emisor_HD_RXBITCTR_INIT;

    #if (Emisor_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        Emisor_SetRxInterruptMode(Emisor_INIT_RX_INTERRUPTS_MASK);
    #endif /* (Emisor_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: Emisor_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the transmitter configuration in half duplex mode. After calling this
    *  function, the UART is ready to transmit data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the receiver configuration.
    *
    *******************************************************************************/
    void Emisor_LoadTxConfig(void) 
    {
    #if (Emisor_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        Emisor_SetRxInterruptMode(0u);
    #endif /* (Emisor_RX_INTERRUPT_ENABLED) */

        Emisor_WriteControlRegister(Emisor_ReadControlRegister() | Emisor_CTRL_HD_SEND);
        Emisor_RXBITCTR_PERIOD_REG = Emisor_HD_TXBITCTR_INIT;
    }

#endif  /* Emisor_HD_ENABLED */


/* [] END OF FILE */
