/*
 * SDCard.h
 *
 * Created: 20.10.2014 23:23:41
 *  Author: Peter Buchegger
 */ 

#ifndef SDCARD_H_
#define SDCARD_H_

#define SDCARD_INIT_ERROR_CMD0	1
#define SDCARD_INIT_ERROR_CMD1	2
#define BLOCK_SIZE			512

typedef struct 
{
	uint8_t		MID;
	char		OID[2];
	char		PNM[5];
	uint8_t		ProductRev;
	uint32_t	PSN;
	uint8_t				:  4;
	uint16_t	MDT		: 12;
	uint8_t	CRC			:  7;
	uint8_t				:  1;
} CID_Data;

/* Disk Status Bits (DSTATUS) */
#define STA_NOINIT		0x01	/* Drive not initialized */
#define STA_NODISK		0x02	/* No medium in the drive */
#define STA_PROTECT		0x04	/* Write protected */

uint8_t SDCard_Init(void);
uint8_t SDCard_Read_Sector(uint32_t addr, uint8_t * buffer);
uint8_t SDCard_Write_Sector(uint32_t addr, uint8_t * buffer);
uint8_t SDCard_Get_CID(CID_Data * data);

#endif /* SDCARD_H_ */
