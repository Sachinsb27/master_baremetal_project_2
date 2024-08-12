#include "i2c.h"


void SlaveHandleDataReceive(CySCB_Type *base, cy_stc_scb_i2c_context_t *context)
{

    /* Check whether there is space to put data */
    if (context->slaveRxBufferSize > 0UL)
    {

        if (context->useRxFifo)
        {
            uint32_t level;

            /* Get the number of bytes to read from RX FIFO */
            uint32_t numToCopy = (((uint32_t)(SCB_RX_FIFO_CTRL(base)) & SCB_RX_FIFO_CTRL_TRIGGER_LEVEL_Msk) >> SCB_RX_FIFO_CTRL_TRIGGER_LEVEL_Pos) + 1UL;

            /* Get data from RX FIFO */
            numToCopy = Cy_SCB_ReadArray(base, context->slaveRxBuffer, numToCopy);
            context->slaveRxBufferIdx  += numToCopy;
            context->slaveRxBufferSize -= numToCopy;
            context->slaveRxBuffer      = &context->slaveRxBuffer[numToCopy];

            /* Prepare to read a next chunk of data */
            if (context->slaveRxBufferSize > CY_SCB_I2C_FIFO_SIZE)
            {
                level = context->slaveRxBufferSize - CY_SCB_I2C_FIFO_SIZE;
                level = ((level > CY_SCB_I2C_FIFO_SIZE) ? (CY_SCB_I2C_FIFO_SIZE / 2UL) : level) - 1UL;
            }
            else
            {
                SCB_I2C_CTRL(base) |= SCB_I2C_CTRL_S_NOT_READY_DATA_NACK_Msk;

                level = (context->slaveRxBufferSize == 0UL) ? (0UL) : (context->slaveRxBufferSize - 1UL);
                SCB_INTR_RX_MASK(base) = CY_SCB_CLEAR_ALL_INTR_SRC;
            }

            /* Set the RX level to trigger an interrupt */
            CY_REG32_CLR_SET(SCB_RX_FIFO_CTRL(base), SCB_RX_FIFO_CTRL_TRIGGER_LEVEL, level);
        }
        else
        {
            /* Continue the transfer: send an ACK */
            SCB_I2C_S_CMD(base) |= SCB_I2C_S_CMD_S_ACK_Msk;

            /* Put data into the RX buffer */
            context->slaveRxBuffer[context->slaveRxBufferIdx] = (uint8_t) Cy_SCB_ReadRxFifo(base);
            ++context->slaveRxBufferIdx;
            --context->slaveRxBufferSize;
        }
    }
    else
    {
        /* Finish a transfer: send a NACK and discard the received byte */
        SCB_I2C_S_CMD(base) |= SCB_I2C_S_CMD_S_NACK_Msk;
        SCB_INTR_RX_MASK(base) = CY_SCB_CLEAR_ALL_INTR_SRC;
    }
}


void Cy_SCB_I2C_Init(CySCB_Type *base, cy_stc_scb_i2c_config_t const *config, cy_stc_scb_i2c_context_t *context)
{

        bool notMasterMode = CY_SCB_I2C_MASTER != config->i2cMode;

        /* Configure the I2C interface */
        SCB_CTRL(base) = (((config->acceptAddrInFifo) != false) ? (SCB_CTRL_ADDR_ACCEPT_Msk) : 0UL);

        SCB_I2C_CTRL(base) = (((uint32_t)(config->i2cMode) << CY_SCB_I2C_CTRL_MODE_Pos) & CY_SCB_I2C_CTRL_MODE_Msk);

        SCB_CTRL(base) |= SCB_CTRL_BYTE_MODE_Msk;

        SCB_RX_FIFO_CTRL(base) = (config->useRxFifo ? (CY_SCB_I2C_FIFO_SIZE - 1UL) : 0UL);

        /* Set the default address and mask */
        SCB_RX_MATCH(base) = (((uint32_t)(config->slaveAddress << 1UL) << SCB_RX_MATCH_ADDR_Pos) & SCB_RX_MATCH_ADDR_Msk) |
                             (((uint32_t)(config->slaveAddressMask) << SCB_RX_MATCH_MASK_Pos) & SCB_RX_MATCH_MASK_Msk);

        /* Configure the TX direction */
        SCB_TX_CTRL(base)      = CY_SCB_I2C_TX_CTRL;
        SCB_TX_FIFO_CTRL(base) = (config->useTxFifo ? CY_SCB_I2C_HALF_FIFO_SIZE : 1UL);

        /* Configure interrupt sources */
        SCB_INTR_SPI_EC_MASK(base) = 0UL;
        SCB_INTR_I2C_EC_MASK(base) = 0UL;
        SCB_INTR_RX_MASK(base)     = 0UL;
        SCB_INTR_TX_MASK(base)     = 0UL;
        SCB_INTR_M_MASK(base)      = 0UL;

        SCB_INTR_S_MASK(base) = (notMasterMode) ? CY_SCB_I2C_SLAVE_INTR : 0UL;

        /* Initialize the context */
        context->useRxFifo = config->useRxFifo;
        context->useTxFifo = config->useTxFifo;
        context->delayInFifoAddress = config->delayInFifoAddress;


        context->state = CY_SCB_I2C_IDLE;

        /* Slave-specific */
        context->slaveStatus       = 0UL;

        context->slaveRxBufferIdx  = 0UL;
        context->slaveRxBufferSize = 0UL;

        context->slaveTxBufferIdx  = 0UL;
        context->slaveTxBufferSize = 0UL;
}

