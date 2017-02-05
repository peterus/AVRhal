/*
 * LCD_Touch_Test.c
 *
 * Created: 30.08.2014 17:14:08
 *  Author: Peter Buchegger
 */ 

#include <stdint.h>
#include <stdio.h>

#include "COM/UART.h"
#include "LCD/LCD.h"
#include "LCD/Touch.h"
//#define _DEBUG
#include "Debug.h"
#include "System.h"

int main(void)
{
	uint32_t lx = 0;
	uint32_t ly = 0;
	
	LCD_Init();
	Touch_Init();
	UART_Init(UART_BAUD_SELECT(9600, F_CPU));
	interrupts(1); //sei();
	
	Paint(0x0000);	// schwarz
	
	while(1)
	{
		if(Touch_Loop() == 0)
		{
			Touch_Read_XY();
			
			DEBUG_OUT("x: %d, y: %d\n", Touch_GetX(), Touch_GetY());

			lx = (Touch_GetX() - 340) * 10 / 144;
			ly = 320 - ((Touch_GetY() - 320) / 11 );
			
			//PORTG &= ~(1 << 1);
			LCD_Set_Address(lx, ly, lx + 1, ly + 1);
			for(uint8_t i = 0; i < 1; i++)
			{
				LCD_Write_Data(0xF800);
			}
			//PORTG |= (1 << 1);
		}
		else
		{
			DEBUG_OUT("no touch\n");
		}
	}
}
