#ifndef __OSKERNEL_H__
#define __OSKERNEL_H__
#include <stdint.h>
#include "stm32f446xx.h"

#define NUM_OF_THREADS 10
#define STACKSIZE 400
#define BUS_FREQ 16000000
#define CTRL_ENABLE (1U << 0)
#define CTRL_TICKINT (1U << 1)
#define CTRL_CLCKSRC (1U << 2)
#define CTRL_COUNTFLAG (1U << 16)
#define SYSTICK_RST 0
#define TIM2EN (1U << 0)
#define CR1_CEN (1U << 0)
#define DIER_UIE (1U << 0)
#define INTCTRL (*((volatile uint32_t *)0xE000ED04))
#define PENDSTSET (1U << 26)

// Define the task function pointer type
typedef void (*TaskFunction)(void);

void tim2_1hz_interrupt_init(void);
void osKernelInit(void);
void osKernelLaunch(uint32_t quanta);
uint8_t osKernelAddThread(TaskFunction task);
void osThreadYield(void);

void osSemaphoreInit(int32_t *semaphore, int32_t value);
void osSemaphoreSet(int32_t *semaphore);
void osSemaphoreWait(int32_t *semaphore);

#endif
