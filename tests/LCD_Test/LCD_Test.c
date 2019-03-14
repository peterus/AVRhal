/*
 * LCD_Test.c
 *
 * Created: 09.10.2014 21:58:05
 *  Author: Peter Buchegger
 */ 

#include <stdint.h>
#include <stdio.h>

#include "LCD/LCD.h"

LCD_Color black;
LCD_Color white;

int main(void)
{
	black.data = 0;

	white.red = 0b11111;
	white.blue = 0b11111;
	white.green = 0b111111;

	LCD_Init();
	
	while(1)
	{
		LCD_Activate();
		/*Paint(0x0000);	// schwarz
		Paint(0xff00);	// gelb
		Paint(0x00ff);	// blau
		Paint(0xffff);	// weiss
*/
		Paint_field(black, MIN_X, MIN_Y, MAX_X, MAX_Y);
		
		//Paint_field(0xff00, MAX_X/4+1,   MIN_Y,   MAX_X, MAX_Y/4);
		//Paint_field(0x00ff,   MIN_X, MAX_Y/4+1, MAX_X/4, MAX_Y);
		//Paint_field(0xffff, MAX_X/4+1, MAX_Y/4+1,   MAX_X, MAX_Y);

		LCD_Set_Pixel(white, 100, 100);

		/*LCD_Set_Address(0, 0, 240/2, 320/2);
		LCD_Write_Data(0x0000);
		LCD_Set_Address(239/2, 0, 239, 319/2);
		LCD_Write_Data(0xff00);
		LCD_Set_Address(0, 319/2, 239/2, 319);
		LCD_Write_Data(0x00ff);
		LCD_Set_Address(239/2, 319/2, 239, 319);
		LCD_Write_Data(0xffff);*/
		LCD_Deactivate();
	}
}
