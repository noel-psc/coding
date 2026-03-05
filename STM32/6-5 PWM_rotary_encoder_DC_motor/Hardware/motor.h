#ifndef __MOTOR_H
#define __MOTOR_H
#include <stdint.h>

void Motor_Init(void);
void Motor_SetSpeed(int8_t speed); // Speed range: -100 to 100

#endif
