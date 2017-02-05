/*
 * SPI.c
 *
 * Created: 30.08.2014 17:26:46
 *  Author: Peter Buchegger
 */ 

#include <stdint.h>
#include "Debug.h"
#include "COM/SPI.h"

void SPI_Init(void)
{
}

uint8_t SPI_Write(uint8_t data)
{
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
	return 0;
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
}

void SPI_SwitchSlowMode(void)
{
}

