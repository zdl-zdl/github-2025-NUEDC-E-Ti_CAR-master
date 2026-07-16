#include "encoder.h"

int encoder_left_count = 0;
int encoder_right_count = 0;

/*
		E1A E1B: encoder_left_count   (GPIOB.4 / GPIOB.5)
		E2A E2B: encoder_right_count  (GPIOB.23 / GPIOB.12)
		两个编码器均挂在 GPIOB 组中断上
*/

void EncoderInit(void)
{
	NVIC_ClearPendingIRQ(GPIO_MULTIPLE_GPIOB_INT_IRQN);
	NVIC_EnableIRQ(GPIO_MULTIPLE_GPIOB_INT_IRQN);
	NVIC_ClearPendingIRQ(GPIO_MULTIPLE_GPIOB_INT_IRQN);
	NVIC_EnableIRQ(GPIO_MULTIPLE_GPIOB_INT_IRQN);
}

/*******************************************************
功能：外部中断模块采集编码器A/B相信号（两路均在GPIOB）
***********************************************************/

void GROUP1_IRQHandler(void)
{
	uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(GPIOB,
		Encoder_left_E1A_PIN  | Encoder_left_E1B_PIN |
		Encoder_right_E2A_PIN | Encoder_right_E2B_PIN);

	// 左编码器 E1A/E1B (GPIOB)
	if ((gpioB & Encoder_left_E1A_PIN) == Encoder_left_E1A_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_left_PORT, Encoder_left_E1B_PIN))
			encoder_left_count--;
		else
			encoder_left_count++;
		DL_GPIO_clearInterruptStatus(Encoder_left_PORT, Encoder_left_E1A_PIN);
	}
	else if ((gpioB & Encoder_left_E1B_PIN) == Encoder_left_E1B_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_left_PORT, Encoder_left_E1A_PIN))
			encoder_left_count++;
		else
			encoder_left_count--;
		DL_GPIO_clearInterruptStatus(Encoder_left_PORT, Encoder_left_E1B_PIN);
	}

	// 右编码器 E2A/E2B (GPIOB)
	if ((gpioB & Encoder_right_E2A_PIN) == Encoder_right_E2A_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_right_PORT, Encoder_right_E2B_PIN))
			encoder_right_count--;
		else
			encoder_right_count++;
		DL_GPIO_clearInterruptStatus(Encoder_right_PORT, Encoder_right_E2A_PIN);
	}
	else if ((gpioB & Encoder_right_E2B_PIN) == Encoder_right_E2B_PIN)
	{
		if (!DL_GPIO_readPins(Encoder_right_PORT, Encoder_right_E2A_PIN))
			encoder_right_count++;
		else
			encoder_right_count--;
		DL_GPIO_clearInterruptStatus(Encoder_right_PORT, Encoder_right_E2B_PIN);
	}
}

