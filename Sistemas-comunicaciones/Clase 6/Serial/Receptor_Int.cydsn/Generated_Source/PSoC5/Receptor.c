/*******************************************************************************
* File Name: Receptor.c
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

#include "Receptor.h"
#if (Receptor_INTERNAL_CLOCK_USED)
    #include "Receptor_IntClock.h"
#endif /* End Receptor_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 Receptor_initVar = 0u;

#if (Receptor_TX_INTERRUPT_ENABLED && Receptor_TX_ENABLED)
    volatile uint8 Receptor_txBuffer[Receptor_TX_BUFFER_SIZE];
    volatile uint8 Receptor_txBufferRead = 0u;
    uint8 Receptor_txBufferWrite = 0u;
#endif /* (Receptor_TX_INTERRUPT_ENABLED && Receptor_TX_ENABLED) */

#if (Receptor_RX_INTERRUPT_ENABLED && (Receptor_RX_ENABLED || Receptor_HD_ENABLED))
    uint8 Receptor_errorStatus = 0u;
    volatile uint8 Receptor_rxBuffer[Receptor_RX_BUFFER_SIZE];
    volatile uint8 Receptor_rxBufferRead  = 0u;
    volatile uint8 Receptor_rxBufferWrite = 0u;
    volatile uint8 Receptor_rxBufferLoopDetect = 0u;
    volatile uint8 Receptor_rxBufferOverflow   = 0u;
    #if (Receptor_RXHW_ADDRESS_ENABLED)
        volatile uint8 Receptor_rxAddressMode = Receptor_RX_ADDRESS_MODE;
        volatile uint8 Receptor_rxAddressDetected = 0u;
    #endif /* (Receptor_RXHW_ADDRESS_ENABLED) */
#endif /* (Receptor_RX_INTERRUPT_ENABLED && (Receptor_RX_ENABLED || Receptor_HD_ENABLED)) */


