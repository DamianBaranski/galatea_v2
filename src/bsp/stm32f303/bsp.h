#ifndef BSP_H
#define BSP_H
#include "igpio.h"
#include "ii2c_master.h"
#include "iuart.h"
#include <memory>

class Bsp {
	public:
		Bsp();
		std::unique_ptr<II2cMaster> i2cBus;
		std::unique_ptr<IUart> uartBus;

	private:
		std::unique_ptr<IGpio> mSdaPin;
		std::unique_ptr<IGpio> mSclPin;
		std::unique_ptr<IGpio> mRxPin;
		std::unique_ptr<IGpio> mTxPin;

		void initClock();
		void initDistanceSensors();
};

#endif
