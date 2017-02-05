/*
 * Touch.c
 *
 * Created: 01.10.2014 22:16:31
 *  Author: Peter Buchegger
 */ 

#include <stdint.h>
#include "LCD/Touch.h"
#include "System.h"

uint16_t X;
uint16_t Y;

void Touch_Init(void)
{
}

uint8_t Touch_Loop(void)
{
	return 0;
}

uint16_t Touch_GetX(void)
{
	return X;
}

uint16_t Touch_GetY(void)
{
	return Y;
}

void Touch_Read_XY(void)
{
}
