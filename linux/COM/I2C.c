/*
* I2C.c
*
* Created: 30.08.2014 17:27:11
*  Author: Peter Buchegger
*/

#include <stdint.h>
#include "COM/I2C.h"

void I2C_Init(void)
{
}

uint8_t I2C_Start(uint8_t address, uint8_t mode)
{
	return 0;
}

void I2C_Start_Wait(uint8_t address, uint8_t mode)
{
}

uint8_t I2C_Rep_Start(uint8_t address, uint8_t mode)
{
    return 0;
}

void I2C_Stop(void)
{
}

uint8_t I2C_Write( uint8_t data )
{
	return 0;
}

uint8_t I2C_ReadAck(void)
{
	return 0;
}

uint8_t I2C_ReadNak(void)
{
	return 0;
}
