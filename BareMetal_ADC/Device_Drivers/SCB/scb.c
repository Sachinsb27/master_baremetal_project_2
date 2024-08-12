#include "scb.h"


void Cy_SCB_ClearI2CInterrupt(CySCB_Type *base, uint32_t interruptMask)
{
    SCB_INTR_I2C_EC(base) = interruptMask;
    (void) SCB_INTR_I2C_EC(base);
}

uint32_t Cy_SCB_GetNumInRxFifo(CySCB_Type const *base)
{
    return _FLD2VAL(SCB_RX_FIFO_STATUS_USED, SCB_RX_FIFO_STATUS(base));
}

void Cy_SCB_ClearRxFifo(CySCB_Type* base)
{
    SCB_RX_FIFO_CTRL(base) |= (uint32_t)  SCB_RX_FIFO_CTRL_CLEAR_Msk;
    SCB_RX_FIFO_CTRL(base) &= (uint32_t) ~SCB_RX_FIFO_CTRL_CLEAR_Msk;

    (void) SCB_RX_FIFO_CTRL(base);
}
void Cy_SCB_SetRxInterruptMask(CySCB_Type *base, uint32_t interruptMask)
{
    SCB_INTR_RX_MASK(base) = interruptMask;
}

uint32_t Cy_SCB_GetTxSrValid(CySCB_Type const *base)
{
    return _FLD2VAL(SCB_TX_FIFO_STATUS_SR_VALID, SCB_TX_FIFO_STATUS(base));
}

void Cy_SCB_SetTxInterruptMask(CySCB_Type *base, uint32_t interruptMask)
{
    SCB_INTR_TX_MASK(base) = interruptMask;
}

void Cy_SCB_ClearRxInterrupt(CySCB_Type *base, uint32_t interruptMask)
{
    SCB_INTR_RX(base) = interruptMask;
    (void) SCB_INTR_RX(base);
}

void Cy_SCB_ClearSlaveInterrupt(CySCB_Type *base, uint32_t interruptMask)
{
    SCB_INTR_S(base) = interruptMask;
    (void) SCB_INTR_S(base);
}

void Cy_SCB_SetSlaveInterruptMask(CySCB_Type *base, uint32_t interruptMask)
{
    SCB_INTR_S_MASK(base) = interruptMask;
}

void Cy_SCB_ClearTxFifo(CySCB_Type *base)
{
    SCB_TX_FIFO_CTRL(base) |= (uint32_t)  SCB_TX_FIFO_CTRL_CLEAR_Msk;
    SCB_TX_FIFO_CTRL(base) &= (uint32_t) ~SCB_TX_FIFO_CTRL_CLEAR_Msk;

    (void) SCB_TX_FIFO_CTRL(base);
}

void Cy_SCB_SetRxFifoLevel(CySCB_Type *base, uint32_t level)
{
    CY_REG32_CLR_SET(SCB_RX_FIFO_CTRL(base), SCB_RX_FIFO_CTRL_TRIGGER_LEVEL, level);
}

uint32_t Cy_SCB_GetSlaveInterruptStatusMasked(CySCB_Type const *base)
{
    return (SCB_INTR_S_MASKED(base));
}

void Cy_SCB_ClearTxInterrupt(CySCB_Type *base, uint32_t interruptMask)
{
    SCB_INTR_TX(base) = interruptMask;
    (void) SCB_INTR_TX(base);
}

void Cy_SCB_FwBlockReset(CySCB_Type *base)
{
    SCB_CTRL(base) &= (uint32_t) ~SCB_CTRL_ENABLED_Msk;

    /* Clean-up command registers */
    SCB_I2C_M_CMD(base) = 0UL;
    SCB_I2C_S_CMD(base) = 0UL;

    SCB_CTRL(base) |= (uint32_t)  SCB_CTRL_ENABLED_Msk;

    (void) SCB_CTRL(base);
}

bool Cy_SCB_IsTxDataWidthByte(CySCB_Type const *base)
{
    return (_FLD2VAL(SCB_TX_CTRL_DATA_WIDTH, SCB_TX_CTRL(base)) < CY_SCB_BYTE_WIDTH);
}

