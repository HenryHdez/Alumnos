/*******************************************************************************
* File Name: Receptor.h
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


#if !defined(CY_UART_Receptor_H)
#define CY_UART_Receptor_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
* Conditional Compilation Parameters
***************************************/

#define Receptor_RX_ENABLED                     (1u)
#define Receptor_TX_ENABLED                     (1u)
#define Receptor_HD_ENABLED                     (0u)
#define Receptor_RX_INTERRUPT_ENABLED           (0u)
#define Receptor_TX_INTERRUPT_ENABLED           (0u)
#define Receptor_INTERNAL_CLOCK_USED            (1u)
#define Receptor_RXHW_ADDRESS_ENABLED           (0u)
#define Receptor_OVER_SAMPLE_COUNT              (8u)
#define Receptor_PARITY_TYPE                    (0u)
#define Receptor_PARITY_TYPE_SW                 (0u)
#define Receptor_BREAK_DETECT                   (0u)
#define Receptor_BREAK_BITS_TX                  (13u)
#define Receptor_BREAK_BITS_RX                  (13u)
#define Receptor_TXCLKGEN_DP                    (1u)
#define Receptor_USE23POLLING                   (1u)
#define Receptor_FLOW_CONTROL                   (0u)
#define Receptor_CLK_FREQ                       (0u)
#define Receptor_TX_BUFFER_SIZE                 (4u)
#define Receptor_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(Receptor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define Receptor_CONTROL_REG_REMOVED            (0u)
#else
    #define Receptor_CONTROL_REG_REMOVED            (1u)
#endif /* End Receptor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct Receptor_backupStruct_
{
    uint8 enableState;

    #if(Receptor_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End Receptor_CONTROL_REG_REMOVED */

} Receptor_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void Receptor_Start(void) ;
void Receptor_Stop(void) ;
uint8 Receptor_ReadControlRegister(void) ;
void Receptor_WriteControlRegister(uint8 control) ;

void Receptor_Init(void) ;
void Receptor_Enable(void) ;
void Receptor_SaveConfig(void) ;
void Receptor_RestoreConfig(void) ;
void Receptor_Sleep(void) ;
void Receptor_Wakeup(void) ;

/* Only if RX is enabled */
#if( (Receptor_RX_ENABLED) || (Receptor_HD_ENABLED) )

    #if (Receptor_RX_INTERRUPT_ENABLED)
        #define Receptor_EnableRxInt()  CyIntEnable (Receptor_RX_VECT_NUM)
        #define Receptor_DisableRxInt() CyIntDisable(Receptor_RX_VECT_NUM)
        CY_ISR_PROTO(Receptor_RXISR);
    #endif /* Receptor_RX_INTERRUPT_ENABLED */

    void Receptor_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void Receptor_SetRxAddress1(uint8 address) ;
    void Receptor_SetRxAddress2(uint8 address) ;

    void  Receptor_SetRxInterruptMode(uint8 intSrc) ;
    uint8 Receptor_ReadRxData(void) ;
    uint8 Receptor_ReadRxStatus(void) ;
    uint8 Receptor_GetChar(void) ;
    uint16 Receptor_GetByte(void) ;
    uint8 Receptor_GetRxBufferSize(void)
                                                            ;
    void Receptor_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define Receptor_GetRxInterruptSource   Receptor_ReadRxStatus

#endif /* End (Receptor_RX_ENABLED) || (Receptor_HD_ENABLED) */

/* Only if TX is enabled */
#if(Receptor_TX_ENABLED || Receptor_HD_ENABLED)

    #if(Receptor_TX_INTERRUPT_ENABLED)
        #define Receptor_EnableTxInt()  CyIntEnable (Receptor_TX_VECT_NUM)
        #define Receptor_DisableTxInt() CyIntDisable(Receptor_TX_VECT_NUM)
        #define Receptor_SetPendingTxInt() CyIntSetPending(Receptor_TX_VECT_NUM)
        #define Receptor_ClearPendingTxInt() CyIntClearPending(Receptor_TX_VECT_NUM)
        CY_ISR_PROTO(Receptor_TXISR);
    #endif /* Receptor_TX_INTERRUPT_ENABLED */

    void Receptor_SetTxInterruptMode(uint8 intSrc) ;
    void Receptor_WriteTxData(uint8 txDataByte) ;
    uint8 Receptor_ReadTxStatus(void) ;
    void Receptor_PutChar(uint8 txDataByte) ;
    void Receptor_PutString(const char8 string[]) ;
    void Receptor_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void Receptor_PutCRLF(uint8 txDataByte) ;
    void Receptor_ClearTxBuffer(void) ;
    void Receptor_SetTxAddressMode(uint8 addressMode) ;
    void Receptor_SendBreak(uint8 retMode) ;
    uint8 Receptor_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define Receptor_PutStringConst         Receptor_PutString
    #define Receptor_PutArrayConst          Receptor_PutArray
    #define Receptor_GetTxInterruptSource   Receptor_ReadTxStatus

