/*******************************************************************************
* File Name: PUERTO_CAN_1.h
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

#if !defined(CY_CAN_PUERTO_CAN_1_H)
#define CY_CAN_PUERTO_CAN_1_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"
#include "cyapicallbacks.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component CAN_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

extern uint8 PUERTO_CAN_1_initVar;

#define PUERTO_CAN_1_INT_ISR_DISABLE                (0u)


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define PUERTO_CAN_1_ARB_LOST                       (0u)
#define PUERTO_CAN_1_OVERLOAD                       (0u)
#define PUERTO_CAN_1_BIT_ERR                        (0u)
#define PUERTO_CAN_1_STUFF_ERR                      (0u)
#define PUERTO_CAN_1_ACK_ERR                        (0u)
#define PUERTO_CAN_1_FORM_ERR                       (0u)
#define PUERTO_CAN_1_CRC_ERR                        (0u)
#define PUERTO_CAN_1_BUS_OFF                        (1u)
#define PUERTO_CAN_1_RX_MSG_LOST                    (0u)
#define PUERTO_CAN_1_TX_MESSAGE                     (0u)
#define PUERTO_CAN_1_RX_MESSAGE                     (1u)
#define PUERTO_CAN_1_ARB_LOST_USE_HELPER            (1u)
#define PUERTO_CAN_1_OVERLOAD_USE_HELPER            (1u)
#define PUERTO_CAN_1_BIT_ERR_USE_HELPER             (1u)
#define PUERTO_CAN_1_STUFF_ERR_USE_HELPER           (1u)
#define PUERTO_CAN_1_ACK_ERR_USE_HELPER             (1u)
#define PUERTO_CAN_1_FORM_ERR_USE_HELPER            (1u)
#define PUERTO_CAN_1_CRC_ERR_USE_HELPER             (1u)
#define PUERTO_CAN_1_BUS_OFF_USE_HELPER             (1u)
#define PUERTO_CAN_1_RX_MSG_LOST_USE_HELPER         (1u)
#define PUERTO_CAN_1_TX_MESSAGE_USE_HELPER          (1u)
#define PUERTO_CAN_1_RX_MESSAGE_USE_HELPER          (1u)

#if (!(CY_PSOC3 || CY_PSOC5))
    #define PUERTO_CAN_1_RTR_AUTO_MSG_SENT          (0u)
    #define PUERTO_CAN_1_STUCK_AT_ZERO              (0u)
    #define PUERTO_CAN_1_SST_FAILURE                (0u)

    #define PUERTO_CAN_1_RTR_MESSAGE_USE_HELPER     (1u)
    #define PUERTO_CAN_1_STUCK_AT_ZERO_USE_HELPER   (1u)
    #define PUERTO_CAN_1_SST_FAILURE_USE_HELPER     (1u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#define PUERTO_CAN_1_ADVANCED_INTERRUPT_CFG         (0u)

/* TX/RX Function Enable */
#define PUERTO_CAN_1_TX0_FUNC_ENABLE   (1u)
#define PUERTO_CAN_1_TX1_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_TX2_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_TX3_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_TX4_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_TX5_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_TX6_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_TX7_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_RX0_FUNC_ENABLE   (1u)
#define PUERTO_CAN_1_RX1_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_RX2_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_RX3_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_RX4_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_RX5_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_RX6_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_RX7_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_RX8_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_RX9_FUNC_ENABLE   (0u)
#define PUERTO_CAN_1_RX10_FUNC_ENABLE  (0u)
#define PUERTO_CAN_1_RX11_FUNC_ENABLE  (0u)
#define PUERTO_CAN_1_RX12_FUNC_ENABLE  (0u)
#define PUERTO_CAN_1_RX13_FUNC_ENABLE  (0u)
#define PUERTO_CAN_1_RX14_FUNC_ENABLE  (0u)
#define PUERTO_CAN_1_RX15_FUNC_ENABLE  (0u)
#define PUERTO_CAN_1_RX_MAILBOX_TYPE   (0x1u)
#define PUERTO_CAN_1_TX_MAILBOX_TYPE   (0x1u)


/***************************************
*        Data Struct Definition
***************************************/

/* Struct for DATA of BASIC CAN mailbox */
typedef struct
{
    uint8 byte[8u];
} PUERTO_CAN_1_DATA_BYTES_MSG;

/* Struct for DATA of CAN RX register */
typedef struct
{
    reg8 byte[8u];
} PUERTO_CAN_1_DATA_BYTES;

/* Struct for 32-bit CAN register */
typedef struct
{
    reg8 byte[4u];
} PUERTO_CAN_1_REG_32;

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
    PUERTO_CAN_1_DATA_BYTES_MSG *msg;
} PUERTO_CAN_1_TX_MSG;

/* Constant configuration of CAN RX */
typedef struct
{
    uint8 rxmailbox;
    uint32 rxcmd;
    uint32 rxamr;
    uint32 rxacr;
} PUERTO_CAN_1_RX_CFG;

/* Constant configuration of CAN TX */
typedef struct
{
    uint8 txmailbox;
    uint32 txcmd;
    uint32 txid;
} PUERTO_CAN_1_TX_CFG;

/* CAN RX registers */
typedef struct
{
    PUERTO_CAN_1_REG_32 rxcmd;
    PUERTO_CAN_1_REG_32 rxid;
    PUERTO_CAN_1_DATA_BYTES rxdata;
    PUERTO_CAN_1_REG_32 rxamr;
    PUERTO_CAN_1_REG_32 rxacr;
    PUERTO_CAN_1_REG_32 rxamrd;
    PUERTO_CAN_1_REG_32 rxacrd;
} PUERTO_CAN_1_RX_STRUCT;

/* CAN TX registers */
typedef struct
{
    PUERTO_CAN_1_REG_32 txcmd;
    PUERTO_CAN_1_REG_32 txid;
    PUERTO_CAN_1_DATA_BYTES txdata;
} PUERTO_CAN_1_TX_STRUCT;

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
} PUERTO_CAN_1_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8  PUERTO_CAN_1_Init(void) ;
uint8  PUERTO_CAN_1_Start(void) ;
uint8  PUERTO_CAN_1_Stop(void) ;
uint8  PUERTO_CAN_1_Enable(void) ;
uint8  PUERTO_CAN_1_GlobalIntEnable(void) ;
uint8  PUERTO_CAN_1_GlobalIntDisable(void) ;
uint8  PUERTO_CAN_1_SetPreScaler(uint16 bitrate) ;
uint8  PUERTO_CAN_1_SetArbiter(uint8 arbiter) ;
uint8  PUERTO_CAN_1_SetTsegSample(uint8 cfgTseg1, uint8 cfgTseg2, uint8 sjw, uint8 sm)
                                                ;
uint8  PUERTO_CAN_1_SetRestartType(uint8 reset) ;
uint8  PUERTO_CAN_1_SetEdgeMode(uint8 edge) ;
uint8  PUERTO_CAN_1_SetOpMode(uint8 opMode) ;
uint8  PUERTO_CAN_1_RXRegisterInit(reg32 *regAddr, uint32 config)
                                            ;
uint8  PUERTO_CAN_1_SetIrqMask(uint16 mask) ;
uint8  PUERTO_CAN_1_GetTXErrorFlag(void) ;
uint8  PUERTO_CAN_1_GetRXErrorFlag(void) ;
uint8  PUERTO_CAN_1_GetTXErrorCount(void) ;
uint8  PUERTO_CAN_1_GetRXErrorCount(void) ;
uint8  PUERTO_CAN_1_GetErrorState(void) ;
void   PUERTO_CAN_1_Sleep(void) ;
void   PUERTO_CAN_1_Wakeup(void) ;
void   PUERTO_CAN_1_SaveConfig(void) ;
void   PUERTO_CAN_1_RestoreConfig(void) ;

#if (!(CY_PSOC3 || CY_PSOC5))
    uint8  PUERTO_CAN_1_SetSwapDataEndianness(uint8 swap);
    uint8  PUERTO_CAN_1_SetErrorCaptureRegisterMode(uint8 ecrMode);
    uint32 PUERTO_CAN_1_ReadErrorCaptureRegister(void);
    uint8  PUERTO_CAN_1_ArmErrorCaptureRegister(void);
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#if (PUERTO_CAN_1_ARB_LOST)
    void PUERTO_CAN_1_ArbLostIsr(void) ;
#endif /* PUERTO_CAN_1_ARB_LOST */
#if (PUERTO_CAN_1_OVERLOAD)
    void PUERTO_CAN_1_OvrLdErrorIsr(void) ;
#endif /* PUERTO_CAN_1_OVERLOAD */
#if (PUERTO_CAN_1_BIT_ERR)
    void PUERTO_CAN_1_BitErrorIsr(void) ;
#endif /* PUERTO_CAN_1_BIT_ERR */
#if (PUERTO_CAN_1_STUFF_ERR)
    void PUERTO_CAN_1_BitStuffErrorIsr(void) ;
#endif /* PUERTO_CAN_1_STUFF_ERR */
#if (PUERTO_CAN_1_ACK_ERR)
    void PUERTO_CAN_1_AckErrorIsr(void) ;
#endif /* PUERTO_CAN_1_ACK_ERR */
#if (PUERTO_CAN_1_FORM_ERR)
    void PUERTO_CAN_1_MsgErrorIsr(void) ;
#endif /* PUERTO_CAN_1_FORM_ERR */
#if (PUERTO_CAN_1_CRC_ERR)
    void PUERTO_CAN_1_CrcErrorIsr(void) ;
#endif /* PUERTO_CAN_1_CRC_ERR */
#if (PUERTO_CAN_1_BUS_OFF)
    void PUERTO_CAN_1_BusOffIsr(void) ;
#endif /* PUERTO_CAN_1_BUS_OFF */
#if (PUERTO_CAN_1_RX_MSG_LOST)
    void PUERTO_CAN_1_MsgLostIsr(void) ;
#endif /* PUERTO_CAN_1_RX_MSG_LOST */
#if (PUERTO_CAN_1_TX_MESSAGE)
   void PUERTO_CAN_1_MsgTXIsr(void) ;
#endif /* PUERTO_CAN_1_TX_MESSAGE */
#if (PUERTO_CAN_1_RX_MESSAGE)
    void PUERTO_CAN_1_MsgRXIsr(void) ;
#endif /* PUERTO_CAN_1_RX_MESSAGE */

#if (!(CY_PSOC3 || CY_PSOC5))
    #if (PUERTO_CAN_1_RTR_AUTO_MSG_SENT)
        void PUERTO_CAN_1_RtrAutoMsgSentIsr(void);
    #endif /* PUERTO_CAN_1_RTR_MESSAGE */
    #if (PUERTO_CAN_1_STUCK_AT_ZERO)
        void PUERTO_CAN_1_StuckAtZeroIsr(void);
    #endif /* PUERTO_CAN_1_STUCK_AT_ZERO */
    #if (PUERTO_CAN_1_SST_FAILURE)
        void PUERTO_CAN_1_SSTErrorIsr(void);
    #endif /* PUERTO_CAN_1_SST_ERROR */
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

uint8 PUERTO_CAN_1_RxBufConfig(const PUERTO_CAN_1_RX_CFG *rxConfig) \
                                   ;
uint8 PUERTO_CAN_1_TxBufConfig(const PUERTO_CAN_1_TX_CFG *txConfig) \
                                   ;
uint8 PUERTO_CAN_1_RxTxBuffersConfig(void) ;                                
uint8 PUERTO_CAN_1_SendMsg(const PUERTO_CAN_1_TX_MSG *message) ;
void  PUERTO_CAN_1_TxCancel(uint8 bufferId) ;
void  PUERTO_CAN_1_ReceiveMsg(uint8 rxMailbox) ;

#if (PUERTO_CAN_1_TX0_FUNC_ENABLE)
    uint8 PUERTO_CAN_1_SendMsg0(void) ;
#endif /* PUERTO_CAN_1_TX0_FUNC_ENABLE */
#if (PUERTO_CAN_1_TX1_FUNC_ENABLE)
    uint8 PUERTO_CAN_1_SendMsg1(void) ;
#endif /* PUERTO_CAN_1_TX1_FUNC_ENABLE */
#if (PUERTO_CAN_1_TX2_FUNC_ENABLE)
    uint8 PUERTO_CAN_1_SendMsg2(void) ;
#endif /* PUERTO_CAN_1_TX2_FUNC_ENABLE */
#if (PUERTO_CAN_1_TX3_FUNC_ENABLE)
    uint8 PUERTO_CAN_1_SendMsg3(void) ;
#endif /* PUERTO_CAN_1_TX3_FUNC_ENABLE */
#if (PUERTO_CAN_1_TX4_FUNC_ENABLE)
    uint8 PUERTO_CAN_1_SendMsg4(void) ;
#endif /* PUERTO_CAN_1_TX4_FUNC_ENABLE */
#if (PUERTO_CAN_1_TX5_FUNC_ENABLE)
    uint8 PUERTO_CAN_1_SendMsg5(void) ;
#endif /* PUERTO_CAN_1_TX5_FUNC_ENABLE */
#if (PUERTO_CAN_1_TX6_FUNC_ENABLE)
    uint8 PUERTO_CAN_1_SendMsg6(void) ;
