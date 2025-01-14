/*******************************************************************************
* File Name: CAN.h
* Version 3.0
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the CAN Component.
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

#if !defined(CY_CAN_CAN_H)
#define CY_CAN_CAN_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"
#include "cyapicallbacks.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component CAN_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

extern uint8 CAN_initVar;

#define CAN_INT_ISR_DISABLE                (0u)


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define CAN_ARB_LOST                       (0u)
#define CAN_OVERLOAD                       (0u)
#define CAN_BIT_ERR                        (0u)
#define CAN_STUFF_ERR                      (0u)
#define CAN_ACK_ERR                        (0u)
#define CAN_FORM_ERR                       (0u)
#define CAN_CRC_ERR                        (0u)
#define CAN_BUS_OFF                        (1u)
#define CAN_RX_MSG_LOST                    (0u)
#define CAN_TX_MESSAGE                     (0u)
#define CAN_RX_MESSAGE                     (1u)
#define CAN_ARB_LOST_USE_HELPER            (1u)
#define CAN_OVERLOAD_USE_HELPER            (1u)
#define CAN_BIT_ERR_USE_HELPER             (1u)
#define CAN_STUFF_ERR_USE_HELPER           (1u)
#define CAN_ACK_ERR_USE_HELPER             (1u)
#define CAN_FORM_ERR_USE_HELPER            (1u)
#define CAN_CRC_ERR_USE_HELPER             (1u)
#define CAN_BUS_OFF_USE_HELPER             (1u)
#define CAN_RX_MSG_LOST_USE_HELPER         (1u)
#define CAN_TX_MESSAGE_USE_HELPER          (1u)
#define CAN_RX_MESSAGE_USE_HELPER          (1u)

#if (!(CY_PSOC3 || CY_PSOC5))
    #define CAN_RTR_AUTO_MSG_SENT          (0u)
    #define CAN_STUCK_AT_ZERO              (0u)
    #define CAN_SST_FAILURE                (0u)

    #define CAN_RTR_MESSAGE_USE_HELPER     (1u)
    #define CAN_STUCK_AT_ZERO_USE_HELPER   (1u)
    #define CAN_SST_FAILURE_USE_HELPER     (1u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#define CAN_ADVANCED_INTERRUPT_CFG         (0u)

/* TX/RX Function Enable */
#define CAN_TX0_FUNC_ENABLE            (1u)
#define CAN_TX1_FUNC_ENABLE            (0u)
#define CAN_TX2_FUNC_ENABLE            (0u)
#define CAN_TX3_FUNC_ENABLE            (0u)
#define CAN_TX4_FUNC_ENABLE            (0u)
#define CAN_TX5_FUNC_ENABLE            (0u)
#define CAN_TX6_FUNC_ENABLE            (0u)
#define CAN_TX7_FUNC_ENABLE            (0u)
#define CAN_RX0_FUNC_ENABLE            (1u)
#define CAN_RX1_FUNC_ENABLE            (0u)
#define CAN_RX2_FUNC_ENABLE            (0u)
#define CAN_RX3_FUNC_ENABLE            (0u)
#define CAN_RX4_FUNC_ENABLE            (0u)
#define CAN_RX5_FUNC_ENABLE            (0u)
#define CAN_RX6_FUNC_ENABLE            (0u)
#define CAN_RX7_FUNC_ENABLE            (0u)
#define CAN_RX8_FUNC_ENABLE            (0u)
#define CAN_RX9_FUNC_ENABLE            (0u)
#define CAN_RX10_FUNC_ENABLE           (0u)
#define CAN_RX11_FUNC_ENABLE           (0u)
#define CAN_RX12_FUNC_ENABLE           (0u)
#define CAN_RX13_FUNC_ENABLE           (0u)
#define CAN_RX14_FUNC_ENABLE           (0u)
#define CAN_RX15_FUNC_ENABLE           (0u)
#define CAN_RX_MAILBOX_TYPE            (0x1u)
#define CAN_TX_MAILBOX_TYPE            (0x1u)


/***************************************
*        Data Struct Definition
***************************************/

/* Struct for DATA of BASIC CAN mailbox */
typedef struct
{
    uint8 byte[8u];
} CAN_DATA_BYTES_MSG;

/* Struct for DATA of CAN RX register */
typedef struct
{
    reg8 byte[8u];
} CAN_DATA_BYTES;

/* Struct for 32-bit CAN register */
typedef struct
{
    reg8 byte[4u];
} CAN_REG_32;

/* Struct for BASIC CAN mailbox to send messages */
typedef struct
{
    uint32 id;
    uint8 rtr;
    uint8 ide;
    uint8 dlc;
    uint8 irq;
    #if (!(CY_PSOC3 || CY_PSOC5))
        uint8 sst;
    #endif /* (!(CY_PSOC3 || CY_PSOC5)) */
    CAN_DATA_BYTES_MSG *msg;
} CAN_TX_MSG;

/* Constant configuration of CAN RX */
typedef struct
{
    uint8 rxmailbox;
    uint32 rxcmd;
    uint32 rxamr;
    uint32 rxacr;
} CAN_RX_CFG;

/* Constant configuration of CAN TX */
typedef struct
{
    uint8 txmailbox;
    uint32 txcmd;
    uint32 txid;
} CAN_TX_CFG;

/* CAN RX registers */
typedef struct
{
    CAN_REG_32 rxcmd;
    CAN_REG_32 rxid;
    CAN_DATA_BYTES rxdata;
    CAN_REG_32 rxamr;
    CAN_REG_32 rxacr;
    CAN_REG_32 rxamrd;
    CAN_REG_32 rxacrd;
} CAN_RX_STRUCT;

/* CAN TX registers */
typedef struct
{
    CAN_REG_32 txcmd;
    CAN_REG_32 txid;
    CAN_DATA_BYTES txdata;
} CAN_TX_STRUCT;

/* Sleep Mode API Support */
typedef struct
{
    uint8  enableState;
    #if (CY_PSOC3 || CY_PSOC5)
        uint32 intSr;
        uint32 intEn;
        uint32 cmd;
        uint32 cfg;
    #endif /* CY_PSOC3 || CY_PSOC5 */
} CAN_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8  CAN_Init(void) ;
uint8  CAN_Start(void) ;
uint8  CAN_Stop(void) ;
uint8  CAN_Enable(void) ;
uint8  CAN_GlobalIntEnable(void) ;
uint8  CAN_GlobalIntDisable(void) ;
uint8  CAN_SetPreScaler(uint16 bitrate) ;
uint8  CAN_SetArbiter(uint8 arbiter) ;
uint8  CAN_SetTsegSample(uint8 cfgTseg1, uint8 cfgTseg2, uint8 sjw, uint8 sm)
                                                ;
uint8  CAN_SetRestartType(uint8 reset) ;
uint8  CAN_SetEdgeMode(uint8 edge) ;
uint8  CAN_SetOpMode(uint8 opMode) ;
uint8  CAN_RXRegisterInit(reg32 *regAddr, uint32 config)
                                            ;
uint8  CAN_SetIrqMask(uint16 mask) ;
uint8  CAN_GetTXErrorFlag(void) ;
uint8  CAN_GetRXErrorFlag(void) ;
uint8  CAN_GetTXErrorCount(void) ;
uint8  CAN_GetRXErrorCount(void) ;
uint8  CAN_GetErrorState(void) ;
void   CAN_Sleep(void) ;
void   CAN_Wakeup(void) ;
void   CAN_SaveConfig(void) ;
void   CAN_RestoreConfig(void) ;

#if (!(CY_PSOC3 || CY_PSOC5))
    uint8  CAN_SetSwapDataEndianness(uint8 swap);
    uint8  CAN_SetErrorCaptureRegisterMode(uint8 ecrMode);
    uint32 CAN_ReadErrorCaptureRegister(void);
    uint8  CAN_ArmErrorCaptureRegister(void);
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#if (CAN_ARB_LOST)
    void CAN_ArbLostIsr(void) ;
#endif /* CAN_ARB_LOST */
#if (CAN_OVERLOAD)
    void CAN_OvrLdErrorIsr(void) ;
#endif /* CAN_OVERLOAD */
#if (CAN_BIT_ERR)
    void CAN_BitErrorIsr(void) ;
#endif /* CAN_BIT_ERR */
#if (CAN_STUFF_ERR)
    void CAN_BitStuffErrorIsr(void) ;
#endif /* CAN_STUFF_ERR */
#if (CAN_ACK_ERR)
    void CAN_AckErrorIsr(void) ;
#endif /* CAN_ACK_ERR */
#if (CAN_FORM_ERR)
    void CAN_MsgErrorIsr(void) ;
#endif /* CAN_FORM_ERR */
#if (CAN_CRC_ERR)
    void CAN_CrcErrorIsr(void) ;
#endif /* CAN_CRC_ERR */
#if (CAN_BUS_OFF)
    void CAN_BusOffIsr(void) ;
#endif /* CAN_BUS_OFF */
#if (CAN_RX_MSG_LOST)
    void CAN_MsgLostIsr(void) ;
#endif /* CAN_RX_MSG_LOST */
#if (CAN_TX_MESSAGE)
   void CAN_MsgTXIsr(void) ;
#endif /* CAN_TX_MESSAGE */
#if (CAN_RX_MESSAGE)
    void CAN_MsgRXIsr(void) ;
#endif /* CAN_RX_MESSAGE */

#if (!(CY_PSOC3 || CY_PSOC5))
    #if (CAN_RTR_AUTO_MSG_SENT)
        void CAN_RtrAutoMsgSentIsr(void);
    #endif /* CAN_RTR_MESSAGE */
    #if (CAN_STUCK_AT_ZERO)
        void CAN_StuckAtZeroIsr(void);
    #endif /* CAN_STUCK_AT_ZERO */
    #if (CAN_SST_FAILURE)
        void CAN_SSTErrorIsr(void);
    #endif /* CAN_SST_ERROR */
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

uint8 CAN_RxBufConfig(const CAN_RX_CFG *rxConfig) \
                                   ;
uint8 CAN_TxBufConfig(const CAN_TX_CFG *txConfig) \
                                   ;
uint8 CAN_RxTxBuffersConfig(void) ;                                
uint8 CAN_SendMsg(const CAN_TX_MSG *message) ;
void  CAN_TxCancel(uint8 bufferId) ;
void  CAN_ReceiveMsg(uint8 rxMailbox) ;

#if (CAN_TX0_FUNC_ENABLE)
    uint8 CAN_SendMsg0(void) ;
#endif /* CAN_TX0_FUNC_ENABLE */
#if (CAN_TX1_FUNC_ENABLE)
    uint8 CAN_SendMsg1(void) ;
#endif /* CAN_TX1_FUNC_ENABLE */
#if (CAN_TX2_FUNC_ENABLE)
    uint8 CAN_SendMsg2(void) ;
#endif /* CAN_TX2_FUNC_ENABLE */
#if (CAN_TX3_FUNC_ENABLE)
    uint8 CAN_SendMsg3(void) ;
#endif /* CAN_TX3_FUNC_ENABLE */
#if (CAN_TX4_FUNC_ENABLE)
    uint8 CAN_SendMsg4(void) ;
#endif /* CAN_TX4_FUNC_ENABLE */
#if (CAN_TX5_FUNC_ENABLE)
    uint8 CAN_SendMsg5(void) ;
#endif /* CAN_TX5_FUNC_ENABLE */
#if (CAN_TX6_FUNC_ENABLE)
    uint8 CAN_SendMsg6(void) ;
