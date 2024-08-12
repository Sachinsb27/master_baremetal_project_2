#ifndef SCB_H
#define SCB_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define _VAL2FLD(field, value)    (((uint32_t)(value) << field ## _Pos) & field ## _Msk)
#define _FLD2VAL(field, value)    (((uint32_t)(value) & field ## _Msk) >> field ## _Pos)

#define _BOOL2FLD(field, value) (((value) != false) ? (field ## _Msk) : 0UL)
#define _FLD2BOOL(field, value) (((value) & (field ## _Msk)) != 0UL)

#define _CLR_SET_FLD32U(reg, field, value) (((reg) & ((uint32_t)(~(field ## _Msk)))) | (_VAL2FLD(field, value)))
#define CY_REG32_CLR_SET(reg, field, value) ((reg) = _CLR_SET_FLD32U((reg), field, (value)))


/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

/* SCB CTRL modes */
#define CY_SCB_CTRL_MODE_I2C   (0UL)
#define CY_SCB_CTRL_MODE_SPI   (1UL)
#define CY_SCB_CTRL_MODE_UART  (2UL)

/* Max number of bits for byte mode */
#define CY_SCB_BYTE_WIDTH   (8UL)

/* Single unit to wait */
#define CY_SCB_WAIT_1_UNIT  (1U)

/* Clear interrupt sources */
#define CY_SCB_CLEAR_ALL_INTR_SRC   (0UL)



typedef struct {
  __IOM uint32_t CTRL;                          /*!< 0x00000000 Generic control register. */
   __IM uint32_t STATUS;                        /*!< 0x00000004 Generic status register. */
  __IOM uint32_t CMD_RESP_CTRL;                 /*!< 0x00000008 Command/response control register. */
   __IM uint32_t CMD_RESP_STATUS;               /*!< 0x0000000C Command/response status register. */
   __IM uint32_t RESERVED[4];
  __IOM uint32_t SPI_CTRL;                      /*!< 0x00000020 SPI control register. */
   __IM uint32_t SPI_STATUS;                    /*!< 0x00000024 SPI status register. */
   __IM uint32_t RESERVED1[6];
  __IOM uint32_t UART_CTRL;                     /*!< 0x00000040 UART control register. */
  __IOM uint32_t UART_TX_CTRL;                  /*!< 0x00000044 UART transmitter control register. */
  __IOM uint32_t UART_RX_CTRL;                  /*!< 0x00000048 UART receiver control register. */
   __IM uint32_t UART_RX_STATUS;                /*!< 0x0000004C UART receiver status register. */
  __IOM uint32_t UART_FLOW_CTRL;                /*!< 0x00000050 UART flow control register */
   __IM uint32_t RESERVED2[3];
  __IOM uint32_t I2C_CTRL;                      /*!< 0x00000060 I2C control register. */
   __IM uint32_t I2C_STATUS;                    /*!< 0x00000064 I2C status register. */
  __IOM uint32_t I2C_M_CMD;                     /*!< 0x00000068 I2C master command register. */
  __IOM uint32_t I2C_S_CMD;                     /*!< 0x0000006C I2C slave command register. */
  __IOM uint32_t I2C_CFG;                       /*!< 0x00000070 I2C configuration register. */
   __IM uint32_t RESERVED3[99];
  __IOM uint32_t TX_CTRL;                       /*!< 0x00000200 Transmitter control register. */
  __IOM uint32_t TX_FIFO_CTRL;                  /*!< 0x00000204 Transmitter FIFO control register. */
   __IM uint32_t TX_FIFO_STATUS;                /*!< 0x00000208 Transmitter FIFO status register. */
   __IM uint32_t RESERVED4[13];
   __OM uint32_t TX_FIFO_WR;                    /*!< 0x00000240 Transmitter FIFO write register. */
   __IM uint32_t RESERVED5[47];
  __IOM uint32_t RX_CTRL;                       /*!< 0x00000300 Receiver control register. */
  __IOM uint32_t RX_FIFO_CTRL;                  /*!< 0x00000304 Receiver FIFO control register. */
   __IM uint32_t RX_FIFO_STATUS;                /*!< 0x00000308 Receiver FIFO status register. */
   __IM uint32_t RESERVED6;
  __IOM uint32_t RX_MATCH;                      /*!< 0x00000310 Slave address and mask register. */
   __IM uint32_t RESERVED7[11];
   __IM uint32_t RX_FIFO_RD;                    /*!< 0x00000340 Receiver FIFO read register. */
   __IM uint32_t RX_FIFO_RD_SILENT;             /*!< 0x00000344 Receiver FIFO read register. */
   __IM uint32_t RESERVED8[46];
  __IOM uint32_t EZ_DATA[512];                  /*!< 0x00000400 Memory buffer registers. */
   __IM uint32_t RESERVED9[128];
   __IM uint32_t INTR_CAUSE;                    /*!< 0x00000E00 Active clocked interrupt signal register */
   __IM uint32_t RESERVED10[31];
  __IOM uint32_t INTR_I2C_EC;                   /*!< 0x00000E80 Externally clocked I2C interrupt request register */
   __IM uint32_t RESERVED11;
  __IOM uint32_t INTR_I2C_EC_MASK;              /*!< 0x00000E88 Externally clocked I2C interrupt mask register */
   __IM uint32_t INTR_I2C_EC_MASKED;            /*!< 0x00000E8C Externally clocked I2C interrupt masked register */
   __IM uint32_t RESERVED12[12];
  __IOM uint32_t INTR_SPI_EC;                   /*!< 0x00000EC0 Externally clocked SPI interrupt request register */
   __IM uint32_t RESERVED13;
  __IOM uint32_t INTR_SPI_EC_MASK;              /*!< 0x00000EC8 Externally clocked SPI interrupt mask register */
   __IM uint32_t INTR_SPI_EC_MASKED;            /*!< 0x00000ECC Externally clocked SPI interrupt masked register */
   __IM uint32_t RESERVED14[12];
  __IOM uint32_t INTR_M;                        /*!< 0x00000F00 Master interrupt request register. */
  __IOM uint32_t INTR_M_SET;                    /*!< 0x00000F04 Master interrupt set request register */
  __IOM uint32_t INTR_M_MASK;                   /*!< 0x00000F08 Master interrupt mask register. */
   __IM uint32_t INTR_M_MASKED;                 /*!< 0x00000F0C Master interrupt masked request register */
   __IM uint32_t RESERVED15[12];
  __IOM uint32_t INTR_S;                        /*!< 0x00000F40 Slave interrupt request register. */
  __IOM uint32_t INTR_S_SET;                    /*!< 0x00000F44 Slave interrupt set request register. */
  __IOM uint32_t INTR_S_MASK;                   /*!< 0x00000F48 Slave interrupt mask register. */
   __IM uint32_t INTR_S_MASKED;                 /*!< 0x00000F4C Slave interrupt masked request register */
   __IM uint32_t RESERVED16[12];
  __IOM uint32_t INTR_TX;                       /*!< 0x00000F80 Transmitter interrupt request register. */
  __IOM uint32_t INTR_TX_SET;                   /*!< 0x00000F84 Transmitter interrupt set request register */
  __IOM uint32_t INTR_TX_MASK;                  /*!< 0x00000F88 Transmitter interrupt mask register. */
   __IM uint32_t INTR_TX_MASKED;                /*!< 0x00000F8C Transmitter interrupt masked request register */
   __IM uint32_t RESERVED17[12];
  __IOM uint32_t INTR_RX;                       /*!< 0x00000FC0 Receiver interrupt request register. */
  __IOM uint32_t INTR_RX_SET;                   /*!< 0x00000FC4 Receiver interrupt set request register. */
  __IOM uint32_t INTR_RX_MASK;                  /*!< 0x00000FC8 Receiver interrupt mask register. */
   __IM uint32_t INTR_RX_MASKED;                /*!< 0x00000FCC Receiver interrupt masked request register */
} CySCB_Type;                                   /*!< Size = 4048 (0xFD0) */


