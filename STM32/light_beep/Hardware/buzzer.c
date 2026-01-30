#include "stm32f10x.h"

#define BUZZER_PIN GPIO_Pin_12

void  Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN; // Assuming buzzer is connected to PB12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, BUZZER_PIN); // Turn off buzzer initially
}

void Buzzer_On()
{
	GPIO_ResetBits(GPIOB, BUZZER_PIN);
}
void Buzzer_Off()
{
	GPIO_SetBits(GPIOB, BUZZER_PIN);
}
void Buzzer_Toggle()
{
	GPIO_WriteBit(GPIOB, BUZZER_PIN, (BitAction)!GPIO_ReadOutputDataBit(GPIOB, BUZZER_PIN));
}
