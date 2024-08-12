#include <stdint.h>
#include <stdbool.h>
#define TRNG_H

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

#define TRNG_DATA_BIT_SIZE_MIN          1U
#define TRNG_DATA_BIT_SIZE_MAX          32U

typedef struct stc_trng_config{
  /**
* The polynomial for the programmable Fibonacci ring oscillator. The polynomial is represented
* WITHOUT the high order bit (this bit is always assumed '1'). The polynomial should
* be aligned so that the more significant bits (bit 30 and down) contain the polynomial
* and the less significant bits (bit 0 and up) contain padding '0's.
*/
  uint32_t  trng_firo_ctl_reg_value;

  /**
* The polynomial for programmable Galois ring oscillator. The polynomial is represented
* WITHOUT the high order bit (this bit is always assumed '1'). The polynomial should be aligned
* so that the more significant bits (bit 30 and down) contain the polynomial and the less
* significant bits (bit 0 and up) contain padding '0's.
*/
  uint32_t  trng_garo_ctl_reg_value; 

  uint32_t  trng_ctl0_reg_value;

  uint32_t  trng_cmd_start_ro; 
  
  uint32_t  trng_bit_size;

}cy_stc_trng_config_t;


typedef struct {
  __IOM uint32_t CTL;                           /*!< 0x00000000 Control */
  __IM uint32_t RESERVED[159];

  __IOM uint32_t TR_CTL0;                       /*!< 0x00000280 True random control 0 */
  __IOM uint32_t TR_CTL1;                       /*!< 0x00000284 True random control 1 */
  __IOM uint32_t TR_RESULT0;                    /*!< 0x00000288 True random result 0 */
  __IOM uint32_t TR_RESULT1;                    /*!< 0x0000028C True random result 1 */
  __IOM uint32_t TR_CMD;                        /*!< 0x00000290 True random command */
   __IM uint32_t RESERVED8[3];
  __IOM uint32_t TR_GARO_CTL;                   /*!< 0x000002A0 True random GARO control */
  __IOM uint32_t TR_FIRO_CTL;                   /*!< 0x000002A4 True random FIRO control */

  __IM uint32_t RESERVED9[326]; 

  __IOM uint32_t INTR;                          /*!< 0x000007C0 Interrupt request */
  __IOM uint32_t INTR_SET;                      /*!< 0x000007C4 Interrupt set request */
  __IOM uint32_t INTR_MASK;                     /*!< 0x000007C8 Interrupt mask */
   __IM uint32_t INTR_MASKED;                   /*!< 0x000007CC Interrupt masked */
   __IM uint32_t RESERVED19[12];
  __IOM uint32_t MEM_BUFF[512];                 /*!< 0x00000800 Memory buffer */
   __IM uint32_t RESERVED20[15296];
  __IOM uint32_t PRIV_BUF;                      /*!< 0x0000FF00 Buffer Privilege register */
} CRYPTO_Type;

#define CRYPTO_BASE                              0x402C0000UL
#define CRYPTO                                   ((CRYPTO_Type*) CRYPTO_BASE)

/*******************************************************************************
*                CRYPTO
*******************************************************************************/

/* Registers */
#define REG_CRYPTO_CTL(base)               (((CRYPTO_Type*)(base))->CTL)
#define REG_CRYPTO_TR_CTL0(base)           (((CRYPTO_Type*)(base))->TR_CTL0)
#define REG_CRYPTO_TR_CTL1(base)           (((CRYPTO_Type*)(base))->TR_CTL1)
#define REG_CRYPTO_TR_RESULT0(base)        (((CRYPTO_Type*)(base))->TR_RESULT0)
#define REG_CRYPTO_TR_RESULT1(base)        (((CRYPTO_Type*)(base))->TR_RESULT1)
#define REG_CRYPTO_TR_CMD(base)            (((CRYPTO_Type*)(base))->TR_CMD)
#define REG_CRYPTO_TR_GARO_CTL(base)       (((CRYPTO_Type*)(base))->TR_GARO_CTL)
#define REG_CRYPTO_TR_FIRO_CTL(base)       (((CRYPTO_Type*)(base))->TR_FIRO_CTL)
#define REG_CRYPTO_INTR(base)              (((CRYPTO_Type*)(base))->INTR)
#define REG_CRYPTO_INTR_SET(base)          (((CRYPTO_Type*)(base))->INTR_SET)
#define REG_CRYPTO_INTR_MASK(base)         (((CRYPTO_Type*)(base))->INTR_MASK)
#define REG_CRYPTO_INTR_MASKED(base)       (((CRYPTO_Type*)(base))->INTR_MASKED)

