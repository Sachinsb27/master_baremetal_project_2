#ifndef I2C_H
#define I2C_H
#include "uart.h"
/** I2C Command ACK / NAK */
typedef enum
{
    CY_SCB_I2C_ACK,     /**< Send ACK to current byte */
    CY_SCB_I2C_NAK,     /**< Send NAK to current byte */
    CY_SCB_I2C_WAIT,    /**< Wait for application to send ACK/NAK */
} cy_en_scb_i2c_command_t;

typedef void (* cy_cb_scb_i2c_handle_deep_sleep_mode_t)(uint32_t event);
typedef cy_en_scb_i2c_command_t (* cy_cb_scb_i2c_handle_addr_t)(uint32_t event);
typedef void (* cy_cb_scb_i2c_handle_events_t)(uint32_t event);
/* Analog filter settings. */
#define CY_SCB_I2C_ENABLE_ANALOG_FITLER    (CY_SCB_I2C_CFG_DEF_VAL)
#define CY_SCB_I2C_DISABLE_ANALOG_FITLER   (CY_SCB_I2C_CFG_DEF_VAL & \
                                            (uint32_t) ~(SCB_I2C_CFG_SDA_IN_FILT_SEL_Msk | \
                                                         SCB_I2C_CFG_SCL_IN_FILT_SEL_Msk))

/* FIFO size */
#define CY_SCB_I2C_FIFO_SIZE          CY_SCB_FIFO_SIZE
#define CY_SCB_I2C_HALF_FIFO_SIZE     (CY_SCB_FIFO_SIZE / 2UL)

                           /* The slave interrupt mask */
#define CY_SCB_I2C_SLAVE_INTR      (CY_SCB_SLAVE_INTR_I2C_ADDR_MATCH | CY_SCB_SLAVE_INTR_I2C_GENERAL_ADDR | \
                                    CY_SCB_SLAVE_INTR_I2C_STOP       | CY_SCB_SLAVE_INTR_I2C_BUS_ERROR    | \
                                    CY_SCB_SLAVE_INTR_I2C_ARB_LOST)

#define CY_SCB_I2C_SLAVE_INTR_NO_STOP   (CY_SCB_I2C_SLAVE_INTR & (uint32_t) ~CY_SCB_SLAVE_INTR_I2C_STOP)

#define CY_SCB_I2C_SLAVE_INTR_ADDR      (CY_SCB_SLAVE_INTR_I2C_ADDR_MATCH | CY_SCB_SLAVE_INTR_I2C_GENERAL_ADDR)

#define CY_SCB_I2C_SLAVE_ADDR_DONE      (CY_SCB_I2C_SLAVE_INTR_ADDR)

#define CY_SCB_I2C_SLAVE_INTR_NO_ADDR   (CY_SCB_I2C_SLAVE_INTR & (uint32_t) ~CY_SCB_I2C_SLAVE_INTR_ADDR)

#define CY_SCB_I2C_SLAVE_INTR_TX        (CY_SCB_TX_INTR_LEVEL | CY_SCB_TX_INTR_UNDERFLOW)

#define CY_SCB_I2C_SLAVE_INTR_ERROR     (CY_SCB_SLAVE_INTR_I2C_BUS_ERROR | CY_SCB_SLAVE_INTR_I2C_ARB_LOST)

/* I2C states */
#define CY_SCB_I2C_IDLE              (0x10000000UL)
#define CY_SCB_I2C_IDLE_MASK         (0x10000000UL)

/* Slave states */
#define CY_SCB_I2C_SLAVE_ACTIVE      (0x00001000UL)
#define CY_SCB_I2C_SLAVE_RX_MASK     (0x00001001UL)
#define CY_SCB_I2C_SLAVE_RX          (0x00001001UL)
#define CY_SCB_I2C_SLAVE_TX          (0x00001002UL)


#define CY_SCB_I2C_SLAVE_INTR_ERROR     (CY_SCB_SLAVE_INTR_I2C_BUS_ERROR | CY_SCB_SLAVE_INTR_I2C_ARB_LOST)

#define CY_SCB_I2C_SLAVE_RD_BUSY       (0x00000001UL)

/**
* All read data has been loaded into the TX FIFO, applicable only if
* the TX FIFO is used
*/
#define CY_SCB_I2C_SLAVE_RD_IN_FIFO    (0x00000002UL)

/**
* The master has finished reading data from the slave
*/
#define CY_SCB_I2C_SLAVE_RD_CMPLT      (0x00000004UL)

