#include "led.h"
#include "uart.h"
#include "timebase.h"


void motor_run(void);
void motor_stop(void);
void valve_open(void);
void valve_close(void);


int motor_main(void)
{
	while(1)
	{
		motor_run();
		delay(1);
		motor_stop();
		delay(1);
	}
}

int valve_main(void)
{
	while(1)
	{
		valve_open();
		delay(1);
		valve_close();
		delay(1);
	}
}
int main(void)
{
	uint32_t volatile start  = 0U;
	led_init();
	uart_tx_init();
	timebase_init();


	if(start)
	{
		motor_main();

	}
	else{
		valve_main();
	}

	while(1)
	{


	}
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

