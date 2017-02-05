/*
 * SDCard.c
 *
 * Created: 20.10.2014 23:24:04
 *  Author: Peter Buchegger
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define _DEBUG
#include "Debug.h"
#include "COM/SPI.h"
#include "SDCard/SDCard.h"

#define SDCARD_DDR	DDRB
#define SDCARD_PORT	PORTB
#define SDCARD_CS	0

/* Definitions for MMC/SDC command */
#define CMD0	(0)			/* GO_IDLE_STATE */
#define CMD1	(1)			/* SEND_OP_COND */
#define	ACMD41	(0x80+41)	/* SEND_OP_COND (SDC) */
#define CMD8	(8)			/* SEND_IF_COND */
#define CMD9	(9)			/* SEND_CSD */
#define CMD10	(10)		/* SEND_CID */
#define CMD12	(12)		/* STOP_TRANSMISSION */
#define CMD13	(13)		/* SEND_STATUS */
#define ACMD13	(0x80+13)	/* SD_STATUS (SDC) */
#define CMD16	(16)		/* SET_BLOCKLEN */
#define CMD17	(17)		/* READ_SINGLE_BLOCK */
#define CMD18	(18)		/* READ_MULTIPLE_BLOCK */
#define CMD23	(23)		/* SET_BLOCK_COUNT */
#define	ACMD23	(0x80+23)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24)		/* WRITE_BLOCK */
#define CMD25	(25)		/* WRITE_MULTIPLE_BLOCK */
#define CMD32	(32)		/* ERASE_ER_BLK_START */
#define CMD33	(33)		/* ERASE_ER_BLK_END */
#define CMD38	(38)		/* ERASE */
#define CMD55	(55)		/* APP_CMD */
#define CMD58	(58)		/* READ_OCR */


/* Card type flags (CardType) */
#define CT_MMC		0x01	/* MMC ver 3 */
#define CT_SD1		0x02	/* SD ver 1 */
#define CT_SD2		0x04	/* SD ver 2 */
#define CT_BLOCK	0x08	/* Block addressing */

uint8_t CardStatus = STA_NOINIT;	/* Disk status */
uint8_t CardType;					/* b0:MMC, b1:SDv1, b2:SDv2, b3:Block addressing */

void SDCard_Deselect(void);
uint8_t SDCard_Select(void);
uint8_t SDCard_Write_Command(uint8_t cmd, uint32_t arg);

