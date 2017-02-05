/*
 * Touch.h
 *
 * Created: 01.10.2014 22:16:42
 *  Author: Peter Buchegger
 */ 


#ifndef TOUCH_H_
#define TOUCH_H_

void Touch_Init(void);

uint8_t Touch_Loop(void);

void Touch_Read_XY(void);
uint16_t Touch_GetX(void);
uint16_t Touch_GetY(void);



#endif /* TOUCH_H_ */