/* CRYPTO.CTL */
#define CRYPTO_CTL_OPCODE_Pos                   0UL
#define CRYPTO_CTL_OPCODE_Msk                   0x1FUL
#define CRYPTO_CTL_ENABLED_Pos                  31UL
#define CRYPTO_CTL_ENABLED_Msk                  0x80000000UL

/* CRYPTO.TR_CTL0 */
#define CRYPTO_TR_CTL0_SAMPLE_CLOCK_DIV_Pos     0UL
#define CRYPTO_TR_CTL0_SAMPLE_CLOCK_DIV_Msk     0xFFUL
#define CRYPTO_TR_CTL0_RED_CLOCK_DIV_Pos        8UL
#define CRYPTO_TR_CTL0_RED_CLOCK_DIV_Msk        0xFF00UL
#define CRYPTO_TR_CTL0_INIT_DELAY_Pos           16UL
#define CRYPTO_TR_CTL0_INIT_DELAY_Msk           0xFF0000UL
#define CRYPTO_TR_CTL0_VON_NEUMANN_CORR_Pos     24UL
#define CRYPTO_TR_CTL0_VON_NEUMANN_CORR_Msk     0x1000000UL
#define CRYPTO_TR_CTL0_STOP_ON_AP_DETECT_Pos    28UL
#define CRYPTO_TR_CTL0_STOP_ON_AP_DETECT_Msk    0x10000000UL
#define CRYPTO_TR_CTL0_STOP_ON_RC_DETECT_Pos    29UL
#define CRYPTO_TR_CTL0_STOP_ON_RC_DETECT_Msk    0x20000000UL
/* CRYPTO.TR_CTL1 */
#define CRYPTO_TR_CTL1_DATA_BIT_SIZE_Pos        0UL
#define CRYPTO_TR_CTL1_DATA_BIT_SIZE_Msk        0x3FUL
/* CRYPTO.TR_RESULT0 */
#define CRYPTO_TR_RESULT0_DATA32_Pos            0UL
#define CRYPTO_TR_RESULT0_DATA32_Msk            0xFFFFFFFFUL
/* CRYPTO.TR_RESULT1 */
#define CRYPTO_TR_RESULT1_DATA_BIT_SIZE_Pos     0UL
#define CRYPTO_TR_RESULT1_DATA_BIT_SIZE_Msk     0x3FUL
/* CRYPTO.TR_CMD */
#define CRYPTO_TR_CMD_START_RO11_Pos            0UL
#define CRYPTO_TR_CMD_START_RO11_Msk            0x1UL
#define CRYPTO_TR_CMD_START_RO15_Pos            1UL
#define CRYPTO_TR_CMD_START_RO15_Msk            0x2UL
#define CRYPTO_TR_CMD_START_GARO15_Pos          2UL
#define CRYPTO_TR_CMD_START_GARO15_Msk          0x4UL
#define CRYPTO_TR_CMD_START_GARO31_Pos          3UL
#define CRYPTO_TR_CMD_START_GARO31_Msk          0x8UL
#define CRYPTO_TR_CMD_START_FIRO15_Pos          4UL
#define CRYPTO_TR_CMD_START_FIRO15_Msk          0x10UL
#define CRYPTO_TR_CMD_START_FIRO31_Pos          5UL
#define CRYPTO_TR_CMD_START_FIRO31_Msk          0x20UL
/* CRYPTO.TR_GARO_CTL */
#define CRYPTO_TR_GARO_CTL_POLYNOMIAL31_Pos     0UL
#define CRYPTO_TR_GARO_CTL_POLYNOMIAL31_Msk     0x7FFFFFFFUL
/* CRYPTO.TR_FIRO_CTL */
#define CRYPTO_TR_FIRO_CTL_POLYNOMIAL31_Pos     0UL
#define CRYPTO_TR_FIRO_CTL_POLYNOMIAL31_Msk     0x7FFFFFFFUL