#endif /* CAN_TX6_FUNC_ENABLE */
#if (CAN_TX7_FUNC_ENABLE)
    uint8 CAN_SendMsg7(void) ;
#endif /* CAN_TX7_FUNC_ENABLE */
#if (CAN_RX0_FUNC_ENABLE)
    void CAN_ReceiveMsg0(void) ;
#endif /* CAN_RX0_FUNC_ENABLE */
#if (CAN_RX1_FUNC_ENABLE)
    void CAN_ReceiveMsg1(void) ;
#endif /* CAN_RX1_FUNC_ENABLE */
#if (CAN_RX2_FUNC_ENABLE)
    void CAN_ReceiveMsg2(void) ;
#endif /* CAN_RX2_FUNC_ENABLE */
#if (CAN_RX3_FUNC_ENABLE)
    void CAN_ReceiveMsg3(void) ;
#endif /* CAN_RX3_FUNC_ENABLE */
#if (CAN_RX4_FUNC_ENABLE)
    void CAN_ReceiveMsg4(void) ;
#endif /* CAN_RX4_FUNC_ENABLE */
#if (CAN_RX5_FUNC_ENABLE)
    void CAN_ReceiveMsg5(void) ;
#endif /* CAN_RX5_FUNC_ENABLE */
#if (CAN_RX6_FUNC_ENABLE)
    void CAN_ReceiveMsg6(void) ;
#endif /* CAN_RX6_FUNC_ENABLE */
#if (CAN_RX7_FUNC_ENABLE)
    void CAN_ReceiveMsg7(void) ;
#endif /* CAN_RX7_FUNC_ENABLE */
#if (CAN_RX8_FUNC_ENABLE)
    void CAN_ReceiveMsg8(void) ;
#endif /* CAN_RX8_FUNC_ENABLE */
#if (CAN_RX9_FUNC_ENABLE)
    void CAN_ReceiveMsg9(void) ;
#endif /* CAN_RX9_FUNC_ENABLE */
#if (CAN_RX10_FUNC_ENABLE)
    void CAN_ReceiveMsg10(void) ;
#endif /* CAN_RX10_FUNC_ENABLE */
#if (CAN_RX11_FUNC_ENABLE)
    void CAN_ReceiveMsg11(void) ;
#endif /* CAN_RX11_FUNC_ENABLE */
#if (CAN_RX12_FUNC_ENABLE)
    void CAN_ReceiveMsg12(void) ;
#endif /* CAN_RX12_FUNC_ENABLE */
#if (CAN_RX13_FUNC_ENABLE)
    void CAN_ReceiveMsg13(void) ;
#endif /* CAN_RX13_FUNC_ENABLE */
#if (CAN_RX14_FUNC_ENABLE)
    void CAN_ReceiveMsg14(void) ;
#endif /* CAN_RX14_FUNC_ENABLE */
#if (CAN_RX15_FUNC_ENABLE)
    void CAN_ReceiveMsg15(void) ;
#endif /* CAN_RX15_FUNC_ENABLE */

#if(!CAN_INT_ISR_DISABLE)
    /* Interrupt handler */
    CY_ISR_PROTO(CAN_ISR);
#endif /* !CAN_INT_ISR_DISABLE */


/***************************************
*           API Constants
***************************************/

#if (!CAN_INT_ISR_DISABLE)
    /* Number of CAN_isr interrupt */
    #define CAN_ISR_NUMBER            ((uint8) CAN_isr__INTC_NUMBER)
    /* Priority of CAN_isr interrupt */
    #define CAN_ISR_PRIORITY          ((uint8) CAN_isr__INTC_PRIOR_NUM)
#endif /* !CAN_INT_ISR_DISABLE */

/* One bit time in CAN clock cycles */
#define CAN_ONE_BIT_TIME              ((CAN_BITRATE + 1u) * \
        ((CAN_CFG_REG_TSEG1 + 1u) + (CAN_CFG_REG_TSEG2 + 1u) + 1u))

/* Timeout for CAN state machine to switch operation mode to Run */
#define CAN_MODE_STATE_RUN_TIMEOUT    (12u * CAN_ONE_BIT_TIME)
/* Timeout for CAN state machine to switch operation mode to Stop */
#define CAN_MODE_STATE_STOP_TIMEOUT   (160u * CAN_ONE_BIT_TIME)

/* One or more parameters to function were invalid. */
#define CAN_FAIL                      (0x01u)
#define CAN_OUT_OF_RANGE              (0x02u)

#if (CY_PSOC3 || CY_PSOC5)
    /* PM_ACT_CFG (Active Power Mode CFG Register) */
    #define CAN_ACT_PWR_EN            (CAN_CanIP__PM_ACT_MSK)    /* Power enable mask */
    /* PM_STBY_CFG (Alternate Active (Standby) Power Mode CFG Register) */
    #define CAN_STBY_PWR_EN           (CAN_CanIP__PM_STBY_MSK)   /* Power enable mask */
#endif /* CY_PSOC3 || CY_PSOC5 */

/* Number of TX and RX mailboxes */
#define CAN_NUMBER_OF_TX_MAILBOXES    (8u)
#define CAN_NUMBER_OF_RX_MAILBOXES    (16u)

/* Error status of CAN */
#define CAN_ERROR_ACTIVE              (0x00u)
#define CAN_ERROR_PASIVE              (0x01u)
#define CAN_ERROR_BUS_OFF             (0x10u)

/* Operation mode */
#define CAN_INITIAL_MODE              (0x00u)
#define CAN_STOP_MODE                 (0x00u)
#define CAN_ACTIVE_RUN_MODE           (0x01u)
#define CAN_LISTEN_ONLY_MODE          (0x02u)
#if (!(CY_PSOC3 || CY_PSOC5))
    #define CAN_INTERNAL_LOOP_BACK    (0x06u)
    #define CAN_EXTERNAL_LOOP_BACK    (0x04u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

/* TX Defines to link mailbox names with mailbox numbers */
#define CAN_TX_MAILBOX_0               (0u)
#define CAN_TX_MAILBOX_1               (1u)
#define CAN_TX_MAILBOX_2               (2u)
#define CAN_TX_MAILBOX_3               (3u)
#define CAN_TX_MAILBOX_4               (4u)
#define CAN_TX_MAILBOX_5               (5u)
#define CAN_TX_MAILBOX_6               (6u)
#define CAN_TX_MAILBOX_7               (7u)

/* RX Defines to link mailbox names with mailbox numbers */
#define CAN_RX_MAILBOX_0               (0u)
#define CAN_RX_MAILBOX_1               (1u)
#define CAN_RX_MAILBOX_2               (2u)
#define CAN_RX_MAILBOX_3               (3u)
#define CAN_RX_MAILBOX_4               (4u)
#define CAN_RX_MAILBOX_5               (5u)
#define CAN_RX_MAILBOX_6               (6u)
#define CAN_RX_MAILBOX_7               (7u)
#define CAN_RX_MAILBOX_8               (8u)
#define CAN_RX_MAILBOX_9               (9u)
#define CAN_RX_MAILBOX_10              (10u)
#define CAN_RX_MAILBOX_11              (11u)
#define CAN_RX_MAILBOX_12              (12u)
#define CAN_RX_MAILBOX_13              (13u)
#define CAN_RX_MAILBOX_14              (14u)
#define CAN_RX_MAILBOX_15              (15u)


/***************************************
*    Initial Parameter Constants
***************************************/

/* General */
#define CAN_BITRATE                   (2u)
#define CAN_CFG_REG_TSEG1             (5u - 1u)
#define CAN_CFG_REG_TSEG2             (2u - 1u)
#define CAN_CFG_REG_SJW               (2u - 1u)
#define CAN_SAMPLING_MODE             (0u)
#define CAN_ARBITER                   (0u)
#define CAN_RESET_TYPE                (0u)
#define CAN_SYNC_EDGE                 (0u)

#if (!(CY_PSOC3 || CY_PSOC5))
    #define CAN_SWAP_DATA_END         (0u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

/* Interrupts */
#define CAN_INT_ENABLE                (1u)

#if (CY_PSOC3 || CY_PSOC5)
    #define CAN_INIT_INTERRUPT_MASK (((uint16) CAN_INT_ENABLE) | \
                ((uint16) ((uint16) CAN_ARB_LOST    <<  CAN_ARBITRATION_LOST_SHIFT)) | \
                ((uint16) ((uint16) CAN_OVERLOAD    <<  CAN_OVERLOAD_ERROR_SHIFT))   | \
                ((uint16) ((uint16) CAN_BIT_ERR     <<  CAN_BIT_ERROR_SHIFT))        | \
                ((uint16) ((uint16) CAN_STUFF_ERR   <<  CAN_STUFF_ERROR_SHIFT))      | \
                ((uint16) ((uint16) CAN_ACK_ERR     <<  CAN_ACK_ERROR_SHIFT))        | \
                ((uint16) ((uint16) CAN_FORM_ERR    <<  CAN_FORM_ERROR_SHIFT))       | \
                ((uint16) ((uint16) CAN_CRC_ERR     << (CAN_ONE_BYTE_OFFSET          + \
                                                                     CAN_CRC_ERROR_SHIFT)))       | \
                ((uint16) ((uint16) CAN_BUS_OFF     << (CAN_ONE_BYTE_OFFSET          + \
                                                                     CAN_BUS_OFF_SHIFT)))         | \
                ((uint16) ((uint16) CAN_RX_MSG_LOST << (CAN_ONE_BYTE_OFFSET          + \
                                                                     CAN_RX_MSG_LOST_SHIFT)))     | \
                ((uint16) ((uint16) CAN_TX_MESSAGE  << (CAN_ONE_BYTE_OFFSET          + \
                                                                     CAN_TX_MESSAGE_SHIFT)))      | \
                ((uint16) ((uint16) CAN_RX_MESSAGE  << (CAN_ONE_BYTE_OFFSET          + \
                                                                     CAN_RX_MESSAGE_SHIFT))))
#else /* CY_PSOC4 */
    #define CAN_INIT_INTERRUPT_MASK    (((uint16) CAN_INT_ENABLE) | \
                ((uint16) ((uint16) CAN_ARB_LOST    <<  CAN_ARBITRATION_LOST_SHIFT)) | \
                ((uint16) ((uint16) CAN_OVERLOAD    <<  CAN_OVERLOAD_ERROR_SHIFT))   | \
                ((uint16) ((uint16) CAN_BIT_ERR     <<  CAN_BIT_ERROR_SHIFT))        | \
                ((uint16) ((uint16) CAN_STUFF_ERR   <<  CAN_STUFF_ERROR_SHIFT))      | \
                ((uint16) ((uint16) CAN_ACK_ERR     <<  CAN_ACK_ERROR_SHIFT))        | \
                ((uint16) ((uint16) CAN_FORM_ERR    <<  CAN_FORM_ERROR_SHIFT))       | \
                ((uint16) ((uint16) CAN_CRC_ERR     <<  CAN_CRC_ERROR_SHIFT))        | \
                ((uint16) ((uint16) CAN_BUS_OFF     <<  CAN_BUS_OFF_SHIFT))          | \
                ((uint16) ((uint16) CAN_RX_MSG_LOST <<  CAN_RX_MSG_LOST_SHIFT))      | \
                ((uint16) ((uint16) CAN_TX_MESSAGE  <<  CAN_TX_MESSAGE_SHIFT))       | \
                ((uint16) ((uint16) CAN_RX_MESSAGE  <<  CAN_RX_MESSAGE_SHIFT))       | \
                ((uint16) ((uint16) CAN_RTR_AUTO_MSG_SENT  << CAN_RTR_MSG_SHIFT))    | \
                ((uint16) ((uint16) CAN_STUCK_AT_ZERO << CAN_STUCK_AT_ZERO_SHIFT))   | \
                ((uint16) ((uint16) CAN_SST_FAILURE   << CAN_SST_FAILURE_SHIFT)))