#endif /* End Receptor_TX_ENABLED || Receptor_HD_ENABLED */

#if(Receptor_HD_ENABLED)
    void Receptor_LoadRxConfig(void) ;
    void Receptor_LoadTxConfig(void) ;
#endif /* End Receptor_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Receptor) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    Receptor_CyBtldrCommStart(void) CYSMALL ;
    void    Receptor_CyBtldrCommStop(void) CYSMALL ;
    void    Receptor_CyBtldrCommReset(void) CYSMALL ;
    cystatus Receptor_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus Receptor_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Receptor)
        #define CyBtldrCommStart    Receptor_CyBtldrCommStart
        #define CyBtldrCommStop     Receptor_CyBtldrCommStop
        #define CyBtldrCommReset    Receptor_CyBtldrCommReset
        #define CyBtldrCommWrite    Receptor_CyBtldrCommWrite
        #define CyBtldrCommRead     Receptor_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Receptor) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define Receptor_BYTE2BYTE_TIME_OUT (25u)
    #define Receptor_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define Receptor_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define Receptor_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define Receptor_SET_SPACE      (0x00u)
#define Receptor_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (Receptor_TX_ENABLED) || (Receptor_HD_ENABLED) )
    #if(Receptor_TX_INTERRUPT_ENABLED)
        #define Receptor_TX_VECT_NUM            (uint8)Receptor_TXInternalInterrupt__INTC_NUMBER
        #define Receptor_TX_PRIOR_NUM           (uint8)Receptor_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Receptor_TX_INTERRUPT_ENABLED */

    #define Receptor_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define Receptor_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define Receptor_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(Receptor_TX_ENABLED)
        #define Receptor_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (Receptor_HD_ENABLED) */
        #define Receptor_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (Receptor_TX_ENABLED) */

    #define Receptor_TX_STS_COMPLETE            (uint8)(0x01u << Receptor_TX_STS_COMPLETE_SHIFT)
    #define Receptor_TX_STS_FIFO_EMPTY          (uint8)(0x01u << Receptor_TX_STS_FIFO_EMPTY_SHIFT)
    #define Receptor_TX_STS_FIFO_FULL           (uint8)(0x01u << Receptor_TX_STS_FIFO_FULL_SHIFT)
    #define Receptor_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << Receptor_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (Receptor_TX_ENABLED) || (Receptor_HD_ENABLED)*/

#if( (Receptor_RX_ENABLED) || (Receptor_HD_ENABLED) )
    #if(Receptor_RX_INTERRUPT_ENABLED)
        #define Receptor_RX_VECT_NUM            (uint8)Receptor_RXInternalInterrupt__INTC_NUMBER
        #define Receptor_RX_PRIOR_NUM           (uint8)Receptor_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Receptor_RX_INTERRUPT_ENABLED */
    #define Receptor_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define Receptor_RX_STS_BREAK_SHIFT             (0x01u)
    #define Receptor_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define Receptor_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define Receptor_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define Receptor_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define Receptor_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define Receptor_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define Receptor_RX_STS_MRKSPC           (uint8)(0x01u << Receptor_RX_STS_MRKSPC_SHIFT)
    #define Receptor_RX_STS_BREAK            (uint8)(0x01u << Receptor_RX_STS_BREAK_SHIFT)
    #define Receptor_RX_STS_PAR_ERROR        (uint8)(0x01u << Receptor_RX_STS_PAR_ERROR_SHIFT)
    #define Receptor_RX_STS_STOP_ERROR       (uint8)(0x01u << Receptor_RX_STS_STOP_ERROR_SHIFT)
    #define Receptor_RX_STS_OVERRUN          (uint8)(0x01u << Receptor_RX_STS_OVERRUN_SHIFT)
    #define Receptor_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << Receptor_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define Receptor_RX_STS_ADDR_MATCH       (uint8)(0x01u << Receptor_RX_STS_ADDR_MATCH_SHIFT)
    #define Receptor_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << Receptor_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define Receptor_RX_HW_MASK                     (0x7Fu)