#endif /* PUERTO_CAN_1_TX6_FUNC_ENABLE */
#if (PUERTO_CAN_1_TX7_FUNC_ENABLE)
    uint8 PUERTO_CAN_1_SendMsg7(void) ;
#endif /* PUERTO_CAN_1_TX7_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX0_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg0(void) ;
#endif /* PUERTO_CAN_1_RX0_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX1_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg1(void) ;
#endif /* PUERTO_CAN_1_RX1_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX2_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg2(void) ;
#endif /* PUERTO_CAN_1_RX2_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX3_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg3(void) ;
#endif /* PUERTO_CAN_1_RX3_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX4_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg4(void) ;
#endif /* PUERTO_CAN_1_RX4_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX5_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg5(void) ;
#endif /* PUERTO_CAN_1_RX5_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX6_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg6(void) ;
#endif /* PUERTO_CAN_1_RX6_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX7_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg7(void) ;
#endif /* PUERTO_CAN_1_RX7_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX8_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg8(void) ;
#endif /* PUERTO_CAN_1_RX8_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX9_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg9(void) ;
#endif /* PUERTO_CAN_1_RX9_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX10_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg10(void) ;
#endif /* PUERTO_CAN_1_RX10_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX11_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg11(void) ;
#endif /* PUERTO_CAN_1_RX11_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX12_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg12(void) ;
#endif /* PUERTO_CAN_1_RX12_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX13_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg13(void) ;
#endif /* PUERTO_CAN_1_RX13_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX14_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg14(void) ;
#endif /* PUERTO_CAN_1_RX14_FUNC_ENABLE */
#if (PUERTO_CAN_1_RX15_FUNC_ENABLE)
    void PUERTO_CAN_1_ReceiveMsg15(void) ;
#endif /* PUERTO_CAN_1_RX15_FUNC_ENABLE */

#if(!PUERTO_CAN_1_INT_ISR_DISABLE)
    /* Interrupt handler */
    CY_ISR_PROTO(PUERTO_CAN_1_ISR);
#endif /* !PUERTO_CAN_1_INT_ISR_DISABLE */


/***************************************
*           API Constants
***************************************/

#if (!PUERTO_CAN_1_INT_ISR_DISABLE)
    /* Number of PUERTO_CAN_1_isr interrupt */
    #define PUERTO_CAN_1_ISR_NUMBER            ((uint8) PUERTO_CAN_1_isr__INTC_NUMBER)
    /* Priority of PUERTO_CAN_1_isr interrupt */
    #define PUERTO_CAN_1_ISR_PRIORITY          ((uint8) PUERTO_CAN_1_isr__INTC_PRIOR_NUM)
#endif /* !PUERTO_CAN_1_INT_ISR_DISABLE */

/* One bit time in CAN clock cycles */
#define PUERTO_CAN_1_ONE_BIT_TIME              ((PUERTO_CAN_1_BITRATE + 1u) * \
        ((PUERTO_CAN_1_CFG_REG_TSEG1 + 1u) + (PUERTO_CAN_1_CFG_REG_TSEG2 + 1u) + 1u))

/* Timeout for CAN state machine to switch operation mode to Run */
#define PUERTO_CAN_1_MODE_STATE_RUN_TIMEOUT    (12u * PUERTO_CAN_1_ONE_BIT_TIME)
/* Timeout for CAN state machine to switch operation mode to Stop */
#define PUERTO_CAN_1_MODE_STATE_STOP_TIMEOUT   (160u * PUERTO_CAN_1_ONE_BIT_TIME)

/* One or more parameters to function were invalid. */
#define PUERTO_CAN_1_FAIL                      (0x01u)
#define PUERTO_CAN_1_OUT_OF_RANGE              (0x02u)

#if (CY_PSOC3 || CY_PSOC5)
    /* PM_ACT_CFG (Active Power Mode CFG Register) */
    #define PUERTO_CAN_1_ACT_PWR_EN            (PUERTO_CAN_1_CanIP__PM_ACT_MSK)    /* Power enable mask */
    /* PM_STBY_CFG (Alternate Active (Standby) Power Mode CFG Register) */
    #define PUERTO_CAN_1_STBY_PWR_EN           (PUERTO_CAN_1_CanIP__PM_STBY_MSK)   /* Power enable mask */
#endif /* CY_PSOC3 || CY_PSOC5 */

/* Number of TX and RX mailboxes */
#define PUERTO_CAN_1_NUMBER_OF_TX_MAILBOXES    (8u)
#define PUERTO_CAN_1_NUMBER_OF_RX_MAILBOXES    (16u)

/* Error status of CAN */
#define PUERTO_CAN_1_ERROR_ACTIVE              (0x00u)
#define PUERTO_CAN_1_ERROR_PASIVE              (0x01u)
#define PUERTO_CAN_1_ERROR_BUS_OFF             (0x10u)

/* Operation mode */
#define PUERTO_CAN_1_INITIAL_MODE              (0x00u)
#define PUERTO_CAN_1_STOP_MODE                 (0x00u)
#define PUERTO_CAN_1_ACTIVE_RUN_MODE           (0x01u)
#define PUERTO_CAN_1_LISTEN_ONLY_MODE          (0x02u)
#if (!(CY_PSOC3 || CY_PSOC5))
    #define PUERTO_CAN_1_INTERNAL_LOOP_BACK    (0x06u)
    #define PUERTO_CAN_1_EXTERNAL_LOOP_BACK    (0x04u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

/* TX Defines to link mailbox names with mailbox numbers */
#define PUERTO_CAN_1_TX_MAILBOX_0      (0u)
#define PUERTO_CAN_1_TX_MAILBOX_1      (1u)
#define PUERTO_CAN_1_TX_MAILBOX_2      (2u)
#define PUERTO_CAN_1_TX_MAILBOX_3      (3u)
#define PUERTO_CAN_1_TX_MAILBOX_4      (4u)
#define PUERTO_CAN_1_TX_MAILBOX_5      (5u)
#define PUERTO_CAN_1_TX_MAILBOX_6      (6u)
#define PUERTO_CAN_1_TX_MAILBOX_7      (7u)

/* RX Defines to link mailbox names with mailbox numbers */
#define PUERTO_CAN_1_RX_MAILBOX_0      (0u)
#define PUERTO_CAN_1_RX_MAILBOX_1      (1u)
#define PUERTO_CAN_1_RX_MAILBOX_2      (2u)
#define PUERTO_CAN_1_RX_MAILBOX_3      (3u)
#define PUERTO_CAN_1_RX_MAILBOX_4      (4u)
#define PUERTO_CAN_1_RX_MAILBOX_5      (5u)
#define PUERTO_CAN_1_RX_MAILBOX_6      (6u)
#define PUERTO_CAN_1_RX_MAILBOX_7      (7u)
#define PUERTO_CAN_1_RX_MAILBOX_8      (8u)
#define PUERTO_CAN_1_RX_MAILBOX_9      (9u)
#define PUERTO_CAN_1_RX_MAILBOX_10     (10u)
#define PUERTO_CAN_1_RX_MAILBOX_11     (11u)
#define PUERTO_CAN_1_RX_MAILBOX_12     (12u)
#define PUERTO_CAN_1_RX_MAILBOX_13     (13u)
#define PUERTO_CAN_1_RX_MAILBOX_14     (14u)
#define PUERTO_CAN_1_RX_MAILBOX_15     (15u)


/***************************************
*    Initial Parameter Constants
***************************************/

/* General */
#define PUERTO_CAN_1_BITRATE                   (2u)
#define PUERTO_CAN_1_CFG_REG_TSEG1             (10u - 1u)
#define PUERTO_CAN_1_CFG_REG_TSEG2             (5u - 1u)
#define PUERTO_CAN_1_CFG_REG_SJW               (4u - 1u)
#define PUERTO_CAN_1_SAMPLING_MODE             (0u)
#define PUERTO_CAN_1_ARBITER                   (0u)
#define PUERTO_CAN_1_RESET_TYPE                (0u)
#define PUERTO_CAN_1_SYNC_EDGE                 (0u)

#if (!(CY_PSOC3 || CY_PSOC5))
    #define PUERTO_CAN_1_SWAP_DATA_END         (0u)
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

/* Interrupts */
#define PUERTO_CAN_1_INT_ENABLE                (1u)

#if (CY_PSOC3 || CY_PSOC5)
    #define PUERTO_CAN_1_INIT_INTERRUPT_MASK (((uint16) PUERTO_CAN_1_INT_ENABLE) | \
                ((uint16) ((uint16) PUERTO_CAN_1_ARB_LOST    <<  PUERTO_CAN_1_ARBITRATION_LOST_SHIFT)) | \
                ((uint16) ((uint16) PUERTO_CAN_1_OVERLOAD    <<  PUERTO_CAN_1_OVERLOAD_ERROR_SHIFT))   | \
                ((uint16) ((uint16) PUERTO_CAN_1_BIT_ERR     <<  PUERTO_CAN_1_BIT_ERROR_SHIFT))        | \
                ((uint16) ((uint16) PUERTO_CAN_1_STUFF_ERR   <<  PUERTO_CAN_1_STUFF_ERROR_SHIFT))      | \
                ((uint16) ((uint16) PUERTO_CAN_1_ACK_ERR     <<  PUERTO_CAN_1_ACK_ERROR_SHIFT))        | \
                ((uint16) ((uint16) PUERTO_CAN_1_FORM_ERR    <<  PUERTO_CAN_1_FORM_ERROR_SHIFT))       | \
                ((uint16) ((uint16) PUERTO_CAN_1_CRC_ERR     << (PUERTO_CAN_1_ONE_BYTE_OFFSET          + \
                                                                     PUERTO_CAN_1_CRC_ERROR_SHIFT)))       | \
                ((uint16) ((uint16) PUERTO_CAN_1_BUS_OFF     << (PUERTO_CAN_1_ONE_BYTE_OFFSET          + \
                                                                     PUERTO_CAN_1_BUS_OFF_SHIFT)))         | \
                ((uint16) ((uint16) PUERTO_CAN_1_RX_MSG_LOST << (PUERTO_CAN_1_ONE_BYTE_OFFSET          + \
                                                                     PUERTO_CAN_1_RX_MSG_LOST_SHIFT)))     | \
                ((uint16) ((uint16) PUERTO_CAN_1_TX_MESSAGE  << (PUERTO_CAN_1_ONE_BYTE_OFFSET          + \
                                                                     PUERTO_CAN_1_TX_MESSAGE_SHIFT)))      | \
                ((uint16) ((uint16) PUERTO_CAN_1_RX_MESSAGE  << (PUERTO_CAN_1_ONE_BYTE_OFFSET          + \
                                                                     PUERTO_CAN_1_RX_MESSAGE_SHIFT))))
#else /* CY_PSOC4 */
    #define PUERTO_CAN_1_INIT_INTERRUPT_MASK    (((uint16) PUERTO_CAN_1_INT_ENABLE) | \
                ((uint16) ((uint16) PUERTO_CAN_1_ARB_LOST    <<  PUERTO_CAN_1_ARBITRATION_LOST_SHIFT)) | \
                ((uint16) ((uint16) PUERTO_CAN_1_OVERLOAD    <<  PUERTO_CAN_1_OVERLOAD_ERROR_SHIFT))   | \
                ((uint16) ((uint16) PUERTO_CAN_1_BIT_ERR     <<  PUERTO_CAN_1_BIT_ERROR_SHIFT))        | \
                ((uint16) ((uint16) PUERTO_CAN_1_STUFF_ERR   <<  PUERTO_CAN_1_STUFF_ERROR_SHIFT))      | \
                ((uint16) ((uint16) PUERTO_CAN_1_ACK_ERR     <<  PUERTO_CAN_1_ACK_ERROR_SHIFT))        | \
                ((uint16) ((uint16) PUERTO_CAN_1_FORM_ERR    <<  PUERTO_CAN_1_FORM_ERROR_SHIFT))       | \
                ((uint16) ((uint16) PUERTO_CAN_1_CRC_ERR     <<  PUERTO_CAN_1_CRC_ERROR_SHIFT))        | \
                ((uint16) ((uint16) PUERTO_CAN_1_BUS_OFF     <<  PUERTO_CAN_1_BUS_OFF_SHIFT))          | \
                ((uint16) ((uint16) PUERTO_CAN_1_RX_MSG_LOST <<  PUERTO_CAN_1_RX_MSG_LOST_SHIFT))      | \
                ((uint16) ((uint16) PUERTO_CAN_1_TX_MESSAGE  <<  PUERTO_CAN_1_TX_MESSAGE_SHIFT))       | \
                ((uint16) ((uint16) PUERTO_CAN_1_RX_MESSAGE  <<  PUERTO_CAN_1_RX_MESSAGE_SHIFT))       | \
                ((uint16) ((uint16) PUERTO_CAN_1_RTR_AUTO_MSG_SENT  << PUERTO_CAN_1_RTR_MSG_SHIFT))    | \
                ((uint16) ((uint16) PUERTO_CAN_1_STUCK_AT_ZERO << PUERTO_CAN_1_STUCK_AT_ZERO_SHIFT))   | \
                ((uint16) ((uint16) PUERTO_CAN_1_SST_FAILURE   << PUERTO_CAN_1_SST_FAILURE_SHIFT)))
