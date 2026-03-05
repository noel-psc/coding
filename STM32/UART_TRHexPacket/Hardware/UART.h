#ifndef __UART_H
#define __UART_H

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdarg.h>

#define PAK_SIZE 4
extern uint8_t UART_RxPacket[PAK_SIZE];

void UART_Init(void);
void UART_SendByte(uint8_t byte);
void UART_SendArray(uint8_t *arr, uint16_t len);
void UART_SendString(const char *str);
void UART_SendNumber(uint32_t num, uint8_t len);
void UART_Printf(const char *format, ...);
uint8_t UART_GetRxFlag(void);
void UART_SendPacket(uint8_t *packet, uint8_t len);
uint8_t UART_GetRxFlag(void);

#endif
