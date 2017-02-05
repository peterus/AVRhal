/*
 * LCD_Test.c
 *
 * Created: 09.10.2014 21:58:05
 *  Author: Peter Buchegger
 */ 

#include <stdint.h>
#include <stdio.h>

#include "LCD/LCD.h"

int main(void)
{
	LCD_Init();
	
	while(1)
	{
		Paint(0x0000);	// schwarz
		Paint(0xff00);	// gelb
		Paint(0x00ff);	// blau
		Paint(0xffff);	// weiss
	}
}