/*******************************************************************************
*                                     SCB
*******************************************************************************/

#define SCB0_BASE                               0x40240000UL
#define SCB1_BASE                               0x40250000UL
#define SCB2_BASE                               0x40260000UL
#define SCB3_BASE                               0x40270000UL
#define SCB4_BASE                               0x40280000UL
#define SCB0                                    ((CySCB_Type*) SCB0_BASE)                                         /* 0x40240000 */
#define SCB1                                    ((CySCB_Type*) SCB1_BASE)                                         /* 0x40250000 */
#define SCB2                                    ((CySCB_Type*) SCB2_BASE)                                         /* 0x40260000 */
#define SCB3                                    ((CySCB_Type*) SCB3_BASE)                                         /* 0x40270000 */
#define SCB4                                    ((CySCB_Type*) SCB4_BASE)                                         /* 0x40280000 */


/*******************************************************************************
*                SCB
*******************************************************************************/

#define SCB_CTRL(base)                      (((CySCB_Type*) (base))->CTRL)
#define SCB_SPI_CTRL(base)                  (((CySCB_Type*) (base))->SPI_CTRL)
#define SCB_SPI_STATUS(base)                (((CySCB_Type*) (base))->SPI_STATUS)
#define SCB_SPI_TX_CTRL(base)               (((CySCB_Type*) (base))->SPI_TX_CTRL) /* for PSoC 4100S Max only */
#define SCB_SPI_RX_CTRL(base)               (((CySCB_Type*) (base))->SPI_RX_CTRL) /* for PSoC 4100S Max only */
#define SCB_UART_CTRL(base)                 (((CySCB_Type*) (base))->UART_CTRL)
#define SCB_UART_TX_CTRL(base)              (((CySCB_Type*) (base))->UART_TX_CTRL)
#define SCB_UART_RX_CTRL(base)              (((CySCB_Type*) (base))->UART_RX_CTRL)
#define SCB_UART_RX_STATUS(base)            (((CySCB_Type*) (base))->UART_RX_STATUS)
#define SCB_UART_FLOW_CTRL(base)            (((CySCB_Type*) (base))->UART_FLOW_CTRL)
#define SCB_I2C_CTRL(base)                  (((CySCB_Type*) (base))->I2C_CTRL)
#define SCB_I2C_STATUS(base)                (((CySCB_Type*) (base))->I2C_STATUS)
#define SCB_I2C_M_CMD(base)                 (((CySCB_Type*) (base))->I2C_M_CMD)
#define SCB_I2C_S_CMD(base)                 (((CySCB_Type*) (base))->I2C_S_CMD)
#define SCB_I2C_CFG(base)                   (((CySCB_Type*) (base))->I2C_CFG)
#define SCB_I2C_STRETCH_CTRL(base)          (((CySCB_Type*) (base))->I2C_STRETCH_CTRL)   /* for PSoC 4100S Max only */
#define SCB_I2C_STRETCH_STATUS(base)        (((CySCB_Type*) (base))->I2C_STRETCH_STATUS) /* for PSoC 4100S Max only */
#define SCB_I2C_CTRL_HS(base)               (((CySCB_Type*) (base))->I2C_CTRL_HS)        /* for PSoC 4100S Max only */
#define SCB_TX_CTRL(base)                   (((CySCB_Type*) (base))->TX_CTRL)
#define SCB_TX_FIFO_CTRL(base)              (((CySCB_Type*) (base))->TX_FIFO_CTRL)
#define SCB_TX_FIFO_STATUS(base)            (((CySCB_Type*) (base))->TX_FIFO_STATUS)
#define SCB_TX_FIFO_WR(base)                (((CySCB_Type*) (base))->TX_FIFO_WR)
#define SCB_RX_CTRL(base)                   (((CySCB_Type*) (base))->RX_CTRL)
#define SCB_RX_FIFO_CTRL(base)              (((CySCB_Type*) (base))->RX_FIFO_CTRL)
#define SCB_RX_FIFO_STATUS(base)            (((CySCB_Type*) (base))->RX_FIFO_STATUS)
#define SCB_RX_MATCH(base)                  (((CySCB_Type*) (base))->RX_MATCH)
#define SCB_RX_FIFO_RD(base)                (((CySCB_Type*) (base))->RX_FIFO_RD)
#define SCB_INTR_CAUSE(base)                (((CySCB_Type*) (base))->INTR_CAUSE)
#define SCB_INTR_I2C_EC(base)               (((CySCB_Type*) (base))->INTR_I2C_EC)
#define SCB_INTR_I2C_EC_MASK(base)          (((CySCB_Type*) (base))->INTR_I2C_EC_MASK)
#define SCB_INTR_I2C_EC_MASKED(base)        (((CySCB_Type*) (base))->INTR_I2C_EC_MASKED)
#define SCB_INTR_SPI_EC(base)               (((CySCB_Type*) (base))->INTR_SPI_EC)
#define SCB_INTR_SPI_EC_MASK(base)          (((CySCB_Type*) (base))->INTR_SPI_EC_MASK)
#define SCB_INTR_SPI_EC_MASKED(base)        (((CySCB_Type*) (base))->INTR_SPI_EC_MASKED)
#define SCB_INTR_M(base)                    (((CySCB_Type*) (base))->INTR_M)
#define SCB_INTR_M_SET(base)                (((CySCB_Type*) (base))->INTR_M_SET)
#define SCB_INTR_M_MASK(base)               (((CySCB_Type*) (base))->INTR_M_MASK)
#define SCB_INTR_M_MASKED(base)             (((CySCB_Type*) (base))->INTR_M_MASKED)
#define SCB_INTR_S(base)                    (((CySCB_Type*) (base))->INTR_S)
#define SCB_INTR_S_SET(base)                (((CySCB_Type*) (base))->INTR_S_SET)
#define SCB_INTR_S_MASK(base)               (((CySCB_Type*) (base))->INTR_S_MASK)
#define SCB_INTR_S_MASKED(base)             (((CySCB_Type*) (base))->INTR_S_MASKED)
#define SCB_INTR_TX(base)                   (((CySCB_Type*) (base))->INTR_TX)
#define SCB_INTR_TX_SET(base)               (((CySCB_Type*) (base))->INTR_TX_SET)
#define SCB_INTR_TX_MASK(base)              (((CySCB_Type*) (base))->INTR_TX_MASK)
#define SCB_INTR_TX_MASKED(base)            (((CySCB_Type*) (base))->INTR_TX_MASKED)
#define SCB_INTR_RX(base)                   (((CySCB_Type*) (base))->INTR_RX)
#define SCB_INTR_RX_SET(base)               (((CySCB_Type*) (base))->INTR_RX_SET)
#define SCB_INTR_RX_MASK(base)              (((CySCB_Type*) (base))->INTR_RX_MASK)
#define SCB_INTR_RX_MASKED(base)            (((CySCB_Type*) (base))->INTR_RX_MASKED)

