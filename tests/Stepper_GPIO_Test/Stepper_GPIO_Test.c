/*
 * Stepper_GPIO_Test.c
 *
 * Created: 06.02.2017 01:38:00
 *  Author: Peter Buchegger
 */

#include <util/delay.h>
#include "GPIO/GPIO.h"
#include "Stepper/Stepper.h"
#include "System.h"
#include "GPIO_def.h"

#define STEP_100ML (407934)

int main(void)
{
	sleep(100);
	// 43
	set_output(&gpio[ePORTL][6]);
	set_low(&gpio[ePORTL][6]);
	
	stepper_t stepper1 =
	{
		.enable = M1_ENABLE,
		.direction = M1_DIR,
		.step = M1_STEP,
	};
	
	stepper_t stepper2 =
	{
		.enable = M2_ENABLE,
		.direction = M2_DIR,
		.step = M2_STEP,
	};
	
	stepper_init(&stepper1);
	stepper_init(&stepper2);
	
	sleep(1);
	
	//stepper_steps32(&stepper1, 3200);
	/*for(uint8_t i = 0; i < 127; i++)
	{
		stepper_steps32(&stepper2, 3200);
	}*/
	stepper_steps32(&stepper2, STEP_100ML/100*4);
	
	while(1)
	{
		
		//set_toggle(&M1_STEP_PORT, M1_STEP_PIN);
		
		//sleep(1);
		//_delay_us(500);
	}
}
