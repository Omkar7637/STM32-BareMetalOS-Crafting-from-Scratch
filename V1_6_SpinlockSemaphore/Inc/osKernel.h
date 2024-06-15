#ifndef __OSKERNEL_H__
#define __OSKERNEL_H__
#include <stdint.h>
#include "stm32f446xx.h"

#define PERIOD 100   /*Period is 100*quanta, e.g. quanta =10-> 100*10 = 1000*/
#define SR_UIF		(1U<<0)

void tim2_1hz_interrupt_init(void);


void osKernelInit(void);
void osKernelLaunch(uint32_t quanta);
uint8_t osKernelAddThreads(void(*task0)(void),void(*task1)(void),void(*task2)(void));
void osThreadYield(void);
void task3(void);


void osSemaphoreInit(int32_t *semaphore, int32_t value);
void osSemaphoreSet(int32_t * semaphore);
void osSemaphoreWait(int32_t * semaphore);

#endif