#endif /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*             Registers
***************************************/

#if (CY_PSOC3 || CY_PSOC5)
#define PUERTO_CAN_1_TX          ( (volatile PUERTO_CAN_1_TX_STRUCT XDATA *) PUERTO_CAN_1_CanIP__TX0_CMD)
#define PUERTO_CAN_1_RX          ( (volatile PUERTO_CAN_1_RX_STRUCT XDATA *) PUERTO_CAN_1_CanIP__RX0_CMD)
#define PUERTO_CAN_1_INT_SR_REG  (*(volatile PUERTO_CAN_1_REG_32 XDATA *) PUERTO_CAN_1_CanIP__CSR_INT_SR)
#define PUERTO_CAN_1_INT_SR_PTR  ( (reg32 *) PUERTO_CAN_1_CanIP__CSR_INT_SR)
#define PUERTO_CAN_1_INT_EN_REG  (*(volatile PUERTO_CAN_1_REG_32 XDATA *) PUERTO_CAN_1_CanIP__CSR_INT_EN)
#define PUERTO_CAN_1_INT_EN_PTR  ( (reg32 *) PUERTO_CAN_1_CanIP__CSR_INT_EN)
#define PUERTO_CAN_1_BUF_SR_REG  (*(volatile PUERTO_CAN_1_REG_32 XDATA *) PUERTO_CAN_1_CanIP__CSR_BUF_SR)
#define PUERTO_CAN_1_BUF_SR_PTR  ( (reg32 *) PUERTO_CAN_1_CanIP__CSR_BUF_SR)
#define PUERTO_CAN_1_ERR_SR_REG  (*(volatile PUERTO_CAN_1_REG_32 XDATA *) PUERTO_CAN_1_CanIP__CSR_ERR_SR)
#define PUERTO_CAN_1_ERR_SR_PTR  ( (reg32 *) PUERTO_CAN_1_CanIP__CSR_ERR_SR)
#define PUERTO_CAN_1_CMD_REG     (*(volatile PUERTO_CAN_1_REG_32 XDATA *) PUERTO_CAN_1_CanIP__CSR_CMD)
#define PUERTO_CAN_1_CMD_PTR     ( (reg32 *) PUERTO_CAN_1_CanIP__CSR_CMD)
#define PUERTO_CAN_1_CFG_REG     (*(volatile PUERTO_CAN_1_REG_32 XDATA *) PUERTO_CAN_1_CanIP__CSR_CFG)
#define PUERTO_CAN_1_CFG_PTR     ( (reg32 *) PUERTO_CAN_1_CanIP__CSR_CFG)

/* Power manager */
#define PUERTO_CAN_1_PM_ACT_CFG_REG           (*(reg8 *) PUERTO_CAN_1_CanIP__PM_ACT_CFG)
#define PUERTO_CAN_1_PM_ACT_CFG_PTR           ( (reg8 *) PUERTO_CAN_1_CanIP__PM_ACT_CFG)
#define PUERTO_CAN_1_PM_STBY_CFG_REG          (*(reg8 *) PUERTO_CAN_1_CanIP__PM_STBY_CFG)
#define PUERTO_CAN_1_PM_STBY_CFG_PTR          ( (reg8 *) PUERTO_CAN_1_CanIP__PM_STBY_CFG)

#define PUERTO_CAN_1_RX_FIRST_REGISTER_PTR    ((reg32 *) PUERTO_CAN_1_CanIP__RX0_CMD)
#define PUERTO_CAN_1_RX_LAST_REGISTER_PTR     ((reg32 *) PUERTO_CAN_1_CanIP__RX15_ACRD)

#else /* CY_PSOC4 */
#define PUERTO_CAN_1_TX    ((volatile PUERTO_CAN_1_TX_STRUCT XDATA *) PUERTO_CAN_1_CanIP__CAN_TX0_CONTROL)
#define PUERTO_CAN_1_RX    ((volatile PUERTO_CAN_1_RX_STRUCT XDATA *) PUERTO_CAN_1_CanIP__CAN_RX0_CONTROL)
#define PUERTO_CAN_1_TX_REG                   (*(reg32 *) PUERTO_CAN_1_CanIP__CAN_TX0_CONTROL)
#define PUERTO_CAN_1_TX_PTR                   ( (reg32 *) PUERTO_CAN_1_CanIP__CAN_TX0_CONTROL)
#define PUERTO_CAN_1_RX_REG                   (*(reg32 *) PUERTO_CAN_1_CanIP__CAN_RX0_CONTROL)
#define PUERTO_CAN_1_RX_PTR                   ( (reg32 *) PUERTO_CAN_1_CanIP__CAN_RX0_CONTROL)
#define PUERTO_CAN_1_INT_SR_REG               (*(reg32 *) PUERTO_CAN_1_CanIP__INT_STATUS)
#define PUERTO_CAN_1_INT_SR_PTR               ( (reg32 *) PUERTO_CAN_1_CanIP__INT_STATUS)
#define PUERTO_CAN_1_INT_EN_REG               (*(reg32 *) PUERTO_CAN_1_CanIP__INT_EBL)
#define PUERTO_CAN_1_INT_EN_PTR               ( (reg32 *) PUERTO_CAN_1_CanIP__INT_EBL)
#define PUERTO_CAN_1_BUF_SR_REG               (*(reg32 *) PUERTO_CAN_1_CanIP__BUFFER_STATUS)
#define PUERTO_CAN_1_BUF_SR_PTR               ( (reg32 *) PUERTO_CAN_1_CanIP__BUFFER_STATUS)
#define PUERTO_CAN_1_ERR_SR_REG               (*(reg32 *) PUERTO_CAN_1_CanIP__ERROR_STATUS)
#define PUERTO_CAN_1_ERR_SR_PTR               ( (reg32 *) PUERTO_CAN_1_CanIP__ERROR_STATUS)
#define PUERTO_CAN_1_CNTL_REG                 (*(reg32 *) PUERTO_CAN_1_CanIP__CNTL)
#define PUERTO_CAN_1_CNTL_PTR                 ( (reg32 *) PUERTO_CAN_1_CanIP__CNTL)
#define PUERTO_CAN_1_CMD_REG                  (*(reg32 *) PUERTO_CAN_1_CanIP__COMMAND)
#define PUERTO_CAN_1_CMD_PTR                  ( (reg32 *) PUERTO_CAN_1_CanIP__COMMAND)
#define PUERTO_CAN_1_CFG_REG                  (*(reg32 *) PUERTO_CAN_1_CanIP__CONFIG)
#define PUERTO_CAN_1_CFG_PTR                  ( (reg32 *) PUERTO_CAN_1_CanIP__CONFIG)
#define PUERTO_CAN_1_ECR_REG                  (*(reg32 *) PUERTO_CAN_1_CanIP__ECR)
#define PUERTO_CAN_1_ECR_PTR                  ( (reg32 *) PUERTO_CAN_1_CanIP__ECR)
#define PUERTO_CAN_1_RX_FIRST_REGISTER_PTR    ( (reg32 *) PUERTO_CAN_1_CanIP__CAN_RX0_CONTROL)
#define PUERTO_CAN_1_RX_LAST_REGISTER_PTR     ( (reg32 *) PUERTO_CAN_1_CanIP__CAN_RX15_ACR_DATA)

#define PUERTO_CAN_1_TX_DATA_LO_REG(i)        (*(reg32 *) (&PUERTO_CAN_1_TX[i].txdata))
#define PUERTO_CAN_1_TX_DATA_HI_REG(i)        (*(reg32 *) ((uint32) (&PUERTO_CAN_1_TX[i].txdata) + \
                                                  PUERTO_CAN_1_DATA_HIGH_ADDR))
#define PUERTO_CAN_1_RX_DATA_LO_REG(i)        (*(reg32 *) (&PUERTO_CAN_1_RX[i].rxdata))
#define PUERTO_CAN_1_RX_DATA_HI_REG(i)        (*(reg32 *) ((uint32) (&PUERTO_CAN_1_RX[i].rxdata) + \
                                                  PUERTO_CAN_1_DATA_HIGH_ADDR))
#endif /* (CY_PSOC3 || CY_PSOC5) */

#define PUERTO_CAN_1_TX_CMD_PTR(i)            ( (reg32 *) (&PUERTO_CAN_1_TX[i].txcmd))
#define PUERTO_CAN_1_TX_CMD_REG(i)            (*(reg32 *) (&PUERTO_CAN_1_TX[i].txcmd))
#define PUERTO_CAN_1_RX_CMD_PTR(i)            ( (reg32 *) (&PUERTO_CAN_1_RX[i].rxcmd))
#define PUERTO_CAN_1_RX_CMD_REG(i)            (*(reg32 *) (&PUERTO_CAN_1_RX[i].rxcmd))
#define PUERTO_CAN_1_RX_ID_PTR(i)             ( (reg32 *) (&PUERTO_CAN_1_RX[i].rxid))
#define PUERTO_CAN_1_RX_ID_REG(i)             (*(reg32 *) (&PUERTO_CAN_1_RX[i].rxid))
#define PUERTO_CAN_1_TX_ID_PTR(i)             ( (reg32 *) (&PUERTO_CAN_1_TX[i].txid))
#define PUERTO_CAN_1_TX_ID_REG(i)             (*(reg32 *) (&PUERTO_CAN_1_TX[i].txid))


/***************************************
*        Register Constants
***************************************/

/* Run/Stop mode */
#define PUERTO_CAN_1_MODE_STOP                (0x00u)
#define PUERTO_CAN_1_MODE_START               (0x01u)

/* Transmit buffer arbiter */
#define PUERTO_CAN_1_ROUND_ROBIN              (0x00u)
#define PUERTO_CAN_1_FIXED_PRIORITY           (0x01u)

/* Restart type */
#define PUERTO_CAN_1_MANUAL_RESTART           (0x00u)
#define PUERTO_CAN_1_AUTO_RESTART             (0x01u)

/* Sampling mode */
#define PUERTO_CAN_1_ONE_SAMPLE_POINT         (0x00u)
#define PUERTO_CAN_1_THREE_SAMPLE_POINTS      (0x01u)

/* Edge mode */
#define PUERTO_CAN_1_EDGE_R_TO_D              (0x00u)
#define PUERTO_CAN_1_BOTH_EDGES               (0x01u)

/* Extended identifier */
#define PUERTO_CAN_1_STANDARD_MESSAGE         (0x00u)
#define PUERTO_CAN_1_EXTENDED_MESSAGE         (0x01u)

/* Write Protect Mask for Basic and Full mailboxes */
#define PUERTO_CAN_1_TX_WPN_CLEAR           ((uint32) (~PUERTO_CAN_1_TX_WPN_SET))
#define PUERTO_CAN_1_RX_WPN_CLEAR           ((uint32) (~PUERTO_CAN_1_RX_WPN_SET))
#define PUERTO_CAN_1_TX_RSVD_MASK           ((uint32) 0x00FF00FFu)
#define PUERTO_CAN_1_TX_READ_BACK_MASK      (PUERTO_CAN_1_TX_WPN_CLEAR & PUERTO_CAN_1_TX_RSVD_MASK)
#define PUERTO_CAN_1_RX_READ_BACK_MASK      (PUERTO_CAN_1_RX_WPN_CLEAR & PUERTO_CAN_1_TX_RSVD_MASK)
#define PUERTO_CAN_1_RX_CMD_REG_WIDTH       (0x20u)

#if (CY_PSOC3 || CY_PSOC5)
    #define PUERTO_CAN_1_TX_WPN_SET         (((uint32) ((uint32) 0x00000001u << PUERTO_CAN_1_TX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << (PUERTO_CAN_1_TWO_BYTE_OFFSET + PUERTO_CAN_1_TX_WPNH_SHIFT))))
    #define PUERTO_CAN_1_RX_WPN_SET         (((uint32) ((uint32) 0x00000001u << PUERTO_CAN_1_RX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << (PUERTO_CAN_1_TWO_BYTE_OFFSET + PUERTO_CAN_1_RX_WPNH_SHIFT))))
#else  /* CY_PSOC4 */
    #define PUERTO_CAN_1_TX_WPN_SET         (((uint32) ((uint32) 0x00000001u << PUERTO_CAN_1_TX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << PUERTO_CAN_1_TX_WPNH_SHIFT)))
    #define PUERTO_CAN_1_RX_WPN_SET         (((uint32) ((uint32) 0x00000001u << PUERTO_CAN_1_RX_WPNL_SHIFT)) | \
            ((uint32) ((uint32) 0x00000001u << PUERTO_CAN_1_RX_WPNH_SHIFT)))

    /* CAN IP Block Enable */
    #define PUERTO_CAN_1_IP_ENABLE_SHIFT    (31u)
    #define PUERTO_CAN_1_IP_ENABLE          ((uint32) ((uint32) 0x00000001u << PUERTO_CAN_1_IP_ENABLE_SHIFT))

    /* Error Capture register mode setting */
    #define PUERTO_CAN_1_ECR_FREE_RUNNING   (0x00u)
    #define PUERTO_CAN_1_ECR_ERROR_CAPTURE  (0x01u)

    /* Swap Endian */
    #define PUERTO_CAN_1_SWAP_ENDIANNESS_DISABLE  (0x00u)
    #define PUERTO_CAN_1_SWAP_ENDIANNESS_ENABLE   (0x01u)
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* TX send message */
#define PUERTO_CAN_1_TX_REQUEST_PENDING     (0x01u)
#define PUERTO_CAN_1_RETRY_NUMBER           (0x03u)
#define PUERTO_CAN_1_SEND_MESSAGE_SHIFT     (0u)
#define PUERTO_CAN_1_SEND_MESSAGE           ((uint32) ((uint32) 0x00000001u << PUERTO_CAN_1_SEND_MESSAGE_SHIFT))

