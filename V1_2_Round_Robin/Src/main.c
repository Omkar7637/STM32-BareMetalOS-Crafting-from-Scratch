#include "led.h"
#include "uart.h"
#include "osKernel.h"


#define		QUANTA		10

typedef uint32_t TaskProfiler;

TaskProfiler Task0_Profiler,Task1_Profiler,Task2_Profiler;

void motor_run(void);
void motor_stop(void);
void valve_open(void);
void valve_close(void);


void task0(void)
{
	while(1)
	{
		Task0_Profiler++;
		printf("Uart is working\n\r");
		for(int i = 0; i<90000; i++){}

		//motor_run();
	}
}


void task1(void)
{
	while(1)
	{
		Task1_Profiler++;
		led_init();
		led_on();
		for(int i = 0; i<90000; i++){}
		led_off();
		for(int i = 0; i<90000; i++){}
		//valve_open();
	}
}

void task2(void)
{
	while(1)
	{
		Task2_Profiler++;
		for(int i = 0; i<90000; i++){}
	}
}

int main(void)
{


	uart_tx_init();
	led_init();

	/*Initialize Kernel*/
	osKernelInit();
	/*Add Threads*/
	osKernelAddThreads(&task0,&task1,&task2);

	/*Set RoundRobin time quanta*/
	osKernelLaunch(QUANTA);


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