/* CRYPTO.INTR */
#define CRYPTO_INTR_DONE_Pos                    0UL
#define CRYPTO_INTR_DONE_Msk                    0x1UL
#define CRYPTO_INTR_ACCESS_ERROR_Pos            1UL
#define CRYPTO_INTR_ACCESS_ERROR_Msk            0x2UL
#define CRYPTO_INTR_TR_INITIALIZED_Pos          6UL
#define CRYPTO_INTR_TR_INITIALIZED_Msk          0x40UL
#define CRYPTO_INTR_TR_DATA_AVAILABLE_Pos       7UL
#define CRYPTO_INTR_TR_DATA_AVAILABLE_Msk       0x80UL
#define CRYPTO_INTR_TR_AP_DETECT_Pos            8UL
#define CRYPTO_INTR_TR_AP_DETECT_Msk            0x100UL
#define CRYPTO_INTR_TR_RC_DETECT_Pos            9UL
#define CRYPTO_INTR_TR_RC_DETECT_Msk            0x200UL
/* CRYPTO.INTR_SET */
#define CRYPTO_INTR_SET_DONE_Pos                0UL
#define CRYPTO_INTR_SET_DONE_Msk                0x1UL
#define CRYPTO_INTR_SET_ACCESS_ERROR_Pos        1UL
#define CRYPTO_INTR_SET_ACCESS_ERROR_Msk        0x2UL
#define CRYPTO_INTR_SET_TR_INITIALIZED_Pos      6UL
#define CRYPTO_INTR_SET_TR_INITIALIZED_Msk      0x40UL
#define CRYPTO_INTR_SET_TR_DATA_AVAILABLE_Pos   7UL
#define CRYPTO_INTR_SET_TR_DATA_AVAILABLE_Msk   0x80UL
#define CRYPTO_INTR_SET_TR_AP_DETECT_Pos        8UL
#define CRYPTO_INTR_SET_TR_AP_DETECT_Msk        0x100UL
#define CRYPTO_INTR_SET_TR_RC_DETECT_Pos        9UL
#define CRYPTO_INTR_SET_TR_RC_DETECT_Msk        0x200UL
/* CRYPTO.INTR_MASK */
#define CRYPTO_INTR_MASK_DONE_Pos               0UL
#define CRYPTO_INTR_MASK_DONE_Msk               0x1UL
#define CRYPTO_INTR_MASK_ACCESS_ERROR_Pos       1UL
#define CRYPTO_INTR_MASK_ACCESS_ERROR_Msk       0x2UL
#define CRYPTO_INTR_MASK_TR_INITIALIZED_Pos     6UL
#define CRYPTO_INTR_MASK_TR_INITIALIZED_Msk     0x40UL
#define CRYPTO_INTR_MASK_TR_DATA_AVAILABLE_Pos  7UL
#define CRYPTO_INTR_MASK_TR_DATA_AVAILABLE_Msk  0x80UL
#define CRYPTO_INTR_MASK_TR_AP_DETECT_Pos       8UL
#define CRYPTO_INTR_MASK_TR_AP_DETECT_Msk       0x100UL
#define CRYPTO_INTR_MASK_TR_RC_DETECT_Pos       9UL
#define CRYPTO_INTR_MASK_TR_RC_DETECT_Msk       0x200UL
/* CRYPTO.INTR_MASKED */
#define CRYPTO_INTR_MASKED_DONE_Pos             0UL
#define CRYPTO_INTR_MASKED_DONE_Msk             0x1UL
#define CRYPTO_INTR_MASKED_ACCESS_ERROR_Pos     1UL
#define CRYPTO_INTR_MASKED_ACCESS_ERROR_Msk     0x2UL
#define CRYPTO_INTR_MASKED_TR_INITIALIZED_Pos   6UL
#define CRYPTO_INTR_MASKED_TR_INITIALIZED_Msk   0x40UL
#define CRYPTO_INTR_MASKED_TR_DATA_AVAILABLE_Pos 7UL
#define CRYPTO_INTR_MASKED_TR_DATA_AVAILABLE_Msk 0x80UL
#define CRYPTO_INTR_MASKED_TR_AP_DETECT_Pos     8UL
#define CRYPTO_INTR_MASKED_TR_AP_DETECT_Msk     0x100UL
#define CRYPTO_INTR_MASKED_TR_RC_DETECT_Pos     9UL
#define CRYPTO_INTR_MASKED_TR_RC_DETECT_Msk     0x200UL

void Crypto_TRNG_Enable(CRYPTO_Type *base);
bool Cy_Crypto_IsEnabled(CRYPTO_Type *base);
uint32_t Cy_Crypto_GetInterruptStatus(CRYPTO_Type *base);
void Cy_Crypto_Trng_WaitForComplete(CRYPTO_Type *base);
void Crypto_Trng_Get_Random(CRYPTO_Type *base, uint32_t *randomNum, cy_stc_trng_config_t const *config);