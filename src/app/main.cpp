#include "bsp.h"
#include "logger.h"

UartStream *UartStream::mInstance = nullptr;

int main() {
	Bsp bsp;
	UartStream logStream(*bsp.uartBus);	
	Logger() << "Test message 1o";
	while(1);
	return 0;
}
