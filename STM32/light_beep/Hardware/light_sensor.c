#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include <stdint.h>

#define LIGHTSENSOR_PIN GPIO_Pin_13

void LightSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = LIGHTSENSOR_PIN; // Assuming Key is connected to PB0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Input with Pull-Up
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t LightSensor_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOB, LIGHTSENSOR_PIN);
}