/* SCB.CTRL */
#define SCB_CTRL_OVS_Pos                        0UL
#define SCB_CTRL_OVS_Msk                        0xFUL
#define SCB_CTRL_EC_AM_MODE_Pos                 8UL
#define SCB_CTRL_EC_AM_MODE_Msk                 0x100UL
#define SCB_CTRL_EC_OP_MODE_Pos                 9UL
#define SCB_CTRL_EC_OP_MODE_Msk                 0x200UL
#define SCB_CTRL_EZ_MODE_Pos                    10UL
#define SCB_CTRL_EZ_MODE_Msk                    0x400UL
#define SCB_CTRL_BYTE_MODE_Pos                  11UL
#define SCB_CTRL_BYTE_MODE_Msk                  0x800UL
#define SCB_CTRL_CMD_RESP_MODE_Pos              12UL
#define SCB_CTRL_CMD_RESP_MODE_Msk              0x1000UL
#define SCB_CTRL_ADDR_ACCEPT_Pos                16UL
#define SCB_CTRL_ADDR_ACCEPT_Msk                0x10000UL
#define SCB_CTRL_BLOCK_Pos                      17UL
#define SCB_CTRL_BLOCK_Msk                      0x20000UL
#define SCB_CTRL_MODE_Pos                       24UL
#define SCB_CTRL_MODE_Msk                       0x3000000UL
#define SCB_CTRL_ENABLED_Pos                    31UL
#define SCB_CTRL_ENABLED_Msk                    0x80000000UL

