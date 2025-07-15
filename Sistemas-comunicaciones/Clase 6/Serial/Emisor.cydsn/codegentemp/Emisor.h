/*******************************************************************************
* File Name: Emisor.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_Emisor_H)
#define CY_UART_Emisor_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define Emisor_RX_ENABLED                     (1u)
#define Emisor_TX_ENABLED                     (1u)
#define Emisor_HD_ENABLED                     (0u)
#define Emisor_RX_INTERRUPT_ENABLED           (0u)
#define Emisor_TX_INTERRUPT_ENABLED           (0u)
#define Emisor_INTERNAL_CLOCK_USED            (1u)
#define Emisor_RXHW_ADDRESS_ENABLED           (0u)
#define Emisor_OVER_SAMPLE_COUNT              (8u)
#define Emisor_PARITY_TYPE                    (0u)
#define Emisor_PARITY_TYPE_SW                 (0u)
#define Emisor_BREAK_DETECT                   (0u)
#define Emisor_BREAK_BITS_TX                  (13u)
#define Emisor_BREAK_BITS_RX                  (13u)
#define Emisor_TXCLKGEN_DP                    (1u)
#define Emisor_USE23POLLING                   (1u)
#define Emisor_FLOW_CONTROL                   (0u)
#define Emisor_CLK_FREQ                       (0u)
#define Emisor_TX_BUFFER_SIZE                 (4u)
#define Emisor_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(Emisor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define Emisor_CONTROL_REG_REMOVED            (0u)
#else
    #define Emisor_CONTROL_REG_REMOVED            (1u)
#endif /* End Emisor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct Emisor_backupStruct_
{
    uint8 enableState;

    #if(Emisor_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End Emisor_CONTROL_REG_REMOVED */

} Emisor_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void Emisor_Start(void) ;
void Emisor_Stop(void) ;
uint8 Emisor_ReadControlRegister(void) ;
void Emisor_WriteControlRegister(uint8 control) ;

void Emisor_Init(void) ;
void Emisor_Enable(void) ;
void Emisor_SaveConfig(void) ;
void Emisor_RestoreConfig(void) ;
void Emisor_Sleep(void) ;
void Emisor_Wakeup(void) ;

/* Only if RX is enabled */
#if( (Emisor_RX_ENABLED) || (Emisor_HD_ENABLED) )

    #if (Emisor_RX_INTERRUPT_ENABLED)
        #define Emisor_EnableRxInt()  CyIntEnable (Emisor_RX_VECT_NUM)
        #define Emisor_DisableRxInt() CyIntDisable(Emisor_RX_VECT_NUM)
        CY_ISR_PROTO(Emisor_RXISR);
    #endif /* Emisor_RX_INTERRUPT_ENABLED */

    void Emisor_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void Emisor_SetRxAddress1(uint8 address) ;
    void Emisor_SetRxAddress2(uint8 address) ;

    void  Emisor_SetRxInterruptMode(uint8 intSrc) ;
    uint8 Emisor_ReadRxData(void) ;
    uint8 Emisor_ReadRxStatus(void) ;
    uint8 Emisor_GetChar(void) ;
    uint16 Emisor_GetByte(void) ;
    uint8 Emisor_GetRxBufferSize(void)
                                                            ;
    void Emisor_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define Emisor_GetRxInterruptSource   Emisor_ReadRxStatus

#endif /* End (Emisor_RX_ENABLED) || (Emisor_HD_ENABLED) */

/* Only if TX is enabled */
#if(Emisor_TX_ENABLED || Emisor_HD_ENABLED)

    #if(Emisor_TX_INTERRUPT_ENABLED)
        #define Emisor_EnableTxInt()  CyIntEnable (Emisor_TX_VECT_NUM)
        #define Emisor_DisableTxInt() CyIntDisable(Emisor_TX_VECT_NUM)
        #define Emisor_SetPendingTxInt() CyIntSetPending(Emisor_TX_VECT_NUM)
        #define Emisor_ClearPendingTxInt() CyIntClearPending(Emisor_TX_VECT_NUM)
        CY_ISR_PROTO(Emisor_TXISR);
    #endif /* Emisor_TX_INTERRUPT_ENABLED */

    void Emisor_SetTxInterruptMode(uint8 intSrc) ;
    void Emisor_WriteTxData(uint8 txDataByte) ;
    uint8 Emisor_ReadTxStatus(void) ;
    void Emisor_PutChar(uint8 txDataByte) ;
    void Emisor_PutString(const char8 string[]) ;
    void Emisor_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void Emisor_PutCRLF(uint8 txDataByte) ;
    void Emisor_ClearTxBuffer(void) ;
    void Emisor_SetTxAddressMode(uint8 addressMode) ;
    void Emisor_SendBreak(uint8 retMode) ;
    uint8 Emisor_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define Emisor_PutStringConst         Emisor_PutString
    #define Emisor_PutArrayConst          Emisor_PutArray
    #define Emisor_GetTxInterruptSource   Emisor_ReadTxStatus

