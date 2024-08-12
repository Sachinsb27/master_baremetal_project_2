#ifndef UART_H
#define UART_H
#include "scb.h"

/** UART Mode */
typedef enum
{
    CY_SCB_UART_STANDARD  = 0U, /**< Configures the SCB for Standard UART operation */
} cy_en_scb_uart_mode_t;

/** UART Stop Bits */
typedef enum
{
    CY_SCB_UART_STOP_BITS_1   = 2U,  /**< UART looks for 1 Stop Bit    */
    CY_SCB_UART_STOP_BITS_1_5 = 3U,  /**< UART looks for 1.5 Stop Bits */
    CY_SCB_UART_STOP_BITS_2   = 4U,  /**< UART looks for 2 Stop Bits   */
    CY_SCB_UART_STOP_BITS_2_5 = 5U,  /**< UART looks for 2.5 Stop Bits */
    CY_SCB_UART_STOP_BITS_3   = 6U,  /**< UART looks for 3 Stop Bits   */
    CY_SCB_UART_STOP_BITS_3_5 = 7U,  /**< UART looks for 3.5 Stop Bits */
    CY_SCB_UART_STOP_BITS_4   = 8U,  /**< UART looks for 4 Stop Bits   */
} cy_en_scb_uart_stop_bits_t;

/** UART Parity */
typedef enum
{
    CY_SCB_UART_PARITY_NONE = 0U,    /**< UART has no parity check   */
    CY_SCB_UART_PARITY_EVEN = 2U,    /**< UART has even parity check */
    CY_SCB_UART_PARITY_ODD  = 3U,    /**< UART has odd parity check  */
} cy_en_scb_uart_parity_t;

/** UART Polarity */
typedef enum
{
    CY_SCB_UART_ACTIVE_LOW  = 0U,   /**< Signal is active low */
    CY_SCB_UART_ACTIVE_HIGH = 1U,   /**< Signal is active high */
} cy_en_scb_uart_polarity_t;

/** UART configuration structure */
typedef struct stc_scb_uart_config
{
    /** Specifies the UART's mode of operation */
    cy_en_scb_uart_mode_t    uartMode;

    /**
    * Oversample factor for UART.
    * * The UART baud rate is the SCB Clock frequency / oversample
    *  (valid range is 8-16).
    */
    uint32_t    oversample;

    /** The width of UART data (valid range is 5 to 9) */
    uint32_t    dataWidth;

    /**
    * Enables the hardware to shift out data element MSB first; otherwise,
    * LSB first
    */
    bool        enableMsbFirst;

    /**
    * Specifies the number of stop bits in the UART transaction, in half-bit
    * increments.
    *
    * \note For the PSoC 4000S, PSoC 4100S, PSoC 4100S Plus, and PSoC 4500S
    * series, a stop bits error is detected only if the stop bits length equals
    * or exceeds 1.5 bits.
    */
    cy_en_scb_uart_stop_bits_t    stopBits;

    /** Configures the UART parity */
    cy_en_scb_uart_parity_t    parity;

    /**
    * Enables the usage of the CTS input signal for the transmitter. The
    * transmitter waits for CTS to be active before sending data
    */
    bool        enableCts;

    /** Sets the CTS Polarity */
    cy_en_scb_uart_polarity_t    ctsPolarity;

    /**
    * When the RX FIFO has fewer entries than rtsRxFifoLevel, the
    * RTS signal is active (note to disable RTS, set this field to zero)
    */
    uint32_t    rtsRxFifoLevel;

    /** Sets the RTS Polarity */
    cy_en_scb_uart_polarity_t    rtsPolarity;

    /**
    * When there are more entries in the RX FIFO than this level
    * the RX trigger output goes high. This output can be connected
    * to a DMA channel through a trigger mux.
    * Also, it controls the \ref CY_SCB_UART_RX_TRIGGER interrupt source.
    */
    uint32_t    rxFifoTriggerLevel;

    /**
    * The bits set in this mask allow the event to cause an interrupt
    * (See \ref group_scb_uart_macros_rx_fifo_status for the set of constants)
    */
    uint32_t    rxFifoIntEnableMask;

    /**
    * When there are fewer entries in the TX FIFO then this level
    * the TX trigger output goes high. This output can be connected
    * to a DMA channel through a trigger mux.
    * Also, it controls \ref CY_SCB_UART_TX_TRIGGER interrupt source.
    */
    uint32_t    txFifoTriggerLevel;

    /**
    * Bits set in this mask allows the event to cause an interrupt
    * (See \ref group_scb_uart_macros_tx_fifo_status for the set of constants)
    */
    uint32_t    txFifoIntEnableMask;
} cy_stc_scb_uart_config_t;

