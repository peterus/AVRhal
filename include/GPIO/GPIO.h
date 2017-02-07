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
	ePORTL,
};

extern gpio_t gpio[8][8];

void set_output(gpio_t * gpio);
void set_high(gpio_t * gpio);
void set_low(gpio_t * gpio);
void set_toggle(gpio_t * gpio);

void set_input(gpio_t * gpio);
void activate_pullup(gpio_t * gpio);
void deactivate_pullup(gpio_t * gpio);
uint8_t get_status(gpio_t * gpio);

#endif /* GPIO_H_ */