/* Offsets to maintain bytes within uint32 */
#define PUERTO_CAN_1_ONE_BYTE_OFFSET        (8u)
#define PUERTO_CAN_1_TWO_BYTE_OFFSET        (16u)
#define PUERTO_CAN_1_THREE_BYTE_OFFSET      (24u)

#if (CY_PSOC3 || CY_PSOC5)
    /* Set/Clear bits macro for PUERTO_CAN_1_RX mailbox(i) */
    /* Bit 0 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_ACK_MSG_SHIFT       (0u)
    #define PUERTO_CAN_1_RX_ACK_MSG             ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_RX_ACK_MSG_SHIFT))
    /* Bit 2 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_RTR_ABORT_SHIFT     (2u)
    #define PUERTO_CAN_1_RX_RTR_ABORT_MASK      ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_RX_RTR_ABORT_SHIFT))
    /* Bit 3 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_BUF_ENABLE_SHIFT    (3u)
    #define PUERTO_CAN_1_RX_BUF_ENABLE_MASK     ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_RX_BUF_ENABLE_SHIFT))
    /* Bit 4 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_RTRREPLY_SHIFT      (4u)
    #define PUERTO_CAN_1_RX_RTRREPLY_MASK       ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_RX_RTRREPLY_SHIFT))
    /* Bit 5 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_INT_ENABLE_SHIFT    (5u)
    #define PUERTO_CAN_1_RX_INT_ENABLE_MASK     ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_RX_INT_ENABLE_SHIFT))
    /* Bit 6 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_LINKING_SHIFT       (6u)
    #define PUERTO_CAN_1_RX_LINKING_MASK        ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_RX_LINKING_SHIFT))
    /* Bit 7 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_WPNL_SHIFT          (7u)
    #define PUERTO_CAN_1_RX_WPNL_MASK           ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_RX_WPNL_SHIFT))
    /* Bits 19-16 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_DLC_VALUE_SHIFT     (0u)
    #define PUERTO_CAN_1_RX_DLC_VALUE_MASK      ((uint8) ((uint8) 0x0Fu << PUERTO_CAN_1_RX_DLC_VALUE_SHIFT))
    /* Bit 20 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_IDE_SHIFT           (4u)
    #define PUERTO_CAN_1_RX_IDE_MASK            ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_RX_IDE_SHIFT))
    /* Bit 23 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_WPNH_SHIFT          (7u)
    #define PUERTO_CAN_1_RX_WPNH_MASK           ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_RX_WPNH_SHIFT))

    #define PUERTO_CAN_1_RX_ACK_MESSAGE(i)    (PUERTO_CAN_1_RX[i].rxcmd.byte[0u] |= PUERTO_CAN_1_RX_ACK_MSG)
    #define PUERTO_CAN_1_RX_RTR_ABORT_MESSAGE(i) \
            (PUERTO_CAN_1_RX[i].rxcmd.byte[0u] |= PUERTO_CAN_1_RX_RTR_ABORT_MASK)
    #define PUERTO_CAN_1_RX_BUF_ENABLE(i)      \
            (PUERTO_CAN_1_RX[i].rxcmd.byte[0u] |= PUERTO_CAN_1_RX_BUF_ENABLE_MASK)
    #define PUERTO_CAN_1_RX_BUF_DISABLE(i)     \
            (PUERTO_CAN_1_RX[i].rxcmd.byte[0u] &= (uint8) (~PUERTO_CAN_1_RX_BUF_ENABLE_MASK))
    #define PUERTO_CAN_1_SET_RX_RTRREPLY(i)    \
            (PUERTO_CAN_1_RX[i].rxcmd.byte[0u] |= PUERTO_CAN_1_RX_RTRREPLY_MASK)
    #define PUERTO_CAN_1_CLEAR_RX_RTRREPLY(i)  \
            (PUERTO_CAN_1_RX[i].rxcmd.byte[0u] &= (uint8) (~PUERTO_CAN_1_RX_RTRREPLY_MASK))
    #define PUERTO_CAN_1_RX_INT_ENABLE(i)      \
            (PUERTO_CAN_1_RX[i].rxcmd.byte[0u] |= PUERTO_CAN_1_RX_INT_ENABLE_MASK)
    #define PUERTO_CAN_1_RX_INT_DISABLE(i)     \
            (PUERTO_CAN_1_RX[i].rxcmd.byte[0u] &= (uint8) (~PUERTO_CAN_1_RX_INT_ENABLE_MASK))
    #define PUERTO_CAN_1_SET_RX_LINKING(i)     \
            (PUERTO_CAN_1_RX[i].rxcmd.byte[0u] |= PUERTO_CAN_1_RX_LINKING_MASK)
    #define PUERTO_CAN_1_CLEAR_RX_LINKING(i)   \
            (PUERTO_CAN_1_RX[i].rxcmd.byte[0u] &= (uint8) (~PUERTO_CAN_1_RX_LINKING_MASK))
    #define PUERTO_CAN_1_SET_RX_WNPL(i)     (PUERTO_CAN_1_RX[i].rxcmd.byte[0u] |= PUERTO_CAN_1_RX_WPNL_MASK)
    #define PUERTO_CAN_1_CLEAR_RX_WNPL(i)      \
            (PUERTO_CAN_1_RX[i].rxcmd.byte[0u] &= (uint8) (~PUERTO_CAN_1_RX_WPNL_MASK))
    #define PUERTO_CAN_1_SET_RX_WNPH(i)     (PUERTO_CAN_1_RX[i].rxcmd.byte[2u] |= PUERTO_CAN_1_RX_WPNH_MASK)
    #define PUERTO_CAN_1_CLEAR_RX_WNPH(i)      \
            (PUERTO_CAN_1_RX[i].rxcmd.byte[2u] &= (uint8) (~PUERTO_CAN_1_RX_WPNH_MASK))
    #define PUERTO_CAN_1_GET_DLC(i)            \
            (PUERTO_CAN_1_RX[i].rxcmd.byte[2u] & PUERTO_CAN_1_RX_DLC_VALUE_MASK)
    #define PUERTO_CAN_1_GET_RX_IDE(i)         ((uint8) \
            (PUERTO_CAN_1_RX[i].rxcmd.byte[2u] & PUERTO_CAN_1_RX_IDE_MASK) >> PUERTO_CAN_1_RX_IDE_SHIFT)
    #define PUERTO_CAN_1_GET_RX_ID(i)          ((PUERTO_CAN_1_GET_RX_IDE(i)) ? \
            (CY_GET_REG32(PUERTO_CAN_1_RX_ID_PTR(i)) >> PUERTO_CAN_1_SET_TX_ID_EXTENDED_MSG_SHIFT) : \
            (CY_GET_REG32(PUERTO_CAN_1_RX_ID_PTR(i)) >> PUERTO_CAN_1_SET_TX_ID_STANDARD_MSG_SHIFT))

    /* Set/Clear bits macro for PUERTO_CAN_1_TX mailbox(i) */
    /* Bit 0 within TX_CMD[i] */
    #define PUERTO_CAN_1_TX_TRANSMIT_REQUEST_SHIFT (0u)
    #define PUERTO_CAN_1_TX_TRANSMIT_REQUEST ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_TX_TRANSMIT_REQUEST_SHIFT))
    /* Bit 1 within TX_CMD[i] */
    #define PUERTO_CAN_1_TX_ABORT_SHIFT        (1u)
    #define PUERTO_CAN_1_TX_ABORT_MASK         ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_TX_ABORT_SHIFT))
    /* Bit 2 within TX_CMD[i] */
    #define PUERTO_CAN_1_TRANSMIT_INT_ENABLE   (0x01u)
    #define PUERTO_CAN_1_TRANSMIT_INT_DISABLE  (0x00u)
    #define PUERTO_CAN_1_TX_INT_ENABLE_SHIFT   (2u)
    #define PUERTO_CAN_1_TX_INT_ENABLE_MASK    \
            ((uint32) ((uint32) 0x00000001u << PUERTO_CAN_1_TX_INT_ENABLE_SHIFT))
    /* Bit 3 within TX_CMD[i] */
    #define PUERTO_CAN_1_TX_WPNL_SHIFT         (3u)
    #define PUERTO_CAN_1_TX_WPNL_MASK          ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_TX_WPNL_SHIFT))
    /* Bits 19-16 within TX_CMD[i] */
    #define PUERTO_CAN_1_TX_DLC_VALUE_SHIFT    (0u)
    #define PUERTO_CAN_1_TX_DLC_UPPER_VALUE_SHIFT (19u)
    #define PUERTO_CAN_1_TX_DLC_UPPER_VALUE    \
            ((uint32) ((uint32) 0x00000001u << PUERTO_CAN_1_TX_DLC_UPPER_VALUE_SHIFT))
    #define PUERTO_CAN_1_TX_DLC_VALUE_MASK     ((uint8) ((uint8) 0x0Fu << PUERTO_CAN_1_TX_DLC_VALUE_SHIFT))
    #define PUERTO_CAN_1_TX_DLC_MAX_VALUE      (8u)
    /* Bit 20 within TX_CMD[i] */
    #define PUERTO_CAN_1_TX_IDE_SHIFT          (20u)
    #define PUERTO_CAN_1_TX_IDE_MASK           ((uint32) ((uint32) 0x00000001u << PUERTO_CAN_1_TX_IDE_SHIFT))
    /* Bit 21 within TX_CMD[i] */
    #define PUERTO_CAN_1_TX_RTR_SHIFT          (21u)
    #define PUERTO_CAN_1_TX_RTR_MASK           ((uint32) ((uint32) 0x00000001u <<  PUERTO_CAN_1_TX_RTR_SHIFT))
    /* Bit 23 within TX_CMD[i] */
    #define PUERTO_CAN_1_TX_WPNH_SHIFT         (7u)
    #define PUERTO_CAN_1_TX_WPNH_MASK          ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_TX_WPNH_SHIFT))

    #define PUERTO_CAN_1_TX_TRANSMIT_MESSAGE(i) \
            (PUERTO_CAN_1_TX[i].txcmd.byte[0u] |= PUERTO_CAN_1_TX_TRANSMIT_REQUEST)
    #define PUERTO_CAN_1_TX_ABORT_MESSAGE(i)   \
            (PUERTO_CAN_1_TX[i].txcmd.byte[0u] = (PUERTO_CAN_1_TX[i].txcmd.byte[0u] & \
            (uint8) (~PUERTO_CAN_1_TX_TRANSMIT_REQUEST)) | PUERTO_CAN_1_TX_ABORT_MASK)
    #define PUERTO_CAN_1_TX_INT_ENABLE(i)      \
            (PUERTO_CAN_1_TX[i].txcmd.byte[0u] |= (uint8) PUERTO_CAN_1_TX_INT_ENABLE_MASK)
    #define PUERTO_CAN_1_TX_INT_DISABLE(i)     \
            (PUERTO_CAN_1_TX[i].txcmd.byte[0u] &= (uint8) (~PUERTO_CAN_1_TX_INT_ENABLE_MASK))
    #define PUERTO_CAN_1_SET_TX_WNPL(i)        \
            (PUERTO_CAN_1_TX[i].txcmd.byte[0u] |= PUERTO_CAN_1_TX_WPNL_MASK)
    #define PUERTO_CAN_1_CLEAR_TX_WNPL(i)      \
            (PUERTO_CAN_1_TX[i].txcmd.byte[0u] &= (uint8) (~PUERTO_CAN_1_TX_WPNL_MASK))
    #define PUERTO_CAN_1_SET_TX_IDE(i)         (PUERTO_CAN_1_TX[i].txcmd.byte[2u] |= \
            (uint8) (PUERTO_CAN_1_TX_IDE_MASK >> PUERTO_CAN_1_TWO_BYTE_OFFSET))
    #define PUERTO_CAN_1_CLEAR_TX_IDE(i)       (PUERTO_CAN_1_TX[i].txcmd.byte[2u] &= \
            (uint8) (((uint32) (~PUERTO_CAN_1_TX_IDE_MASK)) >> PUERTO_CAN_1_TWO_BYTE_OFFSET))
    #define PUERTO_CAN_1_SET_TX_RTR(i)         (PUERTO_CAN_1_TX[i].txcmd.byte[2u] |= \
            (uint8) (PUERTO_CAN_1_TX_RTR_MASK >> PUERTO_CAN_1_TWO_BYTE_OFFSET))
    #define PUERTO_CAN_1_CLEAR_TX_RTR(i)       (PUERTO_CAN_1_TX[i].txcmd.byte[2u] &= \
            (uint8) (((uint32) (~PUERTO_CAN_1_TX_RTR_MASK)) >> PUERTO_CAN_1_TWO_BYTE_OFFSET))
    #define PUERTO_CAN_1_SET_TX_WNPH(i)        \
            (PUERTO_CAN_1_TX[i].txcmd.byte[2u] |= PUERTO_CAN_1_TX_WPNH_MASK)
    #define PUERTO_CAN_1_CLEAR_TX_WNPH(i)      \
            (PUERTO_CAN_1_TX[i].txcmd.byte[2u] &= (uint8) (~PUERTO_CAN_1_TX_WPNH_MASK))

    #define PUERTO_CAN_1_RX_DATA_BYTE(mailbox, i) (PUERTO_CAN_1_RX[mailbox].rxdata.byte[((i) > 3u) ? \
                                                      (7u - ((i) - 4u)) : (3u - (i))])
    #define PUERTO_CAN_1_TX_DATA_BYTE(mailbox, i) (PUERTO_CAN_1_TX[mailbox].txdata.byte[((i) > 3u) ? \
                                                      (7u - ((i) - 4u)) : (3u - (i))])