/*******************************************************************************
* Function Name: Receptor_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  Receptor_Start() sets the initVar variable, calls the
*  Receptor_Init() function, and then calls the
*  Receptor_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The Receptor_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time Receptor_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the Receptor_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Receptor_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(Receptor_initVar == 0u)
    {
        Receptor_Init();
        Receptor_initVar = 1u;
    }

    Receptor_Enable();
}


/*******************************************************************************
* Function Name: Receptor_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call Receptor_Init() because
*  the Receptor_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Receptor_Init(void) 
{
    #if(Receptor_RX_ENABLED || Receptor_HD_ENABLED)

        #if (Receptor_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(Receptor_RX_VECT_NUM, &Receptor_RXISR);
            CyIntSetPriority(Receptor_RX_VECT_NUM, Receptor_RX_PRIOR_NUM);
            Receptor_errorStatus = 0u;
        #endif /* (Receptor_RX_INTERRUPT_ENABLED) */

        #if (Receptor_RXHW_ADDRESS_ENABLED)
            Receptor_SetRxAddressMode(Receptor_RX_ADDRESS_MODE);
            Receptor_SetRxAddress1(Receptor_RX_HW_ADDRESS1);
            Receptor_SetRxAddress2(Receptor_RX_HW_ADDRESS2);
        #endif /* End Receptor_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        Receptor_RXBITCTR_PERIOD_REG = Receptor_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        Receptor_RXSTATUS_MASK_REG  = Receptor_INIT_RX_INTERRUPTS_MASK;
    #endif /* End Receptor_RX_ENABLED || Receptor_HD_ENABLED*/

    #if(Receptor_TX_ENABLED)
        #if (Receptor_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(Receptor_TX_VECT_NUM, &Receptor_TXISR);
            CyIntSetPriority(Receptor_TX_VECT_NUM, Receptor_TX_PRIOR_NUM);
        #endif /* (Receptor_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (Receptor_TXCLKGEN_DP)
            Receptor_TXBITCLKGEN_CTR_REG = Receptor_BIT_CENTER;
            Receptor_TXBITCLKTX_COMPLETE_REG = ((Receptor_NUMBER_OF_DATA_BITS +
                        Receptor_NUMBER_OF_START_BIT) * Receptor_OVER_SAMPLE_COUNT) - 1u;
        #else
            Receptor_TXBITCTR_PERIOD_REG = ((Receptor_NUMBER_OF_DATA_BITS +
                        Receptor_NUMBER_OF_START_BIT) * Receptor_OVER_SAMPLE_8) - 1u;
        #endif /* End Receptor_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (Receptor_TX_INTERRUPT_ENABLED)
            Receptor_TXSTATUS_MASK_REG = Receptor_TX_STS_FIFO_EMPTY;
        #else
            Receptor_TXSTATUS_MASK_REG = Receptor_INIT_TX_INTERRUPTS_MASK;
        #endif /*End Receptor_TX_INTERRUPT_ENABLED*/

    #endif /* End Receptor_TX_ENABLED */

    #if(Receptor_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        Receptor_WriteControlRegister( \
            (Receptor_ReadControlRegister() & (uint8)~Receptor_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(Receptor_PARITY_TYPE << Receptor_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End Receptor_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: Receptor_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call Receptor_Enable() because the Receptor_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Receptor_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void Receptor_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (Receptor_RX_ENABLED || Receptor_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        Receptor_RXBITCTR_CONTROL_REG |= Receptor_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        Receptor_RXSTATUS_ACTL_REG  |= Receptor_INT_ENABLE;

        #if (Receptor_RX_INTERRUPT_ENABLED)
            Receptor_EnableRxInt();

            #if (Receptor_RXHW_ADDRESS_ENABLED)
                Receptor_rxAddressDetected = 0u;
            #endif /* (Receptor_RXHW_ADDRESS_ENABLED) */
        #endif /* (Receptor_RX_INTERRUPT_ENABLED) */
    #endif /* (Receptor_RX_ENABLED || Receptor_HD_ENABLED) */

    #if(Receptor_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!Receptor_TXCLKGEN_DP)
            Receptor_TXBITCTR_CONTROL_REG |= Receptor_CNTR_ENABLE;
        #endif /* End Receptor_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        Receptor_TXSTATUS_ACTL_REG |= Receptor_INT_ENABLE;
        #if (Receptor_TX_INTERRUPT_ENABLED)
            Receptor_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            Receptor_EnableTxInt();
        #endif /* (Receptor_TX_INTERRUPT_ENABLED) */
     #endif /* (Receptor_TX_INTERRUPT_ENABLED) */

    #if (Receptor_INTERNAL_CLOCK_USED)
        Receptor_IntClock_Start();  /* Enable the clock */
    #endif /* (Receptor_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Receptor_Stop
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
void Receptor_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (Receptor_RX_ENABLED || Receptor_HD_ENABLED)
        Receptor_RXBITCTR_CONTROL_REG &= (uint8) ~Receptor_CNTR_ENABLE;
    #endif /* (Receptor_RX_ENABLED || Receptor_HD_ENABLED) */

    #if (Receptor_TX_ENABLED)
        #if(!Receptor_TXCLKGEN_DP)
            Receptor_TXBITCTR_CONTROL_REG &= (uint8) ~Receptor_CNTR_ENABLE;
        #endif /* (!Receptor_TXCLKGEN_DP) */
    #endif /* (Receptor_TX_ENABLED) */

    #if (Receptor_INTERNAL_CLOCK_USED)
        Receptor_IntClock_Stop();   /* Disable the clock */
    #endif /* (Receptor_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (Receptor_RX_ENABLED || Receptor_HD_ENABLED)
        Receptor_RXSTATUS_ACTL_REG  &= (uint8) ~Receptor_INT_ENABLE;

        #if (Receptor_RX_INTERRUPT_ENABLED)
            Receptor_DisableRxInt();
        #endif /* (Receptor_RX_INTERRUPT_ENABLED) */
    #endif /* (Receptor_RX_ENABLED || Receptor_HD_ENABLED) */

    #if (Receptor_TX_ENABLED)
        Receptor_TXSTATUS_ACTL_REG &= (uint8) ~Receptor_INT_ENABLE;

        #if (Receptor_TX_INTERRUPT_ENABLED)
            Receptor_DisableTxInt();
        #endif /* (Receptor_TX_INTERRUPT_ENABLED) */
    #endif /* (Receptor_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Receptor_ReadControlRegister
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
uint8 Receptor_ReadControlRegister(void) 
{
    #if (Receptor_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(Receptor_CONTROL_REG);
    #endif /* (Receptor_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: Receptor_WriteControlRegister
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
void  Receptor_WriteControlRegister(uint8 control) 
{
    #if (Receptor_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       Receptor_CONTROL_REG = control;
    #endif /* (Receptor_CONTROL_REG_REMOVED) */
}


#if(Receptor_RX_ENABLED || Receptor_HD_ENABLED)
    /*******************************************************************************
    * Function Name: Receptor_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      Receptor_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      Receptor_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      Receptor_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      Receptor_RX_STS_BREAK            Interrupt on break.
    *      Receptor_RX_STS_OVERRUN          Interrupt on overrun error.
    *      Receptor_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      Receptor_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void Receptor_SetRxInterruptMode(uint8 intSrc) 
    {
        Receptor_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: Receptor_ReadRxData
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
    *  Receptor_rxBuffer - RAM buffer pointer for save received data.
    *  Receptor_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  Receptor_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  Receptor_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 Receptor_ReadRxData(void) 
    {
        uint8 rxData;

    #if (Receptor_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        Receptor_DisableRxInt();

        locRxBufferRead  = Receptor_rxBufferRead;
        locRxBufferWrite = Receptor_rxBufferWrite;

        if( (Receptor_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = Receptor_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= Receptor_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            Receptor_rxBufferRead = locRxBufferRead;

            if(Receptor_rxBufferLoopDetect != 0u)
            {
                Receptor_rxBufferLoopDetect = 0u;
                #if ((Receptor_RX_INTERRUPT_ENABLED) && (Receptor_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( Receptor_HD_ENABLED )
                        if((Receptor_CONTROL_REG & Receptor_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            Receptor_RXSTATUS_MASK_REG  |= Receptor_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        Receptor_RXSTATUS_MASK_REG  |= Receptor_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end Receptor_HD_ENABLED */
                #endif /* ((Receptor_RX_INTERRUPT_ENABLED) && (Receptor_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = Receptor_RXDATA_REG;
        }

        Receptor_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = Receptor_RXDATA_REG;

    #endif /* (Receptor_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: Receptor_ReadRxStatus
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
    *  Receptor_RX_STS_FIFO_NOTEMPTY.
    *  Receptor_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  Receptor_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   Receptor_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   Receptor_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 Receptor_ReadRxStatus(void) 
    {
        uint8 status;

        status = Receptor_RXSTATUS_REG & Receptor_RX_HW_MASK;

    #if (Receptor_RX_INTERRUPT_ENABLED)
        if(Receptor_rxBufferOverflow != 0u)
        {
            status |= Receptor_RX_STS_SOFT_BUFF_OVER;
            Receptor_rxBufferOverflow = 0u;
        }
    #endif /* (Receptor_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: Receptor_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. Receptor_GetChar() is
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
    *  Receptor_rxBuffer - RAM buffer pointer for save received data.
    *  Receptor_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  Receptor_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  Receptor_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 Receptor_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (Receptor_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        Receptor_DisableRxInt();

        locRxBufferRead  = Receptor_rxBufferRead;
        locRxBufferWrite = Receptor_rxBufferWrite;

        if( (Receptor_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = Receptor_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= Receptor_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            Receptor_rxBufferRead = locRxBufferRead;

            if(Receptor_rxBufferLoopDetect != 0u)
            {
                Receptor_rxBufferLoopDetect = 0u;
                #if( (Receptor_RX_INTERRUPT_ENABLED) && (Receptor_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( Receptor_HD_ENABLED )
                        if((Receptor_CONTROL_REG & Receptor_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            Receptor_RXSTATUS_MASK_REG |= Receptor_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        Receptor_RXSTATUS_MASK_REG |= Receptor_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end Receptor_HD_ENABLED */
                #endif /* Receptor_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = Receptor_RXSTATUS_REG;
            if((rxStatus & Receptor_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = Receptor_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (Receptor_RX_STS_BREAK | Receptor_RX_STS_PAR_ERROR |
                                Receptor_RX_STS_STOP_ERROR | Receptor_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        Receptor_EnableRxInt();

    #else

        rxStatus =Receptor_RXSTATUS_REG;
        if((rxStatus & Receptor_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = Receptor_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (Receptor_RX_STS_BREAK | Receptor_RX_STS_PAR_ERROR |
                            Receptor_RX_STS_STOP_ERROR | Receptor_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (Receptor_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: Receptor_GetByte
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
    uint16 Receptor_GetByte(void) 
    {
        
    #if (Receptor_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        Receptor_DisableRxInt();
        locErrorStatus = (uint16)Receptor_errorStatus;
        Receptor_errorStatus = 0u;
        Receptor_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | Receptor_ReadRxData() );
    #else
        return ( ((uint16)Receptor_ReadRxStatus() << 8u) | Receptor_ReadRxData() );
    #endif /* Receptor_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: Receptor_GetRxBufferSize
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
    *  Receptor_rxBufferWrite - used to calculate left bytes.
    *  Receptor_rxBufferRead - used to calculate left bytes.
    *  Receptor_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 Receptor_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (Receptor_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        Receptor_DisableRxInt();

        if(Receptor_rxBufferRead == Receptor_rxBufferWrite)
        {
            if(Receptor_rxBufferLoopDetect != 0u)
            {
                size = Receptor_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(Receptor_rxBufferRead < Receptor_rxBufferWrite)
        {
            size = (Receptor_rxBufferWrite - Receptor_rxBufferRead);
        }
        else
        {
            size = (Receptor_RX_BUFFER_SIZE - Receptor_rxBufferRead) + Receptor_rxBufferWrite;
        }

        Receptor_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((Receptor_RXSTATUS_REG & Receptor_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (Receptor_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: Receptor_ClearRxBuffer
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
    *  Receptor_rxBufferWrite - cleared to zero.
    *  Receptor_rxBufferRead - cleared to zero.
    *  Receptor_rxBufferLoopDetect - cleared to zero.
    *  Receptor_rxBufferOverflow - cleared to zero.
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
    void Receptor_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        Receptor_RXDATA_AUX_CTL_REG |= (uint8)  Receptor_RX_FIFO_CLR;
        Receptor_RXDATA_AUX_CTL_REG &= (uint8) ~Receptor_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (Receptor_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        Receptor_DisableRxInt();

        Receptor_rxBufferRead = 0u;
        Receptor_rxBufferWrite = 0u;
        Receptor_rxBufferLoopDetect = 0u;
        Receptor_rxBufferOverflow = 0u;

        Receptor_EnableRxInt();

    #endif /* (Receptor_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: Receptor_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  Receptor__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  Receptor__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  Receptor__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  Receptor__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  Receptor__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Receptor_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  Receptor_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void Receptor_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(Receptor_RXHW_ADDRESS_ENABLED)
            #if(Receptor_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* Receptor_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = Receptor_CONTROL_REG & (uint8)~Receptor_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << Receptor_CTRL_RXADDR_MODE0_SHIFT);
                Receptor_CONTROL_REG = tmpCtrl;

                #if(Receptor_RX_INTERRUPT_ENABLED && \
                   (Receptor_RXBUFFERSIZE > Receptor_FIFO_LENGTH) )
                    Receptor_rxAddressMode = addressMode;
                    Receptor_rxAddressDetected = 0u;
                #endif /* End Receptor_RXBUFFERSIZE > Receptor_FIFO_LENGTH*/
            #endif /* End Receptor_CONTROL_REG_REMOVED */
        #else /* Receptor_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End Receptor_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: Receptor_SetRxAddress1
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
    void Receptor_SetRxAddress1(uint8 address) 
    {
        Receptor_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: Receptor_SetRxAddress2
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
    void Receptor_SetRxAddress2(uint8 address) 
    {
        Receptor_RXADDRESS2_REG = address;
    }

#endif  /* Receptor_RX_ENABLED || Receptor_HD_ENABLED*/


#if( (Receptor_TX_ENABLED) || (Receptor_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: Receptor_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   Receptor_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   Receptor_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   Receptor_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   Receptor_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void Receptor_SetTxInterruptMode(uint8 intSrc) 
    {
        Receptor_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: Receptor_WriteTxData
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
    *  Receptor_txBuffer - RAM buffer pointer for save data for transmission
    *  Receptor_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  Receptor_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  Receptor_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void Receptor_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(Receptor_initVar != 0u)
        {
        #if (Receptor_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            Receptor_DisableTxInt();

            if( (Receptor_txBufferRead == Receptor_txBufferWrite) &&
                ((Receptor_TXSTATUS_REG & Receptor_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                Receptor_TXDATA_REG = txDataByte;
            }
            else
            {
                if(Receptor_txBufferWrite >= Receptor_TX_BUFFER_SIZE)
                {
                    Receptor_txBufferWrite = 0u;
                }

                Receptor_txBuffer[Receptor_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                Receptor_txBufferWrite++;
            }

            Receptor_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            Receptor_TXDATA_REG = txDataByte;

        #endif /*(Receptor_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: Receptor_ReadTxStatus
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
    uint8 Receptor_ReadTxStatus(void) 
    {
        return(Receptor_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: Receptor_PutChar
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
    *  Receptor_txBuffer - RAM buffer pointer for save data for transmission
    *  Receptor_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  Receptor_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  Receptor_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void Receptor_PutChar(uint8 txDataByte) 
    {
    #if (Receptor_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((Receptor_TX_BUFFER_SIZE > Receptor_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            Receptor_DisableTxInt();
        #endif /* (Receptor_TX_BUFFER_SIZE > Receptor_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = Receptor_txBufferWrite;
            locTxBufferRead  = Receptor_txBufferRead;

        #if ((Receptor_TX_BUFFER_SIZE > Receptor_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            Receptor_EnableTxInt();
        #endif /* (Receptor_TX_BUFFER_SIZE > Receptor_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(Receptor_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((Receptor_TXSTATUS_REG & Receptor_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            Receptor_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= Receptor_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            Receptor_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((Receptor_TX_BUFFER_SIZE > Receptor_MAX_BYTE_VALUE) && (CY_PSOC3))
            Receptor_DisableTxInt();
        #endif /* (Receptor_TX_BUFFER_SIZE > Receptor_MAX_BYTE_VALUE) && (CY_PSOC3) */

            Receptor_txBufferWrite = locTxBufferWrite;

        #if ((Receptor_TX_BUFFER_SIZE > Receptor_MAX_BYTE_VALUE) && (CY_PSOC3))
            Receptor_EnableTxInt();
        #endif /* (Receptor_TX_BUFFER_SIZE > Receptor_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (Receptor_TXSTATUS_REG & Receptor_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                Receptor_SetPendingTxInt();
            }
        }

    #else

        while((Receptor_TXSTATUS_REG & Receptor_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        Receptor_TXDATA_REG = txDataByte;

    #endif /* Receptor_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: Receptor_PutString
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
    *  Receptor_initVar - checked to identify that the component has been
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
    void Receptor_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(Receptor_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                Receptor_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: Receptor_PutArray
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
    *  Receptor_initVar - checked to identify that the component has been
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
    void Receptor_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(Receptor_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                Receptor_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: Receptor_PutCRLF
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
    *  Receptor_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void Receptor_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(Receptor_initVar != 0u)
        {
            Receptor_PutChar(txDataByte);
            Receptor_PutChar(0x0Du);
            Receptor_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: Receptor_GetTxBufferSize
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
    *  Receptor_txBufferWrite - used to calculate left space.
    *  Receptor_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 Receptor_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (Receptor_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        Receptor_DisableTxInt();

        if(Receptor_txBufferRead == Receptor_txBufferWrite)
        {
            size = 0u;
        }
        else if(Receptor_txBufferRead < Receptor_txBufferWrite)
        {
            size = (Receptor_txBufferWrite - Receptor_txBufferRead);
        }
        else
        {
            size = (Receptor_TX_BUFFER_SIZE - Receptor_txBufferRead) +
                    Receptor_txBufferWrite;
        }

        Receptor_EnableTxInt();

    #else

        size = Receptor_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & Receptor_TX_STS_FIFO_FULL) != 0u)
        {
            size = Receptor_FIFO_LENGTH;
        }
        else if((size & Receptor_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (Receptor_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: Receptor_ClearTxBuffer
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
    *  Receptor_txBufferWrite - cleared to zero.
    *  Receptor_txBufferRead - cleared to zero.
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
    void Receptor_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        Receptor_TXDATA_AUX_CTL_REG |= (uint8)  Receptor_TX_FIFO_CLR;
        Receptor_TXDATA_AUX_CTL_REG &= (uint8) ~Receptor_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (Receptor_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        Receptor_DisableTxInt();

        Receptor_txBufferRead = 0u;
        Receptor_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        Receptor_EnableTxInt();

    #endif /* (Receptor_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: Receptor_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   Receptor_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   Receptor_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   Receptor_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   Receptor_SEND_WAIT_REINIT - Performs both options: 
    *      Receptor_SEND_BREAK and Receptor_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Receptor_initVar - checked to identify that the component has been
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
    *     When interrupt appear with Receptor_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The Receptor_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void Receptor_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(Receptor_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(Receptor_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == Receptor_SEND_BREAK) ||
                (retMode == Receptor_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                Receptor_WriteControlRegister(Receptor_ReadControlRegister() |
                                                      Receptor_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                Receptor_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = Receptor_TXSTATUS_REG;
                }
                while((tmpStat & Receptor_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == Receptor_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Receptor_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = Receptor_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & Receptor_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == Receptor_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Receptor_REINIT) ||
                (retMode == Receptor_SEND_WAIT_REINIT) )
            {
                Receptor_WriteControlRegister(Receptor_ReadControlRegister() &
                                              (uint8)~Receptor_CTRL_HD_SEND_BREAK);
            }

        #else /* Receptor_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == Receptor_SEND_BREAK) ||
                (retMode == Receptor_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (Receptor_PARITY_TYPE != Receptor__B_UART__NONE_REVB) || \
                                    (Receptor_PARITY_TYPE_SW != 0u) )
                    Receptor_WriteControlRegister(Receptor_ReadControlRegister() |
                                                          Receptor_CTRL_HD_SEND_BREAK);
                #endif /* End Receptor_PARITY_TYPE != Receptor__B_UART__NONE_REVB  */

                #if(Receptor_TXCLKGEN_DP)
                    txPeriod = Receptor_TXBITCLKTX_COMPLETE_REG;
                    Receptor_TXBITCLKTX_COMPLETE_REG = Receptor_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = Receptor_TXBITCTR_PERIOD_REG;
                    Receptor_TXBITCTR_PERIOD_REG = Receptor_TXBITCTR_BREAKBITS8X;
                #endif /* End Receptor_TXCLKGEN_DP */

                /* Send zeros */
                Receptor_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = Receptor_TXSTATUS_REG;
                }
                while((tmpStat & Receptor_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == Receptor_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Receptor_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = Receptor_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & Receptor_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == Receptor_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == Receptor_REINIT) ||
                (retMode == Receptor_SEND_WAIT_REINIT) )
            {

            #if(Receptor_TXCLKGEN_DP)
                Receptor_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                Receptor_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End Receptor_TXCLKGEN_DP */

            #if( (Receptor_PARITY_TYPE != Receptor__B_UART__NONE_REVB) || \
                 (Receptor_PARITY_TYPE_SW != 0u) )
                Receptor_WriteControlRegister(Receptor_ReadControlRegister() &
                                                      (uint8) ~Receptor_CTRL_HD_SEND_BREAK);
            #endif /* End Receptor_PARITY_TYPE != NONE */
            }
        #endif    /* End Receptor_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: Receptor_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       Receptor_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       Receptor_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears Receptor_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void Receptor_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( Receptor_CONTROL_REG_REMOVED == 0u )
            Receptor_WriteControlRegister(Receptor_ReadControlRegister() |
                                                  Receptor_CTRL_MARK);
        #endif /* End Receptor_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( Receptor_CONTROL_REG_REMOVED == 0u )
            Receptor_WriteControlRegister(Receptor_ReadControlRegister() &
                                                  (uint8) ~Receptor_CTRL_MARK);
        #endif /* End Receptor_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndReceptor_TX_ENABLED */

#if(Receptor_HD_ENABLED)


    /*******************************************************************************
    * Function Name: Receptor_LoadRxConfig
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
    void Receptor_LoadRxConfig(void) 
    {
        Receptor_WriteControlRegister(Receptor_ReadControlRegister() &
                                                (uint8)~Receptor_CTRL_HD_SEND);
        Receptor_RXBITCTR_PERIOD_REG = Receptor_HD_RXBITCTR_INIT;

    #if (Receptor_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        Receptor_SetRxInterruptMode(Receptor_INIT_RX_INTERRUPTS_MASK);
    #endif /* (Receptor_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: Receptor_LoadTxConfig
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
    void Receptor_LoadTxConfig(void) 
    {
    #if (Receptor_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        Receptor_SetRxInterruptMode(0u);
    #endif /* (Receptor_RX_INTERRUPT_ENABLED) */

        Receptor_WriteControlRegister(Receptor_ReadControlRegister() | Receptor_CTRL_HD_SEND);
        Receptor_RXBITCTR_PERIOD_REG = Receptor_HD_TXBITCTR_INIT;
    }

#endif  /* Receptor_HD_ENABLED */


/* [] END OF FILE */