#endif /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*             Registers
***************************************/

#if (CY_PSOC3 || CY_PSOC5)
#define CAN_TX          ( (volatile CAN_TX_STRUCT XDATA *) CAN_CanIP__TX0_CMD)
#define CAN_RX          ( (volatile CAN_RX_STRUCT XDATA *) CAN_CanIP__RX0_CMD)
#define CAN_INT_SR_REG  (*(volatile CAN_REG_32 XDATA *) CAN_CanIP__CSR_INT_SR)
#define CAN_INT_SR_PTR  ( (reg32 *) CAN_CanIP__CSR_INT_SR)
#define CAN_INT_EN_REG  (*(volatile CAN_REG_32 XDATA *) CAN_CanIP__CSR_INT_EN)
#define CAN_INT_EN_PTR  ( (reg32 *) CAN_CanIP__CSR_INT_EN)
#define CAN_BUF_SR_REG  (*(volatile CAN_REG_32 XDATA *) CAN_CanIP__CSR_BUF_SR)
#define CAN_BUF_SR_PTR  ( (reg32 *) CAN_CanIP__CSR_BUF_SR)
#define CAN_ERR_SR_REG  (*(volatile CAN_REG_32 XDATA *) CAN_CanIP__CSR_ERR_SR)
#define CAN_ERR_SR_PTR  ( (reg32 *) CAN_CanIP__CSR_ERR_SR)
#define CAN_CMD_REG     (*(volatile CAN_REG_32 XDATA *) CAN_CanIP__CSR_CMD)
#define CAN_CMD_PTR     ( (reg32 *) CAN_CanIP__CSR_CMD)
#define CAN_CFG_REG     (*(volatile CAN_REG_32 XDATA *) CAN_CanIP__CSR_CFG)
#define CAN_CFG_PTR     ( (reg32 *) CAN_CanIP__CSR_CFG)

/* Power manager */
#define CAN_PM_ACT_CFG_REG           (*(reg8 *) CAN_CanIP__PM_ACT_CFG)
#define CAN_PM_ACT_CFG_PTR           ( (reg8 *) CAN_CanIP__PM_ACT_CFG)
#define CAN_PM_STBY_CFG_REG          (*(reg8 *) CAN_CanIP__PM_STBY_CFG)
#define CAN_PM_STBY_CFG_PTR          ( (reg8 *) CAN_CanIP__PM_STBY_CFG)

#define CAN_RX_FIRST_REGISTER_PTR    ((reg32 *) CAN_CanIP__RX0_CMD)
#define CAN_RX_LAST_REGISTER_PTR     ((reg32 *) CAN_CanIP__RX15_ACRD)

#else /* CY_PSOC4 */
#define CAN_TX    ((volatile CAN_TX_STRUCT XDATA *) CAN_CanIP__CAN_TX0_CONTROL)
#define CAN_RX    ((volatile CAN_RX_STRUCT XDATA *) CAN_CanIP__CAN_RX0_CONTROL)
#define CAN_TX_REG                   (*(reg32 *) CAN_CanIP__CAN_TX0_CONTROL)
#define CAN_TX_PTR                   ( (reg32 *) CAN_CanIP__CAN_TX0_CONTROL)
#define CAN_RX_REG                   (*(reg32 *) CAN_CanIP__CAN_RX0_CONTROL)
#define CAN_RX_PTR                   ( (reg32 *) CAN_CanIP__CAN_RX0_CONTROL)
#define CAN_INT_SR_REG               (*(reg32 *) CAN_CanIP__INT_STATUS)
#define CAN_INT_SR_PTR               ( (reg32 *) CAN_CanIP__INT_STATUS)
#define CAN_INT_EN_REG               (*(reg32 *) CAN_CanIP__INT_EBL)
#define CAN_INT_EN_PTR               ( (reg32 *) CAN_CanIP__INT_EBL)
#define CAN_BUF_SR_REG               (*(reg32 *) CAN_CanIP__BUFFER_STATUS)
#define CAN_BUF_SR_PTR               ( (reg32 *) CAN_CanIP__BUFFER_STATUS)
#define CAN_ERR_SR_REG               (*(reg32 *) CAN_CanIP__ERROR_STATUS)
#define CAN_ERR_SR_PTR               ( (reg32 *) CAN_CanIP__ERROR_STATUS)
#define CAN_CNTL_REG                 (*(reg32 *) CAN_CanIP__CNTL)
#define CAN_CNTL_PTR                 ( (reg32 *) CAN_CanIP__CNTL)
#define CAN_CMD_REG                  (*(reg32 *) CAN_CanIP__COMMAND)
#define CAN_CMD_PTR                  ( (reg32 *) CAN_CanIP__COMMAND)
#define CAN_CFG_REG                  (*(reg32 *) CAN_CanIP__CONFIG)
#define CAN_CFG_PTR                  ( (reg32 *) CAN_CanIP__CONFIG)
#define CAN_ECR_REG                  (*(reg32 *) CAN_CanIP__ECR)
#define CAN_ECR_PTR                  ( (reg32 *) CAN_CanIP__ECR)
#define CAN_RX_FIRST_REGISTER_PTR    ( (reg32 *) CAN_CanIP__CAN_RX0_CONTROL)
#define CAN_RX_LAST_REGISTER_PTR     ( (reg32 *) CAN_CanIP__CAN_RX15_ACR_DATA)

#define CAN_TX_DATA_LO_REG(i)        (*(reg32 *) (&CAN_TX[i].txdata))
#define CAN_TX_DATA_HI_REG(i)        (*(reg32 *) ((uint32) (&CAN_TX[i].txdata) + \
                                                  CAN_DATA_HIGH_ADDR))
#define CAN_RX_DATA_LO_REG(i)        (*(reg32 *) (&CAN_RX[i].rxdata))
#define CAN_RX_DATA_HI_REG(i)        (*(reg32 *) ((uint32) (&CAN_RX[i].rxdata) + \
                                                  CAN_DATA_HIGH_ADDR))
#endif /* (CY_PSOC3 || CY_PSOC5) */

#define CAN_TX_CMD_PTR(i)            ( (reg32 *) (&CAN_TX[i].txcmd))
#define CAN_TX_CMD_REG(i)            (*(reg32 *) (&CAN_TX[i].txcmd))
#define CAN_RX_CMD_PTR(i)            ( (reg32 *) (&CAN_RX[i].rxcmd))
#define CAN_RX_CMD_REG(i)            (*(reg32 *) (&CAN_RX[i].rxcmd))
#define CAN_RX_ID_PTR(i)             ( (reg32 *) (&CAN_RX[i].rxid))
#define CAN_RX_ID_REG(i)             (*(reg32 *) (&CAN_RX[i].rxid))
#define CAN_TX_ID_PTR(i)             ( (reg32 *) (&CAN_TX[i].txid))
#define CAN_TX_ID_REG(i)             (*(reg32 *) (&CAN_TX[i].txid))


/***************************************
*        Register Constants
***************************************/

/* Run/Stop mode */
#define CAN_MODE_STOP                (0x00u)
#define CAN_MODE_START               (0x01u)

/* Transmit buffer arbiter */
#define CAN_ROUND_ROBIN              (0x00u)
#define CAN_FIXED_PRIORITY           (0x01u)

/* Restart type */
#define CAN_MANUAL_RESTART           (0x00u)
#define CAN_AUTO_RESTART             (0x01u)

/* Sampling mode */
#define CAN_ONE_SAMPLE_POINT         (0x00u)
#define CAN_THREE_SAMPLE_POINTS      (0x01u)

/* Edge mode */
#define CAN_EDGE_R_TO_D              (0x00u)
#define CAN_BOTH_EDGES               (0x01u)

/* Extended identifier */
#define CAN_STANDARD_MESSAGE         (0x00u)
#define CAN_EXTENDED_MESSAGE         (0x01u)

/* Write Protect Mask for Basic and Full mailboxes */
#define CAN_TX_WPN_CLEAR           ((uint32) (~CAN_TX_WPN_SET))
#define CAN_RX_WPN_CLEAR           ((uint32) (~CAN_RX_WPN_SET))
#define CAN_TX_RSVD_MASK           ((uint32) 0x00FF00FFu)
#define CAN_TX_READ_BACK_MASK      (CAN_TX_WPN_CLEAR & CAN_TX_RSVD_MASK)
#define CAN_RX_READ_BACK_MASK      (CAN_RX_WPN_CLEAR & CAN_TX_RSVD_MASK)
#define CAN_RX_CMD_REG_WIDTH       (0x20u)

#if (CY_PSOC3 || CY_PSOC5)
    #define CAN_TX_WPN_SET         (((uint32) ((uint32) 0x00000001u << CAN_TX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << (CAN_TWO_BYTE_OFFSET + CAN_TX_WPNH_SHIFT))))
    #define CAN_RX_WPN_SET         (((uint32) ((uint32) 0x00000001u << CAN_RX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << (CAN_TWO_BYTE_OFFSET + CAN_RX_WPNH_SHIFT))))
#else  /* CY_PSOC4 */
    #define CAN_TX_WPN_SET         (((uint32) ((uint32) 0x00000001u << CAN_TX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << CAN_TX_WPNH_SHIFT)))
    #define CAN_RX_WPN_SET         (((uint32) ((uint32) 0x00000001u << CAN_RX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << CAN_RX_WPNH_SHIFT)))

    /* CAN IP Block Enable */
    #define CAN_IP_ENABLE_SHIFT    (31u)
    #define CAN_IP_ENABLE          ((uint32) ((uint32) 0x00000001u << CAN_IP_ENABLE_SHIFT))

    /* Error Capture register mode setting */
    #define CAN_ECR_FREE_RUNNING   (0x00u)
    #define CAN_ECR_ERROR_CAPTURE  (0x01u)

    /* Swap Endian */
    #define CAN_SWAP_ENDIANNESS_DISABLE  (0x00u)
    #define CAN_SWAP_ENDIANNESS_ENABLE   (0x01u)
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* TX send message */
#define CAN_TX_REQUEST_PENDING     (0x01u)
#define CAN_RETRY_NUMBER           (0x03u)
#define CAN_SEND_MESSAGE_SHIFT     (0u)
#define CAN_SEND_MESSAGE           ((uint32) ((uint32) 0x00000001u << CAN_SEND_MESSAGE_SHIFT))

/* Offsets to maintain bytes within uint32 */
#define CAN_ONE_BYTE_OFFSET        (8u)
#define CAN_TWO_BYTE_OFFSET        (16u)
#define CAN_THREE_BYTE_OFFSET      (24u)