#endif /* End Emisor_TX_ENABLED || Emisor_HD_ENABLED */

#if(Emisor_HD_ENABLED)
    void Emisor_LoadRxConfig(void) ;
    void Emisor_LoadTxConfig(void) ;
#endif /* End Emisor_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Emisor) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    Emisor_CyBtldrCommStart(void) CYSMALL ;
    void    Emisor_CyBtldrCommStop(void) CYSMALL ;
    void    Emisor_CyBtldrCommReset(void) CYSMALL ;
    cystatus Emisor_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus Emisor_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Emisor)
        #define CyBtldrCommStart    Emisor_CyBtldrCommStart
        #define CyBtldrCommStop     Emisor_CyBtldrCommStop
        #define CyBtldrCommReset    Emisor_CyBtldrCommReset
        #define CyBtldrCommWrite    Emisor_CyBtldrCommWrite
        #define CyBtldrCommRead     Emisor_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Emisor) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define Emisor_BYTE2BYTE_TIME_OUT (25u)
    #define Emisor_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define Emisor_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define Emisor_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define Emisor_SET_SPACE      (0x00u)
#define Emisor_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (Emisor_TX_ENABLED) || (Emisor_HD_ENABLED) )
    #if(Emisor_TX_INTERRUPT_ENABLED)
        #define Emisor_TX_VECT_NUM            (uint8)Emisor_TXInternalInterrupt__INTC_NUMBER
        #define Emisor_TX_PRIOR_NUM           (uint8)Emisor_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Emisor_TX_INTERRUPT_ENABLED */

    #define Emisor_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define Emisor_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define Emisor_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(Emisor_TX_ENABLED)
        #define Emisor_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (Emisor_HD_ENABLED) */
        #define Emisor_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (Emisor_TX_ENABLED) */

    #define Emisor_TX_STS_COMPLETE            (uint8)(0x01u << Emisor_TX_STS_COMPLETE_SHIFT)
    #define Emisor_TX_STS_FIFO_EMPTY          (uint8)(0x01u << Emisor_TX_STS_FIFO_EMPTY_SHIFT)
    #define Emisor_TX_STS_FIFO_FULL           (uint8)(0x01u << Emisor_TX_STS_FIFO_FULL_SHIFT)
    #define Emisor_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << Emisor_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (Emisor_TX_ENABLED) || (Emisor_HD_ENABLED)*/

#if( (Emisor_RX_ENABLED) || (Emisor_HD_ENABLED) )
    #if(Emisor_RX_INTERRUPT_ENABLED)
        #define Emisor_RX_VECT_NUM            (uint8)Emisor_RXInternalInterrupt__INTC_NUMBER
        #define Emisor_RX_PRIOR_NUM           (uint8)Emisor_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Emisor_RX_INTERRUPT_ENABLED */
    #define Emisor_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define Emisor_RX_STS_BREAK_SHIFT             (0x01u)
    #define Emisor_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define Emisor_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define Emisor_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define Emisor_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define Emisor_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define Emisor_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define Emisor_RX_STS_MRKSPC           (uint8)(0x01u << Emisor_RX_STS_MRKSPC_SHIFT)
    #define Emisor_RX_STS_BREAK            (uint8)(0x01u << Emisor_RX_STS_BREAK_SHIFT)
    #define Emisor_RX_STS_PAR_ERROR        (uint8)(0x01u << Emisor_RX_STS_PAR_ERROR_SHIFT)
    #define Emisor_RX_STS_STOP_ERROR       (uint8)(0x01u << Emisor_RX_STS_STOP_ERROR_SHIFT)
    #define Emisor_RX_STS_OVERRUN          (uint8)(0x01u << Emisor_RX_STS_OVERRUN_SHIFT)
    #define Emisor_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << Emisor_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define Emisor_RX_STS_ADDR_MATCH       (uint8)(0x01u << Emisor_RX_STS_ADDR_MATCH_SHIFT)
    #define Emisor_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << Emisor_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define Emisor_RX_HW_MASK                     (0x7Fu)
