/*
 * UART_Test.c
 *
 * Created: 06.02.2017 01:12:00
 *  Author: Peter Buchegger
 */

#include "GPIO/GPIO.h"
#include "System.h"

int main(void)
{
	gpio_t * f0 = &gpio[ePORTF][0];
	set_output(f0);
	set_high(f0);
	
	gpio_t * f1 = &gpio[ePORTF][1];
	set_output(f1);
	set_low(f1);
	
	while(1)
	{
		set_toggle(f0);
		sleep(250);
	}
}
