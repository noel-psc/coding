#include "stm32f10x.h"
#include <stdint.h>

#define GPIO_ENCODER_A GPIO_Pin_0
#define GPIO_ENCODER_B GPIO_Pin_1
#define EXTI_ENCODER_A EXTI_Line0
#define EXTI_ENCODER_B EXTI_Line1

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

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // Trigger on rising edge
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_Init(&NVIC_InitStructure);
}

int16_t RotaryEncoder_GetCount(void)
{
	int16_t temp = encoder_count;
	encoder_count = 0;
	return temp;
}

void EXTI0_IRQHandler(void)
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
}

void EXTI1_IRQHandler(void)
{
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
