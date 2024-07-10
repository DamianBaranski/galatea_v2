#ifndef LOGGER_H
#define LOGGER_H

#include "iuart.h"
#include "ring_buffer.h"
#include <cassert>
#include <cstring>


class UartStream {
    public:
        UartStream(IUart &uart):mUart(uart) {
            if(mInstance) {
                assert("Cannot create second instance");
            }
            mInstance = this;
            mUart.registerTxCallback([this](){this->txCompleted();});
        }

        void print(const char* str) {
            std::size_t len = strlen(str);
            mBuffer.push(reinterpret_cast<const uint8_t*>(str), len);
            send();
        }

        static UartStream *getInstance() {
            if(!mInstance) {
                assert("UartStream is not created");
            }
            return mInstance;
        }
    private:
    void txCompleted(){
        mBuffer.remove(mSending);
        if(!mBuffer.empty()) {
            send();
        }
    }
    void send() {
        if(mUart.isSending()) {
            return;
        }
        mSending = mBuffer.chunkSize();
        mUart.send(mBuffer.front(), mSending);
    }

    RingBuffer<uint8_t, 128> mBuffer;
    static UartStream *mInstance;
    IUart &mUart;
    size_t mSending;

};


class Logger {
    public:
    Logger(){};
    ~Logger(){operator<<("\r\n");}
    Logger& operator<<(const char* str) {
        UartStream::getInstance()->print(str);
        return *this;
    }
};

#endif