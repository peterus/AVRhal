/*
 * Touch.c
 *
 * Created: 01.10.2014 22:16:31
 *  Author: Peter Buchegger
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "LCD/Touch.h"
#include "System.h"

#define TOUCH_CLK_PORT		PORTH
#define TOUCH_CLK_DDR		DDRH
#define TOUCH_CLK_PIN		3	// 6
#define TOUCH_CS_PORT		PORTE
#define TOUCH_CS_DDR		DDRE
#define TOUCH_CS_PIN		3	// 5
#define TOUCH_DIN_PORT		PINE
#define TOUCH_DIN_DDR		DDRE
#define TOUCH_DIN_PIN		5	// 4
#define TOUCH_DOUT_PORT		PORTG
#define TOUCH_DOUT_DDR		DDRG
#define TOUCH_DOUT_PIN		5	// 3
#define TOUCH_IRQ_PORT		PINE
#define TOUCH_IRQ_DDR		DDRE
#define TOUCH_IRQ_PIN		4	// 2


void Touch_Write(uint8_t data);
uint16_t Touch_Read(void);
void Touch_SPI_Start(void);

uint16_t X;
uint16_t Y;

void Touch_Init(void)
{
	// Inputs:
	TOUCH_IRQ_DDR &= ~(1 << TOUCH_IRQ_PIN);
	TOUCH_DIN_DDR &= ~(1 << TOUCH_DIN_PIN);
	
	// Outputs:
	TOUCH_CLK_DDR |= (1 << TOUCH_CLK_PIN);
	TOUCH_CS_DDR |= (1 << TOUCH_CS_PIN);
	TOUCH_DOUT_DDR |= (1 << TOUCH_DOUT_PIN);
	
	// Setup pins:
	TOUCH_CS_PORT |= (1 << TOUCH_CS_PIN);
	TOUCH_CLK_PORT &= ~(1 << TOUCH_CLK_PIN);
	TOUCH_DOUT_PORT &= ~(1 << TOUCH_DOUT_PIN);
}

uint8_t Touch_Loop(void)
{
	return (TOUCH_IRQ_PORT & (1 << TOUCH_IRQ_PIN));
}

uint16_t Touch_GetX(void)
{
	return X;
}

uint16_t Touch_GetY(void)
{
	return Y;
}

void Touch_wait_Busy(void)
{
	while (TOUCH_IRQ_PORT & (1 << TOUCH_IRQ_PIN))
	{
		asm volatile ("nop");
	}
}

void Touch_Toggle_Clk(void)
{
	TOUCH_CLK_PORT |= (1 << TOUCH_CLK_PIN);
	asm volatile ("nop");
	TOUCH_CLK_PORT &= ~(1 << TOUCH_CLK_PIN);
}

void Touch_Read_XY(void)
{
	TOUCH_CS_PORT &= ~(1 << TOUCH_CS_PIN);
	
	Touch_Write(0x90);
	Touch_Toggle_Clk();
	Touch_wait_Busy();
	Y = Touch_Read();
	
	Touch_Write(0xD0);
	Touch_Toggle_Clk();
	Touch_wait_Busy();
	X = Touch_Read();
	
	TOUCH_CS_PORT |= (1 << TOUCH_CS_PIN);
}

void Touch_Write(uint8_t data)
{
	uint8_t i = 0;
	
	for(i = 0; i < 8; i++)
	{
		if(data & 0x80)
		{
			TOUCH_DOUT_PORT |= (1 << TOUCH_DOUT_PIN);
		}
		else
		{
			TOUCH_DOUT_PORT &= ~(1 << TOUCH_DOUT_PIN);
		}
		data = data << 1;
		Touch_Toggle_Clk();
	}
}

uint16_t Touch_Read(void)
{
	uint8_t i = 0;
	uint16_t val = 0;
	
	for(i = 0; i < 12; i++)
	{
		val = val << 1;
		TOUCH_CLK_PORT |= (1 << TOUCH_CLK_PIN);
		asm volatile ("nop");
		if(TOUCH_DIN_PORT & (1 << TOUCH_DIN_PIN))
		{
			val++;
		}
		TOUCH_CLK_PORT &= ~(1 << TOUCH_CLK_PIN);
	}
	return val;
}

