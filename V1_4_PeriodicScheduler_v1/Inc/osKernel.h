#ifndef __OSKERNEL_H__
#define __OSKERNEL_H__
#include <stdint.h>
#include "stm32f446xx.h"
#include "stm32f4xx.h"

#define PERIOD 100

void osKernelInit(void);
void osKernelLaunch(uint32_t quanta);
uint8_t osKernelAddThreads(void(*task0)(void),void(*task1)(void),void(*task2)(void));
void osThreadYield(void);
void task3(void);

#endif
