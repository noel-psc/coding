#include "motor.h"
#include "stm32f10x.h"
#include "PWM.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5; // Assuming motor control pins
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	PWM_Init(); // Initialize PWM for servo control
}

void Motor_SetSpeed(int8_t speed)
{
	if (speed >= 0) {
		GPIO_SetBits(GPIOA, GPIO_Pin_4); // Forward
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		PWM_SetDutyCycle(speed);
	} else {
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5); // Reverse
		PWM_SetDutyCycle(-speed);
	}
}