void Cy_SCB_ReadArrayNoCheck(CySCB_Type const *base, void *buffer, uint32_t size)
{
    uint32_t idx;

    if ((_FLD2VAL(SCB_RX_CTRL_DATA_WIDTH, SCB_RX_CTRL(base)) < CY_SCB_BYTE_WIDTH))
    {
        uint8_t *buf = (uint8_t *) buffer;

        /* Get data available in RX FIFO */
        for (idx = 0UL; idx < size; ++idx)
        {
            buf[idx] = (uint8_t) SCB_RX_FIFO_RD(base); // read fifo
        }
    }
    else
    {
        uint16_t *buf = (uint16_t *) buffer;

        /* Get data available in RX FIFO */
        for (idx = 0UL; idx < size; ++idx)
        {
            buf[idx] = (uint16_t) SCB_RX_FIFO_RD(base);
        }
    }
}


uint32_t Cy_SCB_ReadArray(CySCB_Type const *base, void *buffer, uint32_t size)
{
    /* Get available items in RX FIFO */
    uint32_t numToCopy = _FLD2VAL(SCB_RX_FIFO_STATUS_USED, SCB_RX_FIFO_STATUS(base));

    /* Adjust items that will be read */
    if (numToCopy > size)
    {
        numToCopy = size;
    }

    /* Get data available in RX FIFO */
    Cy_SCB_ReadArrayNoCheck(base, buffer, numToCopy);

    return (numToCopy);
}

void Cy_SCB_WriteDefaultArrayNoCheck(CySCB_Type *base, uint32_t txData, uint32_t size)
{
    uint32_t locSize = size; 
    while (locSize > 0UL)
    {
        SCB_TX_FIFO_WR(base) = txData;
        --locSize;
    }
}

uint32_t Cy_SCB_WriteDefaultArray(CySCB_Type *base, uint32_t txData, uint32_t size)
{
    /* Get free entries in TX FIFO */
    uint32_t numToCopy = Cy_SCB_GetFifoSize(base) - Cy_SCB_GetNumInTxFifo(base);

    /* Adjust data elements to write */
    if (numToCopy > size)
    {
        numToCopy = size;
    }

    Cy_SCB_WriteDefaultArrayNoCheck(base, txData, numToCopy);

    return (numToCopy);
}

void Cy_SCB_WriteArrayNoCheck(CySCB_Type *base, void const *buffer, uint32_t size)
{
    uint32_t idx;

    if (Cy_SCB_IsTxDataWidthByte(base))
    {
        uint8_t const *buf = (uint8_t *) buffer;

        /* Put data into TX FIFO */
        for (idx = 0UL; idx < size; ++idx)
        {
            Cy_SCB_WriteTxFifo(base, (uint32_t) buf[idx]);
        }
    }
    else
    {
        uint16_t const *buf = (uint16_t *) buffer;

        /* Put data into TX FIFO */
        for (idx = 0UL; idx < size; ++idx)
        {
            Cy_SCB_WriteTxFifo(base, (uint32_t) buf[idx]);
        }
    }
}

uint32_t Cy_SCB_WriteArray(CySCB_Type *base, void const *buffer, uint32_t size)
{
    /* Get free entries in TX FIFO */
    uint32_t numToCopy = Cy_SCB_GetFifoSize(base) - Cy_SCB_GetNumInTxFifo(base);

    /* Adjust the data elements to write */
    if (numToCopy > size)
    {
        numToCopy = size;
    }

    Cy_SCB_WriteArrayNoCheck(base, buffer, numToCopy);

    return (numToCopy);
}

void Cy_SCB_WriteArrayBlocking(CySCB_Type *base, void *buffer, uint32_t size)
{
    uint32_t numCopied;
    uint8_t  *buf = (uint8_t *) buffer;
    bool     byteMode = ((((uint32_t)(SCB_TX_CTRL(base)) & SCB_TX_CTRL_DATA_WIDTH_Msk) >> SCB_TX_CTRL_DATA_WIDTH_Pos) < CY_SCB_BYTE_WIDTH);
    uint32_t locSize = size;

    /* Get data from RX FIFO. Stop when the requested locSize is read. */
    while (locSize > 0UL)
    {
        numCopied = Cy_SCB_WriteArray(base, (void *) buf, locSize);

        buf = &buf[(byteMode ? (numCopied) : (2UL * numCopied))];
        locSize -= numCopied;
    }
}