/* SCB.UART_CTRL */
#define SCB_UART_CTRL_LOOPBACK_Pos              16UL
#define SCB_UART_CTRL_LOOPBACK_Msk              0x10000UL
#define SCB_UART_CTRL_MODE_Pos                  24UL
#define SCB_UART_CTRL_MODE_Msk                  0x3000000UL
/* SCB.UART_TX_CTRL */
#define SCB_UART_TX_CTRL_STOP_BITS_Pos          0UL
#define SCB_UART_TX_CTRL_STOP_BITS_Msk          0x7UL
#define SCB_UART_TX_CTRL_PARITY_Pos             4UL
#define SCB_UART_TX_CTRL_PARITY_Msk             0x10UL
#define SCB_UART_TX_CTRL_PARITY_ENABLED_Pos     5UL
#define SCB_UART_TX_CTRL_PARITY_ENABLED_Msk     0x20UL
#define SCB_UART_TX_CTRL_RETRY_ON_NACK_Pos      8UL
#define SCB_UART_TX_CTRL_RETRY_ON_NACK_Msk      0x100UL
/* SCB.UART_RX_CTRL */
#define SCB_UART_RX_CTRL_STOP_BITS_Pos          0UL
#define SCB_UART_RX_CTRL_STOP_BITS_Msk          0x7UL
#define SCB_UART_RX_CTRL_PARITY_Pos             4UL
#define SCB_UART_RX_CTRL_PARITY_Msk             0x10UL
#define SCB_UART_RX_CTRL_PARITY_ENABLED_Pos     5UL
#define SCB_UART_RX_CTRL_PARITY_ENABLED_Msk     0x20UL
#define SCB_UART_RX_CTRL_POLARITY_Pos           6UL
#define SCB_UART_RX_CTRL_POLARITY_Msk           0x40UL
#define SCB_UART_RX_CTRL_DROP_ON_PARITY_ERROR_Pos 8UL
#define SCB_UART_RX_CTRL_DROP_ON_PARITY_ERROR_Msk 0x100UL
#define SCB_UART_RX_CTRL_DROP_ON_FRAME_ERROR_Pos 9UL
#define SCB_UART_RX_CTRL_DROP_ON_FRAME_ERROR_Msk 0x200UL

