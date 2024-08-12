#include "uart.h"
#include "i2c.h"

void Cy_SCB_UART_Init(CySCB_Type *base, cy_stc_scb_uart_config_t const *config, cy_stc_scb_uart_context_t *context)
{

    uint32_t ovs = (config->oversample - 1UL);

    /* Configure the UART interface */
    SCB_CTRL(base) = (((uint32_t)(ovs) << SCB_CTRL_OVS_Pos) & SCB_CTRL_OVS_Msk)  |
                        (((uint32_t)(CY_SCB_CTRL_MODE_UART) << SCB_CTRL_MODE_Pos) & SCB_CTRL_MODE_Msk);

    SCB_CTRL(base) |= ((((config->dataWidth <= CY_SCB_BYTE_WIDTH)) != false) ? (SCB_CTRL_BYTE_MODE_Msk) : 0UL);

    SCB_UART_CTRL(base) = (((uint32_t) config->uartMode << SCB_UART_CTRL_MODE_Pos) & SCB_UART_CTRL_MODE_Msk);

    /* Configure the RX direction */
    SCB_UART_RX_CTRL(base) = ((((uint32_t)(config->stopBits)-1) << SCB_UART_RX_CTRL_STOP_BITS_Pos) & SCB_UART_RX_CTRL_STOP_BITS_Msk) |
                                (((uint32_t)(config->parity) << CY_SCB_UART_RX_CTRL_SET_PARITY_Pos) & CY_SCB_UART_RX_CTRL_SET_PARITY_Msk);

    SCB_RX_CTRL(base) = _BOOL2FLD(SCB_RX_CTRL_MSB_FIRST, config->enableMsbFirst) |
                        _VAL2FLD(SCB_RX_CTRL_DATA_WIDTH, (config->dataWidth - 1UL));

    /* Configure the TX direction */
    SCB_UART_TX_CTRL(base) = _VAL2FLD(SCB_UART_TX_CTRL_STOP_BITS, ((uint32_t) config->stopBits) - 1UL)    |
                                _VAL2FLD(CY_SCB_UART_TX_CTRL_SET_PARITY, (uint32_t) config->parity);

    SCB_TX_CTRL(base)  = _BOOL2FLD(SCB_TX_CTRL_MSB_FIRST,  config->enableMsbFirst)    |
                            _VAL2FLD(SCB_TX_CTRL_DATA_WIDTH,  (config->dataWidth - 1UL));


    SCB_RX_FIFO_CTRL(base) = _VAL2FLD(SCB_RX_FIFO_CTRL_TRIGGER_LEVEL, config->rxFifoTriggerLevel);

    /* Configure the flow control */
    SCB_UART_FLOW_CTRL(base) = _BOOL2FLD(SCB_UART_FLOW_CTRL_CTS_ENABLED, config->enableCts)                                 |
                                _BOOL2FLD(SCB_UART_FLOW_CTRL_CTS_POLARITY, (CY_SCB_UART_ACTIVE_HIGH == config->ctsPolarity)) |
                                _BOOL2FLD(SCB_UART_FLOW_CTRL_RTS_POLARITY, (CY_SCB_UART_ACTIVE_HIGH == config->rtsPolarity)) |
                                _VAL2FLD(SCB_UART_FLOW_CTRL_TRIGGER_LEVEL, config->rtsRxFifoLevel);

    SCB_TX_FIFO_CTRL(base) = _VAL2FLD(SCB_TX_FIFO_CTRL_TRIGGER_LEVEL, config->txFifoTriggerLevel);

    /* Set up interrupt sources */
    SCB_INTR_RX_MASK(base) = (config->rxFifoIntEnableMask & CY_SCB_UART_RX_INTR_MASK);
    SCB_INTR_TX_MASK(base) = (config->txFifoIntEnableMask & CY_SCB_UART_TX_INTR_MASK);

    /* Initialize context */
    if (NULL != context)
    {
        context->rxStatus  = 0UL;
        context->txStatus  = 0UL;

        context->rxRingBuf = NULL;
        context->rxRingBufSize = 0UL;

        context->rxBufIdx  = 0UL;
        context->txLeftToTransmit = 0UL;
    }
}

void Cy_SCB_UART_Enable(CySCB_Type *base)
{
    SCB_CTRL(base) |= SCB_CTRL_ENABLED_Msk;
}

void Cy_SCB_UART_PutString(CySCB_Type *base, char const string[])
{
    Cy_SCB_WriteString(base, string);
}

void Cy_SCB_WriteString(CySCB_Type *base, char const string[])
{
    uint32_t idx = 0UL;
    uint32_t fifoSize = Cy_SCB_GetFifoSize(base);

    /* Put data from TX FIFO. Stop when string is terminated */
    while (((char) 0) != string[idx])
    {
        /* Wait for free space to be available */
        while (fifoSize == Cy_SCB_GetNumInTxFifo(base))
        {
        }

        Cy_SCB_WriteTxFifo(base, (uint32_t) string[idx]);
        ++idx;
    }
}

uint32_t Cy_SCB_GetFifoSize(CySCB_Type const *base)
{
    return (_FLD2BOOL(SCB_CTRL_BYTE_MODE, SCB_CTRL(base)) ? (CY_SCB_FIFO_SIZE) : (CY_SCB_FIFO_SIZE / 2UL));
}

uint32_t Cy_SCB_GetNumInTxFifo(CySCB_Type const *base)
{
    return _FLD2VAL(SCB_TX_FIFO_STATUS_USED, SCB_TX_FIFO_STATUS(base));
}

void Cy_SCB_WriteTxFifo(CySCB_Type* base, uint32_t data)
{
    SCB_TX_FIFO_WR(base) = data;
}

uint32_t Cy_SCB_UART_GetNumInRxFifo(CySCB_Type const *base)
{
    return _FLD2VAL(SCB_RX_FIFO_STATUS_USED, SCB_RX_FIFO_STATUS(base));
}

uint32_t Cy_SCB_UART_Get(CySCB_Type const *base)
{
    return Cy_SCB_ReadRxFifo(base);
}

uint32_t Cy_SCB_ReadRxFifo(CySCB_Type const *base)
{
    return (SCB_RX_FIFO_RD(base));
}

uint32_t Cy_SCB_UART_Put(CySCB_Type *base, uint32_t data)
{
    return Cy_SCB_Write(base, data);
}

uint32_t Cy_SCB_Write(CySCB_Type *base, uint32_t data)
{
    uint32_t numCopied = 0UL;

    if (Cy_SCB_GetFifoSize(base) != Cy_SCB_GetNumInTxFifo(base))
    {
        Cy_SCB_WriteTxFifo(base, data);

        numCopied = 1UL;
    }

    return (numCopied);
}

