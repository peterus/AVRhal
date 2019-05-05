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
		{ .ddr = &DDRA, .port = &PORTA, .pin_ = &PINA, .pin = 0 },
		{ .ddr = &DDRA, .port = &PORTA, .pin_ = &PINA, .pin = 1 },
		{ .ddr = &DDRA, .port = &PORTA, .pin_ = &PINA, .pin = 2 },
		{ .ddr = &DDRA, .port = &PORTA, .pin_ = &PINA, .pin = 3 },
		{ .ddr = &DDRA, .port = &PORTA, .pin_ = &PINA, .pin = 4 },
		{ .ddr = &DDRA, .port = &PORTA, .pin_ = &PINA, .pin = 5 },
		{ .ddr = &DDRA, .port = &PORTA, .pin_ = &PINA, .pin = 6 },
		{ .ddr = &DDRA, .port = &PORTA, .pin_ = &PINA, .pin = 7 },
	},
	[ePORTB] = {
		{ .ddr = &DDRB, .port = &PORTB, .pin_ = &PINB, .pin = 0 },
		{ .ddr = &DDRB, .port = &PORTB, .pin_ = &PINB, .pin = 1 },
		{ .ddr = &DDRB, .port = &PORTB, .pin_ = &PINB, .pin = 2 },
		{ .ddr = &DDRB, .port = &PORTB, .pin_ = &PINB, .pin = 3 },
		{ .ddr = &DDRB, .port = &PORTB, .pin_ = &PINB, .pin = 4 },
		{ .ddr = &DDRB, .port = &PORTB, .pin_ = &PINB, .pin = 5 },
		{ .ddr = &DDRB, .port = &PORTB, .pin_ = &PINB, .pin = 6 },
		{ .ddr = &DDRB, .port = &PORTB, .pin_ = &PINB, .pin = 7 },
	},
	[ePORTC] = {
		{ .ddr = &DDRC, .port = &PORTC, .pin_ = &PINC, .pin = 0 },
		{ .ddr = &DDRC, .port = &PORTC, .pin_ = &PINC, .pin = 1 },
		{ .ddr = &DDRC, .port = &PORTC, .pin_ = &PINC, .pin = 2 },
		{ .ddr = &DDRC, .port = &PORTC, .pin_ = &PINC, .pin = 3 },
		{ .ddr = &DDRC, .port = &PORTC, .pin_ = &PINC, .pin = 4 },
		{ .ddr = &DDRC, .port = &PORTC, .pin_ = &PINC, .pin = 5 },
		{ .ddr = &DDRC, .port = &PORTC, .pin_ = &PINC, .pin = 6 },
		{ .ddr = &DDRC, .port = &PORTC, .pin_ = &PINC, .pin = 7 },
	},
	[ePORTD] = {
		{ .ddr = &DDRD, .port = &PORTD, .pin_ = &PIND, .pin = 0 },
		{ .ddr = &DDRD, .port = &PORTD, .pin_ = &PIND, .pin = 1 },
		{ .ddr = &DDRD, .port = &PORTD, .pin_ = &PIND, .pin = 2 },
		{ .ddr = &DDRD, .port = &PORTD, .pin_ = &PIND, .pin = 3 },
		{ .ddr = &DDRD, .port = &PORTD, .pin_ = &PIND, .pin = 4 },
		{ .ddr = &DDRD, .port = &PORTD, .pin_ = &PIND, .pin = 5 },
		{ .ddr = &DDRD, .port = &PORTD, .pin_ = &PIND, .pin = 6 },
		{ .ddr = &DDRD, .port = &PORTD, .pin_ = &PIND, .pin = 7 },
	},
	[ePORTE] = {
		{ .ddr = &DDRE, .port = &PORTE, .pin_ = &PINE, .pin = 0 },
		{ .ddr = &DDRE, .port = &PORTE, .pin_ = &PINE, .pin = 1 },
		{ .ddr = &DDRE, .port = &PORTE, .pin_ = &PINE, .pin = 2 },
		{ .ddr = &DDRE, .port = &PORTE, .pin_ = &PINE, .pin = 3 },
		{ .ddr = &DDRE, .port = &PORTE, .pin_ = &PINE, .pin = 4 },
		{ .ddr = &DDRE, .port = &PORTE, .pin_ = &PINE, .pin = 5 },
		{ .ddr = &DDRE, .port = &PORTE, .pin_ = &PINE, .pin = 6 },
		{ .ddr = &DDRE, .port = &PORTE, .pin_ = &PINE, .pin = 7 },
	},
	[ePORTF] = {
		{ .ddr = &DDRF, .port = &PORTF, .pin_ = &PINF, .pin = 0 },
		{ .ddr = &DDRF, .port = &PORTF, .pin_ = &PINF, .pin = 1 },
		{ .ddr = &DDRF, .port = &PORTF, .pin_ = &PINF, .pin = 2 },
		{ .ddr = &DDRF, .port = &PORTF, .pin_ = &PINF, .pin = 3 },
		{ .ddr = &DDRF, .port = &PORTF, .pin_ = &PINF, .pin = 4 },
		{ .ddr = &DDRF, .port = &PORTF, .pin_ = &PINF, .pin = 5 },
		{ .ddr = &DDRF, .port = &PORTF, .pin_ = &PINF, .pin = 6 },
		{ .ddr = &DDRF, .port = &PORTF, .pin_ = &PINF, .pin = 7 },
	},
	[ePORTG] = {
		{ .ddr = &DDRG, .port = &PORTG, .pin_ = &PING, .pin = 0 },
		{ .ddr = &DDRG, .port = &PORTG, .pin_ = &PING, .pin = 1 },
		{ .ddr = &DDRG, .port = &PORTG, .pin_ = &PING, .pin = 2 },
		{ .ddr = &DDRG, .port = &PORTG, .pin_ = &PING, .pin = 3 },
		{ .ddr = &DDRG, .port = &PORTG, .pin_ = &PING, .pin = 4 },
		{ .ddr = &DDRG, .port = &PORTG, .pin_ = &PING, .pin = 5 },
		{ .ddr = &DDRG, .port = &PORTG, .pin_ = &PING, .pin = 6 },
		{ .ddr = &DDRG, .port = &PORTG, .pin_ = &PING, .pin = 7 },
	},
	[ePORTH] = {
		{ .ddr = &DDRH, .port = &PORTH, .pin_ = &PINH, .pin = 0 },
		{ .ddr = &DDRH, .port = &PORTH, .pin_ = &PINH, .pin = 1 },
		{ .ddr = &DDRH, .port = &PORTH, .pin_ = &PINH, .pin = 2 },
		{ .ddr = &DDRH, .port = &PORTH, .pin_ = &PINH, .pin = 3 },
		{ .ddr = &DDRH, .port = &PORTH, .pin_ = &PINH, .pin = 4 },
		{ .ddr = &DDRH, .port = &PORTH, .pin_ = &PINH, .pin = 5 },
		{ .ddr = &DDRH, .port = &PORTH, .pin_ = &PINH, .pin = 6 },
		{ .ddr = &DDRH, .port = &PORTH, .pin_ = &PINH, .pin = 7 },
	},
	[ePORTK] = {
		{ .ddr = &DDRK, .port = &PORTK, .pin_ = &PINK, .pin = 0 },
		{ .ddr = &DDRK, .port = &PORTK, .pin_ = &PINK, .pin = 1 },
		{ .ddr = &DDRK, .port = &PORTK, .pin_ = &PINK, .pin = 2 },
		{ .ddr = &DDRK, .port = &PORTK, .pin_ = &PINK, .pin = 3 },
		{ .ddr = &DDRK, .port = &PORTK, .pin_ = &PINK, .pin = 4 },
		{ .ddr = &DDRK, .port = &PORTK, .pin_ = &PINK, .pin = 5 },
		{ .ddr = &DDRK, .port = &PORTK, .pin_ = &PINK, .pin = 6 },
		{ .ddr = &DDRK, .port = &PORTK, .pin_ = &PINK, .pin = 7 },
	},
	[ePORTL] = {
		{ .ddr = &DDRL, .port = &PORTL, .pin_ = &PINL, .pin = 0 },
		{ .ddr = &DDRL, .port = &PORTL, .pin_ = &PINL, .pin = 1 },
		{ .ddr = &DDRL, .port = &PORTL, .pin_ = &PINL, .pin = 2 },
		{ .ddr = &DDRL, .port = &PORTL, .pin_ = &PINL, .pin = 3 },
		{ .ddr = &DDRL, .port = &PORTL, .pin_ = &PINL, .pin = 4 },
		{ .ddr = &DDRL, .port = &PORTL, .pin_ = &PINL, .pin = 5 },
		{ .ddr = &DDRL, .port = &PORTL, .pin_ = &PINL, .pin = 6 },
		{ .ddr = &DDRL, .port = &PORTL, .pin_ = &PINL, .pin = 7 },
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
	if((*gpio->pin_) & (1 << gpio->pin))
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
