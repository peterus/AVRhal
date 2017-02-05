/*
* I2C.c
*
* Created: 30.08.2014 17:27:11
*  Author: Peter Buchegger
*/
#include <inttypes.h>
#include <compat/twi.h>

#include "COM/I2C.h"

#ifndef F_CPU
#error F_CPU not defined!
#endif

/* I2C clock in Hz */
#define SCL_CLOCK  100000L

/*************************************************************************
Initialization of the I2C bus interface. Need to be called only once
*************************************************************************/
void I2C_Init(void)
{
	/* initialize TWI clock: 100 kHz clock, TWPS = 0 => prescaler = 1 */
	
	TWSR = 0;                         /* no prescaler */
	TWBR = ((F_CPU/SCL_CLOCK)-16)/2;  /* must be > 10 for stable operation */
}


/*************************************************************************
Issues a start condition and sends address and transfer direction.
return 0 = device accessible, 1= failed to access device
*************************************************************************/
uint8_t I2C_Start(uint8_t address, uint8_t mode)
{
	uint8_t   twst;

	// send START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits.
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_START) && (twst != TW_REP_START)) return 1;

	// send device address
	TWDR = address + mode;
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wail until transmission completed and ACK/NACK has been received
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits.
	twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;

	return 0;
}


/*************************************************************************
Issues a start condition and sends address and transfer direction.
If device is busy, use ack polling to wait until device is ready

Input:   address and transfer direction of I2C device
*************************************************************************/
void I2C_Start_Wait(uint8_t address, uint8_t mode)
{
	uint8_t   twst;

	while ( 1 )
	{
		// send START condition
		TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
		
		// wait until transmission completed
		while(!(TWCR & (1<<TWINT)));
		
		// check value of TWI Status Register. Mask prescaler bits.
		twst = TW_STATUS & 0xF8;
		if ( (twst != TW_START) && (twst != TW_REP_START)) continue;
		
		// send device address
		TWDR = address + mode;
		TWCR = (1<<TWINT) | (1<<TWEN);
		
		// wail until transmission completed
		while(!(TWCR & (1<<TWINT)));
		
		// check value of TWI Status Register. Mask prescaler bits.
		twst = TW_STATUS & 0xF8;
		if ( (twst == TW_MT_SLA_NACK )||(twst ==TW_MR_DATA_NACK) )
		{
			/* device busy, send stop condition to terminate write operation */
			TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
			
			// wait until stop condition is executed and bus released
			while(TWCR & (1<<TWSTO));
			
			continue;
		}
		//if( twst != TW_MT_SLA_ACK) return 1;
		break;
	}
}


/*************************************************************************
Issues a repeated start condition and sends address and transfer direction

Input:   address and transfer direction of I2C device

Return:  0 device accessible
1 failed to access device
*************************************************************************/
uint8_t I2C_Rep_Start(uint8_t address, uint8_t mode)
{
	return I2C_Start(address, mode);
}


/*************************************************************************
Terminates the data transfer and releases the I2C bus
*************************************************************************/
void I2C_Stop(void)
{
	/* send stop condition */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	
	// wait until stop condition is executed and bus released
	while(TWCR & (1<<TWSTO));
}


/*************************************************************************
Send one byte to I2C device

Input:    byte to be transfered
Return:   0 write successful
1 write failed
*************************************************************************/
uint8_t I2C_Write( uint8_t data )
{
	uint8_t   twst;
	
	// send data to the previously addressed device
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits
	twst = TW_STATUS & 0xF8;
	if( twst != TW_MT_DATA_ACK) return 1;
	return 0;
}


/*************************************************************************
Read one byte from the I2C device, request more data from device

Return:  byte read from I2C device
*************************************************************************/
uint8_t I2C_ReadAck(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));

	return TWDR;
}


/*************************************************************************
Read one byte from the I2C device, read is followed by a stop condition

Return:  byte read from I2C device
*************************************************************************/
uint8_t I2C_ReadNak(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
	return TWDR;
}
