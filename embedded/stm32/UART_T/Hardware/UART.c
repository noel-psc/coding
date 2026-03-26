#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "UART.h"

#define UART_BAUDRATE 9600
#define UART_PIN_TX GPIO_Pin_9  // PA9
#define UART_PIN_RX GPIO_Pin_10 // PA10
#define UART_GPIO_PORT GPIOA
#define UART_USART_PORT USART1
#define MAX 128

void UART_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = UART_PIN_TX; // TX
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(UART_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = UART_PIN_RX; // RX
	GPIO_Init(UART_GPIO_PORT, &GPIO_InitStruct);

	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = UART_BAUDRATE;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(UART_USART_PORT, &USART_InitStruct);

	USART_Cmd(UART_USART_PORT, ENABLE);
}

void UART_SendByte(uint8_t byte)
{
	while (USART_GetFlagStatus(UART_USART_PORT, USART_FLAG_TXE) == RESET);
	USART_SendData(UART_USART_PORT, byte);
}

void UART_SendArray(uint8_t *arr, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++)
	{
		UART_SendByte(arr[i]);
	}
}

void UART_SendString(const char *str)
{
	while (*str)
	{
		UART_SendByte((uint8_t)(*str));
		str++;
	}
}

uint32_t UART_Pow(uint32_t base, uint32_t exp)
{
	uint32_t result = 1;
	for (uint32_t i = 0; i < exp; i++)
	{
		result *= base;
	}
	return result;
}

void UART_SendNumber(uint32_t num, uint8_t len)
{
	for (int8_t i = len - 1; i >= 0; i--)
	{
		uint32_t divisor = UART_Pow(10, i);
		int8_t digit = (num / divisor) % 10;
		UART_SendByte(digit + '0');
	}
}

int fputc(int ch, FILE *f)
{
	UART_SendByte(ch);
	return ch;
}

int _write(int file, char *ptr, int len)
{
    if (file == STDOUT_FILENO || file == STDERR_FILENO)
    {
        for (int i = 0; i < len; i++)
        {
            UART_SendByte(ptr[i]);
        }
        return len;
    }
    
    // 不是标准输出/错误，返回错误
    errno = EBADF;
    return -1;
}

void UART_Printf(const char *format, ...)
{
	char buffer[MAX]; // 临时缓冲区
	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);
	UART_SendString(buffer);
}