/**
* Set when the master tried to read more bytes than available in the configured
* read buffer. The slave is not able to finish the transaction and sends
* \ref CY_SCB_I2C_DEFAULT_TX.
*/
#define CY_SCB_I2C_SLAVE_RD_UNDRFL     (0x00000008UL)

/** There is a write transaction in progress */
#define CY_SCB_I2C_SLAVE_WR_BUSY       (0x00000010UL)

/**
* The master has finished writing data into the slave
*/
#define CY_SCB_I2C_SLAVE_WR_CMPLT      (0x00000020UL)

/**
* The master attempted to write more bytes than space available in the
* configured Write buffer. Note that all subsequent bytes are dropped.
*/
#define CY_SCB_I2C_SLAVE_WR_OVRFL      (0x00000040UL)

/** The slave lost arbitration, and the transaction was aborted */
#define CY_SCB_I2C_SLAVE_ARB_LOST      (0x00000080UL)

/**
* The slave captured an error on the bus during a master transaction (source
* of error is misplaced Start or Stop).
*/
#define CY_SCB_I2C_SLAVE_BUS_ERR       (0x00000100UL)

#define CY_SCB_I2C_SLAVE_READ_EVENT            (0x00000001UL)

/**
* Indicates that the slave was addressed and the master wants to write data.
* This event can be used to configure the slave Write buffer.
*/
#define CY_SCB_I2C_SLAVE_WRITE_EVENT           (0x00000002UL)

/**
* All slave data from the configured Read buffer has been loaded into the
* TX FIFO. The content of the Read buffer can be modified. Applicable only
* if the TX FIFO is used.
*/
#define CY_SCB_I2C_SLAVE_RD_IN_FIFO_EVENT      (0x00000004UL)

/**
* The master has read all data out of the configured Read buffer.
* This event can be used to configure the next Read buffer. If the buffer
* remains empty, the \ref CY_SCB_I2C_DEFAULT_TX bytes are returned to the master.
*/
#define CY_SCB_I2C_SLAVE_RD_BUF_EMPTY_EVENT    (0x00000008UL)

/**
* Indicates the master completed reading from the slave (set by the master NAK
* or Stop)
*/
#define CY_SCB_I2C_SLAVE_RD_CMPLT_EVENT        (0x00000010UL)

/**
* Indicates the master completed writing to the slave (set by the master Stop
* or Restart)
*/
#define CY_SCB_I2C_SLAVE_WR_CMPLT_EVENT        (0x00000020UL)

/**
* Indicates the I2C hardware detected an error.
* Check \ref Cy_SCB_I2C_SlaveGetStatus to determine the source of the error.
*/
#define CY_SCB_I2C_SLAVE_ERR_EVENT             (0x00000040UL)

/**
* All data specified by \ref Cy_SCB_I2C_MasterWrite has been loaded
* into the TX FIFO. The content of the master write buffer can be modified.
* Applicable only if the TX FIFO is used.
*/
#define CY_SCB_I2C_MASTER_WR_IN_FIFO_EVENT     (0x00010000UL)

/** The master write started by \ref Cy_SCB_I2C_MasterWrite is complete */
#define CY_SCB_I2C_MASTER_WR_CMPLT_EVENT       (0x00020000UL)

/** The master read started by \ref Cy_SCB_I2C_MasterRead is complete */
#define CY_SCB_I2C_MASTER_RD_CMPLT_EVENT       (0x00040000UL)

/**
* Indicates the I2C hardware has detected an error. It occurs together with
* \ref CY_SCB_I2C_MASTER_RD_CMPLT_EVENT or \ref CY_SCB_I2C_MASTER_WR_CMPLT_EVENT
* depends on the direction of the transfer.
* Check \ref Cy_SCB_I2C_MasterGetStatus to determine the source of the error.
*/
#define CY_SCB_I2C_MASTER_ERR_EVENT            (0x00080000UL)

#define CY_SCB_I2C_GENERAL_CALL_EVENT      (0x01UL)

/**
* The slave address is in the RX FIFO.
* Note that the address must be read from the RX FIFO using the
* \ref Cy_SCB_ReadRxFifo function.
*/
#define CY_SCB_I2C_ADDR_IN_FIFO_EVENT      (0x02UL)

#define CY_SCB_I2C_DEFAULT_TX  (0xFFUL)


#define CY_SCB_I2C_SLAVE_RD_CLEAR  (CY_SCB_I2C_SLAVE_RD_CMPLT  | CY_SCB_I2C_SLAVE_RD_IN_FIFO | \
                                    CY_SCB_I2C_SLAVE_RD_UNDRFL | CY_SCB_I2C_SLAVE_ARB_LOST   | \
                                    CY_SCB_I2C_SLAVE_BUS_ERR)

