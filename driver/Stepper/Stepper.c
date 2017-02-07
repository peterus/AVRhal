/*
 * Stepper.c
 *
 * Created: 06.02.2017 21:33:25
 *  Author: Peter Buchegger
 */ 

#include <util/delay.h>
#include "GPIO/GPIO.h"
#include "Stepper/Stepper.h"

#define STEPPER_DELAY (250)

void stepper_init(stepper_t * stepper)
{
	set_high(stepper->enable);
	set_high(stepper->direction);
	set_low(stepper->step);
	set_output(stepper->enable);
	set_output(stepper->direction);
	set_output(stepper->step);
}

void stepper_change_direction(stepper_t * stepper)
{
	set_toggle(stepper->direction);
}

void stepper_step(stepper_t * stepper)
{
	set_high(stepper->step);
	_delay_us(1);
	set_low(stepper->step);
	_delay_us(1);
}

void stepper_enable(stepper_t * stepper)
{
	set_low(stepper->enable);
}

void stepper_disable(stepper_t * stepper)
{
	set_high(stepper->enable);
}

void stepper_steps8(stepper_t * stepper, uint8_t count)
{
	stepper_enable(stepper);
	for(uint8_t i = 0; i < count; i++)
	{
		stepper_step(stepper);
		_delay_us(STEPPER_DELAY);
	}
	stepper_disable(stepper);
}

void stepper_steps16(stepper_t * stepper, uint16_t count)
{
	stepper_enable(stepper);
	for(uint16_t i = 0; i < count; i++)
	{
		stepper_step(stepper);
		_delay_us(STEPPER_DELAY);
	}
	stepper_disable(stepper);
}

void stepper_steps32(stepper_t * stepper, uint32_t count)
{
	stepper_enable(stepper);
	for(uint32_t i = 0; i < count; i++)
	{
		stepper_step(stepper);
		_delay_us(STEPPER_DELAY);
	}
	stepper_disable(stepper);
}
