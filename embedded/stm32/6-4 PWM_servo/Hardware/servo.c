#include "stm32f10x.h"
#include "PWM.h"

void Servo_Init(void)
{
	PWM_Init(); // Initialize PWM for servo control
}

void Servo_SetAngle(double angle)
{
	if (angle < 0) angle = 0; // Limit angle to 0 degrees
	if (angle > 180) angle = 180; // Limit angle to 180 degrees

	// Map angle (0-180) to duty cycle (1000-2000 microseconds)
	uint16_t duty = (uint16_t)(500 + (angle / 180.0) * 2000);
	PWM_SetDutyCycle(duty); // Set the corresponding duty cycle
}
