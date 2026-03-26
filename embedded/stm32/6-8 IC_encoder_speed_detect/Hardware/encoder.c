#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "encoder.h"

void Encoder_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // Assuming LED is connected to PA5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure TIM2 */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseStructure.TIM_Period = 65536 - 1; // ARR
	TIM_TimeBaseStructure.TIM_Prescaler = 1 - 1; // PSC
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	// TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);

	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
	TIM_ICInit(TIM3, &TIM_ICInitStruct);

	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

	TIM_Cmd(TIM3, ENABLE);
}

int16_t Encoder_Get(void)
{
	int16_t encoder_count = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3, 0);
	return encoder_count;
}