#endif /* End (Receptor_RX_ENABLED) || (Receptor_HD_ENABLED) */

/* Control Register definitions */
#define Receptor_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define Receptor_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define Receptor_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define Receptor_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define Receptor_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define Receptor_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define Receptor_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define Receptor_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define Receptor_CTRL_HD_SEND               (uint8)(0x01u << Receptor_CTRL_HD_SEND_SHIFT)
#define Receptor_CTRL_HD_SEND_BREAK         (uint8)(0x01u << Receptor_CTRL_HD_SEND_BREAK_SHIFT)
#define Receptor_CTRL_MARK                  (uint8)(0x01u << Receptor_CTRL_MARK_SHIFT)
#define Receptor_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << Receptor_CTRL_PARITY_TYPE0_SHIFT)
#define Receptor_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << Receptor_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define Receptor_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define Receptor_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define Receptor_SEND_BREAK                         (0x00u)
#define Receptor_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define Receptor_REINIT                             (0x02u)
#define Receptor_SEND_WAIT_REINIT                   (0x03u)

#define Receptor_OVER_SAMPLE_8                      (8u)
#define Receptor_OVER_SAMPLE_16                     (16u)

#define Receptor_BIT_CENTER                         (Receptor_OVER_SAMPLE_COUNT - 2u)

#define Receptor_FIFO_LENGTH                        (4u)
#define Receptor_NUMBER_OF_START_BIT                (1u)
#define Receptor_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define Receptor_TXBITCTR_BREAKBITS8X   ((Receptor_BREAK_BITS_TX * Receptor_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define Receptor_TXBITCTR_BREAKBITS ((Receptor_BREAK_BITS_TX * Receptor_OVER_SAMPLE_COUNT) - 1u)

#define Receptor_HALF_BIT_COUNT   \
                            (((Receptor_OVER_SAMPLE_COUNT / 2u) + (Receptor_USE23POLLING * 1u)) - 2u)
#if (Receptor_OVER_SAMPLE_COUNT == Receptor_OVER_SAMPLE_8)
    #define Receptor_HD_TXBITCTR_INIT   (((Receptor_BREAK_BITS_TX + \
                            Receptor_NUMBER_OF_START_BIT) * Receptor_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define Receptor_RXBITCTR_INIT  ((((Receptor_BREAK_BITS_RX + Receptor_NUMBER_OF_START_BIT) \
                            * Receptor_OVER_SAMPLE_COUNT) + Receptor_HALF_BIT_COUNT) - 1u)

#else /* Receptor_OVER_SAMPLE_COUNT == Receptor_OVER_SAMPLE_16 */
    #define Receptor_HD_TXBITCTR_INIT   ((8u * Receptor_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define Receptor_RXBITCTR_INIT      (((7u * Receptor_OVER_SAMPLE_COUNT) - 1u) + \
                                                      Receptor_HALF_BIT_COUNT)
#endif /* End Receptor_OVER_SAMPLE_COUNT */

#define Receptor_HD_RXBITCTR_INIT                   Receptor_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 Receptor_initVar;
#if (Receptor_TX_INTERRUPT_ENABLED && Receptor_TX_ENABLED)
    extern volatile uint8 Receptor_txBuffer[Receptor_TX_BUFFER_SIZE];
    extern volatile uint8 Receptor_txBufferRead;
    extern uint8 Receptor_txBufferWrite;
#endif /* (Receptor_TX_INTERRUPT_ENABLED && Receptor_TX_ENABLED) */
#if (Receptor_RX_INTERRUPT_ENABLED && (Receptor_RX_ENABLED || Receptor_HD_ENABLED))
    extern uint8 Receptor_errorStatus;
    extern volatile uint8 Receptor_rxBuffer[Receptor_RX_BUFFER_SIZE];
    extern volatile uint8 Receptor_rxBufferRead;
    extern volatile uint8 Receptor_rxBufferWrite;
    extern volatile uint8 Receptor_rxBufferLoopDetect;
    extern volatile uint8 Receptor_rxBufferOverflow;
    #if (Receptor_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 Receptor_rxAddressMode;
        extern volatile uint8 Receptor_rxAddressDetected;
    #endif /* (Receptor_RXHW_ADDRESS_ENABLED) */