/* SCB.UART_RX_STATUS */
#define SCB_UART_RX_STATUS_BR_COUNTER_Pos       0UL
#define SCB_UART_RX_STATUS_BR_COUNTER_Msk       0xFFFUL
/* SCB.UART_FLOW_CTRL */
#define SCB_UART_FLOW_CTRL_TRIGGER_LEVEL_Pos    0UL
#define SCB_UART_FLOW_CTRL_TRIGGER_LEVEL_Msk    0xFFUL
#define SCB_UART_FLOW_CTRL_RTS_POLARITY_Pos     16UL
#define SCB_UART_FLOW_CTRL_RTS_POLARITY_Msk     0x10000UL
#define SCB_UART_FLOW_CTRL_CTS_POLARITY_Pos     24UL
#define SCB_UART_FLOW_CTRL_CTS_POLARITY_Msk     0x1000000UL
#define SCB_UART_FLOW_CTRL_CTS_ENABLED_Pos      25UL
#define SCB_UART_FLOW_CTRL_CTS_ENABLED_Msk      0x2000000UL
/* SCB.I2C_CTRL */
#define SCB_I2C_CTRL_HIGH_PHASE_OVS_Pos         0UL
#define SCB_I2C_CTRL_HIGH_PHASE_OVS_Msk         0xFUL
#define SCB_I2C_CTRL_LOW_PHASE_OVS_Pos          4UL
#define SCB_I2C_CTRL_LOW_PHASE_OVS_Msk          0xF0UL
#define SCB_I2C_CTRL_M_READY_DATA_ACK_Pos       8UL
#define SCB_I2C_CTRL_M_READY_DATA_ACK_Msk       0x100UL
#define SCB_I2C_CTRL_M_NOT_READY_DATA_NACK_Pos  9UL
#define SCB_I2C_CTRL_M_NOT_READY_DATA_NACK_Msk  0x200UL
#define SCB_I2C_CTRL_S_GENERAL_IGNORE_Pos       11UL
#define SCB_I2C_CTRL_S_GENERAL_IGNORE_Msk       0x800UL
#define SCB_I2C_CTRL_S_READY_ADDR_ACK_Pos       12UL
#define SCB_I2C_CTRL_S_READY_ADDR_ACK_Msk       0x1000UL
#define SCB_I2C_CTRL_S_READY_DATA_ACK_Pos       13UL
#define SCB_I2C_CTRL_S_READY_DATA_ACK_Msk       0x2000UL
#define SCB_I2C_CTRL_S_NOT_READY_ADDR_NACK_Pos  14UL
#define SCB_I2C_CTRL_S_NOT_READY_ADDR_NACK_Msk  0x4000UL
#define SCB_I2C_CTRL_S_NOT_READY_DATA_NACK_Pos  15UL
#define SCB_I2C_CTRL_S_NOT_READY_DATA_NACK_Msk  0x8000UL
#define SCB_I2C_CTRL_LOOPBACK_Pos               16UL
#define SCB_I2C_CTRL_LOOPBACK_Msk               0x10000UL
#define SCB_I2C_CTRL_SLAVE_MODE_Pos             30UL
#define SCB_I2C_CTRL_SLAVE_MODE_Msk             0x40000000UL
#define SCB_I2C_CTRL_MASTER_MODE_Pos            31UL
#define SCB_I2C_CTRL_MASTER_MODE_Msk            0x80000000UL
/* SCB.I2C_STATUS */
#define SCB_I2C_STATUS_BUS_BUSY_Pos             0UL
#define SCB_I2C_STATUS_BUS_BUSY_Msk             0x1UL
#define SCB_I2C_STATUS_I2C_EC_BUSY_Pos          1UL
#define SCB_I2C_STATUS_I2C_EC_BUSY_Msk          0x2UL
#define SCB_I2C_STATUS_S_READ_Pos               4UL
#define SCB_I2C_STATUS_S_READ_Msk               0x10UL
/* SCB.I2C_S_CMD */
#define SCB_I2C_S_CMD_S_ACK_Pos                 0UL
#define SCB_I2C_S_CMD_S_ACK_Msk                 0x1UL
#define SCB_I2C_S_CMD_S_NACK_Pos                1UL
#define SCB_I2C_S_CMD_S_NACK_Msk                0x2UL
/* SCB.I2C_CFG */
#define SCB_I2C_CFG_SDA_IN_FILT_TRIM_Pos        0UL
#define SCB_I2C_CFG_SDA_IN_FILT_TRIM_Msk        0x3UL
#define SCB_I2C_CFG_SDA_IN_FILT_SEL_Pos         4UL
#define SCB_I2C_CFG_SDA_IN_FILT_SEL_Msk         0x10UL
#define SCB_I2C_CFG_SCL_IN_FILT_TRIM_Pos        8UL
#define SCB_I2C_CFG_SCL_IN_FILT_TRIM_Msk        0x300UL
#define SCB_I2C_CFG_SCL_IN_FILT_SEL_Pos         12UL
#define SCB_I2C_CFG_SCL_IN_FILT_SEL_Msk         0x1000UL
#define SCB_I2C_CFG_SDA_OUT_FILT0_TRIM_Pos      16UL
#define SCB_I2C_CFG_SDA_OUT_FILT0_TRIM_Msk      0x30000UL
#define SCB_I2C_CFG_SDA_OUT_FILT1_TRIM_Pos      18UL
#define SCB_I2C_CFG_SDA_OUT_FILT1_TRIM_Msk      0xC0000UL
#define SCB_I2C_CFG_SDA_OUT_FILT2_TRIM_Pos      20UL
#define SCB_I2C_CFG_SDA_OUT_FILT2_TRIM_Msk      0x300000UL
#define SCB_I2C_CFG_SDA_OUT_FILT_SEL_Pos        28UL
#define SCB_I2C_CFG_SDA_OUT_FILT_SEL_Msk        0x30000000UL
/* SCB.TX_CTRL */
#define SCB_TX_CTRL_DATA_WIDTH_Pos              0UL
#define SCB_TX_CTRL_DATA_WIDTH_Msk              0xFUL
#define SCB_TX_CTRL_MSB_FIRST_Pos               8UL
#define SCB_TX_CTRL_MSB_FIRST_Msk               0x100UL
/* SCB.TX_FIFO_CTRL */
#define SCB_TX_FIFO_CTRL_TRIGGER_LEVEL_Pos      0UL
#define SCB_TX_FIFO_CTRL_TRIGGER_LEVEL_Msk      0xFFUL
#define SCB_TX_FIFO_CTRL_CLEAR_Pos              16UL
#define SCB_TX_FIFO_CTRL_CLEAR_Msk              0x10000UL
#define SCB_TX_FIFO_CTRL_FREEZE_Pos             17UL
#define SCB_TX_FIFO_CTRL_FREEZE_Msk             0x20000UL
/* SCB.TX_FIFO_STATUS */
#define SCB_TX_FIFO_STATUS_USED_Pos             0UL
#define SCB_TX_FIFO_STATUS_USED_Msk             0x1FFUL
#define SCB_TX_FIFO_STATUS_SR_VALID_Pos         15UL
#define SCB_TX_FIFO_STATUS_SR_VALID_Msk         0x8000UL
#define SCB_TX_FIFO_STATUS_RD_PTR_Pos           16UL
#define SCB_TX_FIFO_STATUS_RD_PTR_Msk           0xFF0000UL
#define SCB_TX_FIFO_STATUS_WR_PTR_Pos           24UL
#define SCB_TX_FIFO_STATUS_WR_PTR_Msk           0xFF000000UL
/* SCB.TX_FIFO_WR */
#define SCB_TX_FIFO_WR_DATA_Pos                 0UL
#define SCB_TX_FIFO_WR_DATA_Msk                 0xFFFFUL
/* SCB.RX_CTRL */
#define SCB_RX_CTRL_DATA_WIDTH_Pos              0UL
#define SCB_RX_CTRL_DATA_WIDTH_Msk              0xFUL
#define SCB_RX_CTRL_MSB_FIRST_Pos               8UL
#define SCB_RX_CTRL_MSB_FIRST_Msk               0x100UL
#define SCB_RX_CTRL_MEDIAN_Pos                  9UL
#define SCB_RX_CTRL_MEDIAN_Msk                  0x200UL
/* SCB.RX_FIFO_CTRL */
#define SCB_RX_FIFO_CTRL_TRIGGER_LEVEL_Pos      0UL
#define SCB_RX_FIFO_CTRL_TRIGGER_LEVEL_Msk      0xFFUL
#define SCB_RX_FIFO_CTRL_CLEAR_Pos              16UL
#define SCB_RX_FIFO_CTRL_CLEAR_Msk              0x10000UL
#define SCB_RX_FIFO_CTRL_FREEZE_Pos             17UL
#define SCB_RX_FIFO_CTRL_FREEZE_Msk             0x20000UL
/* SCB.RX_FIFO_STATUS */
#define SCB_RX_FIFO_STATUS_USED_Pos             0UL
#define SCB_RX_FIFO_STATUS_USED_Msk             0x1FFUL
/* SCB.RX_MATCH */
#define SCB_RX_MATCH_ADDR_Pos                   0UL
#define SCB_RX_MATCH_ADDR_Msk                   0xFFUL
#define SCB_RX_MATCH_MASK_Pos                   16UL
#define SCB_RX_MATCH_MASK_Msk                   0xFF0000UL