/** UART context structure.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct cy_stc_scb_uart_context
{
    /** \cond INTERNAL */
    uint32_t volatile txStatus;         /**< The transmit status */
    uint32_t volatile rxStatus;         /**< The receive status */

    void     *rxRingBuf;                /**< The pointer to the ring buffer */
    uint32_t  rxRingBufSize;            /**< The ring buffer size */
    uint32_t volatile rxRingBufHead;    /**< The ring buffer head index */
    uint32_t volatile rxRingBufTail;    /**< The ring buffer tail index */

    void     *rxBuf;                    /**< The pointer to the receive buffer */
    uint32_t  rxBufSize;                /**< The receive buffer size */
    uint32_t volatile rxBufIdx;         /**< The current location in the receive buffer */

    void     *txBuf;                    /**< The pointer to the transmit buffer */
    uint32_t  txBufSize;                /**< The transmit buffer size */
    uint32_t volatile txLeftToTransmit; /**< The number of data elements left to be transmitted */

} cy_stc_scb_uart_context_t;



/*******************************************************************************
*                               API Constants
*******************************************************************************/

/**
* \defgroup group_scb_uart_macros_rx_fifo_status UART RX FIFO status.
* \{
* Macros to check UART RX FIFO status returned by \ref Cy_SCB_UART_GetRxFifoStatus
* function or assign mask for \ref Cy_SCB_UART_ClearRxFifoStatus function.
* Each UART RX FIFO status is encoded in a separate bit, therefore multiple
* bits may be set to indicate the current status.
*/

/** The number of entries in the RX FIFO is more than the RX FIFO trigger level
* value
*/
#define CY_SCB_UART_RX_TRIGGER         (SCB_INTR_RX_TRIGGER_Msk)

/** The RX FIFO is not empty, there is data to read */
#define CY_SCB_UART_RX_NOT_EMPTY       (SCB_INTR_RX_NOT_EMPTY_Msk)

/**
* The RX FIFO is full, there is no more space for additional data, and
* any additional data will be dropped
*/
#define CY_SCB_UART_RX_FULL            (SCB_INTR_RX_FULL_Msk)

/**
* The RX FIFO was full and there was an attempt to write to it.
* That additional data was dropped.
*/
#define CY_SCB_UART_RX_OVERFLOW        (SCB_INTR_RX_OVERFLOW_Msk)

/** An attempt to read from an empty RX FIFO */
#define CY_SCB_UART_RX_UNDERFLOW       (SCB_INTR_RX_UNDERFLOW_Msk)

/** The RX FIFO detected a frame error, either a stop or stop-bit error */
#define CY_SCB_UART_RX_ERR_FRAME       (SCB_INTR_RX_FRAME_ERROR_Msk)

/** The RX FIFO detected a parity error */
#define CY_SCB_UART_RX_ERR_PARITY      (SCB_INTR_RX_PARITY_ERROR_Msk)

/** The RX FIFO detected a break transmission from the transmitter */
#define CY_SCB_UART_RX_BREAK_DETECT    (SCB_INTR_RX_BREAK_DETECT_Msk)
/** \} group_scb_uart_macros_rx_fifo_status */

/**
* \defgroup group_scb_uart_macros_tx_fifo_status UART TX FIFO Statuses
* \{
* Macros to check UART TX FIFO status returned by \ref Cy_SCB_UART_GetTxFifoStatus
* function or assign mask for \ref Cy_SCB_UART_ClearTxFifoStatus function.
* Each UART TX FIFO status is encoded in a separate bit, therefore multiple bits
* may be set to indicate the current status.
*/

/** The number of entries in the TX FIFO is less than the TX FIFO trigger level
* value
*/
#define CY_SCB_UART_TX_TRIGGER     (SCB_INTR_TX_TRIGGER_Msk)

/** The TX FIFO is not full, there is a space for more data */
#define CY_SCB_UART_TX_NOT_FULL    (SCB_INTR_TX_NOT_FULL_Msk)

/** The TX FIFO is empty, note there may still be data in the shift register.*/
#define CY_SCB_UART_TX_EMPTY       (SCB_INTR_TX_EMPTY_Msk)

/** An attempt to write to the full TX FIFO */
#define CY_SCB_UART_TX_OVERFLOW    (SCB_INTR_TX_OVERFLOW_Msk)

