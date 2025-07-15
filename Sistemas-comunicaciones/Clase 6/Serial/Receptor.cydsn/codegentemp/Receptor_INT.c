/*******************************************************************************
* File Name: ReceptorINT.c
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

#include "Receptor.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (Receptor_RX_INTERRUPT_ENABLED && (Receptor_RX_ENABLED || Receptor_HD_ENABLED))
    /*******************************************************************************
    * Function Name: Receptor_RXISR
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
    *  Receptor_rxBuffer - RAM buffer pointer for save received data.
    *  Receptor_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  Receptor_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  Receptor_rxBufferOverflow - software overflow flag. Set to one
    *     when Receptor_rxBufferWrite index overtakes
    *     Receptor_rxBufferRead index.
    *  Receptor_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when Receptor_rxBufferWrite is equal to
    *    Receptor_rxBufferRead
    *  Receptor_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  Receptor_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(Receptor_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef Receptor_RXISR_ENTRY_CALLBACK
        Receptor_RXISR_EntryCallback();
    #endif /* Receptor_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START Receptor_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = Receptor_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in Receptor_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (Receptor_RX_STS_BREAK | 
                            Receptor_RX_STS_PAR_ERROR |
                            Receptor_RX_STS_STOP_ERROR | 
                            Receptor_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                Receptor_errorStatus |= readStatus & ( Receptor_RX_STS_BREAK | 
                                                            Receptor_RX_STS_PAR_ERROR | 
                                                            Receptor_RX_STS_STOP_ERROR | 
                                                            Receptor_RX_STS_OVERRUN);
                /* `#START Receptor_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef Receptor_RXISR_ERROR_CALLBACK
                Receptor_RXISR_ERROR_Callback();
            #endif /* Receptor_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & Receptor_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = Receptor_RXDATA_REG;
            #if (Receptor_RXHW_ADDRESS_ENABLED)
                if(Receptor_rxAddressMode == (uint8)Receptor__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & Receptor_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & Receptor_RX_STS_ADDR_MATCH) != 0u)
                        {
                            Receptor_rxAddressDetected = 1u;
                        }
                        else
                        {
                            Receptor_rxAddressDetected = 0u;
                        }
                    }
                    if(Receptor_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        Receptor_rxBuffer[Receptor_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    Receptor_rxBuffer[Receptor_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                Receptor_rxBuffer[Receptor_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (Receptor_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(Receptor_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        Receptor_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    Receptor_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(Receptor_rxBufferWrite >= Receptor_RX_BUFFER_SIZE)
                    {
                        Receptor_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(Receptor_rxBufferWrite == Receptor_rxBufferRead)
                    {
                        Receptor_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (Receptor_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            Receptor_RXSTATUS_MASK_REG  &= (uint8)~Receptor_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(Receptor_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (Receptor_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & Receptor_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START Receptor_RXISR_END` */

        /* `#END` */

    #ifdef Receptor_RXISR_EXIT_CALLBACK
        Receptor_RXISR_ExitCallback();
    #endif /* Receptor_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (Receptor_RX_INTERRUPT_ENABLED && (Receptor_RX_ENABLED || Receptor_HD_ENABLED)) */


#if (Receptor_TX_INTERRUPT_ENABLED && Receptor_TX_ENABLED)
    /*******************************************************************************
    * Function Name: Receptor_TXISR
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
    *  Receptor_txBuffer - RAM buffer pointer for transmit data from.
    *  Receptor_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  Receptor_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(Receptor_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef Receptor_TXISR_ENTRY_CALLBACK
        Receptor_TXISR_EntryCallback();
    #endif /* Receptor_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START Receptor_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((Receptor_txBufferRead != Receptor_txBufferWrite) &&
             ((Receptor_TXSTATUS_REG & Receptor_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(Receptor_txBufferRead >= Receptor_TX_BUFFER_SIZE)
            {
                Receptor_txBufferRead = 0u;
            }

            Receptor_TXDATA_REG = Receptor_txBuffer[Receptor_txBufferRead];

            /* Set next pointer */
            Receptor_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START Receptor_TXISR_END` */

        /* `#END` */

    #ifdef Receptor_TXISR_EXIT_CALLBACK
        Receptor_TXISR_ExitCallback();
    #endif /* Receptor_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (Receptor_TX_INTERRUPT_ENABLED && Receptor_TX_ENABLED) */


/* [] END OF FILE */