#endif /* (Receptor_RX_INTERRUPT_ENABLED && (Receptor_RX_ENABLED || Receptor_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define Receptor__B_UART__AM_SW_BYTE_BYTE 1
#define Receptor__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define Receptor__B_UART__AM_HW_BYTE_BY_BYTE 3
#define Receptor__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define Receptor__B_UART__AM_NONE 0

#define Receptor__B_UART__NONE_REVB 0
#define Receptor__B_UART__EVEN_REVB 1
#define Receptor__B_UART__ODD_REVB 2
#define Receptor__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define Receptor_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define Receptor_NUMBER_OF_STOP_BITS    (1u)

#if (Receptor_RXHW_ADDRESS_ENABLED)
    #define Receptor_RX_ADDRESS_MODE    (0u)
    #define Receptor_RX_HW_ADDRESS1     (0u)
    #define Receptor_RX_HW_ADDRESS2     (0u)
#endif /* (Receptor_RXHW_ADDRESS_ENABLED) */

#define Receptor_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << Receptor_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << Receptor_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << Receptor_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << Receptor_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << Receptor_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << Receptor_RX_STS_BREAK_SHIFT) \
                                        | (0 << Receptor_RX_STS_OVERRUN_SHIFT))

#define Receptor_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << Receptor_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << Receptor_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << Receptor_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << Receptor_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef Receptor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Receptor_CONTROL_REG \
                            (* (reg8 *) Receptor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define Receptor_CONTROL_PTR \
                            (  (reg8 *) Receptor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End Receptor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Receptor_TX_ENABLED)
    #define Receptor_TXDATA_REG          (* (reg8 *) Receptor_BUART_sTX_TxShifter_u0__F0_REG)
    #define Receptor_TXDATA_PTR          (  (reg8 *) Receptor_BUART_sTX_TxShifter_u0__F0_REG)
    #define Receptor_TXDATA_AUX_CTL_REG  (* (reg8 *) Receptor_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Receptor_TXDATA_AUX_CTL_PTR  (  (reg8 *) Receptor_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Receptor_TXSTATUS_REG        (* (reg8 *) Receptor_BUART_sTX_TxSts__STATUS_REG)
    #define Receptor_TXSTATUS_PTR        (  (reg8 *) Receptor_BUART_sTX_TxSts__STATUS_REG)
    #define Receptor_TXSTATUS_MASK_REG   (* (reg8 *) Receptor_BUART_sTX_TxSts__MASK_REG)
    #define Receptor_TXSTATUS_MASK_PTR   (  (reg8 *) Receptor_BUART_sTX_TxSts__MASK_REG)
    #define Receptor_TXSTATUS_ACTL_REG   (* (reg8 *) Receptor_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define Receptor_TXSTATUS_ACTL_PTR   (  (reg8 *) Receptor_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(Receptor_TXCLKGEN_DP)
        #define Receptor_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) Receptor_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Receptor_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) Receptor_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Receptor_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) Receptor_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define Receptor_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) Receptor_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define Receptor_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) Receptor_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Receptor_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) Receptor_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Receptor_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Receptor_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Receptor_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Receptor_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Receptor_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) Receptor_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define Receptor_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) Receptor_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* Receptor_TXCLKGEN_DP */

#endif /* End Receptor_TX_ENABLED */

#if(Receptor_HD_ENABLED)

    #define Receptor_TXDATA_REG             (* (reg8 *) Receptor_BUART_sRX_RxShifter_u0__F1_REG )
    #define Receptor_TXDATA_PTR             (  (reg8 *) Receptor_BUART_sRX_RxShifter_u0__F1_REG )
    #define Receptor_TXDATA_AUX_CTL_REG     (* (reg8 *) Receptor_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define Receptor_TXDATA_AUX_CTL_PTR     (  (reg8 *) Receptor_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Receptor_TXSTATUS_REG           (* (reg8 *) Receptor_BUART_sRX_RxSts__STATUS_REG )
    #define Receptor_TXSTATUS_PTR           (  (reg8 *) Receptor_BUART_sRX_RxSts__STATUS_REG )
    #define Receptor_TXSTATUS_MASK_REG      (* (reg8 *) Receptor_BUART_sRX_RxSts__MASK_REG )
    #define Receptor_TXSTATUS_MASK_PTR      (  (reg8 *) Receptor_BUART_sRX_RxSts__MASK_REG )
    #define Receptor_TXSTATUS_ACTL_REG      (* (reg8 *) Receptor_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Receptor_TXSTATUS_ACTL_PTR      (  (reg8 *) Receptor_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End Receptor_HD_ENABLED */

#if( (Receptor_RX_ENABLED) || (Receptor_HD_ENABLED) )
    #define Receptor_RXDATA_REG             (* (reg8 *) Receptor_BUART_sRX_RxShifter_u0__F0_REG )
    #define Receptor_RXDATA_PTR             (  (reg8 *) Receptor_BUART_sRX_RxShifter_u0__F0_REG )
    #define Receptor_RXADDRESS1_REG         (* (reg8 *) Receptor_BUART_sRX_RxShifter_u0__D0_REG )
    #define Receptor_RXADDRESS1_PTR         (  (reg8 *) Receptor_BUART_sRX_RxShifter_u0__D0_REG )
    #define Receptor_RXADDRESS2_REG         (* (reg8 *) Receptor_BUART_sRX_RxShifter_u0__D1_REG )
    #define Receptor_RXADDRESS2_PTR         (  (reg8 *) Receptor_BUART_sRX_RxShifter_u0__D1_REG )
    #define Receptor_RXDATA_AUX_CTL_REG     (* (reg8 *) Receptor_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Receptor_RXBITCTR_PERIOD_REG    (* (reg8 *) Receptor_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Receptor_RXBITCTR_PERIOD_PTR    (  (reg8 *) Receptor_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Receptor_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Receptor_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Receptor_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Receptor_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Receptor_RXBITCTR_COUNTER_REG   (* (reg8 *) Receptor_BUART_sRX_RxBitCounter__COUNT_REG )
    #define Receptor_RXBITCTR_COUNTER_PTR   (  (reg8 *) Receptor_BUART_sRX_RxBitCounter__COUNT_REG )

    #define Receptor_RXSTATUS_REG           (* (reg8 *) Receptor_BUART_sRX_RxSts__STATUS_REG )
    #define Receptor_RXSTATUS_PTR           (  (reg8 *) Receptor_BUART_sRX_RxSts__STATUS_REG )
    #define Receptor_RXSTATUS_MASK_REG      (* (reg8 *) Receptor_BUART_sRX_RxSts__MASK_REG )
    #define Receptor_RXSTATUS_MASK_PTR      (  (reg8 *) Receptor_BUART_sRX_RxSts__MASK_REG )
    #define Receptor_RXSTATUS_ACTL_REG      (* (reg8 *) Receptor_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Receptor_RXSTATUS_ACTL_PTR      (  (reg8 *) Receptor_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (Receptor_RX_ENABLED) || (Receptor_HD_ENABLED) */

#if(Receptor_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define Receptor_INTCLOCK_CLKEN_REG     (* (reg8 *) Receptor_IntClock__PM_ACT_CFG)
    #define Receptor_INTCLOCK_CLKEN_PTR     (  (reg8 *) Receptor_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define Receptor_INTCLOCK_CLKEN_MASK    Receptor_IntClock__PM_ACT_MSK
#endif /* End Receptor_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(Receptor_TX_ENABLED)
    #define Receptor_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End Receptor_TX_ENABLED */

#if(Receptor_HD_ENABLED)
    #define Receptor_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End Receptor_HD_ENABLED */

#if( (Receptor_RX_ENABLED) || (Receptor_HD_ENABLED) )
    #define Receptor_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (Receptor_RX_ENABLED) || (Receptor_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define Receptor_WAIT_1_MS      Receptor_BL_CHK_DELAY_MS   

#define Receptor_TXBUFFERSIZE   Receptor_TX_BUFFER_SIZE
#define Receptor_RXBUFFERSIZE   Receptor_RX_BUFFER_SIZE

#if (Receptor_RXHW_ADDRESS_ENABLED)
    #define Receptor_RXADDRESSMODE  Receptor_RX_ADDRESS_MODE
    #define Receptor_RXHWADDRESS1   Receptor_RX_HW_ADDRESS1
    #define Receptor_RXHWADDRESS2   Receptor_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define Receptor_RXAddressMode  Receptor_RXADDRESSMODE
#endif /* (Receptor_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define Receptor_initvar                    Receptor_initVar

#define Receptor_RX_Enabled                 Receptor_RX_ENABLED
#define Receptor_TX_Enabled                 Receptor_TX_ENABLED
#define Receptor_HD_Enabled                 Receptor_HD_ENABLED
#define Receptor_RX_IntInterruptEnabled     Receptor_RX_INTERRUPT_ENABLED
#define Receptor_TX_IntInterruptEnabled     Receptor_TX_INTERRUPT_ENABLED
#define Receptor_InternalClockUsed          Receptor_INTERNAL_CLOCK_USED
#define Receptor_RXHW_Address_Enabled       Receptor_RXHW_ADDRESS_ENABLED
#define Receptor_OverSampleCount            Receptor_OVER_SAMPLE_COUNT
#define Receptor_ParityType                 Receptor_PARITY_TYPE

#if( Receptor_TX_ENABLED && (Receptor_TXBUFFERSIZE > Receptor_FIFO_LENGTH))
    #define Receptor_TXBUFFER               Receptor_txBuffer
    #define Receptor_TXBUFFERREAD           Receptor_txBufferRead
    #define Receptor_TXBUFFERWRITE          Receptor_txBufferWrite
#endif /* End Receptor_TX_ENABLED */
#if( ( Receptor_RX_ENABLED || Receptor_HD_ENABLED ) && \
     (Receptor_RXBUFFERSIZE > Receptor_FIFO_LENGTH) )
    #define Receptor_RXBUFFER               Receptor_rxBuffer
    #define Receptor_RXBUFFERREAD           Receptor_rxBufferRead
    #define Receptor_RXBUFFERWRITE          Receptor_rxBufferWrite
    #define Receptor_RXBUFFERLOOPDETECT     Receptor_rxBufferLoopDetect
    #define Receptor_RXBUFFER_OVERFLOW      Receptor_rxBufferOverflow
