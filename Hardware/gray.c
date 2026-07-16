#include "headfile.h"

GRAY_Struct gray = {0};

void Gray_Update(void) 
{
	gray.io[0] = DL_GPIO_readPins(Gray_IO_0_PORT, Gray_IO_0_PIN) ? 1 : 0;
	gray.io[1] = DL_GPIO_readPins(Gray_IO_1_PORT, Gray_IO_1_PIN) ? 1 : 0;
	gray.io[2] = DL_GPIO_readPins(Gray_IO_2_PORT, Gray_IO_2_PIN) ? 1 : 0;
	gray.io[3] = DL_GPIO_readPins(Gray_IO_3_PORT, Gray_IO_3_PIN) ? 1 : 0;
	gray.io[4] = DL_GPIO_readPins(Gray_IO_4_PORT, Gray_IO_4_PIN) ? 1 : 0;
	gray.io[5] = DL_GPIO_readPins(Gray_IO_5_PORT, Gray_IO_5_PIN) ? 1 : 0;
	gray.io[6] = DL_GPIO_readPins(Gray_IO_6_PORT, Gray_IO_6_PIN) ? 1 : 0;
	gray.io[7] = DL_GPIO_readPins(Gray_IO_7_PORT, Gray_IO_7_PIN) ? 1 : 0;
}

