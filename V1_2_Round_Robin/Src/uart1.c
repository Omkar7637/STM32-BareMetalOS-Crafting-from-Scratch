/*

 * uart.c
 *
 *  Created on: Apr 1, 2024
 *      Author: Nilesh

#include <stdio.h>
#include "uart1.h"
#include "stm32f4xx.h""

#define TX_PIN	2
#define RX_PIN	3
#define USART_ALT_FN	7

void UartInit(uint32_t baud) {
	// UART GPIO Init -- PA.2 (Tx) and PA.3 (Rx)
	// enable clock
	RCC->AHB1ENR |= BV(RCC_AHB1ENR_GPIOAEN_Pos);
	//	alt fn = 0111 = 7 (Uart Tx and Rx)
	GPIOA->AFR[0] |= ((USART_ALT_FN << GPIO_AFRL_AFSEL3_Pos) | (USART_ALT_FN << GPIO_AFRL_AFSEL2_Pos));
	// 	mode=10 (alt fn), speed=00 (low), pupdr=00 (none), typer=0 (push-pull)
	GPIOA->MODER |= (BV(TX_PIN * 2 + 1) | BV(RX_PIN * 2 + 1));
	GPIOA->MODER &= ~(BV(TX_PIN * 2) | BV(RX_PIN * 2));
	GPIOA->OSPEEDR &= ~(BV(TX_PIN * 2) | BV(TX_PIN * 2 + 1) | BV(RX_PIN * 2) | BV(RX_PIN * 2 + 1));
	GPIOA->PUPDR &= ~(BV(TX_PIN * 2) | BV(TX_PIN * 2 + 1) | BV(RX_PIN * 2) | BV(RX_PIN * 2 + 1));
	GPIOA->OTYPER &= ~(BV(TX_PIN) | BV(RX_PIN));

	// UART Config
	// enable uart clock
	RCC->APB1ENR |= BV(RCC_APB1ENR_USART2EN_Pos);
	// tx en (TE=1), rx en (RE=1), wordlen=8 (M=0), OVER8=0, disable parity (PCE=0)
	USART2->CR1 = BV(USART_CR1_TE_Pos) | BV(USART_CR1_RE_Pos);
	// 1 stop bit (STOP=00), disable clock (CLKEN=0)
	USART2->CR2 = 0x00000000;
	// no hw control, no irda, no dma, no interupts
	USART2->CR3 = 0x00000000;
	// set BRR for given baud rate
	switch(baud) {
		case BAUD_9600:
			USART2->BRR = BAUD_BRR_9600;
			break;
		case BAUD_38400:
			USART2->BRR = BAUD_BRR_38400;
			break;
		case BAUD_115200:
			USART2->BRR = BAUD_BRR_115200;
			break;
	}
	// enable uart interrupt in nvic
	NVIC_EnableIRQ(USART2_IRQn);
	// uart enable (UE=1)
	USART2->CR1 |= BV(USART_CR1_UE_Pos);
}

char *tx_string;
int tx_index = 0;
volatile int tx_complete = 1;
void UartPuts(char str[]) {
	// wait for last string completion
	while(!tx_complete)
		;
	tx_complete = 0;
	tx_string = str;
	// send first char
	tx_index = 0;
	USART2->DR = tx_string[tx_index];
	tx_index++;
	// enable uart txeie interrupt
	USART2->CR1 |= BV(USART_CR1_TXEIE_Pos);
}
void USART2_IRQHandler(void) {
	// check if last char tx
	if((USART2->SR & BV(USART_SR_TXE_Pos)) != 0) {
		// send next char if available
		if(tx_string[tx_index] != '\0') {
			USART2->DR = tx_string[tx_index];
			tx_index++;
		}
		else {
			tx_string = NULL;
			tx_complete = 1;
			// disable uart txeie interrupt
			USART2->CR1 &= ~BV(USART_CR1_TXEIE_Pos);
		}
	}
}




*/
