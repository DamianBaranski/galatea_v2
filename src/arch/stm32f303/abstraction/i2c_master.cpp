#include "i2c_master.h"
#include "cassert"

I2cMaster::I2cMaster(I2C_TypeDef *instance) {
    if(instance == I2C1) {
            __I2C1_CLK_ENABLE();
    } else if(instance == I2C2) {
            __I2C2_CLK_ENABLE();
    } else {
        assert("Unsuported I2C instance");
    }

    mI2cHandler.Instance = instance;
	mI2cHandler.Init.Timing = 0x2000090E;
	mI2cHandler.Init.OwnAddress1 = 0;
	mI2cHandler.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	mI2cHandler.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
	mI2cHandler.Init.OwnAddress2 = 0;
	mI2cHandler.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	mI2cHandler.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
	mI2cHandler.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
	HAL_I2C_Init(&mI2cHandler);

	/**Configure Analogue filter
	 */
	HAL_I2CEx_AnalogFilter_Config(&mI2cHandler, I2C_ANALOGFILTER_ENABLED);
}

I2cMaster::~I2cMaster() {
    if(mI2cHandler.Instance == I2C1) {
            __I2C1_CLK_DISABLE();
    } else if(mI2cHandler.Instance == I2C2) {
            __I2C2_CLK_DISABLE();
    } else {
        assert("Unsuported I2C instance");
    }
}