#endif /* End Receptor_RX_ENABLED */

#ifdef Receptor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Receptor_CONTROL                Receptor_CONTROL_REG
#endif /* End Receptor_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Receptor_TX_ENABLED)
    #define Receptor_TXDATA                 Receptor_TXDATA_REG
    #define Receptor_TXSTATUS               Receptor_TXSTATUS_REG
    #define Receptor_TXSTATUS_MASK          Receptor_TXSTATUS_MASK_REG
    #define Receptor_TXSTATUS_ACTL          Receptor_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(Receptor_TXCLKGEN_DP)
        #define Receptor_TXBITCLKGEN_CTR        Receptor_TXBITCLKGEN_CTR_REG
        #define Receptor_TXBITCLKTX_COMPLETE    Receptor_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define Receptor_TXBITCTR_PERIOD        Receptor_TXBITCTR_PERIOD_REG
        #define Receptor_TXBITCTR_CONTROL       Receptor_TXBITCTR_CONTROL_REG
        #define Receptor_TXBITCTR_COUNTER       Receptor_TXBITCTR_COUNTER_REG
    #endif /* Receptor_TXCLKGEN_DP */
#endif /* End Receptor_TX_ENABLED */

#if(Receptor_HD_ENABLED)
    #define Receptor_TXDATA                 Receptor_TXDATA_REG
    #define Receptor_TXSTATUS               Receptor_TXSTATUS_REG
    #define Receptor_TXSTATUS_MASK          Receptor_TXSTATUS_MASK_REG
    #define Receptor_TXSTATUS_ACTL          Receptor_TXSTATUS_ACTL_REG