/* SCB.INTR_I2C_EC */
#define SCB_INTR_I2C_EC_WAKE_UP_Pos             0UL
#define SCB_INTR_I2C_EC_WAKE_UP_Msk             0x1UL


/* SCB.INTR_S */
#define SCB_INTR_S_I2C_ARB_LOST_Pos             0UL
#define SCB_INTR_S_I2C_ARB_LOST_Msk             0x1UL
#define SCB_INTR_S_I2C_NACK_Pos                 1UL
#define SCB_INTR_S_I2C_NACK_Msk                 0x2UL
#define SCB_INTR_S_I2C_ACK_Pos                  2UL
#define SCB_INTR_S_I2C_ACK_Msk                  0x4UL
#define SCB_INTR_S_I2C_WRITE_STOP_Pos           3UL
#define SCB_INTR_S_I2C_WRITE_STOP_Msk           0x8UL
#define SCB_INTR_S_I2C_STOP_Pos                 4UL
#define SCB_INTR_S_I2C_STOP_Msk                 0x10UL
#define SCB_INTR_S_I2C_START_Pos                5UL
#define SCB_INTR_S_I2C_START_Msk                0x20UL
#define SCB_INTR_S_I2C_ADDR_MATCH_Pos           6UL
#define SCB_INTR_S_I2C_ADDR_MATCH_Msk           0x40UL
#define SCB_INTR_S_I2C_GENERAL_Pos              7UL
#define SCB_INTR_S_I2C_GENERAL_Msk              0x80UL
#define SCB_INTR_S_I2C_BUS_ERROR_Pos            8UL
#define SCB_INTR_S_I2C_BUS_ERROR_Msk            0x100UL

/* SCB.INTR_TX */
#define SCB_INTR_TX_TRIGGER_Pos                 0UL
#define SCB_INTR_TX_TRIGGER_Msk                 0x1UL
#define SCB_INTR_TX_NOT_FULL_Pos                1UL
#define SCB_INTR_TX_NOT_FULL_Msk                0x2UL
#define SCB_INTR_TX_EMPTY_Pos                   4UL
#define SCB_INTR_TX_EMPTY_Msk                   0x10UL
#define SCB_INTR_TX_OVERFLOW_Pos                5UL
#define SCB_INTR_TX_OVERFLOW_Msk                0x20UL
#define SCB_INTR_TX_UNDERFLOW_Pos               6UL
#define SCB_INTR_TX_UNDERFLOW_Msk               0x40UL
#define SCB_INTR_TX_BLOCKED_Pos                 7UL
#define SCB_INTR_TX_BLOCKED_Msk                 0x80UL
#define SCB_INTR_TX_UART_NACK_Pos               8UL
#define SCB_INTR_TX_UART_NACK_Msk               0x100UL
#define SCB_INTR_TX_UART_DONE_Pos               9UL
#define SCB_INTR_TX_UART_DONE_Msk               0x200UL
#define SCB_INTR_TX_UART_ARB_LOST_Pos           10UL
#define SCB_INTR_TX_UART_ARB_LOST_Msk           0x400UL

/* SCB.INTR_RX */
#define SCB_INTR_RX_TRIGGER_Pos                 0UL
#define SCB_INTR_RX_TRIGGER_Msk                 0x1UL
#define SCB_INTR_RX_NOT_EMPTY_Pos               2UL
#define SCB_INTR_RX_NOT_EMPTY_Msk               0x4UL
#define SCB_INTR_RX_FULL_Pos                    3UL
#define SCB_INTR_RX_FULL_Msk                    0x8UL
#define SCB_INTR_RX_OVERFLOW_Pos                5UL
#define SCB_INTR_RX_OVERFLOW_Msk                0x20UL
#define SCB_INTR_RX_UNDERFLOW_Pos               6UL
#define SCB_INTR_RX_UNDERFLOW_Msk               0x40UL
#define SCB_INTR_RX_BLOCKED_Pos                 7UL
#define SCB_INTR_RX_BLOCKED_Msk                 0x80UL
#define SCB_INTR_RX_FRAME_ERROR_Pos             8UL
#define SCB_INTR_RX_FRAME_ERROR_Msk             0x100UL
#define SCB_INTR_RX_PARITY_ERROR_Pos            9UL
#define SCB_INTR_RX_PARITY_ERROR_Msk            0x200UL
#define SCB_INTR_RX_BAUD_DETECT_Pos             10UL
#define SCB_INTR_RX_BAUD_DETECT_Msk             0x400UL
#define SCB_INTR_RX_BREAK_DETECT_Pos            11UL
#define SCB_INTR_RX_BREAK_DETECT_Msk            0x800UL




/*******************************************************************************
*                        API Constants
*******************************************************************************/

/**
* \defgroup group_scb_common_macros_intr_cause SCB Interrupt Causes
* \{
*/
/** Interrupt from Master interrupt sources */
#define CY_SCB_MASTER_INTR SCB_INTR_CAUSE_M_Msk

/** Interrupt from Slave interrupt sources  */
#define CY_SCB_SLAVE_INTR  SCB_INTR_CAUSE_S_Msk

