#ifndef UART_H
#define UART_H

#include "iuart.h"
#include "stm32f3xx_hal.h"

class Uart: public IUart {
    public:
    Uart(USART_TypeDef *instance, uint32_t baudrate);
    ~Uart();
    virtual bool send(const uint8_t*, std::size_t);
    virtual bool isSending() const;
    virtual void registerTxCallback(std::function<void()> callback);
    static size_t uartInstanceToIndex(USART_TypeDef *instance);
    private:
    UART_HandleTypeDef mHandle;
};

#endif