#endif /* End (Emisor_RX_ENABLED) || (Emisor_HD_ENABLED) */

/* Control Register definitions */
#define Emisor_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define Emisor_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define Emisor_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define Emisor_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define Emisor_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define Emisor_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define Emisor_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define Emisor_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define Emisor_CTRL_HD_SEND               (uint8)(0x01u << Emisor_CTRL_HD_SEND_SHIFT)
#define Emisor_CTRL_HD_SEND_BREAK         (uint8)(0x01u << Emisor_CTRL_HD_SEND_BREAK_SHIFT)
#define Emisor_CTRL_MARK                  (uint8)(0x01u << Emisor_CTRL_MARK_SHIFT)
#define Emisor_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << Emisor_CTRL_PARITY_TYPE0_SHIFT)
#define Emisor_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << Emisor_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define Emisor_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define Emisor_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define Emisor_SEND_BREAK                         (0x00u)
#define Emisor_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define Emisor_REINIT                             (0x02u)
#define Emisor_SEND_WAIT_REINIT                   (0x03u)

#define Emisor_OVER_SAMPLE_8                      (8u)
#define Emisor_OVER_SAMPLE_16                     (16u)

#define Emisor_BIT_CENTER                         (Emisor_OVER_SAMPLE_COUNT - 2u)

#define Emisor_FIFO_LENGTH                        (4u)
#define Emisor_NUMBER_OF_START_BIT                (1u)
#define Emisor_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define Emisor_TXBITCTR_BREAKBITS8X   ((Emisor_BREAK_BITS_TX * Emisor_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define Emisor_TXBITCTR_BREAKBITS ((Emisor_BREAK_BITS_TX * Emisor_OVER_SAMPLE_COUNT) - 1u)

#define Emisor_HALF_BIT_COUNT   \
                            (((Emisor_OVER_SAMPLE_COUNT / 2u) + (Emisor_USE23POLLING * 1u)) - 2u)
#if (Emisor_OVER_SAMPLE_COUNT == Emisor_OVER_SAMPLE_8)
    #define Emisor_HD_TXBITCTR_INIT   (((Emisor_BREAK_BITS_TX + \
                            Emisor_NUMBER_OF_START_BIT) * Emisor_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define Emisor_RXBITCTR_INIT  ((((Emisor_BREAK_BITS_RX + Emisor_NUMBER_OF_START_BIT) \
                            * Emisor_OVER_SAMPLE_COUNT) + Emisor_HALF_BIT_COUNT) - 1u)

#else /* Emisor_OVER_SAMPLE_COUNT == Emisor_OVER_SAMPLE_16 */
    #define Emisor_HD_TXBITCTR_INIT   ((8u * Emisor_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define Emisor_RXBITCTR_INIT      (((7u * Emisor_OVER_SAMPLE_COUNT) - 1u) + \
                                                      Emisor_HALF_BIT_COUNT)
#endif /* End Emisor_OVER_SAMPLE_COUNT */

#define Emisor_HD_RXBITCTR_INIT                   Emisor_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 Emisor_initVar;
#if (Emisor_TX_INTERRUPT_ENABLED && Emisor_TX_ENABLED)
    extern volatile uint8 Emisor_txBuffer[Emisor_TX_BUFFER_SIZE];
    extern volatile uint8 Emisor_txBufferRead;
    extern uint8 Emisor_txBufferWrite;
#endif /* (Emisor_TX_INTERRUPT_ENABLED && Emisor_TX_ENABLED) */
#if (Emisor_RX_INTERRUPT_ENABLED && (Emisor_RX_ENABLED || Emisor_HD_ENABLED))
    extern uint8 Emisor_errorStatus;
    extern volatile uint8 Emisor_rxBuffer[Emisor_RX_BUFFER_SIZE];
    extern volatile uint8 Emisor_rxBufferRead;
    extern volatile uint8 Emisor_rxBufferWrite;
    extern volatile uint8 Emisor_rxBufferLoopDetect;
    extern volatile uint8 Emisor_rxBufferOverflow;
    #if (Emisor_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 Emisor_rxAddressMode;
        extern volatile uint8 Emisor_rxAddressDetected;
    #endif /* (Emisor_RXHW_ADDRESS_ENABLED) */