#define CY_SCB_I2C_SLAVE_WR_CLEAR  (CY_SCB_I2C_SLAVE_WR_CMPLT | CY_SCB_I2C_SLAVE_WR_OVRFL | \
                                    CY_SCB_I2C_SLAVE_ARB_LOST | CY_SCB_I2C_SLAVE_BUS_ERR)


/** I2C Operation Modes */
typedef enum
{
    CY_SCB_I2C_SLAVE        = 1U,    /**< Configures SCB for I2C Slave operation */
    CY_SCB_I2C_MASTER       = 2U,    /**< Configures SCB for I2C Master operation */
    CY_SCB_I2C_MASTER_SLAVE = 3U,    /**< Configures SCB for I2C Master-Slave operation */
} cy_en_scb_i2c_mode_t;


/** I2C configuration structure */
typedef struct cy_stc_scb_i2c_config
{
    /** Specifies the mode of operation */
    cy_en_scb_i2c_mode_t i2cMode;

    /**
    * The SCB provides an RX FIFO in hardware (consult the selected device
    * datasheet to get the actual FIFO size). The useRxFifo field defines
    * how the driver firmware reads data from the RX FIFO:
    * * If this option is enabled, the hardware is configured to automatically
    *   ACK incoming data, and interrupt is enabled to take data out of the RX
    *   FIFO when it has some number of bytes (typically, when it is half full).
    * * If this option is disabled, the interrupt is enabled to take data out of
    *   the RX FIFO when a byte is available. Also, hardware does not
    *   automatically ACK the data. Firmware must tell the hardware to ACK
    *   the byte (so each byte requires interrupt processing).
    * \n <b>Typically, this option should be enabled</b> to configure hardware to
    * automatically ACK incoming data. Otherwise hardware might not get the command
    * to ACK or NACK a byte fast enough, and clock stretching is applied
    * (the transaction is delayed) until the command is set. When this option is
    * enabled, the number of interrupts required to process the transaction
    * is significantly reduced because several bytes are handled at once.
    * \n <b>However, there is a side effect:</b>
    * * For master mode, the drawback is that the master may receive more
    *   data than desired due to the interrupt latency. An interrupt fires
    *   when the second-to-last byte has been received. This interrupt tells
    *   the hardware to stop receiving data. If the latency of this interrupt
    *   is longer than one transaction of the byte on the I2C bus, then the
    *   hardware automatically ACKs the following bytes until the interrupt
    *   is serviced or the RX FIFO becomes full.
    * * For slave mode, the drawback is that the slave only NACKs
    *   the master when the RX FIFO becomes full, NOT when the slave write
    *   firmware buffer becomes full.
    * \n In either master or slave mode, all received extra bytes are dropped.
    * \note The useRxFifo option is not available if acceptAddrInFifo is true.
    * \note The useRxFifo option is not available in High-speed mode.
    */
    bool useRxFifo;

    /**
    * The SCB provides a TX FIFO in hardware (consult the selected device
    * datasheet to get the actual FIFO size). The useTxFifo option defines how the
    * driver firmware loads data into the TX FIFO:
    * * If this option is enabled, the TX FIFO is fully loaded with data and the
    *   interrupt is enabled to keep the TX FIFO loaded until the end of the transaction.
    * * If this option is disabled, a single byte is loaded into the TX FIFO and
    *   the interrupt enabled to load the next byte when the TX FIFO becomes empty
    *   (so each byte requires interrupt processing).
    * \n <b>Typically, this option should be enabled</b> to keep the TX FIFO loaded with
    * data and reduce the probability of clock stretching. When there is no data
    * to transfer, clock stretching is applied (the transaction is delayed) until
    * the data is loaded. When this option is enabled, the number of interrupts required
    * to process the transaction is significantly reduced because several
    * bytes are handled at once.
    * \n <b>The drawback of enabling useTxFifo</b> is that the abort operation clears
    * the TX FIFO. The TX FIFO clear operation also clears the shift
    * register. As a result the shifter may be cleared in the middle of a byte
    * transaction, corrupting it. The remaining bits to transaction within the
    * corrupted byte are complemented with 1s. If this is an issue,
    * then do not enable this option.
    */
    bool useTxFifo;

    /**
    * The 7-bit right justified slave address, used only for the slave mode
    */
    uint8_t slaveAddress;

    /**
    * The slave address mask is used to mask bits of the slave address during
    * the address match procedure (it is used only for the slave mode).
    * Bit 0 of the address mask corresponds to the
    * read/write direction bit and is always a do not care in the address match
    * therefore must be set 0. Bit value 0 - excludes bit from address
    * comparison. Bit value 1 - the bit needs to match with the corresponding
    * bit of the I2C slave address.
    */
    uint8_t slaveAddressMask;

    /**
    * True - the slave address is accepted in the RX FIFO, false - the slave
    * addresses are not accepted in the RX FIFO
    */
    bool acceptAddrInFifo;

    /**
    * True - accept the general call address; false - ignore the general
    * call address.
    */
    bool ackGeneralAddr;

    /**
    * True - High Speed mode is enabled. False - High Speed mode is disabled.
    * Only applicable for PSoC 4100S Max.
    */
    bool hsEnable;

    /**
    * This is the check delay of the address matching event in the micro seconds
    * (us). The desired delay must be equal or more then the duration of high
    * period of the SCL clock. Not applicable for PSoC 4100S Max and PSoC 4000T.
    */
    uint16_t delayInFifoAddress;

} cy_stc_scb_i2c_config_t;