void Cy_SCB_I2C_SlaveConfigReadBuf(CySCB_Type const *base, uint8_t *buffer, uint32_t size, cy_stc_scb_i2c_context_t *context)
{

    /* Suppress a compiler warning about unused variables */
    base = base;

    context->slaveTxBuffer     = buffer;
    context->slaveTxBufferSize = size;
    context->slaveTxBufferIdx  = 0UL;
    context->slaveTxBufferCnt  = 0UL;
}

void Cy_SCB_I2C_SlaveConfigWriteBuf(CySCB_Type const *base, uint8_t *buffer, uint32_t size, cy_stc_scb_i2c_context_t *context)
{
    /* Suppress a compiler warning about unused variables */
    base = base;

    context->slaveRxBuffer     = buffer;
    context->slaveRxBufferSize = size;
    context->slaveRxBufferIdx  = 0UL;
}

uint32_t Cy_SCB_I2C_SlaveClearWriteStatus(CySCB_Type const *base, cy_stc_scb_i2c_context_t *context)
{
    uint32_t retStatus;

    /* Suppress a compiler warning about unused variables */
    base = base;

    retStatus = (context->slaveStatus & CY_SCB_I2C_SLAVE_WR_CLEAR);
    context->slaveStatus &= (uint32_t) ~CY_SCB_I2C_SLAVE_WR_CLEAR;

    return (retStatus);
}

void Cy_SCB_I2C_Enable(CySCB_Type *base)
{
    SCB_CTRL(base) |= SCB_CTRL_ENABLED_Msk;
}

