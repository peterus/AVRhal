/*
 * Stepper.h
 *
 * Created: 06.02.2017 21:28:25
 *  Author: Peter Buchegger
 */ 

#ifndef STEPPER_H_
#define STEPPER_H_

typedef struct
{
	gpio_t * enable;
	gpio_t * direction;
	gpio_t * step;
} stepper_t;

void stepper_init(stepper_t * stepper);
void stepper_change_direction(stepper_t * stepper);
void stepper_step(stepper_t * stepper);
void stepper_enable(stepper_t * stepper);
void stepper_disable(stepper_t * stepper);
void stepper_steps8(stepper_t * stepper, uint8_t count);
void stepper_steps16(stepper_t * stepper, uint16_t count);
void stepper_steps32(stepper_t * stepper, uint32_t count);

#endif /* STEPPER_H_ */
