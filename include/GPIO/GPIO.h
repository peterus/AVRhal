/*
 * GPIO.h
 *
 * Created: 05.02.2017 23:09:00
 *  Author: Peter Buchegger
 */ 

#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>

typedef struct
{
	volatile uint8_t * ddr;
	volatile uint8_t * port;
	uint8_t pin;
} gpio_t;

enum port_t
{
	ePORTA,
	ePORTB,
	ePORTC,
	ePORTD,
	ePORTE,
	ePORTF,
	ePORTG,
	ePORTH,
	ePORTK,
	ePORTL,
	ePORT_MAX,
};

extern gpio_t gpio[ePORT_MAX][8];

void set_output(gpio_t * gpio);
void set_high(gpio_t * gpio);
void set_low(gpio_t * gpio);
void set_toggle(gpio_t * gpio);

void set_input(gpio_t * gpio);
void activate_pullup(gpio_t * gpio);
void deactivate_pullup(gpio_t * gpio);
uint8_t get_status(gpio_t * gpio);

typedef struct
{
	const uint8_t size;
	gpio_t * gpio[];
} gpio_map_t;

void set_output_map(gpio_map_t * map);
void set_pins_map(gpio_map_t * map, uint32_t data);

void set_input_map(gpio_map_t * map);
uint32_t get_status_map(gpio_map_t * map);

#endif /* GPIO_H_ */