/** Interrupt from TX interrupt sources */
#define CY_SCB_TX_INTR     SCB_INTR_CAUSE_TX_Msk

/** Interrupt from RX interrupt sources */
#define CY_SCB_RX_INTR     SCB_INTR_CAUSE_RX_Msk

/** Interrupt from I2C externally clocked interrupt sources */
#define CY_SCB_I2C_INTR    SCB_INTR_CAUSE_I2C_EC_Msk

/**
* \defgroup group_scb_common_macros_tx_intr TX Interrupt Statuses
* \{
*/
/**
* The number of data elements in the TX FIFO is less than the value
* of the TX FIFO level
*/
#define CY_SCB_TX_INTR_LEVEL           SCB_INTR_TX_TRIGGER_Msk

/** The TX FIFO is not full */
#define CY_SCB_TX_INTR_NOT_FULL        SCB_INTR_TX_NOT_FULL_Msk

/** The TX FIFO is empty */
#define CY_SCB_TX_INTR_EMPTY           SCB_INTR_TX_EMPTY_Msk

/** An attempt to write to a full TX FIFO */
#define CY_SCB_TX_INTR_OVERFLOW        SCB_INTR_TX_OVERFLOW_Msk

/** An attempt to read from an empty TX FIFO */
#define CY_SCB_TX_INTR_UNDERFLOW       SCB_INTR_TX_UNDERFLOW_Msk

/** The UART transfer is complete: all data elements from the TX FIFO are sent
*/
#define CY_SCB_TX_INTR_UART_DONE       SCB_INTR_TX_UART_DONE_Msk

/** SmartCard only: UART received a NACK */
#define CY_SCB_TX_INTR_UART_NACK       SCB_INTR_TX_UART_NACK_Msk

/**
* SmartCard and LIN only: the value on the TX line of the UART does not match the
* value on the RX line
*/
#define CY_SCB_TX_INTR_UART_ARB_LOST   SCB_INTR_TX_UART_ARB_LOST_Msk
/** \} group_scb_common_macros_tx_intr */

/**
* \defgroup group_scb_common_macros_rx_intr RX Interrupt Statuses
* \{
*/
/**
* The number of data elements in the RX FIFO is greater than the value of the
* RX FIFO level
*/
#define CY_SCB_RX_INTR_LEVEL             SCB_INTR_RX_TRIGGER_Msk

/** The RX FIFO is not empty */
#define CY_SCB_RX_INTR_NOT_EMPTY         SCB_INTR_RX_NOT_EMPTY_Msk

/** The RX FIFO is full */
#define CY_SCB_RX_INTR_FULL              SCB_INTR_RX_FULL_Msk

/** An attempt to write to a full RX FIFO */
#define CY_SCB_RX_INTR_OVERFLOW          SCB_INTR_RX_OVERFLOW_Msk

/** An attempt to read from an empty RX FIFO */
#define CY_SCB_RX_INTR_UNDERFLOW         SCB_INTR_RX_UNDERFLOW_Msk

/** LIN baudrate detection is completed */
#define CY_SCB_RX_INTR_BAUD_DETECT       SCB_INTR_RX_BAUD_DETECT_Msk

/** A UART framing error detected */
#define CY_SCB_RX_INTR_UART_FRAME_ERROR  SCB_INTR_RX_FRAME_ERROR_Msk

/** A UART parity error detected  */
#define CY_SCB_RX_INTR_UART_PARITY_ERROR SCB_INTR_RX_PARITY_ERROR_Msk


/** A UART break detected */
#define CY_SCB_RX_INTR_UART_BREAK_DETECT SCB_INTR_RX_BREAK_DETECT_Msk
/** \} group_scb_common_macros_rx_intr */

/**
* \defgroup group_scb_common_macros_slave_intr Slave Interrupt Statuses
* \{
*/
/**
* I2C slave lost arbitration: the value driven on the SDA line is not the same
* as the value observed on the SDA line
*/
#define CY_SCB_SLAVE_INTR_I2C_ARB_LOST      SCB_INTR_S_I2C_ARB_LOST_Msk

/** The I2C slave received a NAK */
#define CY_SCB_SLAVE_INTR_I2C_NACK          SCB_INTR_S_I2C_NACK_Msk

/** The I2C slave received  an ACK */
#define CY_SCB_SLAVE_INTR_I2C_ACK           SCB_INTR_S_I2C_ACK_Msk

/**
* A Stop or Repeated Start event for a write transfer intended for this slave
* was detected.
*/
#define CY_SCB_SLAVE_INTR_I2C_WRITE_STOP    SCB_INTR_S_I2C_WRITE_STOP_Msk

/** A Stop or Repeated Start event intended for this slave was detected */
#define CY_SCB_SLAVE_INTR_I2C_STOP          SCB_INTR_S_I2C_STOP_Msk

/** The I2C slave received a Start condition */
#define CY_SCB_SLAVE_INTR_I2C_START         SCB_INTR_S_I2C_START_Msk

/** The I2C slave received the matching address */
#define CY_SCB_SLAVE_INTR_I2C_ADDR_MATCH    SCB_INTR_S_I2C_ADDR_MATCH_Msk

/** The I2C Slave received the general call address */
#define CY_SCB_SLAVE_INTR_I2C_GENERAL_ADDR  SCB_INTR_S_I2C_GENERAL_Msk

/** The I2C slave bus error (detection of unexpected Start or Stop condition) */
#define CY_SCB_SLAVE_INTR_I2C_BUS_ERROR     SCB_INTR_S_I2C_BUS_ERROR_Msk


