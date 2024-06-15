/*

 * uart.h
 *
 *  Created on: Apr 1, 2024
 *      Author: Nilesh


#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"
#include "stm32f446xx.h"

#define BAUD_9600		9600
#define BAUD_38400		38400
#define BAUD_115200		115200

#define BAUD_BRR_9600	0x683
#define BAUD_BRR_38400	0x1A1
#define BAUD_BRR_115200	0x8B

void UartInit(uint32_t baud);
void UartPuts(char str[]);

#endif  UART_H_
*/