void SlaveHandleStop(CySCB_Type *base, bool slaveAddrInFifo, cy_stc_scb_i2c_context_t *context)
{
    uint32_t locEvents;
    if (CY_SCB_I2C_SLAVE_RX == context->state)
    {
        /* If any data is left in RX FIFO, this is an overflow */
        if (Cy_SCB_GetNumInRxFifo(base) > 0UL)
        {
            if (context->useRxFifo)
            {
                /* Leave the slave address to be processed by the further */
                context->slaveStatus |= CY_SCB_I2C_SLAVE_WR_OVRFL;
                Cy_SCB_ClearRxFifo(base);
            }
            else
            {
                /* Process data in FIFO in case if there is no address */
                if(!slaveAddrInFifo)
                {
                    context->slaveStatus |= CY_SCB_I2C_SLAVE_WR_OVRFL;
                    SCB_RX_FIFO_RD(base);
                }
            }

        }

        locEvents             = (uint32_t)  CY_SCB_I2C_SLAVE_WR_CMPLT_EVENT;
        context->slaveStatus |= (uint32_t)  CY_SCB_I2C_SLAVE_WR_CMPLT;
        context->slaveStatus &= (uint32_t) ~CY_SCB_I2C_SLAVE_WR_BUSY;

        /* Clean up the RX direction */
        SCB_I2C_CTRL(base) &= (uint32_t) ~(SCB_I2C_CTRL_S_READY_DATA_ACK_Msk |
                                          SCB_I2C_CTRL_S_NOT_READY_DATA_NACK_Msk);

        Cy_SCB_SetRxInterruptMask(base, CY_SCB_CLEAR_ALL_INTR_SRC);
        Cy_SCB_ClearRxInterrupt(base, CY_SCB_RX_INTR_LEVEL);
    }
    else
    {
        /* The number of bytes left in TX FIFO */
        uint32_t size = Cy_SCB_GetNumInTxFifo(base) + Cy_SCB_GetTxSrValid(base);

        /* Get the number of bytes transferred from the read buffer */
        context->slaveTxBufferCnt = (context->slaveTxBufferIdx - size);

        /* Update buffer pointer and its size if there is no overflow */
        if (0UL == (CY_SCB_I2C_SLAVE_RD_UNDRFL & context->slaveStatus))
        {
            context->slaveTxBufferSize += size;
            context->slaveTxBuffer     -= size;
        }

        locEvents             = (uint32_t)  CY_SCB_I2C_SLAVE_RD_CMPLT_EVENT;
        context->slaveStatus |= (uint32_t)  CY_SCB_I2C_SLAVE_RD_CMPLT;
        context->slaveStatus &= (uint32_t) ~CY_SCB_I2C_SLAVE_RD_BUSY;

        /* Clean up the TX direction */
        Cy_SCB_SetTxInterruptMask(base, CY_SCB_CLEAR_ALL_INTR_SRC);
    }

    /* Return scb into the known state after an error */
    if (0UL != (CY_SCB_I2C_SLAVE_INTR_ERROR & SCB_INTR_S_MASKED(base)))
    {
        /* After scb IP is reset, the interrupt statuses are cleared */
        Cy_SCB_FwBlockReset(base);

        locEvents |= CY_SCB_I2C_SLAVE_ERR_EVENT;
    }

    /* After a stop or error, set the state to idle */
    context->state = CY_SCB_I2C_IDLE;

}


void SlaveHandleAck(CySCB_Type *base, cy_stc_scb_i2c_context_t *context)
{
    bool readDirection = (((SCB_I2C_STATUS(base)) & (SCB_I2C_STATUS_S_READ_Msk)) != 0UL);

    /* Prepare for a transfer */
    if (readDirection)
    {
        context->state        = CY_SCB_I2C_SLAVE_TX;
        context->slaveStatus |= CY_SCB_I2C_SLAVE_RD_BUSY;

        /* Prepare to transmit data */
        context->slaveTxBufferIdx = context->slaveTxBufferCnt;
        context->slaveRdBufEmpty  = false;
        Cy_SCB_SetTxInterruptMask(base, CY_SCB_TX_INTR_LEVEL);
    }
    else
    {
        uint32_t level = 0UL;

        context->state        = CY_SCB_I2C_SLAVE_RX;
        context->slaveStatus |= CY_SCB_I2C_SLAVE_WR_BUSY;

        /* Prepare to receive data */
        Cy_SCB_SetRxInterruptMask(base, CY_SCB_RX_INTR_LEVEL);

        if (context->useRxFifo)
        {
            if (context->slaveRxBufferSize > 0UL)
            {
                /* ACK data automatically until RX FIFO is full */
                SCB_I2C_CTRL(base) |= SCB_I2C_CTRL_S_READY_DATA_ACK_Msk;

                if (context->slaveRxBufferSize > CY_SCB_I2C_FIFO_SIZE)
                {
                    /* Set a level in RX FIFO to trigger the receive interrupt source */
                    level = (context->slaveRxBufferSize - CY_SCB_I2C_FIFO_SIZE);
                    level = ((level > CY_SCB_I2C_FIFO_SIZE) ? (CY_SCB_I2C_FIFO_SIZE / 2UL) : level) - 1UL;
                }
                else
                {
                    /* Set a level in RX FIFO to read the number of bytes */
                    level = (context->slaveRxBufferSize - 1UL);

                    /* NACK when RX FIFO becomes full */
                    SCB_I2C_CTRL(base) |= SCB_I2C_CTRL_S_NOT_READY_DATA_NACK_Msk;

                    /* Disable the RX level interrupt and wait until RX FIFO is full or stops */
                    Cy_SCB_SetRxInterruptMask(base, CY_SCB_CLEAR_ALL_INTR_SRC);
                }
            }
        }

        Cy_SCB_SetRxFifoLevel(base, level);
    }
}