/*** \defgroup group_scb_common_macros_i2c_intr I2C Interrupt Statuses
* \{
*/
/**
* Wake up request: the I2C slave received the matching address.
* Note that this interrupt source triggers in active mode.
*/
#define CY_SCB_I2C_INTR_WAKEUP     SCB_INTR_I2C_EC_WAKE_UP_Msk
/** \} group_scb_common_macros_i2c_intr */



/*******************************************************************************
*                           Internal Constants
*******************************************************************************/

/** \cond INTERNAL */
#define CY_SCB_I2C_CFG_DEF_VAL      (_VAL2FLD(SCB_I2C_CFG_SDA_IN_FILT_TRIM, 3UL)   | \
                                     _VAL2FLD(SCB_I2C_CFG_SDA_IN_FILT_SEL, 1UL)    | \
                                     _VAL2FLD(SCB_I2C_CFG_SCL_IN_FILT_SEL, 1UL)    | \
                                     _VAL2FLD(SCB_I2C_CFG_SDA_OUT_FILT0_TRIM, 2UL) | \
                                     _VAL2FLD(SCB_I2C_CFG_SDA_OUT_FILT1_TRIM, 2UL) | \
                                     _VAL2FLD(SCB_I2C_CFG_SDA_OUT_FILT2_TRIM, 2UL))

/* The position and mask to set the I2C mode */
#define CY_SCB_I2C_CTRL_MODE_Pos    SCB_I2C_CTRL_SLAVE_MODE_Pos
#define CY_SCB_I2C_CTRL_MODE_Msk    (SCB_I2C_CTRL_SLAVE_MODE_Msk | \
                                     SCB_I2C_CTRL_MASTER_MODE_Msk)


/* SCB CTRL modes */
#define CY_SCB_CTRL_MODE_I2C   (0UL)
#define CY_SCB_CTRL_MODE_SPI   (1UL)
#define CY_SCB_CTRL_MODE_UART  (2UL)

/* I2C has fixed data width */
#define CY_SCB_I2C_DATA_WIDTH   (7UL)

/* RX and TX control register values */
#define CY_SCB_I2C_RX_CTRL      (_VAL2FLD(SCB_RX_CTRL_DATA_WIDTH, CY_SCB_I2C_DATA_WIDTH) | \
                                 SCB_RX_CTRL_MSB_FIRST_Msk)
#define CY_SCB_I2C_TX_CTRL      (_VAL2FLD(SCB_TX_CTRL_DATA_WIDTH, CY_SCB_I2C_DATA_WIDTH) | \
                                 SCB_TX_CTRL_MSB_FIRST_Msk)


/* Max number of bits for byte mode */
#define CY_SCB_BYTE_WIDTH   (8UL)

/* Single unit to wait */
#define CY_SCB_WAIT_1_UNIT  (1U)

/* Clear interrupt sources */
#define CY_SCB_CLEAR_ALL_INTR_SRC   (0UL)

/* Number of words in EZ memory */
#define SCB_EZ_DATA_NR                  32u

/* Hardware FIFO size */
#define CY_SCB_FIFO_SIZE            (SCB_EZ_DATA_NR / 2U)




void Cy_SCB_ClearI2CInterrupt(CySCB_Type *base, uint32_t interruptMask);
uint32_t Cy_SCB_GetNumInRxFifo(CySCB_Type const *base);
void Cy_SCB_ClearRxFifo(CySCB_Type* base);
void Cy_SCB_SetRxInterruptMask(CySCB_Type *base, uint32_t interruptMask);
uint32_t Cy_SCB_GetNumInTxFifo(CySCB_Type const *base);
uint32_t Cy_SCB_GetTxSrValid(CySCB_Type const *base);
void Cy_SCB_SetTxInterruptMask(CySCB_Type *base, uint32_t interruptMask);
void Cy_SCB_ClearRxInterrupt(CySCB_Type *base, uint32_t interruptMask);
void Cy_SCB_ClearSlaveInterrupt(CySCB_Type *base, uint32_t interruptMask);
void Cy_SCB_SetSlaveInterruptMask(CySCB_Type *base, uint32_t interruptMask);
void Cy_SCB_ClearTxFifo(CySCB_Type *base);
void Cy_SCB_SetRxFifoLevel(CySCB_Type *base, uint32_t level);
uint32_t Cy_SCB_GetFifoSize(CySCB_Type const *base);
uint32_t Cy_SCB_GetSlaveInterruptStatusMasked(CySCB_Type const *base);
void Cy_SCB_ClearTxInterrupt(CySCB_Type *base, uint32_t interruptMask);
void Cy_SCB_FwBlockReset(CySCB_Type *base);
bool Cy_SCB_IsTxDataWidthByte(CySCB_Type const *base);
void Cy_SCB_WriteTxFifo(CySCB_Type* base, uint32_t data);
void Cy_SCB_ReadArrayNoCheck(CySCB_Type const *base, void *buffer, uint32_t size);
uint32_t Cy_SCB_ReadArray(CySCB_Type const *base, void *buffer, uint32_t size);

void Cy_SCB_WriteDefaultArrayNoCheck(CySCB_Type *base, uint32_t txData, uint32_t size);
uint32_t Cy_SCB_WriteDefaultArray(CySCB_Type *base, uint32_t txData, uint32_t size);
void Cy_SCB_WriteArrayNoCheck(CySCB_Type *base, void const *buffer, uint32_t size);
uint32_t Cy_SCB_WriteArray(CySCB_Type *base, void const *buffer, uint32_t size);
void Cy_SCB_WriteArrayBlocking(CySCB_Type *base, void *buffer, uint32_t size);

#endif