/** An attempt to read from an empty transmitter FIFO (hardware reads). */
#define CY_SCB_UART_TX_UNDERFLOW (SCB_INTR_TX_UNDERFLOW_Msk)

/** All data has been transmitted out of the FIFO, including shifter */
#define CY_SCB_UART_TX_DONE        (SCB_INTR_TX_UART_DONE_Msk)

/** SmartCard only: the transmitter received a NACK */
#define CY_SCB_UART_TX_NACK        (SCB_INTR_TX_UART_NACK_Msk)

/** SmartCard and LIN only: the transmitter lost arbitration */
#define CY_SCB_UART_TX_ARB_LOST    (SCB_INTR_TX_UART_ARB_LOST_Msk)
/** \} group_scb_uart_macros_tx_fifo_status */


/*******************************************************************************
*                            Internal Constants
*******************************************************************************/

/** \cond INTERNAL */
#define CY_SCB_UART_TX_INTR_MASK    (CY_SCB_UART_TX_TRIGGER  | CY_SCB_UART_TX_NOT_FULL  | CY_SCB_UART_TX_EMPTY | \
                                     CY_SCB_UART_TX_OVERFLOW | CY_SCB_UART_TX_UNDERFLOW | CY_SCB_UART_TX_DONE  | \
                                     CY_SCB_UART_TX_NACK     | CY_SCB_UART_TX_ARB_LOST)

#define CY_SCB_UART_RX_INTR_MASK    (CY_SCB_UART_RX_TRIGGER    | CY_SCB_UART_RX_NOT_EMPTY | CY_SCB_UART_RX_FULL      | \
                                     CY_SCB_UART_RX_OVERFLOW   | CY_SCB_UART_RX_UNDERFLOW | CY_SCB_UART_RX_ERR_FRAME | \
                                     CY_SCB_UART_RX_ERR_PARITY | CY_SCB_UART_RX_BREAK_DETECT)

#define CY_SCB_UART_TX_INTR        (CY_SCB_TX_INTR_LEVEL | CY_SCB_TX_INTR_UART_NACK | CY_SCB_TX_INTR_UART_ARB_LOST)

#define CY_SCB_UART_RX_INTR        (CY_SCB_RX_INTR_LEVEL | CY_SCB_RX_INTR_OVERFLOW | CY_SCB_RX_INTR_UART_FRAME_ERROR | \
                                    CY_SCB_RX_INTR_UART_PARITY_ERROR | CY_SCB_RX_INTR_UART_BREAK_DETECT)
/* UART parity and parity enable combination */
#define CY_SCB_UART_RX_CTRL_SET_PARITY_Msk      (SCB_UART_RX_CTRL_PARITY_ENABLED_Msk | \
                                                 SCB_UART_RX_CTRL_PARITY_Msk)
#define CY_SCB_UART_RX_CTRL_SET_PARITY_Pos      SCB_UART_RX_CTRL_PARITY_Pos

#define CY_SCB_UART_TX_CTRL_SET_PARITY_Msk      (SCB_UART_TX_CTRL_PARITY_ENABLED_Msk | \
                                                 SCB_UART_TX_CTRL_PARITY_Msk)
#define CY_SCB_UART_TX_CTRL_SET_PARITY_Pos      SCB_UART_TX_CTRL_PARITY_Pos

void Cy_SCB_UART_Init(CySCB_Type *base, cy_stc_scb_uart_config_t const *config, cy_stc_scb_uart_context_t *context);
void Cy_SCB_UART_Enable(CySCB_Type *base);
void Cy_SCB_UART_PutString(CySCB_Type *base, char const string[]);
void Cy_SCB_WriteString(CySCB_Type *base, char const string[]);
uint32_t Cy_SCB_GetFifoSize(CySCB_Type const *base);
uint32_t Cy_SCB_GetNumInTxFifo(CySCB_Type const *base);
void Cy_SCB_WriteTxFifo(CySCB_Type* base, uint32_t data);
uint32_t Cy_SCB_UART_GetNumInRxFifo(CySCB_Type const *base);
uint32_t Cy_SCB_UART_Get(CySCB_Type const *base);
uint32_t Cy_SCB_ReadRxFifo(CySCB_Type const *base);
uint32_t Cy_SCB_UART_Put(CySCB_Type *base, uint32_t data);
uint32_t Cy_SCB_Write(CySCB_Type *base, uint32_t data);
#endif