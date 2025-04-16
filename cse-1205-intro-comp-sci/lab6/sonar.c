#include <stdio.h>
#include <stdlib.h>
#include "sysfs_gpio.h"

int main(void)
{

	int TRIGGER_pin = 4;
	int ECHO_pin = 17;
	
	gpioOutput(TRIGGER_pin);
	gpioInput(ECHO_pin);
	
	int TRIGGER_Signal = 1;
	TRIGGER_Signal = 0;
	
	int counter = 0;
	
	while(TRIGGER_Signal == 1)
	{
		
	}

	while(TRIGGER_Signal == 0)
	{
		counter++;
	}
	
	printf("%d", counter);

	return 0;
}
