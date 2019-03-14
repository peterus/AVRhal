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

#include <avr/io.h>
#define LCD_CS_PORT		(PORTG)
#define LCD_CS_PIN		(1)		// 40

LCD_Color black;

int main(void)
{
	black.data = 0;
	uint32_t lx = 0;
	uint32_t ly = 0;
	
	LCD_Init();
	Touch_Init();
	UART_Init(UART_BAUD_SELECT(9600, F_CPU));
	interrupts(1); //sei();
	
	Paint(black);	// schwarz
	
	while(1)
	{
		DEBUG_OUT("test\n");
		if(Touch_Loop() == 0)
		{
			Touch_Read_XY();
			
			DEBUG_OUT("x: %d, y: %d, ", Touch_GetX(), Touch_GetY());

			lx = (Touch_GetX() - 340) * 10 / 144;
			ly = 320 - ((Touch_GetY() - 320) / 11 );
			DEBUG_OUT("x: %lu, y: %lu\n", lx, ly);
			
			//PORTG &= ~(1 << 1);
			LCD_CS_PORT &= ~(1 << LCD_CS_PIN);
			LCD_Set_Address(lx, ly, lx + 1, ly + 1);
			LCD_Write_Data(0xF800);
			LCD_CS_PORT |= (1 << LCD_CS_PIN);
			/*for(uint8_t i = 0; i < 1; i++)
			{
			}*/
			//PORTG |= (1 << 1);
		}
		else
		{
			DEBUG_OUT("no touch\n");
		}
	}
}