#else  /* CY_PSOC4 */
    /* Set/Clear bits macro for PUERTO_CAN_1_RX mailbox(i) */
    /* Bit 0 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_ACK_MSG_SHIFT       (0u)
    #define PUERTO_CAN_1_RX_ACK_MSG             ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_RX_ACK_MSG_SHIFT))
    /* Bit 2 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_RTR_ABORT_SHIFT     (2u)
    #define PUERTO_CAN_1_RX_RTR_ABORT_MASK      ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_RX_RTR_ABORT_SHIFT))
    /* Bit 3 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_BUF_ENABLE_SHIFT    (3u)
    #define PUERTO_CAN_1_RX_BUF_ENABLE_MASK     ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_RX_BUF_ENABLE_SHIFT))
    /* Bit 4 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_RTRREPLY_SHIFT      (4u)
    #define PUERTO_CAN_1_RX_RTRREPLY_MASK       ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_RX_RTRREPLY_SHIFT))
    /* Bit 5 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_INT_ENABLE_SHIFT    (5u)
    #define PUERTO_CAN_1_RX_INT_ENABLE_MASK     ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_RX_INT_ENABLE_SHIFT))
    /* Bit 6 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_LINKING_SHIFT       (6u)
    #define PUERTO_CAN_1_RX_LINKING_MASK        ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_RX_LINKING_SHIFT))
    /* Bit 7 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_WPNL_SHIFT          (7u)
    #define PUERTO_CAN_1_RX_WPNL_MASK           ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_RX_WPNL_SHIFT))
    /* Bits 19-16 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_DLC_VALUE_SHIFT     (16u)
    #define PUERTO_CAN_1_RX_DLC_VALUE_MASK      ((uint32) ((uint32) 0x0Fu << PUERTO_CAN_1_RX_DLC_VALUE_SHIFT))
    /* Bit 20 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_IDE_SHIFT           (20u)
    #define PUERTO_CAN_1_RX_IDE_MASK            ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_RX_IDE_SHIFT))
    /* Bit 23 within RX_CMD[i] */
    #define PUERTO_CAN_1_RX_WPNH_SHIFT          (23u)
    #define PUERTO_CAN_1_RX_WPNH_MASK           ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_RX_WPNH_SHIFT))

    #define PUERTO_CAN_1_RX_ACK_MESSAGE(i)       (PUERTO_CAN_1_RX_CMD_REG(i) |= PUERTO_CAN_1_RX_ACK_MSG)
    #define PUERTO_CAN_1_RX_RTR_ABORT_MESSAGE(i) (PUERTO_CAN_1_RX_CMD_REG(i) |= \
                                                     PUERTO_CAN_1_RX_RTR_ABORT_MASK)
    #define PUERTO_CAN_1_RX_BUF_ENABLE(i)      (PUERTO_CAN_1_RX_CMD_REG(i) |= \
                                                   PUERTO_CAN_1_RX_BUF_ENABLE_MASK)
    #define PUERTO_CAN_1_RX_BUF_DISABLE(i)     (PUERTO_CAN_1_RX_CMD_REG(i) &= \
                                                   (uint32) (~PUERTO_CAN_1_RX_BUF_ENABLE_MASK))
    #define PUERTO_CAN_1_SET_RX_RTRREPLY(i)    (PUERTO_CAN_1_RX_CMD_REG(i) |= \
                                                   PUERTO_CAN_1_RX_RTRREPLY_MASK)
    #define PUERTO_CAN_1_CLEAR_RX_RTRREPLY(i)  (PUERTO_CAN_1_RX_CMD_REG(i) &= \
                                                   (uint32) (~PUERTO_CAN_1_RX_RTRREPLY_MASK))
    #define PUERTO_CAN_1_RX_INT_ENABLE(i)      (PUERTO_CAN_1_RX_CMD_REG(i) |= \
                                                   PUERTO_CAN_1_RX_INT_ENABLE_MASK)
    #define PUERTO_CAN_1_RX_INT_DISABLE(i)     (PUERTO_CAN_1_RX_CMD_REG(i) &= \
                                                   (uint32) (~PUERTO_CAN_1_RX_INT_ENABLE_MASK))
    #define PUERTO_CAN_1_SET_RX_LINKING(i)     (PUERTO_CAN_1_RX_CMD_REG(i) |= PUERTO_CAN_1_RX_LINKING_MASK)
    #define PUERTO_CAN_1_CLEAR_RX_LINKING(i)   (PUERTO_CAN_1_RX_CMD_REG(i) &= \
                                                   (uint32) (~PUERTO_CAN_1_RX_LINKING_MASK))
    #define PUERTO_CAN_1_SET_RX_WNPL(i)        (PUERTO_CAN_1_RX_CMD_REG(i) |= PUERTO_CAN_1_RX_WPNL_MASK)
    #define PUERTO_CAN_1_CLEAR_RX_WNPL(i)      (PUERTO_CAN_1_RX_CMD_REG(i) &= \
                                                   (uint32) (~PUERTO_CAN_1_RX_WPNL_MASK))
    #define PUERTO_CAN_1_SET_RX_WNPH(i)        (PUERTO_CAN_1_RX_CMD_REG(i) |= PUERTO_CAN_1_RX_WPNH_MASK)
    #define PUERTO_CAN_1_CLEAR_RX_WNPH(i)      (PUERTO_CAN_1_RX_CMD_REG(i) &= \
                                                   (uint32) (~PUERTO_CAN_1_RX_WPNH_MASK))
    #define PUERTO_CAN_1_GET_DLC(i)            ((uint32) ((PUERTO_CAN_1_RX_CMD_REG(i) & \
            PUERTO_CAN_1_RX_DLC_VALUE_MASK) >> PUERTO_CAN_1_RX_DLC_VALUE_SHIFT))
    #define PUERTO_CAN_1_GET_RX_IDE(i)         ((uint32) ((PUERTO_CAN_1_RX_CMD_REG(i) & \
            PUERTO_CAN_1_RX_IDE_MASK) >> PUERTO_CAN_1_RX_IDE_SHIFT))
    #define PUERTO_CAN_1_GET_RX_ID(i)          ((PUERTO_CAN_1_GET_RX_IDE(i) == 0u) ? \
            (PUERTO_CAN_1_RX_ID_REG(i) >> PUERTO_CAN_1_SET_TX_ID_STANDARD_MSG_SHIFT) : \
            (PUERTO_CAN_1_RX_ID_REG(i) >> PUERTO_CAN_1_SET_TX_ID_EXTENDED_MSG_SHIFT))

    /* Set/Clear bits macro for PUERTO_CAN_1_TX mailbox(i) */
    /* Bit 0 within TX_CMD[i] */
    #define PUERTO_CAN_1_TX_TRANSMIT_REQUEST_SHIFT (0u)
    #define PUERTO_CAN_1_TX_TRANSMIT_REQUEST   \
            ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_TX_TRANSMIT_REQUEST_SHIFT))
    /* Bit 1 within TX_CMD[i] */
    #define PUERTO_CAN_1_TX_ABORT_SHIFT        (1u)
    #define PUERTO_CAN_1_TX_ABORT_MASK         ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_TX_ABORT_SHIFT))
    /* Bit 2 within TX_CMD[i] */
    #define PUERTO_CAN_1_TRANSMIT_INT_ENABLE   (0x01u)
    #define PUERTO_CAN_1_TRANSMIT_INT_DISABLE  (0x00u)
    #define PUERTO_CAN_1_TX_INT_ENABLE_SHIFT   (2u)
    #define PUERTO_CAN_1_TX_INT_ENABLE_MASK    \
            ((uint32) ((uint32) 0x00000001u << PUERTO_CAN_1_TX_INT_ENABLE_SHIFT))
    /* Bit 3 within TX_CMD[i] */
    #define PUERTO_CAN_1_TX_WPNL_SHIFT         (3u)
    #define PUERTO_CAN_1_TX_WPNL_MASK          ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_TX_WPNL_SHIFT))
    /* Bits 19-16 within TX_CMD[i] */
    #define PUERTO_CAN_1_TX_DLC_VALUE_SHIFT    (0u)
    #define PUERTO_CAN_1_TX_DLC_UPPER_VALUE_SHIFT (19u)
    #define PUERTO_CAN_1_TX_DLC_UPPER_VALUE    \
            ((uint32) ((uint32) 0x00000001u << PUERTO_CAN_1_TX_DLC_UPPER_VALUE_SHIFT))
    #define PUERTO_CAN_1_TX_DLC_VALUE_MASK     ((uint32) ((uint32) 0x0Fu << PUERTO_CAN_1_TX_DLC_VALUE_SHIFT))
    #define PUERTO_CAN_1_TX_DLC_MAX_VALUE      (8u)
    /* Bit 20 within TX_CMD[i] */
    #define PUERTO_CAN_1_TX_IDE_SHIFT          (20u)
    #define PUERTO_CAN_1_TX_IDE_MASK           ((uint32) ((uint32) 0x00000001u << PUERTO_CAN_1_TX_IDE_SHIFT))
    /* Bit 21 within TX_CMD[i] */
    #define PUERTO_CAN_1_TX_RTR_SHIFT          (21u)
    #define PUERTO_CAN_1_TX_RTR_MASK           ((uint32) ((uint32) 0x00000001u <<  PUERTO_CAN_1_TX_RTR_SHIFT))
    /* Bit 23 within TX_CMD[i] */
    #define PUERTO_CAN_1_TX_WPNH_SHIFT         (23u)
    #define PUERTO_CAN_1_TX_WPNH_MASK          ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_TX_WPNH_SHIFT))

    #define PUERTO_CAN_1_TX_TRANSMIT_MESSAGE(i) \
            (PUERTO_CAN_1_TX_CMD_REG(i) |= PUERTO_CAN_1_TX_TRANSMIT_REQUEST)
    #define PUERTO_CAN_1_TX_ABORT_MESSAGE(i) (PUERTO_CAN_1_TX_CMD_REG(i) = (PUERTO_CAN_1_TX_CMD_REG(i) & \
            (uint32) (~PUERTO_CAN_1_TX_TRANSMIT_REQUEST)) | PUERTO_CAN_1_TX_ABORT_MASK)
    #define PUERTO_CAN_1_TX_INT_ENABLE(i)    (PUERTO_CAN_1_TX_CMD_REG(i) |= PUERTO_CAN_1_TX_INT_ENABLE_MASK)
    #define PUERTO_CAN_1_TX_INT_DISABLE(i)   (PUERTO_CAN_1_TX_CMD_REG(i) &= \
                                                 (uint32) (~PUERTO_CAN_1_TX_INT_ENABLE_MASK))
    #define PUERTO_CAN_1_SET_TX_WNPL(i)     (PUERTO_CAN_1_TX_CMD_REG(i) |= PUERTO_CAN_1_TX_WPNL_MASK)
    #define PUERTO_CAN_1_CLEAR_TX_WNPL(i)   \
            (PUERTO_CAN_1_TX_CMD_REG(i) &= (uint32)(~PUERTO_CAN_1_TX_WPNL_MASK))
    #define PUERTO_CAN_1_SET_TX_IDE(i)      (PUERTO_CAN_1_TX_CMD_REG(i) |= PUERTO_CAN_1_TX_IDE_MASK)
    #define PUERTO_CAN_1_CLEAR_TX_IDE(i)    \
            (PUERTO_CAN_1_TX_CMD_REG(i) &= (uint32) (~PUERTO_CAN_1_TX_IDE_MASK))
    #define PUERTO_CAN_1_SET_TX_RTR(i)      (PUERTO_CAN_1_TX_CMD_REG(i) |= PUERTO_CAN_1_TX_RTR_MASK)
    #define PUERTO_CAN_1_CLEAR_TX_RTR(i)    \
            (PUERTO_CAN_1_TX_CMD_REG(i) &= (uint32) (~PUERTO_CAN_1_TX_RTR_MASK))
    #define PUERTO_CAN_1_SET_TX_WNPH(i)     (PUERTO_CAN_1_TX_CMD_REG(i) |= PUERTO_CAN_1_TX_WPNH_MASK)
    #define PUERTO_CAN_1_CLEAR_TX_WNPH(i)   \
            (PUERTO_CAN_1_TX_CMD_REG(i) &= (uint32)(~PUERTO_CAN_1_TX_WPNH_MASK))

    #define PUERTO_CAN_1_DATA_HIGH_ADDR     (4u)
    #define PUERTO_CAN_1_DATA_BYTE_MASK     ((uint32) 0xFFu)

    #define PUERTO_CAN_1_RX_DATA_BYTE(mailbox, i) (((i) > 3u) ? \
            (uint8) (PUERTO_CAN_1_RX_DATA_HI_REG(mailbox) >> ((7u - (i)) * PUERTO_CAN_1_ONE_BYTE_OFFSET)) : \
            (uint8) (PUERTO_CAN_1_RX_DATA_LO_REG(mailbox) >> ((3u - (i)) * PUERTO_CAN_1_ONE_BYTE_OFFSET)))

    #define PUERTO_CAN_1_TX_DATA_BYTE(mailbox, i, byte) (((i) > 3u) ? \
        (PUERTO_CAN_1_TX_DATA_HI_REG(mailbox) = (PUERTO_CAN_1_TX_DATA_HI_REG(mailbox) & \
        (uint32) (~((uint32) (PUERTO_CAN_1_DATA_BYTE_MASK << ((7u - (i)) * PUERTO_CAN_1_ONE_BYTE_OFFSET))))) | \
        (uint32) ((uint32) (byte) << ((7u - (i)) * PUERTO_CAN_1_ONE_BYTE_OFFSET))) : \
        (PUERTO_CAN_1_TX_DATA_LO_REG(mailbox) = (PUERTO_CAN_1_TX_DATA_LO_REG(mailbox) & \
        (uint32) (~((uint32) (PUERTO_CAN_1_DATA_BYTE_MASK << ((3u - (i)) * PUERTO_CAN_1_ONE_BYTE_OFFSET))))) | \
        (uint32) ((uint32) (byte) << ((3u - (i)) * PUERTO_CAN_1_ONE_BYTE_OFFSET))))