#endif /* End Receptor_HD_ENABLED */

#if( (Receptor_RX_ENABLED) || (Receptor_HD_ENABLED) )
    #define Receptor_RXDATA                 Receptor_RXDATA_REG
    #define Receptor_RXADDRESS1             Receptor_RXADDRESS1_REG
    #define Receptor_RXADDRESS2             Receptor_RXADDRESS2_REG
    #define Receptor_RXBITCTR_PERIOD        Receptor_RXBITCTR_PERIOD_REG
    #define Receptor_RXBITCTR_CONTROL       Receptor_RXBITCTR_CONTROL_REG
    #define Receptor_RXBITCTR_COUNTER       Receptor_RXBITCTR_COUNTER_REG
    #define Receptor_RXSTATUS               Receptor_RXSTATUS_REG
    #define Receptor_RXSTATUS_MASK          Receptor_RXSTATUS_MASK_REG
    #define Receptor_RXSTATUS_ACTL          Receptor_RXSTATUS_ACTL_REG
#endif /* End  (Receptor_RX_ENABLED) || (Receptor_HD_ENABLED) */

#if(Receptor_INTERNAL_CLOCK_USED)
    #define Receptor_INTCLOCK_CLKEN         Receptor_INTCLOCK_CLKEN_REG
#endif /* End Receptor_INTERNAL_CLOCK_USED */

#define Receptor_WAIT_FOR_COMLETE_REINIT    Receptor_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_Receptor_H */


/* [] END OF FILE */
