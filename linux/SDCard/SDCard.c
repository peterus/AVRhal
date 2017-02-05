/*
 * SDCard.c
 *
 * Created: 20.10.2014 23:24:04
 *  Author: Peter Buchegger
 */ 

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#define _DEBUG
#include "Debug.h"
#include "COM/SPI.h"
#include "SDCard/SDCard.h"

FILE * pSDCard;

uint8_t SDCard_Init(void)
{
	pSDCard = fopen("/dev/mmcblk0", "r+");
	return 5;
}

uint8_t SDCard_Write_Sector(uint32_t addr, uint8_t * buffer)
{
	addr = addr << 9;
	fseek(pSDCard, addr, SEEK_SET);
	uint8_t n = fwrite(buffer, BLOCK_SIZE, 1, pSDCard);
	return n;
}

uint8_t SDCard_Read_Sector(uint32_t addr, uint8_t * buffer)
{
	addr = addr << 9;
	fseek(pSDCard, addr, SEEK_SET);
	uint8_t n = fread(buffer, BLOCK_SIZE, 1, pSDCard);
	return n;
}

uint8_t SDCard_Get_CID(CID_Data * data)
{
	data->MID = 3;
	//data->OID = "SD";
	memcpy(data->OID, "SD", 2);
	//data->PNM = "SU01G";
	memcpy(data->PNM, "SU01G", 5);
	data->ProductRev = 128;
	data->PSN = 2021815840;
	data->MDT = 1712;
	data->CRC = 51;
	return 0;
}