#if (CY_PSOC3 || CY_PSOC5)
    /* Set/Clear bits macro for CAN_RX mailbox(i) */
    /* Bit 0 within RX_CMD[i] */
    #define CAN_RX_ACK_MSG_SHIFT       (0u)
    #define CAN_RX_ACK_MSG             ((uint8) ((uint8) 0x01u << CAN_RX_ACK_MSG_SHIFT))
    /* Bit 2 within RX_CMD[i] */
    #define CAN_RX_RTR_ABORT_SHIFT     (2u)
    #define CAN_RX_RTR_ABORT_MASK      ((uint8) ((uint8) 0x01u << CAN_RX_RTR_ABORT_SHIFT))
    /* Bit 3 within RX_CMD[i] */
    #define CAN_RX_BUF_ENABLE_SHIFT    (3u)
    #define CAN_RX_BUF_ENABLE_MASK     ((uint8) ((uint8) 0x01u << CAN_RX_BUF_ENABLE_SHIFT))
    /* Bit 4 within RX_CMD[i] */
    #define CAN_RX_RTRREPLY_SHIFT      (4u)
    #define CAN_RX_RTRREPLY_MASK       ((uint8) ((uint8) 0x01u << CAN_RX_RTRREPLY_SHIFT))
    /* Bit 5 within RX_CMD[i] */
    #define CAN_RX_INT_ENABLE_SHIFT    (5u)
    #define CAN_RX_INT_ENABLE_MASK     ((uint8) ((uint8) 0x01u << CAN_RX_INT_ENABLE_SHIFT))
    /* Bit 6 within RX_CMD[i] */
    #define CAN_RX_LINKING_SHIFT       (6u)
    #define CAN_RX_LINKING_MASK        ((uint8) ((uint8) 0x01u << CAN_RX_LINKING_SHIFT))
    /* Bit 7 within RX_CMD[i] */
    #define CAN_RX_WPNL_SHIFT          (7u)
    #define CAN_RX_WPNL_MASK           ((uint8) ((uint8) 0x01u << CAN_RX_WPNL_SHIFT))
    /* Bits 19-16 within RX_CMD[i] */
    #define CAN_RX_DLC_VALUE_SHIFT     (0u)
    #define CAN_RX_DLC_VALUE_MASK      ((uint8) ((uint8) 0x0Fu << CAN_RX_DLC_VALUE_SHIFT))
    /* Bit 20 within RX_CMD[i] */
    #define CAN_RX_IDE_SHIFT           (4u)
    #define CAN_RX_IDE_MASK            ((uint8) ((uint8) 0x01u << CAN_RX_IDE_SHIFT))
    /* Bit 23 within RX_CMD[i] */
    #define CAN_RX_WPNH_SHIFT          (7u)
    #define CAN_RX_WPNH_MASK           ((uint8) ((uint8) 0x01u << CAN_RX_WPNH_SHIFT))

    #define CAN_RX_ACK_MESSAGE(i)    (CAN_RX[i].rxcmd.byte[0u] |= CAN_RX_ACK_MSG)
    #define CAN_RX_RTR_ABORT_MESSAGE(i) \
            (CAN_RX[i].rxcmd.byte[0u] |= CAN_RX_RTR_ABORT_MASK)
    #define CAN_RX_BUF_ENABLE(i)      \
            (CAN_RX[i].rxcmd.byte[0u] |= CAN_RX_BUF_ENABLE_MASK)
    #define CAN_RX_BUF_DISABLE(i)     \
            (CAN_RX[i].rxcmd.byte[0u] &= (uint8) (~CAN_RX_BUF_ENABLE_MASK))
    #define CAN_SET_RX_RTRREPLY(i)    \
            (CAN_RX[i].rxcmd.byte[0u] |= CAN_RX_RTRREPLY_MASK)
    #define CAN_CLEAR_RX_RTRREPLY(i)  \
            (CAN_RX[i].rxcmd.byte[0u] &= (uint8) (~CAN_RX_RTRREPLY_MASK))
    #define CAN_RX_INT_ENABLE(i)      \
            (CAN_RX[i].rxcmd.byte[0u] |= CAN_RX_INT_ENABLE_MASK)
    #define CAN_RX_INT_DISABLE(i)     \
            (CAN_RX[i].rxcmd.byte[0u] &= (uint8) (~CAN_RX_INT_ENABLE_MASK))
    #define CAN_SET_RX_LINKING(i)     \
            (CAN_RX[i].rxcmd.byte[0u] |= CAN_RX_LINKING_MASK)
    #define CAN_CLEAR_RX_LINKING(i)   \
            (CAN_RX[i].rxcmd.byte[0u] &= (uint8) (~CAN_RX_LINKING_MASK))
    #define CAN_SET_RX_WNPL(i)     (CAN_RX[i].rxcmd.byte[0u] |= CAN_RX_WPNL_MASK)
    #define CAN_CLEAR_RX_WNPL(i)      \
            (CAN_RX[i].rxcmd.byte[0u] &= (uint8) (~CAN_RX_WPNL_MASK))
    #define CAN_SET_RX_WNPH(i)     (CAN_RX[i].rxcmd.byte[2u] |= CAN_RX_WPNH_MASK)
    #define CAN_CLEAR_RX_WNPH(i)      \
            (CAN_RX[i].rxcmd.byte[2u] &= (uint8) (~CAN_RX_WPNH_MASK))
    #define CAN_GET_DLC(i)            \
            (CAN_RX[i].rxcmd.byte[2u] & CAN_RX_DLC_VALUE_MASK)
    #define CAN_GET_RX_IDE(i)         ((uint8) \
            (CAN_RX[i].rxcmd.byte[2u] & CAN_RX_IDE_MASK) >> CAN_RX_IDE_SHIFT)
    #define CAN_GET_RX_ID(i)          ((CAN_GET_RX_IDE(i)) ? \
            (CY_GET_REG32(CAN_RX_ID_PTR(i)) >> CAN_SET_TX_ID_EXTENDED_MSG_SHIFT) : \
            (CY_GET_REG32(CAN_RX_ID_PTR(i)) >> CAN_SET_TX_ID_STANDARD_MSG_SHIFT))

    /* Set/Clear bits macro for CAN_TX mailbox(i) */
    /* Bit 0 within TX_CMD[i] */
    #define CAN_TX_TRANSMIT_REQUEST_SHIFT (0u)
    #define CAN_TX_TRANSMIT_REQUEST ((uint8) ((uint8) 0x01u << CAN_TX_TRANSMIT_REQUEST_SHIFT))
    /* Bit 1 within TX_CMD[i] */
    #define CAN_TX_ABORT_SHIFT        (1u)
    #define CAN_TX_ABORT_MASK         ((uint8) ((uint8) 0x01u << CAN_TX_ABORT_SHIFT))
    /* Bit 2 within TX_CMD[i] */
    #define CAN_TRANSMIT_INT_ENABLE   (0x01u)
    #define CAN_TRANSMIT_INT_DISABLE  (0x00u)
    #define CAN_TX_INT_ENABLE_SHIFT   (2u)
    #define CAN_TX_INT_ENABLE_MASK    \
            ((uint32) ((uint32) 0x00000001u << CAN_TX_INT_ENABLE_SHIFT))
    /* Bit 3 within TX_CMD[i] */
    #define CAN_TX_WPNL_SHIFT         (3u)
    #define CAN_TX_WPNL_MASK          ((uint8) ((uint8) 0x01u << CAN_TX_WPNL_SHIFT))
    /* Bits 19-16 within TX_CMD[i] */
    #define CAN_TX_DLC_VALUE_SHIFT    (0u)
    #define CAN_TX_DLC_UPPER_VALUE_SHIFT (19u)
    #define CAN_TX_DLC_UPPER_VALUE    \
            ((uint32) ((uint32) 0x00000001u << CAN_TX_DLC_UPPER_VALUE_SHIFT))
    #define CAN_TX_DLC_VALUE_MASK     ((uint8) ((uint8) 0x0Fu << CAN_TX_DLC_VALUE_SHIFT))
    #define CAN_TX_DLC_MAX_VALUE      (8u)
    /* Bit 20 within TX_CMD[i] */
    #define CAN_TX_IDE_SHIFT          (20u)
    #define CAN_TX_IDE_MASK           ((uint32) ((uint32) 0x00000001u << CAN_TX_IDE_SHIFT))
    /* Bit 21 within TX_CMD[i] */
    #define CAN_TX_RTR_SHIFT          (21u)
    #define CAN_TX_RTR_MASK           ((uint32) ((uint32) 0x00000001u <<  CAN_TX_RTR_SHIFT))
    /* Bit 23 within TX_CMD[i] */
    #define CAN_TX_WPNH_SHIFT         (7u)
    #define CAN_TX_WPNH_MASK          ((uint8) ((uint8) 0x01u << CAN_TX_WPNH_SHIFT))

    #define CAN_TX_TRANSMIT_MESSAGE(i) \
            (CAN_TX[i].txcmd.byte[0u] |= CAN_TX_TRANSMIT_REQUEST)
    #define CAN_TX_ABORT_MESSAGE(i)   \
            (CAN_TX[i].txcmd.byte[0u] = (CAN_TX[i].txcmd.byte[0u] & \
            (uint8) (~CAN_TX_TRANSMIT_REQUEST)) | CAN_TX_ABORT_MASK)
    #define CAN_TX_INT_ENABLE(i)      \
            (CAN_TX[i].txcmd.byte[0u] |= (uint8) CAN_TX_INT_ENABLE_MASK)
    #define CAN_TX_INT_DISABLE(i)     \
            (CAN_TX[i].txcmd.byte[0u] &= (uint8) (~CAN_TX_INT_ENABLE_MASK))
    #define CAN_SET_TX_WNPL(i)        \
            (CAN_TX[i].txcmd.byte[0u] |= CAN_TX_WPNL_MASK)
    #define CAN_CLEAR_TX_WNPL(i)      \
            (CAN_TX[i].txcmd.byte[0u] &= (uint8) (~CAN_TX_WPNL_MASK))
    #define CAN_SET_TX_IDE(i)         (CAN_TX[i].txcmd.byte[2u] |= \
            (uint8) (CAN_TX_IDE_MASK >> CAN_TWO_BYTE_OFFSET))
    #define CAN_CLEAR_TX_IDE(i)       (CAN_TX[i].txcmd.byte[2u] &= \
            (uint8) (((uint32) (~CAN_TX_IDE_MASK)) >> CAN_TWO_BYTE_OFFSET))
    #define CAN_SET_TX_RTR(i)         (CAN_TX[i].txcmd.byte[2u] |= \
            (uint8) (CAN_TX_RTR_MASK >> CAN_TWO_BYTE_OFFSET))
    #define CAN_CLEAR_TX_RTR(i)       (CAN_TX[i].txcmd.byte[2u] &= \
            (uint8) (((uint32) (~CAN_TX_RTR_MASK)) >> CAN_TWO_BYTE_OFFSET))
    #define CAN_SET_TX_WNPH(i)        \
            (CAN_TX[i].txcmd.byte[2u] |= CAN_TX_WPNH_MASK)
    #define CAN_CLEAR_TX_WNPH(i)      \
            (CAN_TX[i].txcmd.byte[2u] &= (uint8) (~CAN_TX_WPNH_MASK))

    #define CAN_RX_DATA_BYTE(mailbox, i) (CAN_RX[mailbox].rxdata.byte[((i) > 3u) ? \
                                                      (7u - ((i) - 4u)) : (3u - (i))])
    #define CAN_TX_DATA_BYTE(mailbox, i) (CAN_TX[mailbox].txdata.byte[((i) > 3u) ? \
                                                      (7u - ((i) - 4u)) : (3u - (i))])
