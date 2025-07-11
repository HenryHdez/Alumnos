/*******************************************************************************
* File Name: EmisorINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Emisor.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (Emisor_RX_INTERRUPT_ENABLED && (Emisor_RX_ENABLED || Emisor_HD_ENABLED))
    /*******************************************************************************
    * Function Name: Emisor_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Emisor_rxBuffer - RAM buffer pointer for save received data.
    *  Emisor_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  Emisor_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  Emisor_rxBufferOverflow - software overflow flag. Set to one
    *     when Emisor_rxBufferWrite index overtakes
    *     Emisor_rxBufferRead index.
    *  Emisor_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when Emisor_rxBufferWrite is equal to
    *    Emisor_rxBufferRead
    *  Emisor_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  Emisor_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(Emisor_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef Emisor_RXISR_ENTRY_CALLBACK
        Emisor_RXISR_EntryCallback();
    #endif /* Emisor_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START Emisor_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = Emisor_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in Emisor_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (Emisor_RX_STS_BREAK | 
                            Emisor_RX_STS_PAR_ERROR |
                            Emisor_RX_STS_STOP_ERROR | 
                            Emisor_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                Emisor_errorStatus |= readStatus & ( Emisor_RX_STS_BREAK | 
                                                            Emisor_RX_STS_PAR_ERROR | 
                                                            Emisor_RX_STS_STOP_ERROR | 
                                                            Emisor_RX_STS_OVERRUN);
                /* `#START Emisor_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef Emisor_RXISR_ERROR_CALLBACK
                Emisor_RXISR_ERROR_Callback();
            #endif /* Emisor_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & Emisor_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = Emisor_RXDATA_REG;
            #if (Emisor_RXHW_ADDRESS_ENABLED)
                if(Emisor_rxAddressMode == (uint8)Emisor__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & Emisor_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & Emisor_RX_STS_ADDR_MATCH) != 0u)
                        {
                            Emisor_rxAddressDetected = 1u;
                        }
                        else
                        {
                            Emisor_rxAddressDetected = 0u;
                        }
                    }
                    if(Emisor_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        Emisor_rxBuffer[Emisor_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    Emisor_rxBuffer[Emisor_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                Emisor_rxBuffer[Emisor_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (Emisor_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(Emisor_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        Emisor_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    Emisor_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(Emisor_rxBufferWrite >= Emisor_RX_BUFFER_SIZE)
                    {
                        Emisor_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(Emisor_rxBufferWrite == Emisor_rxBufferRead)
                    {
                        Emisor_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (Emisor_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            Emisor_RXSTATUS_MASK_REG  &= (uint8)~Emisor_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(Emisor_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (Emisor_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & Emisor_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START Emisor_RXISR_END` */

        /* `#END` */

    #ifdef Emisor_RXISR_EXIT_CALLBACK
        Emisor_RXISR_ExitCallback();
    #endif /* Emisor_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (Emisor_RX_INTERRUPT_ENABLED && (Emisor_RX_ENABLED || Emisor_HD_ENABLED)) */


#if (Emisor_TX_INTERRUPT_ENABLED && Emisor_TX_ENABLED)
    /*******************************************************************************
    * Function Name: Emisor_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  Emisor_txBuffer - RAM buffer pointer for transmit data from.
    *  Emisor_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  Emisor_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(Emisor_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef Emisor_TXISR_ENTRY_CALLBACK
        Emisor_TXISR_EntryCallback();
    #endif /* Emisor_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START Emisor_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((Emisor_txBufferRead != Emisor_txBufferWrite) &&
             ((Emisor_TXSTATUS_REG & Emisor_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(Emisor_txBufferRead >= Emisor_TX_BUFFER_SIZE)
            {
                Emisor_txBufferRead = 0u;
            }

            Emisor_TXDATA_REG = Emisor_txBuffer[Emisor_txBufferRead];

            /* Set next pointer */
            Emisor_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Emisor_TXISR_END` */

        /* `#END` */

    #ifdef Emisor_TXISR_EXIT_CALLBACK
        Emisor_TXISR_ExitCallback();
    #endif /* Emisor_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (Emisor_TX_INTERRUPT_ENABLED && Emisor_TX_ENABLED) */


/* [] END OF FILE */