void SlaveHandleAddress(CySCB_Type *base, cy_stc_scb_i2c_context_t *context)
{
        /* The default command is the ACK address. It can be overridden in an address callback */
        cy_en_scb_i2c_command_t cmd = CY_SCB_I2C_ACK;

        /* Clear the TX FIFO before continue the transaction */
        Cy_SCB_ClearTxFifo(base);

            /* Set the command to an ACK or NACK address */
        SCB_I2C_S_CMD(base) |= (cmd == CY_SCB_I2C_ACK) ? SCB_I2C_S_CMD_S_ACK_Msk : SCB_I2C_S_CMD_S_NACK_Msk;

        SlaveHandleAck(base, context);

}


void SlaveHandleDataTransmit(CySCB_Type *base, cy_stc_scb_i2c_context_t *context)
{
    uint32_t numToCopy;

    /* Notify the user that there is no data to send to the master.
    * This event triggers once in scope of a transfer.
    */
    if ((!context->slaveRdBufEmpty) && (0UL == context->slaveTxBufferSize))
    {
        /* Update the Read buffer empty status after a callback is involved */
        context->slaveRdBufEmpty = (0UL == context->slaveTxBufferSize);

        /* Enable the TX level interrupt source to continue sending data */
        Cy_SCB_SetTxInterruptMask(base, CY_SCB_TX_INTR_LEVEL);
    }

    /* Check whether the Read buffer was updated in the callback */
    if (context->slaveRdBufEmpty)
    {
        /* The Read buffer is empty: copy CY_SCB_I2C_DEFAULT_TX into TX FIFO */
        numToCopy = (context->useTxFifo) ? Cy_SCB_GetFifoSize(base) : 1UL;

        numToCopy = Cy_SCB_WriteDefaultArray(base, CY_SCB_I2C_DEFAULT_TX, numToCopy);
        context->slaveTxBufferIdx += numToCopy;

        context->slaveStatus |= CY_SCB_I2C_SLAVE_RD_UNDRFL;
    }
    else
    {
        if (context->slaveTxBufferSize > 1UL)
        {
            /* Get the number of bytes to copy into TX FIFO */
            numToCopy = (context->useTxFifo) ? (context->slaveTxBufferSize - 1UL) : (1UL);

            /* Write data into TX FIFO */
            numToCopy = Cy_SCB_WriteArray(base, context->slaveTxBuffer, numToCopy);
            context->slaveTxBufferIdx  += numToCopy;
            context->slaveTxBufferSize -= numToCopy;
            context->slaveTxBuffer      = &context->slaveTxBuffer[numToCopy];
        }

        /* Put the last byte */
        if ((CY_SCB_I2C_FIFO_SIZE != Cy_SCB_GetNumInTxFifo(base)) && (1UL == context->slaveTxBufferSize))
        {

            /* Put the last data byte in the TX FIFO and clear the TX Underflow
            * interrupt source inside the critical section to ensure that the
            * TX Underflow interrupt will trigger after all data bytes from the
            * TX FIFO are transferred onto the bus.
            */
            //Cy_SysLib_EnterCriticalSection();

            Cy_SCB_WriteTxFifo     (base, (uint32_t) context->slaveTxBuffer[0UL]);
            Cy_SCB_ClearTxInterrupt(base, CY_SCB_TX_INTR_UNDERFLOW);

            //Cy_SysLib_ExitCriticalSection(intrStatus);

            /* Move the pointers */
            ++context->slaveTxBufferIdx;
            context->slaveTxBufferSize = 0UL;
            context->slaveTxBuffer     = &context->slaveTxBuffer[1UL];

            /* Enable the TX underflow interrupt to catch when there is no data to send */
            Cy_SCB_SetTxInterruptMask(base, CY_SCB_TX_INTR_UNDERFLOW);

            if (context->useTxFifo)
            {
                /* Data is copied into TX FIFO */
                context->slaveStatus |= CY_SCB_I2C_SLAVE_RD_IN_FIFO;

            }
        }
    }
}

