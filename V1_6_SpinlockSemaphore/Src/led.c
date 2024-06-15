#include "led.h"


#define GPIOAEN			(1U<<0)//  0b 0000 0000 0000 0000 0000 0000 0000 0001
#define LED_PIN			(1U<<5)

void led_init(void)
{
	/*Enable clock access to led port (Port A)*/

	//Example of 'friendly' programming
	// Initial state =    0b 0000 0000 0000 0000 1100 0000 0000 0000
	//Set bit0 = (1u<<0)= 0b 0000 0000 0000 0000 0000 0000 0000 0001
	//final state =  Initial state OR Set bit0  =  0b 0000 0000 0000 0000 1100 0000 0000 0001

	RCC->AHB1ENR  |= GPIOAEN;




	/*Set led pin as output pin*/
	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &= ~(1U<<11);

}


void led_on(void)
{
	/*Set led pin HIGH (PA5)*/
	GPIOA->ODR |= LED_PIN;
}


void led_off(void)
{
	/*Set led pin LOW (PA5)*/
	GPIOA->ODR &= ~LED_PIN;

}