#endif /* (Emisor_RX_INTERRUPT_ENABLED && (Emisor_RX_ENABLED || Emisor_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define Emisor__B_UART__AM_SW_BYTE_BYTE 1
#define Emisor__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define Emisor__B_UART__AM_HW_BYTE_BY_BYTE 3
#define Emisor__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define Emisor__B_UART__AM_NONE 0

#define Emisor__B_UART__NONE_REVB 0
#define Emisor__B_UART__EVEN_REVB 1
#define Emisor__B_UART__ODD_REVB 2
#define Emisor__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define Emisor_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define Emisor_NUMBER_OF_STOP_BITS    (1u)

#if (Emisor_RXHW_ADDRESS_ENABLED)
    #define Emisor_RX_ADDRESS_MODE    (0u)
    #define Emisor_RX_HW_ADDRESS1     (0u)
    #define Emisor_RX_HW_ADDRESS2     (0u)
#endif /* (Emisor_RXHW_ADDRESS_ENABLED) */

#define Emisor_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << Emisor_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << Emisor_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << Emisor_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << Emisor_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << Emisor_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << Emisor_RX_STS_BREAK_SHIFT) \
                                        | (0 << Emisor_RX_STS_OVERRUN_SHIFT))

#define Emisor_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << Emisor_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << Emisor_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << Emisor_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << Emisor_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef Emisor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Emisor_CONTROL_REG \
                            (* (reg8 *) Emisor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define Emisor_CONTROL_PTR \
                            (  (reg8 *) Emisor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End Emisor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Emisor_TX_ENABLED)
    #define Emisor_TXDATA_REG          (* (reg8 *) Emisor_BUART_sTX_TxShifter_u0__F0_REG)
    #define Emisor_TXDATA_PTR          (  (reg8 *) Emisor_BUART_sTX_TxShifter_u0__F0_REG)
    #define Emisor_TXDATA_AUX_CTL_REG  (* (reg8 *) Emisor_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Emisor_TXDATA_AUX_CTL_PTR  (  (reg8 *) Emisor_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Emisor_TXSTATUS_REG        (* (reg8 *) Emisor_BUART_sTX_TxSts__STATUS_REG)
    #define Emisor_TXSTATUS_PTR        (  (reg8 *) Emisor_BUART_sTX_TxSts__STATUS_REG)
    #define Emisor_TXSTATUS_MASK_REG   (* (reg8 *) Emisor_BUART_sTX_TxSts__MASK_REG)
    #define Emisor_TXSTATUS_MASK_PTR   (  (reg8 *) Emisor_BUART_sTX_TxSts__MASK_REG)
    #define Emisor_TXSTATUS_ACTL_REG   (* (reg8 *) Emisor_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define Emisor_TXSTATUS_ACTL_PTR   (  (reg8 *) Emisor_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(Emisor_TXCLKGEN_DP)
        #define Emisor_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) Emisor_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Emisor_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) Emisor_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Emisor_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) Emisor_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define Emisor_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) Emisor_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define Emisor_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) Emisor_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Emisor_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) Emisor_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Emisor_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Emisor_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Emisor_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Emisor_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Emisor_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) Emisor_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define Emisor_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) Emisor_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* Emisor_TXCLKGEN_DP */

#endif /* End Emisor_TX_ENABLED */

#if(Emisor_HD_ENABLED)

    #define Emisor_TXDATA_REG             (* (reg8 *) Emisor_BUART_sRX_RxShifter_u0__F1_REG )
    #define Emisor_TXDATA_PTR             (  (reg8 *) Emisor_BUART_sRX_RxShifter_u0__F1_REG )
    #define Emisor_TXDATA_AUX_CTL_REG     (* (reg8 *) Emisor_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define Emisor_TXDATA_AUX_CTL_PTR     (  (reg8 *) Emisor_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Emisor_TXSTATUS_REG           (* (reg8 *) Emisor_BUART_sRX_RxSts__STATUS_REG )
    #define Emisor_TXSTATUS_PTR           (  (reg8 *) Emisor_BUART_sRX_RxSts__STATUS_REG )
    #define Emisor_TXSTATUS_MASK_REG      (* (reg8 *) Emisor_BUART_sRX_RxSts__MASK_REG )
    #define Emisor_TXSTATUS_MASK_PTR      (  (reg8 *) Emisor_BUART_sRX_RxSts__MASK_REG )
    #define Emisor_TXSTATUS_ACTL_REG      (* (reg8 *) Emisor_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Emisor_TXSTATUS_ACTL_PTR      (  (reg8 *) Emisor_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End Emisor_HD_ENABLED */

#if( (Emisor_RX_ENABLED) || (Emisor_HD_ENABLED) )
    #define Emisor_RXDATA_REG             (* (reg8 *) Emisor_BUART_sRX_RxShifter_u0__F0_REG )
    #define Emisor_RXDATA_PTR             (  (reg8 *) Emisor_BUART_sRX_RxShifter_u0__F0_REG )
    #define Emisor_RXADDRESS1_REG         (* (reg8 *) Emisor_BUART_sRX_RxShifter_u0__D0_REG )
    #define Emisor_RXADDRESS1_PTR         (  (reg8 *) Emisor_BUART_sRX_RxShifter_u0__D0_REG )
    #define Emisor_RXADDRESS2_REG         (* (reg8 *) Emisor_BUART_sRX_RxShifter_u0__D1_REG )
    #define Emisor_RXADDRESS2_PTR         (  (reg8 *) Emisor_BUART_sRX_RxShifter_u0__D1_REG )
    #define Emisor_RXDATA_AUX_CTL_REG     (* (reg8 *) Emisor_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Emisor_RXBITCTR_PERIOD_REG    (* (reg8 *) Emisor_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Emisor_RXBITCTR_PERIOD_PTR    (  (reg8 *) Emisor_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Emisor_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Emisor_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Emisor_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Emisor_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Emisor_RXBITCTR_COUNTER_REG   (* (reg8 *) Emisor_BUART_sRX_RxBitCounter__COUNT_REG )
    #define Emisor_RXBITCTR_COUNTER_PTR   (  (reg8 *) Emisor_BUART_sRX_RxBitCounter__COUNT_REG )

    #define Emisor_RXSTATUS_REG           (* (reg8 *) Emisor_BUART_sRX_RxSts__STATUS_REG )
    #define Emisor_RXSTATUS_PTR           (  (reg8 *) Emisor_BUART_sRX_RxSts__STATUS_REG )
    #define Emisor_RXSTATUS_MASK_REG      (* (reg8 *) Emisor_BUART_sRX_RxSts__MASK_REG )
    #define Emisor_RXSTATUS_MASK_PTR      (  (reg8 *) Emisor_BUART_sRX_RxSts__MASK_REG )
    #define Emisor_RXSTATUS_ACTL_REG      (* (reg8 *) Emisor_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Emisor_RXSTATUS_ACTL_PTR      (  (reg8 *) Emisor_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (Emisor_RX_ENABLED) || (Emisor_HD_ENABLED) */

#if(Emisor_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define Emisor_INTCLOCK_CLKEN_REG     (* (reg8 *) Emisor_IntClock__PM_ACT_CFG)
    #define Emisor_INTCLOCK_CLKEN_PTR     (  (reg8 *) Emisor_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define Emisor_INTCLOCK_CLKEN_MASK    Emisor_IntClock__PM_ACT_MSK
#endif /* End Emisor_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(Emisor_TX_ENABLED)
    #define Emisor_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End Emisor_TX_ENABLED */

#if(Emisor_HD_ENABLED)
    #define Emisor_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End Emisor_HD_ENABLED */

#if( (Emisor_RX_ENABLED) || (Emisor_HD_ENABLED) )
    #define Emisor_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (Emisor_RX_ENABLED) || (Emisor_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define Emisor_WAIT_1_MS      Emisor_BL_CHK_DELAY_MS   

#define Emisor_TXBUFFERSIZE   Emisor_TX_BUFFER_SIZE
#define Emisor_RXBUFFERSIZE   Emisor_RX_BUFFER_SIZE

#if (Emisor_RXHW_ADDRESS_ENABLED)
    #define Emisor_RXADDRESSMODE  Emisor_RX_ADDRESS_MODE
    #define Emisor_RXHWADDRESS1   Emisor_RX_HW_ADDRESS1
    #define Emisor_RXHWADDRESS2   Emisor_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define Emisor_RXAddressMode  Emisor_RXADDRESSMODE
#endif /* (Emisor_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define Emisor_initvar                    Emisor_initVar

#define Emisor_RX_Enabled                 Emisor_RX_ENABLED
#define Emisor_TX_Enabled                 Emisor_TX_ENABLED
#define Emisor_HD_Enabled                 Emisor_HD_ENABLED
#define Emisor_RX_IntInterruptEnabled     Emisor_RX_INTERRUPT_ENABLED
#define Emisor_TX_IntInterruptEnabled     Emisor_TX_INTERRUPT_ENABLED
#define Emisor_InternalClockUsed          Emisor_INTERNAL_CLOCK_USED
#define Emisor_RXHW_Address_Enabled       Emisor_RXHW_ADDRESS_ENABLED
#define Emisor_OverSampleCount            Emisor_OVER_SAMPLE_COUNT
#define Emisor_ParityType                 Emisor_PARITY_TYPE

#if( Emisor_TX_ENABLED && (Emisor_TXBUFFERSIZE > Emisor_FIFO_LENGTH))
    #define Emisor_TXBUFFER               Emisor_txBuffer
    #define Emisor_TXBUFFERREAD           Emisor_txBufferRead
    #define Emisor_TXBUFFERWRITE          Emisor_txBufferWrite
#endif /* End Emisor_TX_ENABLED */
#if( ( Emisor_RX_ENABLED || Emisor_HD_ENABLED ) && \
     (Emisor_RXBUFFERSIZE > Emisor_FIFO_LENGTH) )
    #define Emisor_RXBUFFER               Emisor_rxBuffer
    #define Emisor_RXBUFFERREAD           Emisor_rxBufferRead
    #define Emisor_RXBUFFERWRITE          Emisor_rxBufferWrite
    #define Emisor_RXBUFFERLOOPDETECT     Emisor_rxBufferLoopDetect
    #define Emisor_RXBUFFER_OVERFLOW      Emisor_rxBufferOverflow
