#include "stm32f10x.h"
#include <stdint.h>

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11; // Assuming Key is connected to PB0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Input with Pull-Up
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Key_Scan(uint16_t pin)
{
	if (GPIO_ReadInputDataBit(GPIOB, pin) == Bit_RESET) // Active Low
	{
		while (GPIO_ReadInputDataBit(GPIOB, pin) == Bit_RESET); // Wait for release
		return 1; // Key pressed
	}
	return 0; // Key not pressed
}
