#include "uart.h"
#include <cassert>

std::function<void()> txCallbacks[4] = {};
UART_HandleTypeDef *uartHandlers[4] = {};

Uart::Uart(USART_TypeDef *instance, uint32_t baudrate)
{
    if (instance == USART1)
    {
        __USART1_CLK_ENABLE();
    }
    else if (instance == USART2)
    {
        __USART2_CLK_ENABLE();
    }
    else if (instance == USART3)
    {
        __USART3_CLK_ENABLE();
    }
    else if (instance == UART4)
    {
        __UART4_CLK_ENABLE();
    }
    else if (instance == UART5)
    {
        __UART5_CLK_ENABLE();
    }
    else
    {
        assert("Uart instance not supported");
    }

    uartHandlers[uartInstanceToIndex(instance)] = &mHandle;

    mHandle.Instance = instance;
    mHandle.Init.BaudRate = baudrate;
    mHandle.Init.WordLength = UART_WORDLENGTH_8B;
    mHandle.Init.StopBits = UART_STOPBITS_1;
    mHandle.Init.Parity = UART_PARITY_NONE;
    mHandle.Init.Mode = UART_MODE_TX_RX;
    mHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    mHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    mHandle.Init.OneBitSampling = UART_ONEBIT_SAMPLING_DISABLED;
    mHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    HAL_UART_Init(&mHandle);

    /* Peripheral interrupt init*/
    HAL_NVIC_SetPriority(USART3_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
}

Uart::~Uart()
{
}

bool Uart::send(const uint8_t *data, std::size_t len)
{
    return HAL_UART_Transmit_IT(&mHandle, const_cast<uint8_t *>(data), len) == HAL_OK;
}

bool Uart::isSending() const
{
    return mHandle.State == HAL_UART_STATE_BUSY_TX || mHandle.State == HAL_UART_STATE_BUSY_TX_RX;
}

void Uart::registerTxCallback(std::function<void()> callback)
{
    size_t idx = Uart::uartInstanceToIndex(mHandle.Instance);
    txCallbacks[idx] = callback;
}

size_t Uart::uartInstanceToIndex(USART_TypeDef *instance)
{
    if (instance == USART1)
    {
        return 0;
    }
    else if (instance == USART2)
    {
        return 1;
    }
    else if (instance == USART3)
    {
        return 2;
    }
    else if (instance == UART4)
    {
        return 3;
    }
    else if (instance == UART5)
    {
        return 4;
    }
    else
    {
        assert("Uart instance not supported");
    }
    return 0;
}

extern "C"
{

    void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
    {
        size_t idx = Uart::uartInstanceToIndex(huart->Instance);
        if (txCallbacks[idx])
        {
            txCallbacks[idx]();
        }
    }

    void USART3_IRQHandler(void)
    {
        size_t idx = Uart::uartInstanceToIndex(USART3);
        if (uartHandlers[idx])
        {
            HAL_UART_IRQHandler(uartHandlers[idx]);
        }
    }
}