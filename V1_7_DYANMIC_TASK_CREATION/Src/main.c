#include "led.h"
#include "uart.h"
#include "osKernel.h"

#define QUANTA 2

typedef uint32_t TaskProfiler;

TaskProfiler Task0_Profiler, Task1_Profiler, Task2_Profiler, pTask1_Profiler, pTask2_Profiler, Task4_Profiler, Task5_Profiler, Task6_Profiler, Task7_Profiler;

int32_t semaphore1, semaphore2, semaphore4;

void motor_run(void);
void motor_stop(void);
void valve_open(void);
void valve_close(void);

void task3(void)
{
    pTask1_Profiler++;
}

void task0(void)
{
    while (1)
    {
        Task0_Profiler++;
        led_init();
        led_on();
        for (int i = 0; i < 90000; i++) {}
        led_off();
        for (int i = 0; i < 90000; i++) {}
    }
}

void task1(void)
{
    while (1)
    {
        osSemaphoreWait(&semaphore1);
        motor_run();
        Task1_Profiler++;
        osSemaphoreSet(&semaphore2);
    }
}

void task2(void)
{
    while (1)
    {
        osSemaphoreWait(&semaphore2);
        valve_open();
        Task2_Profiler++;
        osSemaphoreSet(&semaphore1);
    }
}

void task4(void)
{
	while(1){
    Task4_Profiler++;
}}

void task5(void)
{
	while(1){
    Task5_Profiler++;
}}

void task6(void)
{
	while(1){
    Task6_Profiler++;
}}

void task7(void)
{
    while (1)
    {
        // Task4 functionality
        Task7_Profiler++;
        // Example functionality: toggle an LED
        // led_toggle();
        // Delay to simulate task workload
        for (int i = 0; i < 90000; i++) {}
    }
}

void initializeSemaphores(void)
{
    osSemaphoreInit(&semaphore1, 1);
    osSemaphoreInit(&semaphore2, 0);
    osSemaphoreInit(&semaphore4, 1); // Initialize semaphore4 with a value of 1
}

int main(void)
{
    /* Initialize uart */
    uart_tx_init();

    /* Initialize hardware timer */
    tim2_1hz_interrupt_init();

    /* Initialize semaphores */
    initializeSemaphores();

    /* Initialize Kernel */
    osKernelInit();

    /* Add Threads */
    osKernelAddThreads(&task0, &task1, &task2);

    /* Add the new task */
    osKernelAddThread(&task7);
    osKernelAddThread(&task4);
    osKernelAddThread(&task5);
    osKernelAddThread(&task6);

    /* Set RoundRobin time quanta */
    osKernelLaunch(QUANTA);

    while (1) {
        // Main loop
    }
}

void TIM2_IRQHandler(void)
{
    /* Clear update interrupt flag */
    TIM2->SR &= ~SR_UIF;

    /* Do something */
    pTask2_Profiler++;
}

void motor_run(void)
{
    printf("Motor is starting...\n\r");
}

void motor_stop(void)
{
    printf("Motor is stopping...\n\r");
}

void valve_open(void)
{
    printf("Valve is opening...\n\r");
}

void valve_close(void)
{
    printf("Valve is closing...\n\r");
}


// Final completed at 14-09-2024 
