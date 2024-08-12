#include <stdint.h>
#include "trng.h"

void Crypto_TRNG_Enable(CRYPTO_Type *base)
{
    REG_CRYPTO_CTL(base) |= (((uint32_t)(1uL) << CRYPTO_CTL_ENABLED_Pos) & CRYPTO_CTL_ENABLED_Msk); 
}

bool Cy_Crypto_IsEnabled(CRYPTO_Type *base)
{
    return (1uL == (((uint32_t)(REG_CRYPTO_CTL(base)) & CRYPTO_CTL_ENABLED_Msk) >> CRYPTO_CTL_ENABLED_Pos));  
}

uint32_t Cy_Crypto_GetInterruptStatus(CRYPTO_Type *base)
{
    return (REG_CRYPTO_INTR(base));
}

void Cy_Crypto_Trng_WaitForComplete(CRYPTO_Type *base)
{
    uint32_t status;
    /* Wait until the TRNG random generation is complete */
    do
    {
        status = Cy_Crypto_GetInterruptStatus(base) & (CRYPTO_INTR_TR_DATA_AVAILABLE_Msk  |
                                                             CRYPTO_INTR_TR_AP_DETECT_Msk |
                                                            CRYPTO_INTR_TR_RC_DETECT_Msk);
    }
    while (status == 0U);
}

void Crypto_Trng_Get_Random(CRYPTO_Type *base, uint32_t *randomNum, cy_stc_trng_config_t const *config)
{

    if (!Cy_Crypto_IsEnabled(base))
    {
        *randomNum = 0;
    }

    /* Set CTL registers */
    REG_CRYPTO_TR_GARO_CTL(base) = (config->trng_garo_ctl_reg_value & CRYPTO_TR_GARO_CTL_POLYNOMIAL31_Msk);
    REG_CRYPTO_TR_FIRO_CTL(base) = (config->trng_firo_ctl_reg_value & CRYPTO_TR_FIRO_CTL_POLYNOMIAL31_Msk);

    //REG_CRYPTO_TR_CTL0(base) = CTL0_SAMPLE_CLOCK_DIV | CTL0_RED_CLOCK_DIV | CTL0_INIT_DELAY | CTL0_VON_NEUMANN_CORR;
    REG_CRYPTO_TR_CTL0(base) = config->trng_ctl0_reg_value;

    REG_CRYPTO_TR_CTL1(base) = config->trng_bit_size;

    /* Enable required ring oscillators */
    REG_CRYPTO_TR_CMD(base) =  config->trng_cmd_start_ro; 

    /* Wait for TRNG crypto operation completion */
    Cy_Crypto_Trng_WaitForComplete(base);

    /* Read the generated random number */
    *randomNum = REG_CRYPTO_TR_RESULT0(base);

    /* Stop the ring oscillators */
    REG_CRYPTO_TR_CMD(base) =  0;

    /* Clear the consumed bits */
    REG_CRYPTO_TR_RESULT0(base) = 0;

    /* Decrement TR_RESULT1 by the number of consumed bits */
    REG_CRYPTO_TR_RESULT1(base) = REG_CRYPTO_TR_RESULT1(base) - config->trng_bit_size;

    /* Clear TR_DATA_AVAILABLE interrupt */
    REG_CRYPTO_INTR(base) = 0x00000080;

    /* For data length less than Maximum bit size, apply mask and provide only max bits from the randomly generated number. */
    if (config->trng_bit_size < TRNG_DATA_BIT_SIZE_MAX)
    {
        *randomNum &= ((1UL << config->trng_bit_size) - 1U);
    }

}