uint8_t SDCard_Init(void)
{
	uint8_t buffer[4];
	uint8_t ty = 0;
	SDCARD_DDR |= (1 << SDCARD_CS);
	
	DEBUG_OUT("SPI_Init\n");
	SPI_Init();
	SDCard_Deselect();
	
	for (uint8_t i = 0; i < 10; i++)
	{
		SPI_Read();
	}
	
	if(SDCard_Write_Command(CMD0, 0) != 1)
	{
		DEBUG_OUT("CMD0 failer, returning 1\n");
		return 1;
	}
	if(SDCard_Write_Command(CMD8, 0x1AA) == 1)
	{
		// SDv2 ?
		//DEBUG_OUT("SDv2 ?\n");
		SPI_Read_Count(buffer, 4);
		if(buffer[2] == 0x01 && buffer[3] == 0xAA)
		{
			uint16_t i = 0;
			for(i = 0; i < 1000; i++)
			{
				if(SDCard_Write_Command(ACMD41, 1UL << 30) == 0)
				{
					break;
				}
				_delay_us(1000);
			}
			if(i && SDCard_Write_Command(CMD58, 0) == 0)
			{
				SPI_Read_Count(buffer, 4);
				ty = (buffer[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2; // SDv2
			}
		}
	}
	else
	{
		// SDv1 or MMCv3
		//DEBUG_OUT("SDv1 or MMCv3\n");
		uint8_t cmd;
		if(SDCard_Write_Command(ACMD41, 0) <= 1)
		{
			//DEBUG_OUT("SDv1\n");
			ty = CT_SD1;
			cmd = ACMD41;	// SDv1
		}
		else
		{
			//DEBUG_OUT("MMCv3\n");
			ty = CT_MMC;
			cmd = CMD1;	// MMCv3
		}
		uint16_t i = 1000;
		for(i = 1000; i != 0; i--)
		{
			if(SDCard_Write_Command(cmd, 0) == 0)
			{
				//DEBUG_OUT("break\n");
				break;
			}
			//DEBUG_OUT("i++\n");
			_delay_us(1000);
		}
		//DEBUG_OUT("i: %d\n", i);
		if(!i || SDCard_Write_Command(CMD16, 512) != 0)
		{
			//DEBUG_OUT("CMD16 failed or one bevor!\n");
			ty = 0;
		}
	}
	
	CardType = ty;
	CardStatus = ty ? 0 : STA_NOINIT;
	
	SPI_SwitchFastMode();
	SDCard_Deselect();
	
	return CardStatus;
}

uint16_t SDCard_Wait_Ready(void)
{
	uint8_t data;
	uint16_t counter;
	
	for (counter = 5000; counter == 0; counter--)
	{
		data = SPI_Read();
		if(data == 0xFF)
		{
			break;
		}
		_delay_us(100);
	}
	
	if(counter == 0)
	{
		return 1;
	}
	return 0;
}

void SDCard_Deselect(void)
{
	SDCARD_PORT |= (1 << SDCARD_CS);
	SPI_Read();
}

uint8_t SDCard_Select(void)
{
	SDCARD_PORT &= ~(1 << SDCARD_CS);
	SPI_Read();
	
	if(SDCard_Wait_Ready() == 0)
	{
		return 0;
	}
	SDCard_Deselect();
	return 1;
}

uint8_t SDCard_Write_Command(uint8_t cmd, uint32_t arg)
{
	uint8_t n;
	if(cmd & 0x80) // ACMD<x> is CMD55 + CMD<n>
	{
		cmd &= 0x7F;
		n = SDCard_Write_Command(CMD55, 0);
		if (n > 1)
		{
			DEBUG_OUT("n > 1 in ACMD<x>\n");
			return n;
		}
	}
	
	if(cmd != CMD12)
	{
		SDCard_Deselect();
		if(SDCard_Select() != 0)
		{
			DEBUG_OUT("SDCard_Select problem\n");
			return 0xFF;
		}
	}
	
	uint8_t buffer[6];
	buffer[0] = 0x40 | cmd;
	buffer[1] = (uint8_t)(arg >> 24);
	buffer[2] = (uint8_t)(arg >> 16);
	buffer[3] = (uint8_t)(arg >>  8);
	buffer[4] = (uint8_t)(arg);
	n = 0x01;
	if(cmd == CMD0) n = 0x95;
	if(cmd == CMD8) n = 0x87;
	buffer[5] = n;
	
	SPI_Write_Count(buffer, 6);
	
	if(cmd == CMD12)
	{
		SPI_Read();
	}
	
	uint8_t timeout = 10;
	do 
	{
		n = SPI_Read();
		//DEBUG_OUT("timeout++\n");
	} while ((n & 0x80) && --timeout);
	
	return n;
}

uint8_t SDCard_Read_Block(uint8_t * data, uint16_t bytes)
{
	uint8_t n = 0;
	for(uint8_t i = 0; i < 1000; i++)
	{
		n = SPI_Read();
		if(n != 0xFF)
		{
			//DEBUG_OUT("n is cool\n");
			break;
		}
		//DEBUG_OUT("wait n: %d\n", n);
		_delay_us(100);
	}
	if(n != 0xFE)
	{
		//DEBUG_OUT("its not 0xFE: 0x%X\n", n);
		return 1;
	}
	//DEBUG_OUT("n is: 0x%X\n", n);
	
	SPI_Read_Count(data, bytes);
	n = SPI_Read(); // CRC
	//DEBUG_OUT("crc1: 0x%X\n", n);
	n = SPI_Read(); // CRC
	//DEBUG_OUT("crc2: 0x%X\n", n);
	
	return 0;
}

uint8_t SDCard_Write_Sector(uint32_t addr, uint8_t * buffer)
{
	return 0;
}

uint8_t SDCard_Read_Sector(uint32_t addr, uint8_t * buffer)
{
	addr = addr << 9; // addr = addr * 512
	uint8_t n = SDCard_Write_Command(CMD17, addr);
	if(n != 0)
	{
		DEBUG_OUT("n: %d", n);
		return 0;
	}
	n = SDCard_Read_Block(buffer, BLOCK_SIZE);
	SDCard_Deselect();
	return n;
}

uint8_t SDCard_Get_CID(CID_Data * data)
{
	SDCard_Write_Command(CMD10, 0);
	uint8_t n = SDCard_Read_Block((uint8_t*)data, 16);
	SDCard_Deselect();
	return n;
}
