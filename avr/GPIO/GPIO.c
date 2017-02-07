/*
* GPIO.c
*
* Created: 05.02.2017 23:08:10
*  Author: Peter Buchegger
*/
#include <inttypes.h>

#include "GPIO/GPIO.h"

gpio_t gpio[8][8] =
{
	[ePORTA] = {
		{ .ddr = &DDRA, .port = &PORTA, .pin = 0 },
		{ .ddr = &DDRA, .port = &PORTA, .pin = 1 },
		{ .ddr = &DDRA, .port = &PORTA, .pin = 2 },
		{ .ddr = &DDRA, .port = &PORTA, .pin = 3 },
		{ .ddr = &DDRA, .port = &PORTA, .pin = 4 },
		{ .ddr = &DDRA, .port = &PORTA, .pin = 5 },
		{ .ddr = &DDRA, .port = &PORTA, .pin = 6 },
		{ .ddr = &DDRA, .port = &PORTA, .pin = 7 },
	},
	[ePORTD] = {
		{ .ddr = &DDRD, .port = &PORTD, .pin = 0 },
		{ .ddr = &DDRD, .port = &PORTD, .pin = 1 },
		{ .ddr = &DDRD, .port = &PORTD, .pin = 2 },
		{ .ddr = &DDRD, .port = &PORTD, .pin = 3 },
		{ .ddr = &DDRD, .port = &PORTD, .pin = 4 },
		{ .ddr = &DDRD, .port = &PORTD, .pin = 5 },
		{ .ddr = &DDRD, .port = &PORTD, .pin = 6 },
		{ .ddr = &DDRD, .port = &PORTD, .pin = 7 },
	},
	[ePORTG] = {
		{ .ddr = &DDRG, .port = &PORTG, .pin = 0 },
		{ .ddr = &DDRG, .port = &PORTG, .pin = 1 },
		{ .ddr = &DDRG, .port = &PORTG, .pin = 2 },
		{ .ddr = &DDRG, .port = &PORTG, .pin = 3 },
		{ .ddr = &DDRG, .port = &PORTG, .pin = 4 },
		{ .ddr = &DDRG, .port = &PORTG, .pin = 5 },
		{ .ddr = &DDRG, .port = &PORTG, .pin = 6 },
		{ .ddr = &DDRG, .port = &PORTG, .pin = 7 },
	},
	[ePORTL] = {
		{ .ddr = &DDRL, .port = &PORTL, .pin = 0 },
		{ .ddr = &DDRL, .port = &PORTL, .pin = 1 },
		{ .ddr = &DDRL, .port = &PORTL, .pin = 2 },
		{ .ddr = &DDRL, .port = &PORTL, .pin = 3 },
		{ .ddr = &DDRL, .port = &PORTL, .pin = 4 },
		{ .ddr = &DDRL, .port = &PORTL, .pin = 5 },
		{ .ddr = &DDRL, .port = &PORTL, .pin = 6 },
		{ .ddr = &DDRL, .port = &PORTL, .pin = 7 },
	}
};

void set_output(gpio_t * gpio)
{
	(*gpio->ddr) |= (1 << gpio->pin);
}

void set_high(gpio_t * gpio)
{
	(*gpio->port) |= (1 << gpio->pin);
}

void set_low(gpio_t * gpio)
{
	(*gpio->port) &= ~(1 << gpio->pin);
}

void set_toggle(gpio_t * gpio)
{
	(*gpio->port) ^= (1 << gpio->pin);
}


void set_input(gpio_t * gpio)
{
	(*gpio->ddr) &= ~(1 << gpio->pin);
}

void activate_pullup(gpio_t * gpio)
{
	(*gpio->port) |= (1 << gpio->pin);
}

void deactivate_pullup(gpio_t * gpio)
{
	(*gpio->port) &= ~(1 << gpio->pin);
}

uint8_t get_status(gpio_t * gpio)
{
	return (((*gpio->port)) & (1 << gpio->pin));
}