void SCB_I2C_SlaveInterrupt(CySCB_Type *base, cy_stc_scb_i2c_context_t *context)
{
    uint32_t slaveIntrStatus;

    bool slaveAddrInFifo = false;

    /* Handle the slave interrupt sources */
    slaveIntrStatus = SCB_INTR_S_MASKED(base);

    /* Handle the error conditions */
    if (0UL != ((CY_SCB_SLAVE_INTR_I2C_BUS_ERROR | CY_SCB_SLAVE_INTR_I2C_ARB_LOST) & slaveIntrStatus))
    {
        /* Update the status */
        context->slaveStatus |= (0UL != (CY_SCB_SLAVE_INTR_I2C_BUS_ERROR & slaveIntrStatus)) ? CY_SCB_I2C_SLAVE_BUS_ERR : CY_SCB_I2C_SLAVE_ARB_LOST;

        /* Disable the RX interrupt source to drop data into RX FIFO if any */
        SCB_INTR_RX_MASK(base) = CY_SCB_CLEAR_ALL_INTR_SRC;

        /* Add the stop status to back into the default state and set completion statuses */
        slaveIntrStatus |= CY_SCB_SLAVE_INTR_I2C_STOP;
    }
    else
    {
        if (0UL != (CY_SCB_SLAVE_INTR_I2C_STOP & slaveIntrStatus))
        {
            /* Get data from the RX FIFO after a stop is generated if there is
            * space to store it.
            */
            if (((((uint32_t)(SCB_RX_FIFO_STATUS(base)) & SCB_RX_FIFO_STATUS_USED_Msk) >> SCB_RX_FIFO_STATUS_USED_Pos) > 0UL) \
                && (context->slaveRxBufferSize > 0UL))
            {
                SCB_INTR_RX_SET(base) = CY_SCB_RX_INTR_LEVEL;
                SCB_INTR_RX_MASK(base) = CY_SCB_RX_INTR_LEVEL;
            }
        }
    }


    /* Handle the receive direction (master writes data) */
    if (0UL != (CY_SCB_RX_INTR_LEVEL & SCB_INTR_RX_MASKED(base)))
    {
        /* Check if SCB configured to accept the slave address in the RX FIFO */
        if (((SCB_CTRL(base)) & (SCB_CTRL_ADDR_ACCEPT_Msk)) != 0UL)
        {
            slaveAddrInFifo = (0UL != (CY_SCB_SLAVE_INTR_I2C_ADDR_MATCH &
                                    SCB_INTR_S_MASKED(base)));
        }

        /* Process data bytes, but skip processing in case slave address is in RX FIFO.
        *  Leave the address to be processed by the function SlaveHandleAddress().
        */
        if (!slaveAddrInFifo)
        {
            SlaveHandleDataReceive(base, context);

            SCB_INTR_RX(base) = CY_SCB_RX_INTR_LEVEL;
            (void) SCB_INTR_RX(base);
        }
    }

    /* Handle the transfer completion */
    if (0UL != (CY_SCB_SLAVE_INTR_I2C_STOP & slaveIntrStatus))
    {
        SlaveHandleStop(base, slaveAddrInFifo, context);

        SCB_INTR_S(base) = CY_SCB_SLAVE_INTR_I2C_STOP;
        (void) SCB_INTR_S(base);

        /* Update the slave interrupt status */
        slaveIntrStatus = SCB_INTR_S_MASKED(base);
    }

    /* Handle the address reception */
    if (0UL != (CY_SCB_I2C_SLAVE_INTR_ADDR & slaveIntrStatus))
    {
        SlaveHandleAddress(base, context);

        Cy_SCB_ClearI2CInterrupt(base, CY_SCB_I2C_INTR_WAKEUP);
        Cy_SCB_ClearSlaveInterrupt(base, CY_SCB_I2C_SLAVE_INTR_ADDR);
    }

    /* Handle the transmit direction (master reads data) */
    if (0UL != (CY_SCB_I2C_SLAVE_INTR_TX & SCB_INTR_TX_MASKED(base)))
    {
        SlaveHandleDataTransmit(base, context);

        Cy_SCB_ClearTxInterrupt(base, CY_SCB_TX_INTR_LEVEL);
    }
}

uint32_t Cy_SCB_I2C_SlaveGetStatus(CySCB_Type const *base, cy_stc_scb_i2c_context_t const *context)
{
    /* Suppress a compiler warning about unused variables */
    base = base;

    return (context->slaveStatus);
}