#endif /* CY_PSOC3 || CY_PSOC5 */

#if (CY_PSOC3 || CY_PSOC5)
    #define PUERTO_CAN_1_DATA_BYTE_1            (3u)
    #define PUERTO_CAN_1_DATA_BYTE_2            (2u)
    #define PUERTO_CAN_1_DATA_BYTE_3            (1u)
    #define PUERTO_CAN_1_DATA_BYTE_4            (0u)
    #define PUERTO_CAN_1_DATA_BYTE_5            (7u)
    #define PUERTO_CAN_1_DATA_BYTE_6            (6u)
    #define PUERTO_CAN_1_DATA_BYTE_7            (5u)
    #define PUERTO_CAN_1_DATA_BYTE_8            (4u)

    /* Macros for access to RX DATA for mailbox(i) */
    #define PUERTO_CAN_1_RX_DATA_BYTE1(i)       PUERTO_CAN_1_RX[i].rxdata.byte[PUERTO_CAN_1_DATA_BYTE_1]
    #define PUERTO_CAN_1_RX_DATA_BYTE2(i)       PUERTO_CAN_1_RX[i].rxdata.byte[PUERTO_CAN_1_DATA_BYTE_2]
    #define PUERTO_CAN_1_RX_DATA_BYTE3(i)       PUERTO_CAN_1_RX[i].rxdata.byte[PUERTO_CAN_1_DATA_BYTE_3]
    #define PUERTO_CAN_1_RX_DATA_BYTE4(i)       PUERTO_CAN_1_RX[i].rxdata.byte[PUERTO_CAN_1_DATA_BYTE_4]
    #define PUERTO_CAN_1_RX_DATA_BYTE5(i)       PUERTO_CAN_1_RX[i].rxdata.byte[PUERTO_CAN_1_DATA_BYTE_5]
    #define PUERTO_CAN_1_RX_DATA_BYTE6(i)       PUERTO_CAN_1_RX[i].rxdata.byte[PUERTO_CAN_1_DATA_BYTE_6]
    #define PUERTO_CAN_1_RX_DATA_BYTE7(i)       PUERTO_CAN_1_RX[i].rxdata.byte[PUERTO_CAN_1_DATA_BYTE_7]
    #define PUERTO_CAN_1_RX_DATA_BYTE8(i)       PUERTO_CAN_1_RX[i].rxdata.byte[PUERTO_CAN_1_DATA_BYTE_8]

    /* Macros for access to TX DATA for mailbox(i) */
    #define PUERTO_CAN_1_TX_DATA_BYTE1(i)       PUERTO_CAN_1_TX[i].txdata.byte[PUERTO_CAN_1_DATA_BYTE_1]
    #define PUERTO_CAN_1_TX_DATA_BYTE2(i)       PUERTO_CAN_1_TX[i].txdata.byte[PUERTO_CAN_1_DATA_BYTE_2]
    #define PUERTO_CAN_1_TX_DATA_BYTE3(i)       PUERTO_CAN_1_TX[i].txdata.byte[PUERTO_CAN_1_DATA_BYTE_3]
    #define PUERTO_CAN_1_TX_DATA_BYTE4(i)       PUERTO_CAN_1_TX[i].txdata.byte[PUERTO_CAN_1_DATA_BYTE_4]
    #define PUERTO_CAN_1_TX_DATA_BYTE5(i)       PUERTO_CAN_1_TX[i].txdata.byte[PUERTO_CAN_1_DATA_BYTE_5]
    #define PUERTO_CAN_1_TX_DATA_BYTE6(i)       PUERTO_CAN_1_TX[i].txdata.byte[PUERTO_CAN_1_DATA_BYTE_6]
    #define PUERTO_CAN_1_TX_DATA_BYTE7(i)       PUERTO_CAN_1_TX[i].txdata.byte[PUERTO_CAN_1_DATA_BYTE_7]
    #define PUERTO_CAN_1_TX_DATA_BYTE8(i)       PUERTO_CAN_1_TX[i].txdata.byte[PUERTO_CAN_1_DATA_BYTE_8]
