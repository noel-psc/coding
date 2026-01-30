#ifndef __UART_H
#define __UART_H

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdarg.h>

void UART_Init(void);
void UART_SendByte(uint8_t byte);
void UART_SendArray(uint8_t *arr, uint16_t len);
void UART_SendString(const char *str);
void UART_SendNumber(uint32_t num, uint8_t len);
void UART_Printf(const char *format, ...);
uint8_t UART_GetRxFlag(void);
uint8_t UART_GetRxData(void);

#endif
