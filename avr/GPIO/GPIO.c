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
		{ .ddr = &DDRA, .port = &PORTA, .pin = &PINA, .pin_nr = 0 },
		{ .ddr = &DDRA, .port = &PORTA, .pin = &PINA, .pin_nr = 1 },
		{ .ddr = &DDRA, .port = &PORTA, .pin = &PINA, .pin_nr = 2 },
		{ .ddr = &DDRA, .port = &PORTA, .pin = &PINA, .pin_nr = 3 },
		{ .ddr = &DDRA, .port = &PORTA, .pin = &PINA, .pin_nr = 4 },
		{ .ddr = &DDRA, .port = &PORTA, .pin = &PINA, .pin_nr = 5 },
		{ .ddr = &DDRA, .port = &PORTA, .pin = &PINA, .pin_nr = 6 },
		{ .ddr = &DDRA, .port = &PORTA, .pin = &PINA, .pin_nr = 7 },
	},
	[ePORTB] = {
		{ .ddr = &DDRB, .port = &PORTB, .pin = &PINB, .pin_nr = 0 },
		{ .ddr = &DDRB, .port = &PORTB, .pin = &PINB, .pin_nr = 1 },
		{ .ddr = &DDRB, .port = &PORTB, .pin = &PINB, .pin_nr = 2 },
		{ .ddr = &DDRB, .port = &PORTB, .pin = &PINB, .pin_nr = 3 },
		{ .ddr = &DDRB, .port = &PORTB, .pin = &PINB, .pin_nr = 4 },
		{ .ddr = &DDRB, .port = &PORTB, .pin = &PINB, .pin_nr = 5 },
		{ .ddr = &DDRB, .port = &PORTB, .pin = &PINB, .pin_nr = 6 },
		{ .ddr = &DDRB, .port = &PORTB, .pin = &PINB, .pin_nr = 7 },
	},
	[ePORTC] = {
		{ .ddr = &DDRC, .port = &PORTC, .pin = &PINC, .pin_nr = 0 },
		{ .ddr = &DDRC, .port = &PORTC, .pin = &PINC, .pin_nr = 1 },
		{ .ddr = &DDRC, .port = &PORTC, .pin = &PINC, .pin_nr = 2 },
		{ .ddr = &DDRC, .port = &PORTC, .pin = &PINC, .pin_nr = 3 },
		{ .ddr = &DDRC, .port = &PORTC, .pin = &PINC, .pin_nr = 4 },
		{ .ddr = &DDRC, .port = &PORTC, .pin = &PINC, .pin_nr = 5 },
		{ .ddr = &DDRC, .port = &PORTC, .pin = &PINC, .pin_nr = 6 },
		{ .ddr = &DDRC, .port = &PORTC, .pin = &PINC, .pin_nr = 7 },
	},
	[ePORTD] = {
		{ .ddr = &DDRD, .port = &PORTD, .pin = &PIND, .pin_nr = 0 },
		{ .ddr = &DDRD, .port = &PORTD, .pin = &PIND, .pin_nr = 1 },
		{ .ddr = &DDRD, .port = &PORTD, .pin = &PIND, .pin_nr = 2 },
		{ .ddr = &DDRD, .port = &PORTD, .pin = &PIND, .pin_nr = 3 },
		{ .ddr = &DDRD, .port = &PORTD, .pin = &PIND, .pin_nr = 4 },
		{ .ddr = &DDRD, .port = &PORTD, .pin = &PIND, .pin_nr = 5 },
		{ .ddr = &DDRD, .port = &PORTD, .pin = &PIND, .pin_nr = 6 },
		{ .ddr = &DDRD, .port = &PORTD, .pin = &PIND, .pin_nr = 7 },
	},
	[ePORTE] = {
		{ .ddr = &DDRE, .port = &PORTE, .pin = &PINE, .pin_nr = 0 },
		{ .ddr = &DDRE, .port = &PORTE, .pin = &PINE, .pin_nr = 1 },
		{ .ddr = &DDRE, .port = &PORTE, .pin = &PINE, .pin_nr = 2 },
		{ .ddr = &DDRE, .port = &PORTE, .pin = &PINE, .pin_nr = 3 },
		{ .ddr = &DDRE, .port = &PORTE, .pin = &PINE, .pin_nr = 4 },
		{ .ddr = &DDRE, .port = &PORTE, .pin = &PINE, .pin_nr = 5 },
		{ .ddr = &DDRE, .port = &PORTE, .pin = &PINE, .pin_nr = 6 },
		{ .ddr = &DDRE, .port = &PORTE, .pin = &PINE, .pin_nr = 7 },
	},
	[ePORTF] = {
		{ .ddr = &DDRF, .port = &PORTF, .pin = &PINF, .pin_nr = 0 },
		{ .ddr = &DDRF, .port = &PORTF, .pin = &PINF, .pin_nr = 1 },
		{ .ddr = &DDRF, .port = &PORTF, .pin = &PINF, .pin_nr = 2 },
		{ .ddr = &DDRF, .port = &PORTF, .pin = &PINF, .pin_nr = 3 },
		{ .ddr = &DDRF, .port = &PORTF, .pin = &PINF, .pin_nr = 4 },
		{ .ddr = &DDRF, .port = &PORTF, .pin = &PINF, .pin_nr = 5 },
		{ .ddr = &DDRF, .port = &PORTF, .pin = &PINF, .pin_nr = 6 },
		{ .ddr = &DDRF, .port = &PORTF, .pin = &PINF, .pin_nr = 7 },
	},
	[ePORTG] = {
		{ .ddr = &DDRG, .port = &PORTG, .pin = &PING, .pin_nr = 0 },
		{ .ddr = &DDRG, .port = &PORTG, .pin = &PING, .pin_nr = 1 },
		{ .ddr = &DDRG, .port = &PORTG, .pin = &PING, .pin_nr = 2 },
		{ .ddr = &DDRG, .port = &PORTG, .pin = &PING, .pin_nr = 3 },
		{ .ddr = &DDRG, .port = &PORTG, .pin = &PING, .pin_nr = 4 },
		{ .ddr = &DDRG, .port = &PORTG, .pin = &PING, .pin_nr = 5 },
		{ .ddr = &DDRG, .port = &PORTG, .pin = &PING, .pin_nr = 6 },
		{ .ddr = &DDRG, .port = &PORTG, .pin = &PING, .pin_nr = 7 },
	},
	[ePORTH] = {
		{ .ddr = &DDRH, .port = &PORTH, .pin = &PINH, .pin_nr = 0 },
		{ .ddr = &DDRH, .port = &PORTH, .pin = &PINH, .pin_nr = 1 },
		{ .ddr = &DDRH, .port = &PORTH, .pin = &PINH, .pin_nr = 2 },
		{ .ddr = &DDRH, .port = &PORTH, .pin = &PINH, .pin_nr = 3 },
		{ .ddr = &DDRH, .port = &PORTH, .pin = &PINH, .pin_nr = 4 },
		{ .ddr = &DDRH, .port = &PORTH, .pin = &PINH, .pin_nr = 5 },
		{ .ddr = &DDRH, .port = &PORTH, .pin = &PINH, .pin_nr = 6 },
		{ .ddr = &DDRH, .port = &PORTH, .pin = &PINH, .pin_nr = 7 },
	},
	[ePORTK] = {
		{ .ddr = &DDRK, .port = &PORTK, .pin = &PINK, .pin_nr = 0 },
		{ .ddr = &DDRK, .port = &PORTK, .pin = &PINK, .pin_nr = 1 },
		{ .ddr = &DDRK, .port = &PORTK, .pin = &PINK, .pin_nr = 2 },
		{ .ddr = &DDRK, .port = &PORTK, .pin = &PINK, .pin_nr = 3 },
		{ .ddr = &DDRK, .port = &PORTK, .pin = &PINK, .pin_nr = 4 },
		{ .ddr = &DDRK, .port = &PORTK, .pin = &PINK, .pin_nr = 5 },
		{ .ddr = &DDRK, .port = &PORTK, .pin = &PINK, .pin_nr = 6 },
		{ .ddr = &DDRK, .port = &PORTK, .pin = &PINK, .pin_nr = 7 },
	},
	[ePORTL] = {
		{ .ddr = &DDRL, .port = &PORTL, .pin = &PINL, .pin_nr = 0 },
		{ .ddr = &DDRL, .port = &PORTL, .pin = &PINL, .pin_nr = 1 },
		{ .ddr = &DDRL, .port = &PORTL, .pin = &PINL, .pin_nr = 2 },
		{ .ddr = &DDRL, .port = &PORTL, .pin = &PINL, .pin_nr = 3 },
		{ .ddr = &DDRL, .port = &PORTL, .pin = &PINL, .pin_nr = 4 },
		{ .ddr = &DDRL, .port = &PORTL, .pin = &PINL, .pin_nr = 5 },
		{ .ddr = &DDRL, .port = &PORTL, .pin = &PINL, .pin_nr = 6 },
		{ .ddr = &DDRL, .port = &PORTL, .pin = &PINL, .pin_nr = 7 },
	}
};

void set_output(gpio_t * gpio)
{
	(*gpio->ddr) |= (1 << gpio->pin_nr);
}

void set_high(gpio_t * gpio)
{
	(*gpio->port) |= (1 << gpio->pin_nr);
}

void set_low(gpio_t * gpio)
{
	(*gpio->port) &= ~(1 << gpio->pin_nr);
}

void set_toggle(gpio_t * gpio)
{
	(*gpio->port) ^= (1 << gpio->pin_nr);
}


void set_input(gpio_t * gpio)
{
	(*gpio->ddr) &= ~(1 << gpio->pin_nr);
}

void activate_pullup(gpio_t * gpio)
{
	(*gpio->port) |= (1 << gpio->pin_nr);
}

void deactivate_pullup(gpio_t * gpio)
{
	(*gpio->port) &= ~(1 << gpio->pin_nr);
}

uint8_t get_status(gpio_t * gpio)
{
	if((*gpio->pin) & (1 << gpio->pin_nr))
	{
		return 1;
	}
	return 0;
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
		uint32_t read_data = get_status(map->gpio[i]);
		read_data = read_data << i;
		data = data | read_data;
	}
	return data;
}