#else  /* CY_PSOC4 */
    /* Macros for access to RX DATA for mailbox(i) */
    #define PUERTO_CAN_1_RX_DATA_BYTE1(i)       \
            ((uint8) (PUERTO_CAN_1_RX_DATA_LO_REG(i) >> PUERTO_CAN_1_THREE_BYTE_OFFSET))
    #define PUERTO_CAN_1_RX_DATA_BYTE2(i)       \
            ((uint8) (PUERTO_CAN_1_RX_DATA_LO_REG(i) >> PUERTO_CAN_1_TWO_BYTE_OFFSET))
    #define PUERTO_CAN_1_RX_DATA_BYTE3(i)       \
            ((uint8) (PUERTO_CAN_1_RX_DATA_LO_REG(i) >> PUERTO_CAN_1_ONE_BYTE_OFFSET))
    #define PUERTO_CAN_1_RX_DATA_BYTE4(i)       ((uint8) PUERTO_CAN_1_RX_DATA_LO_REG(i))
    #define PUERTO_CAN_1_RX_DATA_BYTE5(i)       \
            ((uint8) (PUERTO_CAN_1_RX_DATA_HI_REG(i) >> PUERTO_CAN_1_THREE_BYTE_OFFSET))
    #define PUERTO_CAN_1_RX_DATA_BYTE6(i)       \
            ((uint8) (PUERTO_CAN_1_RX_DATA_HI_REG(i) >> PUERTO_CAN_1_TWO_BYTE_OFFSET))
    #define PUERTO_CAN_1_RX_DATA_BYTE7(i)       \
            ((uint8) (PUERTO_CAN_1_RX_DATA_HI_REG(i) >> PUERTO_CAN_1_ONE_BYTE_OFFSET))
    #define PUERTO_CAN_1_RX_DATA_BYTE8(i)       ((uint8) PUERTO_CAN_1_RX_DATA_HI_REG(i))

    /* Macros for access to TX DATA for mailbox(i) */
    #define PUERTO_CAN_1_TX_DATA_BYTE1(i, byte) \
            (PUERTO_CAN_1_TX_DATA_LO_REG(i) = (PUERTO_CAN_1_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (PUERTO_CAN_1_DATA_BYTE_MASK << PUERTO_CAN_1_THREE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << PUERTO_CAN_1_THREE_BYTE_OFFSET))
    #define PUERTO_CAN_1_TX_DATA_BYTE2(i, byte) \
            (PUERTO_CAN_1_TX_DATA_LO_REG(i) = (PUERTO_CAN_1_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (PUERTO_CAN_1_DATA_BYTE_MASK << PUERTO_CAN_1_TWO_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << PUERTO_CAN_1_TWO_BYTE_OFFSET))
    #define PUERTO_CAN_1_TX_DATA_BYTE3(i, byte) \
            (PUERTO_CAN_1_TX_DATA_LO_REG(i) = (PUERTO_CAN_1_TX_DATA_LO_REG(i) & \
            (uint32) (~((uint32) (PUERTO_CAN_1_DATA_BYTE_MASK << PUERTO_CAN_1_ONE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << PUERTO_CAN_1_ONE_BYTE_OFFSET))
    #define PUERTO_CAN_1_TX_DATA_BYTE4(i, byte) \
            (PUERTO_CAN_1_TX_DATA_LO_REG(i) = (PUERTO_CAN_1_TX_DATA_LO_REG(i) & \
            (uint32) (~PUERTO_CAN_1_DATA_BYTE_MASK)) | (uint32) (byte))
    #define PUERTO_CAN_1_TX_DATA_BYTE5(i, byte) \
            (PUERTO_CAN_1_TX_DATA_HI_REG(i) = (PUERTO_CAN_1_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (PUERTO_CAN_1_DATA_BYTE_MASK << PUERTO_CAN_1_THREE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << PUERTO_CAN_1_THREE_BYTE_OFFSET))
    #define PUERTO_CAN_1_TX_DATA_BYTE6(i, byte) \
            (PUERTO_CAN_1_TX_DATA_HI_REG(i) = (PUERTO_CAN_1_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (PUERTO_CAN_1_DATA_BYTE_MASK << PUERTO_CAN_1_TWO_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << PUERTO_CAN_1_TWO_BYTE_OFFSET))
    #define PUERTO_CAN_1_TX_DATA_BYTE7(i, byte) \
            (PUERTO_CAN_1_TX_DATA_HI_REG(i) = (PUERTO_CAN_1_TX_DATA_HI_REG(i) & \
            (uint32) (~((uint32) (PUERTO_CAN_1_DATA_BYTE_MASK << PUERTO_CAN_1_ONE_BYTE_OFFSET)))) | \
            (uint32) ((uint32) (byte) << PUERTO_CAN_1_ONE_BYTE_OFFSET))
    #define PUERTO_CAN_1_TX_DATA_BYTE8(i, byte) \
            (PUERTO_CAN_1_TX_DATA_HI_REG(i) = (PUERTO_CAN_1_TX_DATA_HI_REG(i) & \
            (uint32) (~PUERTO_CAN_1_DATA_BYTE_MASK)) | (uint32) (byte))
#endif /* CY_PSOC3 || CY_PSOC5 */

/* Macros for setting Tx Msg Identifier in PUERTO_CAN_1_TX_ID register */
#define PUERTO_CAN_1_SET_TX_ID_STANDARD_MSG_SHIFT  (21u)
#define PUERTO_CAN_1_SET_TX_ID_EXTENDED_MSG_SHIFT  (3u)
#define PUERTO_CAN_1_SET_TX_ID_STANDARD_MSG(i, id) (CY_SET_REG32(PUERTO_CAN_1_TX_ID_PTR(i), \
        (uint32) ((uint32) (id) << PUERTO_CAN_1_SET_TX_ID_STANDARD_MSG_SHIFT)))
#define PUERTO_CAN_1_SET_TX_ID_EXTENDED_MSG(i, id) (CY_SET_REG32(PUERTO_CAN_1_TX_ID_PTR(i), \
        (uint32) ((uint32) (id) << PUERTO_CAN_1_SET_TX_ID_EXTENDED_MSG_SHIFT)))

/* Mask for bits within PUERTO_CAN_1_CSR_CFG */
#define PUERTO_CAN_1_EDGE_MODE_SHIFT           (0u)
/* Bit 0 within CSR_CFG */
#define PUERTO_CAN_1_EDGE_MODE_MASK            ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_EDGE_MODE_SHIFT))
#define PUERTO_CAN_1_SAMPLE_MODE_SHIFT         (1u)
/* Bit 1 within CSR_CFG */
#define PUERTO_CAN_1_SAMPLE_MODE_MASK          ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_SAMPLE_MODE_SHIFT))
#define PUERTO_CAN_1_CFG_REG_SJW_SHIFT         (2u)
/* Bits 3-2 within CSR_CFG */
#define PUERTO_CAN_1_CFG_REG_SJW_MASK          ((uint8) ((uint8) 0x03u << PUERTO_CAN_1_CFG_REG_SJW_SHIFT))
#define PUERTO_CAN_1_CFG_REG_SJW_LOWER_LIMIT   (0x03u)  /* the lowest allowed value of cfg_sjw */
#define PUERTO_CAN_1_RESET_SHIFT               (4u)
/* Bit 4 within CSR_CFG    */
#define PUERTO_CAN_1_RESET_MASK                ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_RESET_SHIFT))
#define PUERTO_CAN_1_CFG_REG_TSEG2_SHIFT       (5u)
/* Bits 7-5 within CSR_CFG */
#define PUERTO_CAN_1_CFG_REG_TSEG2_MASK        ((uint8) ((uint8) 0x07u << PUERTO_CAN_1_CFG_REG_TSEG2_SHIFT))
/* Highest allowed value of cfg_tseg2 */
#define PUERTO_CAN_1_CFG_REG_TSEG2_UPPER_LIMIT (0x07u)
/* Lowest allowed value of cfg_tseg2 */
#define PUERTO_CAN_1_CFG_REG_TSEG2_LOWER_LIMIT (0x02u)
/* Lowest allowed value of cfg_tseg2 if sample point is one point */
#define PUERTO_CAN_1_CFG_REG_TSEG2_EXCEPTION   (0x01u)
/* Bits 11-8 within CSR_CFG */
#define PUERTO_CAN_1_CFG_REG_TSEG1_SHIFT       (8u)
#define PUERTO_CAN_1_CFG_REG_TSEG1_MASK        (0x0Fu)
/* Highest allowed value of cfg_tseg1 */
#define PUERTO_CAN_1_CFG_REG_TSEG1_UPPER_LIMIT (0x0Fu)
/* Lowest allowed value of cfg_tseg1 */
#define PUERTO_CAN_1_CFG_REG_TSEG1_LOWER_LIMIT (0x02u)
#define PUERTO_CAN_1_ARBITER_SHIFT             (12u)

#if (CY_PSOC3 || CY_PSOC5)
    #define PUERTO_CAN_1_ARBITRATION_SHIFT     (4u)
    /* Bit 12 within CSR_CFG */
    #define PUERTO_CAN_1_ARBITRATION_MASK      ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_ARBITRATION_SHIFT))
#else  /* CY_PSOC4 */
    #define PUERTO_CAN_1_ARBITRATION_SHIFT     (12u)
    /* Bit 12 within CSR_CFG */
    #define PUERTO_CAN_1_ARBITRATION_MASK      ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_ARBITRATION_SHIFT))
    /* Bit 13 within CSR_CFG */
    #define PUERTO_CAN_1_ENDIANNESS_SHIFT      (13u)
    #define PUERTO_CAN_1_ENDIANNESS_MASK       ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_ENDIANNESS_SHIFT))
    /* Bit 14 within CSR_CFG */
    #define PUERTO_CAN_1_ECR_MODE_SHIFT        (14u)
    #define PUERTO_CAN_1_ECR_MODE_MASK         ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_ECR_MODE_SHIFT))
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Bits 23-16 within CSR_CFG */
#define PUERTO_CAN_1_BITRATE_SHIFT             (16u)
#define PUERTO_CAN_1_BITRATE_MASK              (0x7FFFu)
#define PUERTO_CAN_1_BITRATE_MASK_SHIFTED      \
        ((uint32) ((uint32) PUERTO_CAN_1_BITRATE_MASK << PUERTO_CAN_1_BITRATE_SHIFT))

/* Mask for bits within PUERTO_CAN_1_CSR_CMD */
#define PUERTO_CAN_1_MODE_SHIFT                (0u)
/* Bit 0 within CSR_CMD */
#define PUERTO_CAN_1_MODE_MASK                 ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_MODE_SHIFT))
#define PUERTO_CAN_1_OPMODE_MASK_SHIFT         (1u)
/* Bit 1 within CSR_CMD */
#define PUERTO_CAN_1_OPMODE_MASK               ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_OPMODE_MASK_SHIFT))

#if (CY_PSOC3 || CY_PSOC5)
    #define PUERTO_CAN_1_OPMODE_FIELD_MASK     ((uint8) ((uint8) 0x03u << PUERTO_CAN_1_MODE_SHIFT))
#else  /* CY_PSOC4 */
    #define PUERTO_CAN_1_OPMODE_FIELD_MASK     ((uint8) ((uint8) 0x07u << PUERTO_CAN_1_MODE_SHIFT))
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Mask for bits within PUERTO_CAN_1_CSR_CMD */
#define PUERTO_CAN_1_ERROR_STATE_SHIFT         (0u)
/* Bit 17-16 within ERR_SR */
#define PUERTO_CAN_1_ERROR_STATE_MASK          ((uint8) ((uint8) 0x03u << PUERTO_CAN_1_ERROR_STATE_SHIFT))

#if (CY_PSOC3 || CY_PSOC5)
    #define PUERTO_CAN_1_TX_ERROR_FLAG_SHIFT   (2u)
    /* Bit 18 within ERR_SR */
    #define PUERTO_CAN_1_TX_ERROR_FLAG_MASK    ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_TX_ERROR_FLAG_SHIFT))
    #define PUERTO_CAN_1_RX_ERROR_FLAG_SHIFT   (3u)
    /* Bit 19 within ERR_SR */
    #define PUERTO_CAN_1_RX_ERROR_FLAG_MASK    ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_RX_ERROR_FLAG_SHIFT))
#else  /* CY_PSOC4 */
    #define PUERTO_CAN_1_TX_ERROR_FLAG_SHIFT   (18u)
    /* Bit 18 within ERR_SR */
    #define PUERTO_CAN_1_TX_ERROR_FLAG_MASK    ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_TX_ERROR_FLAG_SHIFT))
    #define PUERTO_CAN_1_RX_ERROR_FLAG_SHIFT   (19u)
    /* Bit 19 within ERR_SR */
    #define PUERTO_CAN_1_RX_ERROR_FLAG_MASK    ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_RX_ERROR_FLAG_SHIFT))

    /* Mask and Macros for bits within PUERTO_CAN_1_ECR_REG */
    #define PUERTO_CAN_1_ECR_STATUS_ARM        (0x01u)
    /* Mask for clearing PUERTO_CAN_1INT_STATUS */
    #define PUERTO_CAN_1_INT_STATUS_MASK       (0x00001FFCu)
#endif /* (CY_PSOC3 || CY_PSOC5) */

/* Mask and Macros for bits within PUERTO_CAN_1_INT_EN_REG */
#define PUERTO_CAN_1_GLOBAL_INT_SHIFT          (0u)
#define PUERTO_CAN_1_ARBITRATION_LOST_SHIFT    (2u)
#define PUERTO_CAN_1_OVERLOAD_ERROR_SHIFT      (3u)
#define PUERTO_CAN_1_BIT_ERROR_SHIFT           (4u)
#define PUERTO_CAN_1_STUFF_ERROR_SHIFT         (5u)
#define PUERTO_CAN_1_ACK_ERROR_SHIFT           (6u)
#define PUERTO_CAN_1_FORM_ERROR_SHIFT          (7u)

#if (CY_PSOC3 || CY_PSOC5)
    #define PUERTO_CAN_1_CRC_ERROR_SHIFT       (0u)
    #define PUERTO_CAN_1_BUS_OFF_SHIFT         (1u)
    #define PUERTO_CAN_1_RX_MSG_LOST_SHIFT     (2u)
    #define PUERTO_CAN_1_TX_MESSAGE_SHIFT      (3u)
    #define PUERTO_CAN_1_RX_MESSAGE_SHIFT      (4u)

    /* Bit 0 within INT_EN */
    #define PUERTO_CAN_1_GLOBAL_INT_MASK       ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_GLOBAL_INT_SHIFT))
    /* Bit 2 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_ARBITRATION_LOST_MASK ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_ARBITRATION_LOST_SHIFT))
    /* Bit 3 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_OVERLOAD_ERROR_MASK   ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_OVERLOAD_ERROR_SHIFT))
    /* Bit 4 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_BIT_ERROR_MASK        ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_BIT_ERROR_SHIFT))
    /* Bit 5 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_STUFF_ERROR_MASK      ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_STUFF_ERROR_SHIFT))
    /* Bit 6 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_ACK_ERROR_MASK        ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_ACK_ERROR_SHIFT))
    /* Bit 7 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_FORM_ERROR_MASK       ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_FORM_ERROR_SHIFT))
    /* Bit 8 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_CRC_ERROR_MASK        ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_CRC_ERROR_SHIFT))
    /* Bit 9 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_BUS_OFF_MASK          ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_BUS_OFF_SHIFT))
    /* Bit 10 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_RX_MSG_LOST_MASK      ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_RX_MSG_LOST_SHIFT))
    /* Bit 11 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_TX_MESSAGE_MASK       ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_TX_MESSAGE_SHIFT))
    /* Bit 12 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_RX_MESSAGE_MASK       ((uint8) ((uint8) 0x01u << PUERTO_CAN_1_RX_MESSAGE_SHIFT))

    #define PUERTO_CAN_1_ARBITRATION_LOST_INT_ENABLE   \
            (PUERTO_CAN_1_INT_EN_REG.byte[0u] |= PUERTO_CAN_1_ARBITRATION_LOST_MASK)
    #define PUERTO_CAN_1_ARBITRATION_LOST_INT_DISABLE  \
            (PUERTO_CAN_1_INT_EN_REG.byte[0u] &= (uint8) (~PUERTO_CAN_1_ARBITRATION_LOST_MASK))
    #define PUERTO_CAN_1_OVERLOAD_ERROR_INT_ENABLE     \
            (PUERTO_CAN_1_INT_EN_REG.byte[0u] |= PUERTO_CAN_1_OVERLOAD_ERROR_MASK)
    #define PUERTO_CAN_1_OVERLOAD_ERROR_INT_DISABLE    \
            (PUERTO_CAN_1_INT_EN_REG.byte[0u] &= (uint8) (~PUERTO_CAN_1_OVERLOAD_ERROR_MASK))
    #define PUERTO_CAN_1_BIT_ERROR_LOST_INT_ENABLE     \
            (PUERTO_CAN_1_INT_EN_REG.byte[0u] |= PUERTO_CAN_1_BIT_ERROR_MASK)
    #define PUERTO_CAN_1_BIT_ERROR_LOST_INT_DISABLE    \
            (PUERTO_CAN_1_INT_EN_REG.byte[0u] &= (uint8) (~PUERTO_CAN_1_BIT_ERROR_MASK))
    #define PUERTO_CAN_1_STUFF_ERROR_INT_ENABLE        \
            (PUERTO_CAN_1_INT_EN_REG.byte[0u] |= PUERTO_CAN_1_STUFF_ERROR_MASK)
    #define PUERTO_CAN_1_STUFF_ERROR_INT_DISABLE       \
            (PUERTO_CAN_1_INT_EN_REG.byte[0u] &= (uint8) (~PUERTO_CAN_1_STUFF_ERROR_MASK))
    #define PUERTO_CAN_1_ACK_ERROR_INT_ENABLE          \
            (PUERTO_CAN_1_INT_EN_REG.byte[0u] |= PUERTO_CAN_1_ACK_ERROR_MASK)
    #define PUERTO_CAN_1_ACK_ERROR_INT_DISABLE         \
            (PUERTO_CAN_1_INT_EN_REG.byte[0u] &= (uint8) (~PUERTO_CAN_1_ACK_ERROR_MASK))
    #define PUERTO_CAN_1_FORM_ERROR_INT_ENABLE         \
            (PUERTO_CAN_1_INT_EN_REG.byte[0u] |= PUERTO_CAN_1_FORM_ERROR_MASK)
    #define PUERTO_CAN_1_FORM_ERROR_INT_DISABLE        \
            (PUERTO_CAN_1_INT_EN_REG.byte[0u] &= (uint8) (~PUERTO_CAN_1_FORM_ERROR_MASK))
    #define PUERTO_CAN_1_CRC_ERROR_INT_ENABLE          \
            (PUERTO_CAN_1_INT_EN_REG.byte[1u] |= PUERTO_CAN_1_CRC_ERROR_MASK)
    #define PUERTO_CAN_1_CRC_ERROR_INT_DISABLE         \
            (PUERTO_CAN_1_INT_EN_REG.byte[1u] &= (uint8) (~PUERTO_CAN_1_CRC_ERROR_MASK))
    #define PUERTO_CAN_1_BUS_OFF_INT_ENABLE            \
            (PUERTO_CAN_1_INT_EN_REG.byte[1u] |= PUERTO_CAN_1_BUS_OFF_MASK)
    #define PUERTO_CAN_1_BUS_OFF_INT_DISABLE           \
            (PUERTO_CAN_1_INT_EN_REG.byte[1u] &= (uint8) (~PUERTO_CAN_1_BUS_OFF_MASK))
    #define PUERTO_CAN_1_RX_MSG_LOST_INT_ENABLE        \
            (PUERTO_CAN_1_INT_EN_REG.byte[1u] |= PUERTO_CAN_1_RX_MSG_LOST_MASK)
    #define PUERTO_CAN_1_RX_MSG_LOST_INT_DISABLE       \
            (PUERTO_CAN_1_INT_EN_REG.byte[1u] &= (uint8) (~PUERTO_CAN_1_RX_MSG_LOST_MASK))
    #define PUERTO_CAN_1_TX_MSG_INT_ENABLE             \
            (PUERTO_CAN_1_INT_EN_REG.byte[1u] |= PUERTO_CAN_1_TX_MESSAGE_MASK)
    #define PUERTO_CAN_1_TX_MSG_INT_DISABLE            \
            (PUERTO_CAN_1_INT_EN_REG.byte[1u] &= (uint8) (~PUERTO_CAN_1_TX_MESSAGE_MASK))
    #define PUERTO_CAN_1_RX_MSG_INT_ENABLE             \
            (PUERTO_CAN_1_INT_EN_REG.byte[1u] |= PUERTO_CAN_1_RX_MESSAGE_MASK)
    #define PUERTO_CAN_1_RX_MSG_INT_DISABLE            \
            (PUERTO_CAN_1_INT_EN_REG.byte[1u] &= (uint8) (~PUERTO_CAN_1_RX_MESSAGE_MASK))
#else  /* CY_PSOC4 */
    #define PUERTO_CAN_1_CRC_ERROR_SHIFT       (8u)
    #define PUERTO_CAN_1_BUS_OFF_SHIFT         (9u)
    #define PUERTO_CAN_1_RX_MSG_LOST_SHIFT     (10u)
    #define PUERTO_CAN_1_TX_MESSAGE_SHIFT      (11u)
    #define PUERTO_CAN_1_RX_MESSAGE_SHIFT      (12u)

    /* Mask and Macros for bits within PUERTO_CAN_1_INT_EN_REG */
    /* Bit 0 within INT_EN */
    #define PUERTO_CAN_1_GLOBAL_INT_MASK       ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_GLOBAL_INT_SHIFT))
    /* Bit 2 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_ARBITRATION_LOST_MASK ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_ARBITRATION_LOST_SHIFT))
    /* Bit 3 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_OVERLOAD_ERROR_MASK   ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_OVERLOAD_ERROR_SHIFT))
    /* Bit 4 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_BIT_ERROR_MASK        ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_BIT_ERROR_SHIFT))
    /* Bit 5 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_STUFF_ERROR_MASK      ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_STUFF_ERROR_SHIFT))
    /* Bit 6 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_ACK_ERROR_MASK        ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_ACK_ERROR_SHIFT))
    /* Bit 7 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_FORM_ERROR_MASK       ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_FORM_ERROR_SHIFT))
    /* Bit 8 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_CRC_ERROR_MASK        ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_CRC_ERROR_SHIFT))
    /* Bit 9 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_BUS_OFF_MASK          ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_BUS_OFF_SHIFT))
    /* Bit 10 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_RX_MSG_LOST_MASK      ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_RX_MSG_LOST_SHIFT))
    /* Bit 11 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_TX_MESSAGE_MASK       ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_TX_MESSAGE_SHIFT))
    /* Bit 12 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_RX_MESSAGE_MASK       ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_RX_MESSAGE_SHIFT))

    #define PUERTO_CAN_1_ARBITRATION_LOST_INT_ENABLE   \
            (PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_ARBITRATION_LOST_MASK)
    #define PUERTO_CAN_1_ARBITRATION_LOST_INT_DISABLE  \
            (PUERTO_CAN_1_INT_EN_REG &= (uint32) (~PUERTO_CAN_1_ARBITRATION_LOST_MASK))
    #define PUERTO_CAN_1_OVERLOAD_ERROR_INT_ENABLE     \
            (PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_OVERLOAD_ERROR_MASK)
    #define PUERTO_CAN_1_OVERLOAD_ERROR_INT_DISABLE    \
            (PUERTO_CAN_1_INT_EN_REG &= (uint32) (~PUERTO_CAN_1_OVERLOAD_ERROR_MASK))
    #define PUERTO_CAN_1_BIT_ERROR_LOST_INT_ENABLE     \
            (PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_BIT_ERROR_MASK)
    #define PUERTO_CAN_1_BIT_ERROR_LOST_INT_DISABLE    \
            (PUERTO_CAN_1_INT_EN_REG &= (uint32) (~PUERTO_CAN_1_BIT_ERROR_MASK))
    #define PUERTO_CAN_1_STUFF_ERROR_INT_ENABLE        \
            (PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_STUFF_ERROR_MASK)
    #define PUERTO_CAN_1_STUFF_ERROR_INT_DISABLE       \
            (PUERTO_CAN_1_INT_EN_REG &= (uint32) (~PUERTO_CAN_1_STUFF_ERROR_MASK))
    #define PUERTO_CAN_1_ACK_ERROR_INT_ENABLE          \
            (PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_ACK_ERROR_MASK)
    #define PUERTO_CAN_1_ACK_ERROR_INT_DISABLE         \
            (PUERTO_CAN_1_INT_EN_REG &= (uint32) (~PUERTO_CAN_1_ACK_ERROR_MASK))
    #define PUERTO_CAN_1_FORM_ERROR_INT_ENABLE         \
            (PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_FORM_ERROR_MASK)
    #define PUERTO_CAN_1_FORM_ERROR_INT_DISABLE        \
            (PUERTO_CAN_1_INT_EN_REG &= (uint32) (~PUERTO_CAN_1_FORM_ERROR_MASK))
    #define PUERTO_CAN_1_CRC_ERROR_INT_ENABLE          \
            (PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_CRC_ERROR_MASK)
    #define PUERTO_CAN_1_CRC_ERROR_INT_DISABLE         \
            (PUERTO_CAN_1_INT_EN_REG &= (uint32) (~PUERTO_CAN_1_CRC_ERROR_MASK))
    #define PUERTO_CAN_1_BUS_OFF_INT_ENABLE            \
            (PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_BUS_OFF_MASK)
    #define PUERTO_CAN_1_BUS_OFF_INT_DISABLE           \
            (PUERTO_CAN_1_INT_EN_REG &= (uint32) (~PUERTO_CAN_1_BUS_OFF_MASK))
    #define PUERTO_CAN_1_RX_MSG_LOST_INT_ENABLE        \
            (PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_RX_MSG_LOST_MASK)
    #define PUERTO_CAN_1_RX_MSG_LOST_INT_DISABLE       \
            (PUERTO_CAN_1_INT_EN_REG &= (uint32) (~PUERTO_CAN_1_RX_MSG_LOST_MASK))
    #define PUERTO_CAN_1_TX_MSG_INT_ENABLE             \
            (PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_TX_MESSAGE_MASK)
    #define PUERTO_CAN_1_TX_MSG_INT_DISABLE            \
            (PUERTO_CAN_1_INT_EN_REG &= (uint32) (~PUERTO_CAN_1_TX_MESSAGE_MASK))
    #define PUERTO_CAN_1_RX_MSG_INT_ENABLE             \
            (PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_RX_MESSAGE_MASK)
    #define PUERTO_CAN_1_RX_MSG_INT_DISABLE            \
            (PUERTO_CAN_1_INT_EN_REG &= (uint32) (~PUERTO_CAN_1_RX_MESSAGE_MASK))

    /* Bit 13 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_RTR_MSG_SHIFT              (13u)
    #define PUERTO_CAN_1_RTR_MSG_MASK               ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_RTR_MSG_SHIFT))
    #define PUERTO_CAN_1_RTR_MSG_INT_ENABLE         (PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_RTR_MSG_MASK)
    #define PUERTO_CAN_1_RTR_MSG_INT_DISABLE        \
            (PUERTO_CAN_1_INT_EN_REG &= (uint32) (~PUERTO_CAN_1_RTR_MSG_MASK))
    /* Bit 14 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_STUCK_AT_ZERO_SHIFT        (14u)
    #define PUERTO_CAN_1_STUCK_AT_ZERO_MASK         \
            ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_STUCK_AT_ZERO_SHIFT))
    #define PUERTO_CAN_1_STUCK_AT_ZERO_INT_ENABLE   \
            (PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_STUCK_AT_ZERO_MASK)
    #define PUERTO_CAN_1_STUCK_AT_ZERO_INT_DISABLE  \
            (PUERTO_CAN_1_INT_EN_REG &= (uint32) (~PUERTO_CAN_1_STUCK_AT_ZERO_MASK))
    /* Bit 15 within INT_EN and INT_SR */
    #define PUERTO_CAN_1_SST_FAILURE_SHIFT          (15u)
    #define PUERTO_CAN_1_SST_FAILURE_MASK           \
            ((uint32) ((uint32) 0x01u << PUERTO_CAN_1_SST_FAILURE_SHIFT))
    #define PUERTO_CAN_1_SST_FAILURE_INT_ENABLE     \
            (PUERTO_CAN_1_INT_EN_REG |= PUERTO_CAN_1_SST_FAILURE_MASK)
    #define PUERTO_CAN_1_SST_FAILURE_INT_DISABLE    \
            (PUERTO_CAN_1_INT_EN_REG &= (uint32) (~PUERTO_CAN_1_SST_FAILURE_MASK))
#endif /* CY_PSOC3 || CY_PSOC5 */

#define PUERTO_CAN_1_GLOBAL_INT_ENABLE_SHIFT        (0u)
#define PUERTO_CAN_1_ARBITRATION_LOST_ENABLE_SHIFT  (2u)
#define PUERTO_CAN_1_OVERLOAD_ERROR_ENABLE_SHIFT    (3u)
#define PUERTO_CAN_1_BIT_ERROR_ENABLE_SHIFT         (4u)
#define PUERTO_CAN_1_STUFF_ERROR_ENABLE_SHIFT       (5u)
#define PUERTO_CAN_1_ACK_ERROR_ENABLE_SHIFT         (6u)
#define PUERTO_CAN_1_FORM_ERROR_ENABLE_SHIFT        (7u)
#define PUERTO_CAN_1_CRC_ERROR_ENABLE_SHIFT         (8u)
#define PUERTO_CAN_1_BUS_OFF_ENABLE_SHIFT           (9u)
#define PUERTO_CAN_1_RX_MSG_LOST_ENABLE_SHIFT       (10u)
#define PUERTO_CAN_1_TX_MESSAGE_ENABLE_SHIFT        (11u)
#define PUERTO_CAN_1_RX_MESSAGE_ENABLE_SHIFT        (12u)

#define PUERTO_CAN_1_GLOBAL_INT_ENABLE    ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_GLOBAL_INT_ENABLE_SHIFT))
#define PUERTO_CAN_1_ARBITRATION_LOST_ENABLE \
        ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_ARBITRATION_LOST_ENABLE_SHIFT))
#define PUERTO_CAN_1_OVERLOAD_ERROR_ENABLE   \
        ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_OVERLOAD_ERROR_ENABLE_SHIFT))
