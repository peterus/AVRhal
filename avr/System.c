/*
 * System.c
 *
 * Created: 30.09.2014 23:24:57
 *  Author: Peter Buchegger
 */ 

#include <util/delay.h>
#include <avr/interrupt.h>

#include "System.h"

void sleep(uint16_t ms)
{
	for(; ms > 0; ms--)
	{
		_delay_ms(1);
	}
}

void interrupts(uint8_t enable)
{
	if(enable == 1)
	{
		sei();
	}
	else
	{
		cli();
	}
}

