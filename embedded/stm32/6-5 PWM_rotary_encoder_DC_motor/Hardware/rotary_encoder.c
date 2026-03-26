#include "stm32f10x.h"
#include <stdint.h>

#define GPIO_ENCODER_A GPIO_Pin_10
#define GPIO_ENCODER_B GPIO_Pin_11
#define EXTI_ENCODER_A EXTI_Line10
#define EXTI_ENCODER_B EXTI_Line11

int16_t encoder_count = 0;

void RotaryEncoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_ENCODER_A | GPIO_ENCODER_B;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Input with pull-down
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_ENCODER_A | EXTI_ENCODER_B;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // Trigger on rising edge
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

int16_t RotaryEncoder_GetCount(void)
{
	int16_t temp = encoder_count;
	encoder_count = 0;
	return temp;
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_ENCODER_A) != RESET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_ENCODER_A) == Bit_RESET)
		{
			// Handle rotary encoder A channel interrupt
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_ENCODER_B) == Bit_SET)
			{
				encoder_count++;
			}
		}
		EXTI_ClearITPendingBit(EXTI_ENCODER_A);
	}
	if (EXTI_GetITStatus(EXTI_ENCODER_B) != RESET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_ENCODER_B) == Bit_RESET)
		{
			// Handle rotary encoder B channel interrupt
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_ENCODER_A) == Bit_SET)
			{
				encoder_count--;
			}
		}
		EXTI_ClearITPendingBit(EXTI_ENCODER_B);
	}
}