#define PUERTO_CAN_1_BIT_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_BIT_ERROR_ENABLE_SHIFT))
#define PUERTO_CAN_1_STUFF_ERROR_ENABLE   ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_STUFF_ERROR_ENABLE_SHIFT))
#define PUERTO_CAN_1_ACK_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_ACK_ERROR_ENABLE_SHIFT))
#define PUERTO_CAN_1_FORM_ERROR_ENABLE    ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_FORM_ERROR_ENABLE_SHIFT))
#define PUERTO_CAN_1_CRC_ERROR_ENABLE     ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_CRC_ERROR_ENABLE_SHIFT))
#define PUERTO_CAN_1_BUS_OFF_ENABLE       ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_BUS_OFF_ENABLE_SHIFT))
#define PUERTO_CAN_1_RX_MSG_LOST_ENABLE   ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_RX_MSG_LOST_ENABLE_SHIFT))
#define PUERTO_CAN_1_TX_MESSAGE_ENABLE    ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_TX_MESSAGE_ENABLE_SHIFT))
#define PUERTO_CAN_1_RX_MESSAGE_ENABLE    ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_RX_MESSAGE_ENABLE_SHIFT))

#if (!(CY_PSOC3 || CY_PSOC5))
    #define PUERTO_CAN_1_RTR_MESSAGE_ENABLE_SHIFT   (13u)
    #define PUERTO_CAN_1_STUCK_AT_ZERO_ENABLE_SHIFT (14u)
    #define PUERTO_CAN_1_SST_FAILURE_ENABLE_SHIFT   (15u)

    #define PUERTO_CAN_1_RTR_MESSAGE_ENABLE   \
            ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_RTR_MESSAGE_ENABLE_SHIFT))
    #define PUERTO_CAN_1_STUCK_AT_ZERO_ENABLE \
            ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_STUCK_AT_ZERO_ENABLE_SHIFT))
    #define PUERTO_CAN_1_SST_FAILURE_ENABLE   \
            ((uint16) ((uint16) 0x01u << PUERTO_CAN_1_SST_FAILURE_ENABLE_SHIFT))
#endif /* (!(CY_PSOC3 || CY_PSOC5)) */

#define PUERTO_CAN_1_REG_ADDR_MASK        ((uint32) 0x0000FFFFu)


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

#define PUERTO_CAN_1_TREE_BYTE_OFFSET     (PUERTO_CAN_1_THREE_BYTE_OFFSET)

/* PUERTO_CAN_1_SetRestartType() parameters */
#define PUERTO_CAN_1_RESTART_BY_HAND      (PUERTO_CAN_1_MANUAL_RESTART)

/* PUERTO_CAN_1_SetOpMode() parameters */
#define PUERTO_CAN_1_LISTEN_ONLY          (PUERTO_CAN_1_LISTEN_ONLY_MODE)
#define PUERTO_CAN_1_ACTIVE_MODE          (PUERTO_CAN_1_INITIAL_MODE)

#ifdef PUERTO_CAN_1_ISR_CALLBACK
    #define PUERTO_CAN_1_ISR_INTERRUPT_CALLBACK
    #define PUERTO_CAN_1_ISR_InterruptCallback  PUERTO_CAN_1_Isr_Callback
#endif

#endif /* CY_CAN_PUERTO_CAN_1_H */


/* [] END OF FILE */