#else  /* CY_PSOC4 */
    /* Set/Clear bits macro for CAN_RX mailbox(i) */
    /* Bit 0 within RX_CMD[i] */
    #define CAN_RX_ACK_MSG_SHIFT       (0u)
    #define CAN_RX_ACK_MSG             ((uint32) ((uint32) 0x01u << CAN_RX_ACK_MSG_SHIFT))
    /* Bit 2 within RX_CMD[i] */
    #define CAN_RX_RTR_ABORT_SHIFT     (2u)
    #define CAN_RX_RTR_ABORT_MASK      ((uint32) ((uint32) 0x01u << CAN_RX_RTR_ABORT_SHIFT))
    /* Bit 3 within RX_CMD[i] */
    #define CAN_RX_BUF_ENABLE_SHIFT    (3u)
    #define CAN_RX_BUF_ENABLE_MASK     ((uint32) ((uint32) 0x01u << CAN_RX_BUF_ENABLE_SHIFT))
    /* Bit 4 within RX_CMD[i] */
    #define CAN_RX_RTRREPLY_SHIFT      (4u)
    #define CAN_RX_RTRREPLY_MASK       ((uint32) ((uint32) 0x01u << CAN_RX_RTRREPLY_SHIFT))
    /* Bit 5 within RX_CMD[i] */
    #define CAN_RX_INT_ENABLE_SHIFT    (5u)
    #define CAN_RX_INT_ENABLE_MASK     ((uint32) ((uint32) 0x01u << CAN_RX_INT_ENABLE_SHIFT))
    /* Bit 6 within RX_CMD[i] */
    #define CAN_RX_LINKING_SHIFT       (6u)
    #define CAN_RX_LINKING_MASK        ((uint32) ((uint32) 0x01u << CAN_RX_LINKING_SHIFT))
    /* Bit 7 within RX_CMD[i] */
    #define CAN_RX_WPNL_SHIFT          (7u)
    #define CAN_RX_WPNL_MASK           ((uint32) ((uint32) 0x01u << CAN_RX_WPNL_SHIFT))
    /* Bits 19-16 within RX_CMD[i] */
    #define CAN_RX_DLC_VALUE_SHIFT     (16u)
    #define CAN_RX_DLC_VALUE_MASK      ((uint32) ((uint32) 0x0Fu << CAN_RX_DLC_VALUE_SHIFT))
    /* Bit 20 within RX_CMD[i] */
    #define CAN_RX_IDE_SHIFT           (20u)
    #define CAN_RX_IDE_MASK            ((uint32) ((uint32) 0x01u << CAN_RX_IDE_SHIFT))
    /* Bit 23 within RX_CMD[i] */
    #define CAN_RX_WPNH_SHIFT          (23u)
    #define CAN_RX_WPNH_MASK           ((uint32) ((uint32) 0x01u << CAN_RX_WPNH_SHIFT))

    #define CAN_RX_ACK_MESSAGE(i)       (CAN_RX_CMD_REG(i) |= CAN_RX_ACK_MSG)
    #define CAN_RX_RTR_ABORT_MESSAGE(i) (CAN_RX_CMD_REG(i) |= \
                                                     CAN_RX_RTR_ABORT_MASK)
    #define CAN_RX_BUF_ENABLE(i)      (CAN_RX_CMD_REG(i) |= \
                                                   CAN_RX_BUF_ENABLE_MASK)
    #define CAN_RX_BUF_DISABLE(i)     (CAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~CAN_RX_BUF_ENABLE_MASK))
    #define CAN_SET_RX_RTRREPLY(i)    (CAN_RX_CMD_REG(i) |= \
                                                   CAN_RX_RTRREPLY_MASK)
    #define CAN_CLEAR_RX_RTRREPLY(i)  (CAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~CAN_RX_RTRREPLY_MASK))
    #define CAN_RX_INT_ENABLE(i)      (CAN_RX_CMD_REG(i) |= \
                                                   CAN_RX_INT_ENABLE_MASK)
    #define CAN_RX_INT_DISABLE(i)     (CAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~CAN_RX_INT_ENABLE_MASK))
    #define CAN_SET_RX_LINKING(i)     (CAN_RX_CMD_REG(i) |= CAN_RX_LINKING_MASK)
    #define CAN_CLEAR_RX_LINKING(i)   (CAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~CAN_RX_LINKING_MASK))
    #define CAN_SET_RX_WNPL(i)        (CAN_RX_CMD_REG(i) |= CAN_RX_WPNL_MASK)
    #define CAN_CLEAR_RX_WNPL(i)      (CAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~CAN_RX_WPNL_MASK))
    #define CAN_SET_RX_WNPH(i)        (CAN_RX_CMD_REG(i) |= CAN_RX_WPNH_MASK)
    #define CAN_CLEAR_RX_WNPH(i)      (CAN_RX_CMD_REG(i) &= \
                                                   (uint32) (~CAN_RX_WPNH_MASK))
    #define CAN_GET_DLC(i)            ((uint32) ((CAN_RX_CMD_REG(i) & \
            CAN_RX_DLC_VALUE_MASK) >> CAN_RX_DLC_VALUE_SHIFT))
    #define CAN_GET_RX_IDE(i)         ((uint32) ((CAN_RX_CMD_REG(i) & \
            CAN_RX_IDE_MASK) >> CAN_RX_IDE_SHIFT))
    #define CAN_GET_RX_ID(i)          ((CAN_GET_RX_IDE(i) == 0u) ? \
            (CAN_RX_ID_REG(i) >> CAN_SET_TX_ID_STANDARD_MSG_SHIFT) : \
            (CAN_RX_ID_REG(i) >> CAN_SET_TX_ID_EXTENDED_MSG_SHIFT))

    /* Set/Clear bits macro for CAN_TX mailbox(i) */
    /* Bit 0 within TX_CMD[i] */
    #define CAN_TX_TRANSMIT_REQUEST_SHIFT (0u)
    #define CAN_TX_TRANSMIT_REQUEST   \
            ((uint32) ((uint32) 0x01u << CAN_TX_TRANSMIT_REQUEST_SHIFT))
    /* Bit 1 within TX_CMD[i] */
    #define CAN_TX_ABORT_SHIFT        (1u)
    #define CAN_TX_ABORT_MASK         ((uint32) ((uint32) 0x01u << CAN_TX_ABORT_SHIFT))
    /* Bit 2 within TX_CMD[i] */
    #define CAN_TRANSMIT_INT_ENABLE   (0x01u)
    #define CAN_TRANSMIT_INT_DISABLE  (0x00u)
    #define CAN_TX_INT_ENABLE_SHIFT   (2u)
    #define CAN_TX_INT_ENABLE_MASK    \
            ((uint32) ((uint32) 0x00000001u << CAN_TX_INT_ENABLE_SHIFT))
    /* Bit 3 within TX_CMD[i] */
    #define CAN_TX_WPNL_SHIFT         (3u)
    #define CAN_TX_WPNL_MASK          ((uint32) ((uint32) 0x01u << CAN_TX_WPNL_SHIFT))
    /* Bits 19-16 within TX_CMD[i] */
    #define CAN_TX_DLC_VALUE_SHIFT    (0u)
    #define CAN_TX_DLC_UPPER_VALUE_SHIFT (19u)
    #define CAN_TX_DLC_UPPER_VALUE    \
            ((uint32) ((uint32) 0x00000001u << CAN_TX_DLC_UPPER_VALUE_SHIFT))
    #define CAN_TX_DLC_VALUE_MASK     ((uint32) ((uint32) 0x0Fu << CAN_TX_DLC_VALUE_SHIFT))
    #define CAN_TX_DLC_MAX_VALUE      (8u)
    /* Bit 20 within TX_CMD[i] */
    #define CAN_TX_IDE_SHIFT          (20u)
    #define CAN_TX_IDE_MASK           ((uint32) ((uint32) 0x00000001u << CAN_TX_IDE_SHIFT))
    /* Bit 21 within TX_CMD[i] */
    #define CAN_TX_RTR_SHIFT          (21u)
    #define CAN_TX_RTR_MASK           ((uint32) ((uint32) 0x00000001u <<  CAN_TX_RTR_SHIFT))
    /* Bit 23 within TX_CMD[i] */
    #define CAN_TX_WPNH_SHIFT         (23u)
    #define CAN_TX_WPNH_MASK          ((uint32) ((uint32) 0x01u << CAN_TX_WPNH_SHIFT))

    #define CAN_TX_TRANSMIT_MESSAGE(i) \
            (CAN_TX_CMD_REG(i) |= CAN_TX_TRANSMIT_REQUEST)
    #define CAN_TX_ABORT_MESSAGE(i) (CAN_TX_CMD_REG(i) = (CAN_TX_CMD_REG(i) & \
            (uint32) (~CAN_TX_TRANSMIT_REQUEST)) | CAN_TX_ABORT_MASK)
    #define CAN_TX_INT_ENABLE(i)    (CAN_TX_CMD_REG(i) |= CAN_TX_INT_ENABLE_MASK)
    #define CAN_TX_INT_DISABLE(i)   (CAN_TX_CMD_REG(i) &= \
                                                 (uint32) (~CAN_TX_INT_ENABLE_MASK))
    #define CAN_SET_TX_WNPL(i)     (CAN_TX_CMD_REG(i) |= CAN_TX_WPNL_MASK)
    #define CAN_CLEAR_TX_WNPL(i)   \
            (CAN_TX_CMD_REG(i) &= (uint32)(~CAN_TX_WPNL_MASK))
    #define CAN_SET_TX_IDE(i)      (CAN_TX_CMD_REG(i) |= CAN_TX_IDE_MASK)
    #define CAN_CLEAR_TX_IDE(i)    \
            (CAN_TX_CMD_REG(i) &= (uint32) (~CAN_TX_IDE_MASK))
    #define CAN_SET_TX_RTR(i)      (CAN_TX_CMD_REG(i) |= CAN_TX_RTR_MASK)
    #define CAN_CLEAR_TX_RTR(i)    \
            (CAN_TX_CMD_REG(i) &= (uint32) (~CAN_TX_RTR_MASK))
    #define CAN_SET_TX_WNPH(i)     (CAN_TX_CMD_REG(i) |= CAN_TX_WPNH_MASK)
    #define CAN_CLEAR_TX_WNPH(i)   \
            (CAN_TX_CMD_REG(i) &= (uint32)(~CAN_TX_WPNH_MASK))

    #define CAN_DATA_HIGH_ADDR     (4u)
    #define CAN_DATA_BYTE_MASK     ((uint32) 0xFFu)

    #define CAN_RX_DATA_BYTE(mailbox, i) (((i) > 3u) ? \
            (uint8) (CAN_RX_DATA_HI_REG(mailbox) >> ((7u - (i)) * CAN_ONE_BYTE_OFFSET)) : \
            (uint8) (CAN_RX_DATA_LO_REG(mailbox) >> ((3u - (i)) * CAN_ONE_BYTE_OFFSET)))

    #define CAN_TX_DATA_BYTE(mailbox, i, byte) (((i) > 3u) ? \
        (CAN_TX_DATA_HI_REG(mailbox) = (CAN_TX_DATA_HI_REG(mailbox) & \
        (uint32) (~((uint32) (CAN_DATA_BYTE_MASK << ((7u - (i)) * CAN_ONE_BYTE_OFFSET))))) | \
        (uint32) ((uint32) (byte) << ((7u - (i)) * CAN_ONE_BYTE_OFFSET))) : \
        (CAN_TX_DATA_LO_REG(mailbox) = (CAN_TX_DATA_LO_REG(mailbox) & \
        (uint32) (~((uint32) (CAN_DATA_BYTE_MASK << ((3u - (i)) * CAN_ONE_BYTE_OFFSET))))) | \
        (uint32) ((uint32) (byte) << ((3u - (i)) * CAN_ONE_BYTE_OFFSET))))
