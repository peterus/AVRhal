/*
* GPIO.c
*
* Created: 05.02.2017 23:08:10
*  Author: Peter Buchegger
*/
#include <inttypes.h>

#include "GPIO/GPIO.h"

gpio_t gpio[ePORT_MAX][8] =
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
	[ePORTB] = {
		{ .ddr = &DDRB, .port = &PORTB, .pin = 0 },
		{ .ddr = &DDRB, .port = &PORTB, .pin = 1 },
		{ .ddr = &DDRB, .port = &PORTB, .pin = 2 },
		{ .ddr = &DDRB, .port = &PORTB, .pin = 3 },
		{ .ddr = &DDRB, .port = &PORTB, .pin = 4 },
		{ .ddr = &DDRB, .port = &PORTB, .pin = 5 },
		{ .ddr = &DDRB, .port = &PORTB, .pin = 6 },
		{ .ddr = &DDRB, .port = &PORTB, .pin = 7 },
	},
	[ePORTC] = {
		{ .ddr = &DDRC, .port = &PORTC, .pin = 0 },
		{ .ddr = &DDRC, .port = &PORTC, .pin = 1 },
		{ .ddr = &DDRC, .port = &PORTC, .pin = 2 },
		{ .ddr = &DDRC, .port = &PORTC, .pin = 3 },
		{ .ddr = &DDRC, .port = &PORTC, .pin = 4 },
		{ .ddr = &DDRC, .port = &PORTC, .pin = 5 },
		{ .ddr = &DDRC, .port = &PORTC, .pin = 6 },
		{ .ddr = &DDRC, .port = &PORTC, .pin = 7 },
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
	[ePORTE] = {
		{ .ddr = &DDRE, .port = &PORTE, .pin = 0 },
		{ .ddr = &DDRE, .port = &PORTE, .pin = 1 },
		{ .ddr = &DDRE, .port = &PORTE, .pin = 2 },
		{ .ddr = &DDRE, .port = &PORTE, .pin = 3 },
		{ .ddr = &DDRE, .port = &PORTE, .pin = 4 },
		{ .ddr = &DDRE, .port = &PORTE, .pin = 5 },
		{ .ddr = &DDRE, .port = &PORTE, .pin = 6 },
		{ .ddr = &DDRE, .port = &PORTE, .pin = 7 },
	},
	[ePORTF] = {
		{ .ddr = &DDRF, .port = &PORTF, .pin = 0 },
		{ .ddr = &DDRF, .port = &PORTF, .pin = 1 },
		{ .ddr = &DDRF, .port = &PORTF, .pin = 2 },
		{ .ddr = &DDRF, .port = &PORTF, .pin = 3 },
		{ .ddr = &DDRF, .port = &PORTF, .pin = 4 },
		{ .ddr = &DDRF, .port = &PORTF, .pin = 5 },
		{ .ddr = &DDRF, .port = &PORTF, .pin = 6 },
		{ .ddr = &DDRF, .port = &PORTF, .pin = 7 },
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
	[ePORTH] = {
		{ .ddr = &DDRH, .port = &PORTH, .pin = 0 },
		{ .ddr = &DDRH, .port = &PORTH, .pin = 1 },
		{ .ddr = &DDRH, .port = &PORTH, .pin = 2 },
		{ .ddr = &DDRH, .port = &PORTH, .pin = 3 },
		{ .ddr = &DDRH, .port = &PORTH, .pin = 4 },
		{ .ddr = &DDRH, .port = &PORTH, .pin = 5 },
		{ .ddr = &DDRH, .port = &PORTH, .pin = 6 },
		{ .ddr = &DDRH, .port = &PORTH, .pin = 7 },
	},
	[ePORTK] = {
		{ .ddr = &DDRK, .port = &PORTK, .pin = 0 },
		{ .ddr = &DDRK, .port = &PORTK, .pin = 1 },
		{ .ddr = &DDRK, .port = &PORTK, .pin = 2 },
		{ .ddr = &DDRK, .port = &PORTK, .pin = 3 },
		{ .ddr = &DDRK, .port = &PORTK, .pin = 4 },
		{ .ddr = &DDRK, .port = &PORTK, .pin = 5 },
		{ .ddr = &DDRK, .port = &PORTK, .pin = 6 },
		{ .ddr = &DDRK, .port = &PORTK, .pin = 7 },
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


void set_output_map(gpio_map_t * map)
{
	for(uint8_t i = 0; i < map->size; i++)
	{
		set_output(map->gpio[i]);
	}
}

void set_pins_map(gpio_map_t * map, uint32_t data)
{
	for(uint8_t i = 0; i < map->size; i++)
	{
		if(data & 0x01)
			set_high(map->gpio[i]);
		else
			set_low(map->gpio[i]);
		data = data >> 1;
	}
}

void set_input_map(gpio_map_t * map)
{
	for(uint8_t i = 0; i < map->size; i++)
	{
		set_input(map->gpio[i]);
	}
}

uint32_t get_status_map(gpio_map_t * map)
{
	uint32_t data = 0;
	for(uint8_t i = 0; i < map->size; i++)
	{
		data = get_status(map->gpio[i]);
		data = data << 1;
	}
	return data;
}
