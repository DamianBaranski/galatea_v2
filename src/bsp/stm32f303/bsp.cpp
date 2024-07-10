#include "bsp.h"
#include "stm32f3xx_hal.h"
#include "gpio.h"
#include "i2c_master.h"
#include "uart.h"

Bsp::Bsp()
{
	initClock();
	mSdaPin.reset(new Gpio(GPIOB, GPIO_PIN_6, GPIO_MODE_AF_OD, GPIO_PULLUP, GPIO_AF4_I2C1));
	mSclPin.reset(new Gpio(GPIOB, GPIO_PIN_7, GPIO_MODE_AF_OD, GPIO_PULLUP, GPIO_AF4_I2C1));
	i2cBus.reset(new I2cMaster(I2C1));

	mRxPin.reset(new Gpio(GPIOB, GPIO_PIN_10, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3));
	mTxPin.reset(new Gpio(GPIOB, GPIO_PIN_11, GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3));
	uartBus.reset(new Uart(USART3, 115200));

	initDistanceSensors();
}

void Bsp::initClock()
{
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInit;

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = 16;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART3 | RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_TIM1 | RCC_PERIPHCLK_ADC12 | RCC_PERIPHCLK_ADC34;
	PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
	PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV2;
	PeriphClkInit.Adc34ClockSelection = RCC_ADC34PLLCLK_DIV2;
	PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
	PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

void Bsp::initDistanceSensors()
{
}