#endif /* CY_PSOC3 || CY_PSOC5 */

#if (CY_PSOC3 || CY_PSOC5)
    #define CAN_DATA_BYTE_1            (3u)
    #define CAN_DATA_BYTE_2            (2u)
    #define CAN_DATA_BYTE_3            (1u)
    #define CAN_DATA_BYTE_4            (0u)
    #define CAN_DATA_BYTE_5            (7u)
    #define CAN_DATA_BYTE_6            (6u)
    #define CAN_DATA_BYTE_7            (5u)
    #define CAN_DATA_BYTE_8            (4u)

    /* Macros for access to RX DATA for mailbox(i) */
    #define CAN_RX_DATA_BYTE1(i)       CAN_RX[i].rxdata.byte[CAN_DATA_BYTE_1]
    #define CAN_RX_DATA_BYTE2(i)       CAN_RX[i].rxdata.byte[CAN_DATA_BYTE_2]
    #define CAN_RX_DATA_BYTE3(i)       CAN_RX[i].rxdata.byte[CAN_DATA_BYTE_3]
    #define CAN_RX_DATA_BYTE4(i)       CAN_RX[i].rxdata.byte[CAN_DATA_BYTE_4]
    #define CAN_RX_DATA_BYTE5(i)       CAN_RX[i].rxdata.byte[CAN_DATA_BYTE_5]
    #define CAN_RX_DATA_BYTE6(i)       CAN_RX[i].rxdata.byte[CAN_DATA_BYTE_6]
    #define CAN_RX_DATA_BYTE7(i)       CAN_RX[i].rxdata.byte[CAN_DATA_BYTE_7]
    #define CAN_RX_DATA_BYTE8(i)       CAN_RX[i].rxdata.byte[CAN_DATA_BYTE_8]

    /* Macros for access to TX DATA for mailbox(i) */
    #define CAN_TX_DATA_BYTE1(i)       CAN_TX[i].txdata.byte[CAN_DATA_BYTE_1]
    #define CAN_TX_DATA_BYTE2(i)       CAN_TX[i].txdata.byte[CAN_DATA_BYTE_2]
    #define CAN_TX_DATA_BYTE3(i)       CAN_TX[i].txdata.byte[CAN_DATA_BYTE_3]
    #define CAN_TX_DATA_BYTE4(i)       CAN_TX[i].txdata.byte[CAN_DATA_BYTE_4]
    #define CAN_TX_DATA_BYTE5(i)       CAN_TX[i].txdata.byte[CAN_DATA_BYTE_5]
    #define CAN_TX_DATA_BYTE6(i)       CAN_TX[i].txdata.byte[CAN_DATA_BYTE_6]
    #define CAN_TX_DATA_BYTE7(i)       CAN_TX[i].txdata.byte[CAN_DATA_BYTE_7]
    #define CAN_TX_DATA_BYTE8(i)       CAN_TX[i].txdata.byte[CAN_DATA_BYTE_8]