/** I2C context structure.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct cy_stc_scb_i2c_context
{
    /** \cond INTERNAL */
    bool useRxFifo;             /**< Stores RX FIFO configuration */
    bool useTxFifo;             /**< Stores TX FIFO configuration */

    volatile uint32_t state;    /**< The driver state */

    volatile uint32_t masterStatus; /**< The master status */
    bool     masterPause;           /**< Stores how the master ends the transaction */
    bool     masterRdDir;           /**< The direction of the master transaction */

    uint8_t  *masterBuffer;     /**< The pointer to the master buffer (either for a transmit or a receive operation) */
    uint32_t  masterBufferSize;         /**< The current master buffer size */
    volatile uint32_t masterBufferIdx;  /**< The current location in the master buffer */
    volatile uint32_t masterNumBytes;   /**< The number of bytes to send or receive */

    volatile uint32_t slaveStatus;       /**< The slave status */
    volatile bool     slaveRdBufEmpty;   /**< Tracks slave Read buffer empty event */

    uint8_t  *slaveTxBuffer;             /**< The pointer to the slave transmit buffer (a master reads from it) */
    uint32_t  slaveTxBufferSize;         /**< The current slave transmit buffer size */
    volatile uint32_t slaveTxBufferIdx;  /**< The current location in the slave buffer */
    volatile uint32_t slaveTxBufferCnt;  /**< The number of transferred bytes */

    uint8_t  *slaveRxBuffer;             /**< The pointer to the slave receive buffer (a master writes into it) */
    uint32_t  slaveRxBufferSize;         /**< The current slave receive buffer size */
    volatile uint32_t slaveRxBufferIdx;  /**< The current location in the slave buffer */

    /**
    * This is the check delay of the address matching event in the micro seconds
    * (us). The desired delay must be equal or more then the duration of high
    * period of the SCL clock. Not applicable for PSoC 4100S Max and PSoC 4000T.
    */
    uint16_t delayInFifoAddress;

    /** \endcond */
} cy_stc_scb_i2c_context_t;

void SlaveHandleDataReceive(CySCB_Type *base, cy_stc_scb_i2c_context_t *context);
void Cy_SCB_I2C_Init(CySCB_Type *base, cy_stc_scb_i2c_config_t const *config, cy_stc_scb_i2c_context_t *context);
void Cy_SCB_I2C_SlaveConfigReadBuf(CySCB_Type const *base, uint8_t *buffer, uint32_t size, cy_stc_scb_i2c_context_t *context);
void Cy_SCB_I2C_SlaveConfigWriteBuf(CySCB_Type const *base, uint8_t *buffer, uint32_t size, cy_stc_scb_i2c_context_t *context);
uint32_t Cy_SCB_I2C_SlaveClearWriteStatus(CySCB_Type const *base, cy_stc_scb_i2c_context_t *context);
void Cy_SCB_I2C_Enable(CySCB_Type *base);
void SlaveHandleStop(CySCB_Type *base, bool slaveAddrInFifo, cy_stc_scb_i2c_context_t *context);
void SlaveHandleAck(CySCB_Type *base, cy_stc_scb_i2c_context_t *context);
void SlaveHandleAddress(CySCB_Type *base, cy_stc_scb_i2c_context_t *context);

void SlaveHandleDataTransmit(CySCB_Type *base, cy_stc_scb_i2c_context_t *context);
void SCB_I2C_SlaveInterrupt(CySCB_Type *base, cy_stc_scb_i2c_context_t *context);
uint32_t Cy_SCB_I2C_SlaveGetStatus(CySCB_Type const *base, cy_stc_scb_i2c_context_t const *context);
#endif