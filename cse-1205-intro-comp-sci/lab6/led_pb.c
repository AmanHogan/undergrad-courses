#include <stdio.h>
#include <stdlib.h>
#include "sysfs_gpio.h"

int main(void)
{
	int LED_pin = 4;
	int switch_pin = 22;
	
	int LED_value = 0;
	
	gpioOutput(LED_pin);
	gpioInput(switch_pin);
	
	gpioWrite(LED_pin, 1);
	
	while(!gpioRead(switch_pin));


	gpioWrite(LED_pin, LED_value);
	
	return 0;
}