#endif /* End Emisor_RX_ENABLED */

#ifdef Emisor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Emisor_CONTROL                Emisor_CONTROL_REG
#endif /* End Emisor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Emisor_TX_ENABLED)
    #define Emisor_TXDATA                 Emisor_TXDATA_REG
    #define Emisor_TXSTATUS               Emisor_TXSTATUS_REG
    #define Emisor_TXSTATUS_MASK          Emisor_TXSTATUS_MASK_REG
    #define Emisor_TXSTATUS_ACTL          Emisor_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(Emisor_TXCLKGEN_DP)
        #define Emisor_TXBITCLKGEN_CTR        Emisor_TXBITCLKGEN_CTR_REG
        #define Emisor_TXBITCLKTX_COMPLETE    Emisor_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define Emisor_TXBITCTR_PERIOD        Emisor_TXBITCTR_PERIOD_REG
        #define Emisor_TXBITCTR_CONTROL       Emisor_TXBITCTR_CONTROL_REG
        #define Emisor_TXBITCTR_COUNTER       Emisor_TXBITCTR_COUNTER_REG
    #endif /* Emisor_TXCLKGEN_DP */
#endif /* End Emisor_TX_ENABLED */

#if(Emisor_HD_ENABLED)
    #define Emisor_TXDATA                 Emisor_TXDATA_REG
    #define Emisor_TXSTATUS               Emisor_TXSTATUS_REG
    #define Emisor_TXSTATUS_MASK          Emisor_TXSTATUS_MASK_REG
    #define Emisor_TXSTATUS_ACTL          Emisor_TXSTATUS_ACTL_REG
