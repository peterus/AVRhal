/*
 * SPI.c
 *
 * Created: 30.08.2014 17:26:46
 *  Author: Peter Buchegger
 */ 

#include <avr/io.h>
#include "Debug.h"
#include "COM/SPI.h"

#define SPI_DDR		DDRB
#define MOSI_PIN	2
#define MISO_PIN	3
#define SCK_PIN		1

void SPI_Init(void)
{
	SPI_DDR |= (1 << MOSI_PIN) | (1 << SCK_PIN);
	SPI_DDR &= ~(1 << MISO_PIN);
	
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); //setup SPI: Master mode, MSB first, SCK phase low, SCK idle low
	SPSR = (0 << SPI2X);
}

uint8_t SPI_Write(uint8_t data)
{
	// Start transmission
	SPDR = data;

	// Wait for transmission complete
	DEBUG_OUT("SPI_Write start\n");
	while(!(SPSR & (1 << SPIF)))
	{
		DEBUG_OUT("SPI_Write wait\n");
	}
	DEBUG_OUT("SPI_Write end\n");
	data = SPDR;

	return data;
}

void SPI_Write_Count(uint8_t * data, uint16_t data_count)
{
	do 
	{
		SPI_Write(*data++);
	} while (--data_count);
}

uint8_t SPI_Read(void)
{
	// Wait for reception complete
	SPDR = 0xFF;
	while(!(SPSR & (1 << SPIF)))
	{
		
	}
	// Return data register
	return SPDR;
}

void SPI_Read_Count(uint8_t * data, uint16_t data_count)
{
	do 
	{
		*data = SPI_Read();
		data++;
	} while (--data_count);
}

void SPI_SwitchFastMode(void)
{
	SPCR &= ~((1 << SPR0) | (1 << SPR1));
	SPSR |= (1 << SPI2X);
}

void SPI_SwitchSlowMode(void)
{
	SPCR |= (1 << SPR0) | (1 << SPR1);
	SPSR &= ~(1 << SPI2X);
}

