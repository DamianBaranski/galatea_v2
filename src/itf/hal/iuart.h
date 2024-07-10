#ifndef IUART_H
#define IUART_H
#include <cstdint>
#include <functional>

class IUart {
    public:
    virtual bool send(const uint8_t *data, std::size_t len) = 0;
    virtual bool isSending() const = 0;
    virtual void registerTxCallback(std::function<void()> callback) = 0;
};

#endif