#endif /* End Emisor_HD_ENABLED */

#if( (Emisor_RX_ENABLED) || (Emisor_HD_ENABLED) )
    #define Emisor_RXDATA                 Emisor_RXDATA_REG
    #define Emisor_RXADDRESS1             Emisor_RXADDRESS1_REG
    #define Emisor_RXADDRESS2             Emisor_RXADDRESS2_REG
    #define Emisor_RXBITCTR_PERIOD        Emisor_RXBITCTR_PERIOD_REG
    #define Emisor_RXBITCTR_CONTROL       Emisor_RXBITCTR_CONTROL_REG
    #define Emisor_RXBITCTR_COUNTER       Emisor_RXBITCTR_COUNTER_REG
    #define Emisor_RXSTATUS               Emisor_RXSTATUS_REG
    #define Emisor_RXSTATUS_MASK          Emisor_RXSTATUS_MASK_REG
    #define Emisor_RXSTATUS_ACTL          Emisor_RXSTATUS_ACTL_REG
#endif /* End  (Emisor_RX_ENABLED) || (Emisor_HD_ENABLED) */

#if(Emisor_INTERNAL_CLOCK_USED)
    #define Emisor_INTCLOCK_CLKEN         Emisor_INTCLOCK_CLKEN_REG
#endif /* End Emisor_INTERNAL_CLOCK_USED */

#define Emisor_WAIT_FOR_COMLETE_REINIT    Emisor_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_Emisor_H */


/* [] END OF FILE */
