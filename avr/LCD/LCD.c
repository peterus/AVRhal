/*
 * LCD.c
 *
 * Created: 28.09.2014 22:52:39
 *  Author: Peter Buchegger
 */ 
#include <avr/io.h>

#include "LCD/LCD.h"
#include "System.h"

#define LCD_CS_PORT		(PORTG)
#define LCD_CS_DDR		(DDRG)
#define LCD_CS_PIN		(1)		// 40
#define LCD_RS_PORT		(PORTD)
#define LCD_RS_DDR		(DDRD)
#define LCD_RS_PIN		(7)		// 38
#define LCD_WR_PORT		(PORTG)
#define LCD_WR_DDR		(DDRG)
#define LCD_WR_PIN		(2)		// 39
#define LCD_RESET_PORT	(PORTG)
#define LCD_RESET_DDR	(DDRG)
#define LCD_RESET_PIN	(0)		// 41
#define LCD_LOW_PORT	(PORTC)
#define LCD_DB0_PIN		(0) // PORTC
#define LCD_DB1_PIN		(1) // PORTC
#define LCD_DB2_PIN		(2) // PORTC
#define LCD_DB3_PIN		(3) // PORTC
#define LCD_DB4_PIN		(4) // PORTC
#define LCD_DB5_PIN		(5) // PORTC
#define LCD_DB6_PIN		(6) // PORTC
#define LCD_DB7_PIN		(7) // PORTC
#define LCD_HIGH_PORT	(PORTA)
#define LCD_DB8_PIN		(0) // PORTA
#define LCD_DB9_PIN		(1) // PORTA
#define LCD_DB10_PIN	(2) // PORTA
#define LCD_DB11_PIN	(3) // PORTA
#define LCD_DB12_PIN	(4) // PORTA
#define LCD_DB13_PIN	(5) // PORTA
#define LCD_DB14_PIN	(6) // PORTA
#define LCD_DB15_PIN	(7) // PORTA

void LCD_Init_Inner(void);
void LCD_Write_Bus(uint16_t data);
void LCD_Write_Register(uint16_t data);
void LCD_Write_Register_Data(uint16_t Register, uint16_t data);

void LCD_Init(void)
{
	DDRA = 0xFF;
	DDRC = 0xFF;
	DDRD |= (1 << LCD_RS_PIN);
	DDRG |= (1 << LCD_CS_PIN) | (1 << LCD_WR_PIN) | (1 << LCD_RESET_PIN);
	
	LCD_RESET_PORT |= (1 << LCD_RESET_PIN);
	sleep(5);
	LCD_RESET_PORT &= ~(1 << LCD_RESET_PIN);
	sleep(15);
	LCD_RESET_PORT |= (1 << LCD_RESET_PIN);
	sleep(15);
	
	LCD_CS_PORT |= (1 << LCD_CS_PIN);
	
	LCD_Init_Inner();
}

void LCD_PutS(char * str)
{
	
}


void LCD_Init_Inner(void)
{
	LCD_CS_PORT &= ~(1 << LCD_CS_PIN);
	LCD_Write_Register_Data(0x0000, 0x0001);
	LCD_Write_Register_Data(0x0003, 0xA8A4);
	LCD_Write_Register_Data(0x000C, 0x0000);
	LCD_Write_Register_Data(0x000D, 0x080C);
	LCD_Write_Register_Data(0x000E, 0x2B00);
	LCD_Write_Register_Data(0x001E, 0x00B7);
	LCD_Write_Register_Data(0x0001, 0x2B3F);
	LCD_Write_Register_Data(0x0002, 0x0600);
	LCD_Write_Register_Data(0x0010, 0x0000);
	LCD_Write_Register_Data(0x0011, 0x6070);
	LCD_Write_Register_Data(0x0005, 0x0000);	
	LCD_Write_Register_Data(0x0006, 0x0000);
	LCD_Write_Register_Data(0x0016, 0xEF1C);
	LCD_Write_Register_Data(0x0017, 0x0003);
	LCD_Write_Register_Data(0x0007, 0x0233);
	LCD_Write_Register_Data(0x000B, 0x0000);
	LCD_Write_Register_Data(0x000F, 0x0000);
	LCD_Write_Register_Data(0x0041, 0x0000);
	LCD_Write_Register_Data(0x0042, 0x0000);
	LCD_Write_Register_Data(0x0048, 0x0000);
	LCD_Write_Register_Data(0x0049, 0x013F);
	LCD_Write_Register_Data(0x004A, 0x0000);
	LCD_Write_Register_Data(0x004B, 0x0000);
	LCD_Write_Register_Data(0x0044, 0xEF00);
	LCD_Write_Register_Data(0x0045, 0x0000);
	LCD_Write_Register_Data(0x0046, 0x013F);
	LCD_Write_Register_Data(0x0030, 0x0707);
	LCD_Write_Register_Data(0x0031, 0x0204);
	LCD_Write_Register_Data(0x0032, 0x0204);
	LCD_Write_Register_Data(0x0033, 0x0502);
	LCD_Write_Register_Data(0x0034, 0x0507);
	LCD_Write_Register_Data(0x0035, 0x0204);
	LCD_Write_Register_Data(0x0036, 0x0204);
	LCD_Write_Register_Data(0x0037, 0x0502);
	LCD_Write_Register_Data(0x003A, 0x0302);
	LCD_Write_Register_Data(0x003B, 0x0302);
	LCD_Write_Register_Data(0x0023, 0x0000);
	LCD_Write_Register_Data(0x0024, 0x0000);
	LCD_Write_Register_Data(0x0025, 0x8000);
	LCD_Write_Register_Data(0x004f, 0x0000);
	LCD_Write_Register_Data(0x004e, 0x0000);
	LCD_Write_Register(0x0022);
	LCD_CS_PORT |= (1 << LCD_CS_PIN);
}

void LCD_Write_Bus(uint16_t data)
{
	LCD_LOW_PORT = data & 0xFF;
	LCD_HIGH_PORT = (data >> 8) & 0xFF;
	LCD_WR_PORT &= ~(1 << LCD_WR_PIN);
	LCD_WR_PORT |= (1 << LCD_WR_PIN);
}

void LCD_Write_Register(uint16_t data)
{
	LCD_RS_PORT &= ~(1 << LCD_RS_PIN);
	LCD_Write_Bus(data);
}

void LCD_Write_Data(uint16_t data)
{
	LCD_RS_PORT |= (1 << LCD_RS_PIN);
	LCD_Write_Bus(data);
}

void LCD_Write_Register_Data(uint16_t Register, uint16_t data)
{
	LCD_Write_Register(Register);
	LCD_Write_Data(data);
}

void LCD_Set_Address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_Write_Register_Data(0x0044, (x2 << 8) + x1);
	LCD_Write_Register_Data(0x0045, y1);
	LCD_Write_Register_Data(0x0046, y2);
	LCD_Write_Register_Data(0x004e, x1);
	LCD_Write_Register_Data(0x004f, y1);
	LCD_Write_Register(0x0022);
}

void Paint(uint16_t data)
{
	int i, j;
	LCD_CS_PORT &= ~(1 << LCD_CS_PIN);
	LCD_Set_Address(0,0,239,319);
	for(i = 0; i < 320; i++)
	{
		for (j = 0; j < 240; j++)
		{
			LCD_Write_Data(data);
		}
	}
	LCD_CS_PORT |= (1 << LCD_CS_PIN);
}