#else  /* CY_PSOC4 */
    /* Macros for access to RX DATA for mailbox(i) */
    #define CAN_RX_DATA_BYTE1(i)       \
            ((uint8) (CAN_RX_DATA_LO_REG(i) >> CAN_THREE_BYTE_OFFSET))
    #define CAN_RX_DATA_BYTE2(i)       \
            ((uint8) (CAN_RX_DATA_LO_REG(i) >> CAN_TWO_BYTE_OFFSET))
    #define CAN_RX_DATA_BYTE3(i)       \
            ((uint8) (CAN_RX_DATA_LO_REG(i) >> CAN_ONE_BYTE_OFFSET))
    #define CAN_RX_DATA_BYTE4(i)       ((uint8) CAN_RX_DATA_LO_REG(i))
    #define CAN_RX_DATA_BYTE5(i)       \
            ((uint8) (CAN_RX_DATA_HI_REG(i) >> CAN_THREE_BYTE_OFFSET))
    #define CAN_RX_DATA_BYTE6(i)       \
            ((uint8) (CAN_RX_DATA_HI_REG(i) >> CAN_TWO_BYTE_OFFSET))
    #define CAN_RX_DATA_BYTE7(i)       \
            ((uint8) (CAN_RX_DATA_HI_REG(i) >> CAN_ONE_BYTE_OFFSET))
    #define CAN_RX_DATA_BYTE8(i)       ((uint8) CAN_RX_DATA_HI_REG(i))

    /* Macros for access to TX DATA for mailbox(i) */
    #define CAN_TX_DATA_BYTE1(i, byte) \
            (CAN_TX_DATA_LO_REG(i) = (CAN_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (CAN_DATA_BYTE_MASK << CAN_THREE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << CAN_THREE_BYTE_OFFSET))
    #define CAN_TX_DATA_BYTE2(i, byte) \
            (CAN_TX_DATA_LO_REG(i) = (CAN_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (CAN_DATA_BYTE_MASK << CAN_TWO_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << CAN_TWO_BYTE_OFFSET))
    #define CAN_TX_DATA_BYTE3(i, byte) \
            (CAN_TX_DATA_LO_REG(i) = (CAN_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (CAN_DATA_BYTE_MASK << CAN_ONE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << CAN_ONE_BYTE_OFFSET))
    #define CAN_TX_DATA_BYTE4(i, byte) \
            (CAN_TX_DATA_LO_REG(i) = (CAN_TX_DATA_LO_REG(i) & \
            (uint32) (~CAN_DATA_BYTE_MASK)) | (uint32) (byte))
    #define CAN_TX_DATA_BYTE5(i, byte) \
            (CAN_TX_DATA_HI_REG(i) = (CAN_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (CAN_DATA_BYTE_MASK << CAN_THREE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << CAN_THREE_BYTE_OFFSET))
    #define CAN_TX_DATA_BYTE6(i, byte) \
            (CAN_TX_DATA_HI_REG(i) = (CAN_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (CAN_DATA_BYTE_MASK << CAN_TWO_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << CAN_TWO_BYTE_OFFSET))
    #define CAN_TX_DATA_BYTE7(i, byte) \
            (CAN_TX_DATA_HI_REG(i) = (CAN_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (CAN_DATA_BYTE_MASK << CAN_ONE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << CAN_ONE_BYTE_OFFSET))
    #define CAN_TX_DATA_BYTE8(i, byte) \
            (CAN_TX_DATA_HI_REG(i) = (CAN_TX_DATA_HI_REG(i) & \
            (uint32) (~CAN_DATA_BYTE_MASK)) | (uint32) (byte))
#endif /* CY_PSOC3 || CY_PSOC5 */

/* Macros for setting Tx Msg Identifier in CAN_TX_ID register */
#define CAN_SET_TX_ID_STANDARD_MSG_SHIFT  (21u)
#define CAN_SET_TX_ID_EXTENDED_MSG_SHIFT  (3u)
#define CAN_SET_TX_ID_STANDARD_MSG(i, id) (CY_SET_REG32(CAN_TX_ID_PTR(i), \
        (uint32) ((uint32) (id) << CAN_SET_TX_ID_STANDARD_MSG_SHIFT)))
#define CAN_SET_TX_ID_EXTENDED_MSG(i, id) (CY_SET_REG32(CAN_TX_ID_PTR(i), \
        (uint32) ((uint32) (id) << CAN_SET_TX_ID_EXTENDED_MSG_SHIFT)))

/* Mask for bits within CAN_CSR_CFG */
#define CAN_EDGE_MODE_SHIFT           (0u)
/* Bit 0 within CSR_CFG */
#define CAN_EDGE_MODE_MASK            ((uint8) ((uint8) 0x01u << CAN_EDGE_MODE_SHIFT))
#define CAN_SAMPLE_MODE_SHIFT         (1u)
/* Bit 1 within CSR_CFG */
#define CAN_SAMPLE_MODE_MASK          ((uint8) ((uint8) 0x01u << CAN_SAMPLE_MODE_SHIFT))
#define CAN_CFG_REG_SJW_SHIFT         (2u)
/* Bits 3-2 within CSR_CFG */
#define CAN_CFG_REG_SJW_MASK          ((uint8) ((uint8) 0x03u << CAN_CFG_REG_SJW_SHIFT))
#define CAN_CFG_REG_SJW_LOWER_LIMIT   (0x03u)  /* the lowest allowed value of cfg_sjw */
#define CAN_RESET_SHIFT               (4u)
/* Bit 4 within CSR_CFG    */
#define CAN_RESET_MASK                ((uint8) ((uint8) 0x01u << CAN_RESET_SHIFT))
#define CAN_CFG_REG_TSEG2_SHIFT       (5u)
/* Bits 7-5 within CSR_CFG */
#define CAN_CFG_REG_TSEG2_MASK        ((uint8) ((uint8) 0x07u << CAN_CFG_REG_TSEG2_SHIFT))
/* Highest allowed value of cfg_tseg2 */
#define CAN_CFG_REG_TSEG2_UPPER_LIMIT (0x07u)
/* Lowest allowed value of cfg_tseg2 */
#define CAN_CFG_REG_TSEG2_LOWER_LIMIT (0x02u)
/* Lowest allowed value of cfg_tseg2 if sample point is one point */
#define CAN_CFG_REG_TSEG2_EXCEPTION   (0x01u)
/* Bits 11-8 within CSR_CFG */
#define CAN_CFG_REG_TSEG1_SHIFT       (8u)
#define CAN_CFG_REG_TSEG1_MASK        (0x0Fu)
/* Highest allowed value of cfg_tseg1 */
#define CAN_CFG_REG_TSEG1_UPPER_LIMIT (0x0Fu)
/* Lowest allowed value of cfg_tseg1 */
#define CAN_CFG_REG_TSEG1_LOWER_LIMIT (0x02u)
#define CAN_ARBITER_SHIFT             (12u)

#if (CY_PSOC3 || CY_PSOC5)
    #define CAN_ARBITRATION_SHIFT     (4u)
    /* Bit 12 within CSR_CFG */
    #define CAN_ARBITRATION_MASK      ((uint8) ((uint8) 0x01u << CAN_ARBITRATION_SHIFT))
#else  /* CY_PSOC4 */
    #define CAN_ARBITRATION_SHIFT     (12u)
    /* Bit 12 within CSR_CFG */
    #define CAN_ARBITRATION_MASK      ((uint32) ((uint32) 0x01u << CAN_ARBITRATION_SHIFT))
    /* Bit 13 within CSR_CFG */
    #define CAN_ENDIANNESS_SHIFT      (13u)
    #define CAN_ENDIANNESS_MASK       ((uint32) ((uint32) 0x01u << CAN_ENDIANNESS_SHIFT))
    /* Bit 14 within CSR_CFG */
    #define CAN_ECR_MODE_SHIFT        (14u)
    #define CAN_ECR_MODE_MASK         ((uint32) ((uint32) 0x01u << CAN_ECR_MODE_SHIFT))
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Bits 23-16 within CSR_CFG */
#define CAN_BITRATE_SHIFT             (16u)
#define CAN_BITRATE_MASK              (0x7FFFu)
#define CAN_BITRATE_MASK_SHIFTED      \
        ((uint32) ((uint32) CAN_BITRATE_MASK << CAN_BITRATE_SHIFT))

/* Mask for bits within CAN_CSR_CMD */
#define CAN_MODE_SHIFT                (0u)
/* Bit 0 within CSR_CMD */
#define CAN_MODE_MASK                 ((uint8) ((uint8) 0x01u << CAN_MODE_SHIFT))
#define CAN_OPMODE_MASK_SHIFT         (1u)
/* Bit 1 within CSR_CMD */
#define CAN_OPMODE_MASK               ((uint8) ((uint8) 0x01u << CAN_OPMODE_MASK_SHIFT))

#if (CY_PSOC3 || CY_PSOC5)
    #define CAN_OPMODE_FIELD_MASK     ((uint8) ((uint8) 0x03u << CAN_MODE_SHIFT))
#else  /* CY_PSOC4 */
    #define CAN_OPMODE_FIELD_MASK     ((uint8) ((uint8) 0x07u << CAN_MODE_SHIFT))
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Mask for bits within CAN_CSR_CMD */
#define CAN_ERROR_STATE_SHIFT         (0u)
/* Bit 17-16 within ERR_SR */
#define CAN_ERROR_STATE_MASK          ((uint8) ((uint8) 0x03u << CAN_ERROR_STATE_SHIFT))

#if (CY_PSOC3 || CY_PSOC5)
    #define CAN_TX_ERROR_FLAG_SHIFT   (2u)
    /* Bit 18 within ERR_SR */
    #define CAN_TX_ERROR_FLAG_MASK    ((uint8) ((uint8) 0x01u << CAN_TX_ERROR_FLAG_SHIFT))
    #define CAN_RX_ERROR_FLAG_SHIFT   (3u)
    /* Bit 19 within ERR_SR */
    #define CAN_RX_ERROR_FLAG_MASK    ((uint8) ((uint8) 0x01u << CAN_RX_ERROR_FLAG_SHIFT))
#else  /* CY_PSOC4 */
    #define CAN_TX_ERROR_FLAG_SHIFT   (18u)
    /* Bit 18 within ERR_SR */
    #define CAN_TX_ERROR_FLAG_MASK    ((uint32) ((uint32) 0x01u << CAN_TX_ERROR_FLAG_SHIFT))
    #define CAN_RX_ERROR_FLAG_SHIFT   (19u)
    /* Bit 19 within ERR_SR */
    #define CAN_RX_ERROR_FLAG_MASK    ((uint32) ((uint32) 0x01u << CAN_RX_ERROR_FLAG_SHIFT))

    /* Mask and Macros for bits within CAN_ECR_REG */
    #define CAN_ECR_STATUS_ARM        (0x01u)
    /* Mask for clearing CANINT_STATUS */
    #define CAN_INT_STATUS_MASK       (0x00001FFCu)
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Mask and Macros for bits within CAN_INT_EN_REG */
#define CAN_GLOBAL_INT_SHIFT          (0u)
#define CAN_ARBITRATION_LOST_SHIFT    (2u)
#define CAN_OVERLOAD_ERROR_SHIFT      (3u)
#define CAN_BIT_ERROR_SHIFT           (4u)
#define CAN_STUFF_ERROR_SHIFT         (5u)
#define CAN_ACK_ERROR_SHIFT           (6u)
#define CAN_FORM_ERROR_SHIFT          (7u)

#if (CY_PSOC3 || CY_PSOC5)
    #define CAN_CRC_ERROR_SHIFT       (0u)
    #define CAN_BUS_OFF_SHIFT         (1u)
    #define CAN_RX_MSG_LOST_SHIFT     (2u)
    #define CAN_TX_MESSAGE_SHIFT      (3u)
    #define CAN_RX_MESSAGE_SHIFT      (4u)

    /* Bit 0 within INT_EN */
    #define CAN_GLOBAL_INT_MASK       ((uint8) ((uint8) 0x01u << CAN_GLOBAL_INT_SHIFT))
    /* Bit 2 within INT_EN and INT_SR */
    #define CAN_ARBITRATION_LOST_MASK ((uint8) ((uint8) 0x01u << CAN_ARBITRATION_LOST_SHIFT))
    /* Bit 3 within INT_EN and INT_SR */
    #define CAN_OVERLOAD_ERROR_MASK   ((uint8) ((uint8) 0x01u << CAN_OVERLOAD_ERROR_SHIFT))
    /* Bit 4 within INT_EN and INT_SR */
    #define CAN_BIT_ERROR_MASK        ((uint8) ((uint8) 0x01u << CAN_BIT_ERROR_SHIFT))
    /* Bit 5 within INT_EN and INT_SR */
    #define CAN_STUFF_ERROR_MASK      ((uint8) ((uint8) 0x01u << CAN_STUFF_ERROR_SHIFT))
    /* Bit 6 within INT_EN and INT_SR */
    #define CAN_ACK_ERROR_MASK        ((uint8) ((uint8) 0x01u << CAN_ACK_ERROR_SHIFT))
    /* Bit 7 within INT_EN and INT_SR */
    #define CAN_FORM_ERROR_MASK       ((uint8) ((uint8) 0x01u << CAN_FORM_ERROR_SHIFT))
    /* Bit 8 within INT_EN and INT_SR */
    #define CAN_CRC_ERROR_MASK        ((uint8) ((uint8) 0x01u << CAN_CRC_ERROR_SHIFT))
    /* Bit 9 within INT_EN and INT_SR */
    #define CAN_BUS_OFF_MASK          ((uint8) ((uint8) 0x01u << CAN_BUS_OFF_SHIFT))
    /* Bit 10 within INT_EN and INT_SR */
    #define CAN_RX_MSG_LOST_MASK      ((uint8) ((uint8) 0x01u << CAN_RX_MSG_LOST_SHIFT))
    /* Bit 11 within INT_EN and INT_SR */
    #define CAN_TX_MESSAGE_MASK       ((uint8) ((uint8) 0x01u << CAN_TX_MESSAGE_SHIFT))
    /* Bit 12 within INT_EN and INT_SR */
    #define CAN_RX_MESSAGE_MASK       ((uint8) ((uint8) 0x01u << CAN_RX_MESSAGE_SHIFT))

    #define CAN_ARBITRATION_LOST_INT_ENABLE   \
            (CAN_INT_EN_REG.byte[0u] |= CAN_ARBITRATION_LOST_MASK)
    #define CAN_ARBITRATION_LOST_INT_DISABLE  \
            (CAN_INT_EN_REG.byte[0u] &= (uint8) (~CAN_ARBITRATION_LOST_MASK))
    #define CAN_OVERLOAD_ERROR_INT_ENABLE     \
            (CAN_INT_EN_REG.byte[0u] |= CAN_OVERLOAD_ERROR_MASK)
    #define CAN_OVERLOAD_ERROR_INT_DISABLE    \
            (CAN_INT_EN_REG.byte[0u] &= (uint8) (~CAN_OVERLOAD_ERROR_MASK))
    #define CAN_BIT_ERROR_LOST_INT_ENABLE     \
            (CAN_INT_EN_REG.byte[0u] |= CAN_BIT_ERROR_MASK)
    #define CAN_BIT_ERROR_LOST_INT_DISABLE    \
            (CAN_INT_EN_REG.byte[0u] &= (uint8) (~CAN_BIT_ERROR_MASK))
    #define CAN_STUFF_ERROR_INT_ENABLE        \
            (CAN_INT_EN_REG.byte[0u] |= CAN_STUFF_ERROR_MASK)
    #define CAN_STUFF_ERROR_INT_DISABLE       \
            (CAN_INT_EN_REG.byte[0u] &= (uint8) (~CAN_STUFF_ERROR_MASK))
    #define CAN_ACK_ERROR_INT_ENABLE          \
            (CAN_INT_EN_REG.byte[0u] |= CAN_ACK_ERROR_MASK)
    #define CAN_ACK_ERROR_INT_DISABLE         \
            (CAN_INT_EN_REG.byte[0u] &= (uint8) (~CAN_ACK_ERROR_MASK))
    #define CAN_FORM_ERROR_INT_ENABLE         \
            (CAN_INT_EN_REG.byte[0u] |= CAN_FORM_ERROR_MASK)
    #define CAN_FORM_ERROR_INT_DISABLE        \
            (CAN_INT_EN_REG.byte[0u] &= (uint8) (~CAN_FORM_ERROR_MASK))
    #define CAN_CRC_ERROR_INT_ENABLE          \
            (CAN_INT_EN_REG.byte[1u] |= CAN_CRC_ERROR_MASK)
    #define CAN_CRC_ERROR_INT_DISABLE         \
            (CAN_INT_EN_REG.byte[1u] &= (uint8) (~CAN_CRC_ERROR_MASK))
    #define CAN_BUS_OFF_INT_ENABLE            \
            (CAN_INT_EN_REG.byte[1u] |= CAN_BUS_OFF_MASK)
    #define CAN_BUS_OFF_INT_DISABLE           \
            (CAN_INT_EN_REG.byte[1u] &= (uint8) (~CAN_BUS_OFF_MASK))
    #define CAN_RX_MSG_LOST_INT_ENABLE        \
            (CAN_INT_EN_REG.byte[1u] |= CAN_RX_MSG_LOST_MASK)
    #define CAN_RX_MSG_LOST_INT_DISABLE       \
            (CAN_INT_EN_REG.byte[1u] &= (uint8) (~CAN_RX_MSG_LOST_MASK))
    #define CAN_TX_MSG_INT_ENABLE             \
            (CAN_INT_EN_REG.byte[1u] |= CAN_TX_MESSAGE_MASK)
    #define CAN_TX_MSG_INT_DISABLE            \
            (CAN_INT_EN_REG.byte[1u] &= (uint8) (~CAN_TX_MESSAGE_MASK))
    #define CAN_RX_MSG_INT_ENABLE             \
            (CAN_INT_EN_REG.byte[1u] |= CAN_RX_MESSAGE_MASK)
    #define CAN_RX_MSG_INT_DISABLE            \
            (CAN_INT_EN_REG.byte[1u] &= (uint8) (~CAN_RX_MESSAGE_MASK))
#else  /* CY_PSOC4 */
    #define CAN_CRC_ERROR_SHIFT       (8u)
    #define CAN_BUS_OFF_SHIFT         (9u)
    #define CAN_RX_MSG_LOST_SHIFT     (10u)
    #define CAN_TX_MESSAGE_SHIFT      (11u)
    #define CAN_RX_MESSAGE_SHIFT      (12u)

    /* Mask and Macros for bits within CAN_INT_EN_REG */
    /* Bit 0 within INT_EN */
    #define CAN_GLOBAL_INT_MASK       ((uint32) ((uint32) 0x01u << CAN_GLOBAL_INT_SHIFT))
    /* Bit 2 within INT_EN and INT_SR */
    #define CAN_ARBITRATION_LOST_MASK ((uint32) ((uint32) 0x01u << CAN_ARBITRATION_LOST_SHIFT))
    /* Bit 3 within INT_EN and INT_SR */
    #define CAN_OVERLOAD_ERROR_MASK   ((uint32) ((uint32) 0x01u << CAN_OVERLOAD_ERROR_SHIFT))
    /* Bit 4 within INT_EN and INT_SR */
    #define CAN_BIT_ERROR_MASK        ((uint32) ((uint32) 0x01u << CAN_BIT_ERROR_SHIFT))
    /* Bit 5 within INT_EN and INT_SR */
    #define CAN_STUFF_ERROR_MASK      ((uint32) ((uint32) 0x01u << CAN_STUFF_ERROR_SHIFT))
    /* Bit 6 within INT_EN and INT_SR */
    #define CAN_ACK_ERROR_MASK        ((uint32) ((uint32) 0x01u << CAN_ACK_ERROR_SHIFT))
    /* Bit 7 within INT_EN and INT_SR */
    #define CAN_FORM_ERROR_MASK       ((uint32) ((uint32) 0x01u << CAN_FORM_ERROR_SHIFT))
    /* Bit 8 within INT_EN and INT_SR */
    #define CAN_CRC_ERROR_MASK        ((uint32) ((uint32) 0x01u << CAN_CRC_ERROR_SHIFT))
    /* Bit 9 within INT_EN and INT_SR */
    #define CAN_BUS_OFF_MASK          ((uint32) ((uint32) 0x01u << CAN_BUS_OFF_SHIFT))
    /* Bit 10 within INT_EN and INT_SR */
    #define CAN_RX_MSG_LOST_MASK      ((uint32) ((uint32) 0x01u << CAN_RX_MSG_LOST_SHIFT))
    /* Bit 11 within INT_EN and INT_SR */
    #define CAN_TX_MESSAGE_MASK       ((uint32) ((uint32) 0x01u << CAN_TX_MESSAGE_SHIFT))
    /* Bit 12 within INT_EN and INT_SR */
    #define CAN_RX_MESSAGE_MASK       ((uint32) ((uint32) 0x01u << CAN_RX_MESSAGE_SHIFT))

    #define CAN_ARBITRATION_LOST_INT_ENABLE   \
            (CAN_INT_EN_REG |= CAN_ARBITRATION_LOST_MASK)
    #define CAN_ARBITRATION_LOST_INT_DISABLE  \
            (CAN_INT_EN_REG &= (uint32) (~CAN_ARBITRATION_LOST_MASK))
    #define CAN_OVERLOAD_ERROR_INT_ENABLE     \
            (CAN_INT_EN_REG |= CAN_OVERLOAD_ERROR_MASK)
    #define CAN_OVERLOAD_ERROR_INT_DISABLE    \
            (CAN_INT_EN_REG &= (uint32) (~CAN_OVERLOAD_ERROR_MASK))
    #define CAN_BIT_ERROR_LOST_INT_ENABLE     \
            (CAN_INT_EN_REG |= CAN_BIT_ERROR_MASK)
    #define CAN_BIT_ERROR_LOST_INT_DISABLE    \
            (CAN_INT_EN_REG &= (uint32) (~CAN_BIT_ERROR_MASK))
    #define CAN_STUFF_ERROR_INT_ENABLE        \
            (CAN_INT_EN_REG |= CAN_STUFF_ERROR_MASK)
    #define CAN_STUFF_ERROR_INT_DISABLE       \
            (CAN_INT_EN_REG &= (uint32) (~CAN_STUFF_ERROR_MASK))
    #define CAN_ACK_ERROR_INT_ENABLE          \
            (CAN_INT_EN_REG |= CAN_ACK_ERROR_MASK)
    #define CAN_ACK_ERROR_INT_DISABLE         \
            (CAN_INT_EN_REG &= (uint32) (~CAN_ACK_ERROR_MASK))
    #define CAN_FORM_ERROR_INT_ENABLE         \
            (CAN_INT_EN_REG |= CAN_FORM_ERROR_MASK)
    #define CAN_FORM_ERROR_INT_DISABLE        \
            (CAN_INT_EN_REG &= (uint32) (~CAN_FORM_ERROR_MASK))
    #define CAN_CRC_ERROR_INT_ENABLE          \
            (CAN_INT_EN_REG |= CAN_CRC_ERROR_MASK)
    #define CAN_CRC_ERROR_INT_DISABLE         \
            (CAN_INT_EN_REG &= (uint32) (~CAN_CRC_ERROR_MASK))
    #define CAN_BUS_OFF_INT_ENABLE            \
            (CAN_INT_EN_REG |= CAN_BUS_OFF_MASK)
    #define CAN_BUS_OFF_INT_DISABLE           \
            (CAN_INT_EN_REG &= (uint32) (~CAN_BUS_OFF_MASK))
    #define CAN_RX_MSG_LOST_INT_ENABLE        \
            (CAN_INT_EN_REG |= CAN_RX_MSG_LOST_MASK)
    #define CAN_RX_MSG_LOST_INT_DISABLE       \
            (CAN_INT_EN_REG &= (uint32) (~CAN_RX_MSG_LOST_MASK))
    #define CAN_TX_MSG_INT_ENABLE             \
            (CAN_INT_EN_REG |= CAN_TX_MESSAGE_MASK)
    #define CAN_TX_MSG_INT_DISABLE            \
            (CAN_INT_EN_REG &= (uint32) (~CAN_TX_MESSAGE_MASK))
    #define CAN_RX_MSG_INT_ENABLE             \
            (CAN_INT_EN_REG |= CAN_RX_MESSAGE_MASK)
    #define CAN_RX_MSG_INT_DISABLE            \
            (CAN_INT_EN_REG &= (uint32) (~CAN_RX_MESSAGE_MASK))

    /* Bit 13 within INT_EN and INT_SR */
    #define CAN_RTR_MSG_SHIFT              (13u)
    #define CAN_RTR_MSG_MASK               ((uint32) ((uint32) 0x01u << CAN_RTR_MSG_SHIFT))
    #define CAN_RTR_MSG_INT_ENABLE         (CAN_INT_EN_REG |= CAN_RTR_MSG_MASK)
    #define CAN_RTR_MSG_INT_DISABLE        \
            (CAN_INT_EN_REG &= (uint32) (~CAN_RTR_MSG_MASK))
    /* Bit 14 within INT_EN and INT_SR */
    #define CAN_STUCK_AT_ZERO_SHIFT        (14u)
    #define CAN_STUCK_AT_ZERO_MASK         \
            ((uint32) ((uint32) 0x01u << CAN_STUCK_AT_ZERO_SHIFT))
    #define CAN_STUCK_AT_ZERO_INT_ENABLE   \
            (CAN_INT_EN_REG |= CAN_STUCK_AT_ZERO_MASK)
    #define CAN_STUCK_AT_ZERO_INT_DISABLE  \
            (CAN_INT_EN_REG &= (uint32) (~CAN_STUCK_AT_ZERO_MASK))
    /* Bit 15 within INT_EN and INT_SR */
    #define CAN_SST_FAILURE_SHIFT          (15u)
    #define CAN_SST_FAILURE_MASK           \
            ((uint32) ((uint32) 0x01u << CAN_SST_FAILURE_SHIFT))
    #define CAN_SST_FAILURE_INT_ENABLE     \
            (CAN_INT_EN_REG |= CAN_SST_FAILURE_MASK)
    #define CAN_SST_FAILURE_INT_DISABLE    \
            (CAN_INT_EN_REG &= (uint32) (~CAN_SST_FAILURE_MASK))
#endif /* CY_PSOC3 || CY_PSOC5 */

#define CAN_GLOBAL_INT_ENABLE_SHIFT        (0u)
#define CAN_ARBITRATION_LOST_ENABLE_SHIFT  (2u)
#define CAN_OVERLOAD_ERROR_ENABLE_SHIFT    (3u)
#define CAN_BIT_ERROR_ENABLE_SHIFT         (4u)
#define CAN_STUFF_ERROR_ENABLE_SHIFT       (5u)
#define CAN_ACK_ERROR_ENABLE_SHIFT         (6u)
#define CAN_FORM_ERROR_ENABLE_SHIFT        (7u)
#define CAN_CRC_ERROR_ENABLE_SHIFT         (8u)
#define CAN_BUS_OFF_ENABLE_SHIFT           (9u)
#define CAN_RX_MSG_LOST_ENABLE_SHIFT       (10u)
#define CAN_TX_MESSAGE_ENABLE_SHIFT        (11u)
#define CAN_RX_MESSAGE_ENABLE_SHIFT        (12u)

#define CAN_GLOBAL_INT_ENABLE    ((uint16) ((uint16) 0x01u << CAN_GLOBAL_INT_ENABLE_SHIFT))
#define CAN_ARBITRATION_LOST_ENABLE \
        ((uint16) ((uint16) 0x01u << CAN_ARBITRATION_LOST_ENABLE_SHIFT))
#define CAN_OVERLOAD_ERROR_ENABLE   \
        ((uint16) ((uint16) 0x01u << CAN_OVERLOAD_ERROR_ENABLE_SHIFT))
#define CAN_BIT_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << CAN_BIT_ERROR_ENABLE_SHIFT))
#define CAN_STUFF_ERROR_ENABLE   ((uint16) ((uint16) 0x01u << CAN_STUFF_ERROR_ENABLE_SHIFT))
#define CAN_ACK_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << CAN_ACK_ERROR_ENABLE_SHIFT))
#define CAN_FORM_ERROR_ENABLE    ((uint16) ((uint16) 0x01u << CAN_FORM_ERROR_ENABLE_SHIFT))
#define CAN_CRC_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << CAN_CRC_ERROR_ENABLE_SHIFT))
#define CAN_BUS_OFF_ENABLE       ((uint16) ((uint16) 0x01u << CAN_BUS_OFF_ENABLE_SHIFT))
#define CAN_RX_MSG_LOST_ENABLE   ((uint16) ((uint16) 0x01u << CAN_RX_MSG_LOST_ENABLE_SHIFT))
#define CAN_TX_MESSAGE_ENABLE    ((uint16) ((uint16) 0x01u << CAN_TX_MESSAGE_ENABLE_SHIFT))
#define CAN_RX_MESSAGE_ENABLE    ((uint16) ((uint16) 0x01u << CAN_RX_MESSAGE_ENABLE_SHIFT))

#if (!(CY_PSOC3 || CY_PSOC5))
    #define CAN_RTR_MESSAGE_ENABLE_SHIFT   (13u)
    #define CAN_STUCK_AT_ZERO_ENABLE_SHIFT (14u)
    #define CAN_SST_FAILURE_ENABLE_SHIFT   (15u)

    #define CAN_RTR_MESSAGE_ENABLE   \
            ((uint16) ((uint16) 0x01u << CAN_RTR_MESSAGE_ENABLE_SHIFT))
    #define CAN_STUCK_AT_ZERO_ENABLE \
            ((uint16) ((uint16) 0x01u << CAN_STUCK_AT_ZERO_ENABLE_SHIFT))
    #define CAN_SST_FAILURE_ENABLE   \
            ((uint16) ((uint16) 0x01u << CAN_SST_FAILURE_ENABLE_SHIFT))
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#define CAN_REG_ADDR_MASK        ((uint32) 0x0000FFFFu)


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

#define CAN_TREE_BYTE_OFFSET     (CAN_THREE_BYTE_OFFSET)

/* CAN_SetRestartType() parameters */
#define CAN_RESTART_BY_HAND      (CAN_MANUAL_RESTART)

/* CAN_SetOpMode() parameters */
#define CAN_LISTEN_ONLY          (CAN_LISTEN_ONLY_MODE)
#define CAN_ACTIVE_MODE          (CAN_INITIAL_MODE)

#ifdef CAN_ISR_CALLBACK
    #define CAN_ISR_INTERRUPT_CALLBACK
    #define CAN_ISR_InterruptCallback  CAN_Isr_Callback
#endif

#endif /* CY_CAN_CAN_H */


/* [] END OF FILE */
