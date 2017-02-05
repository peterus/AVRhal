/*
 * SDCard_Test.c
 *
 * Created: 26.10.2014 18:33:08
 *  Author: Peter Buchegger
 */ 

//#include "avr_mcu_section.h"
//AVR_MCU(F_CPU, "atmega2560");

#include <stdint.h>
#include <string.h>
#define _DEBUG
#include "Debug.h"
#include "System.h"
#include "COM/UART.h"
#include "SDCard/SDCard.h"
#include "FAT/FAT.h"

void Print_All_Files_In_Directory_To_Cluster(uint16_t cluster);

int main(void)
{
	UART_Init(UART_BAUD_SELECT(9600, F_CPU));
	interrupts(1); //sei();
	/*while(UART_GetC() == UART_NO_DATA)
	{
	}*/

	sleep(500);
	
	DEBUG_OUT("start SDCard_Init\n");
	uint8_t err = SDCard_Init();
	if(err == STA_NOINIT)
	{
		DEBUG_OUT("STA_NOINIT!\n");
	}
	else if(err == STA_NODISK)
	{
		DEBUG_OUT("STA_NODISK!\n");
	}
	else if(err == STA_PROTECT)
	{
		DEBUG_OUT("STA_PROTECT!\n");
	}
	else
	{
		DEBUG_OUT("Passt!\n");
	}
	
	CID_Data data;
	SDCard_Get_CID(&data);
	
	DEBUG_OUT("\nCID:\n");
	DEBUG_OUT("MID:      %d\n", data.MID);
	DEBUG_OUT("OID:      %.2s\n", data.OID);
	DEBUG_OUT("PNM:      %.5s\n", data.PNM);
	DEBUG_OUT("ProdRev.: %d\n", data.ProductRev);
	DEBUG_OUT("PSN:      %lu\n", (long unsigned int)data.PSN);
	DEBUG_OUT("MDT:      %d\n", data.MDT);
	DEBUG_OUT("CRC:      %d\n", data.CRC);
	DEBUG_OUT("\n");
	
	int8_t partitionen = FAT_Init();
	if(partitionen < 0)
	{
		DEBUG_OUT("Error in FAT_Init()\n");
		while(1);
	}
	
	struct t_MBR const * const mbr = FAT_getMBR();
	DEBUG_OUT("\nMBR:\n");
	for (uint8_t i = 0; i < partitionen; i++)
	{
		DEBUG_OUT("Partition[%d].bootable:      %d\n", i, mbr->Partitiontable[i].Status);
		DEBUG_OUT("Partition[%d].PartitionType: %d\n", i, mbr->Partitiontable[i].PartitionType);
		DEBUG_OUT("Partition[%d].StartSector:   %lu\n", i, (long unsigned int)mbr->Partitiontable[i].StartSector);
		DEBUG_OUT("Partition[%d].NumSectors:    %lu\n", i, (long unsigned int)mbr->Partitiontable[i].NumSectors);
	}
	
	for (uint8_t i = 0; i < partitionen; i++)
	{
		struct t_VBR const * const sector = FAT_getVBR(i);
		DEBUG_OUT("\nVBR[%d]:\n", i);
		DEBUG_OUT("BS_jmpBoot:      0x%X%X%X\n", sector->BS_jmpBoot[0], sector->BS_jmpBoot[1], sector->BS_jmpBoot[2]);
		DEBUG_OUT("BS_OEMName:      %.8s\n", sector->BS_OEMName);
		DEBUG_OUT("BPB_BytesPerSec: %d\n", sector->BPB_BytesPerSec);
		DEBUG_OUT("BPB_SecPerClus:  %d\n", sector->BPB_SecPerClus);
		DEBUG_OUT("BPB_RsvdSecCnt:  %d\n", sector->BPB_RsvdSecCnt);
		DEBUG_OUT("BPB_NumFATs:     %d\n", sector->BPB_NumFATs);
		DEBUG_OUT("BPB_RootEntCnt:  %d\n", sector->BPB_RootEntCnt);
		DEBUG_OUT("BPB_TotSec16:    %d\n", sector->BPB_TotSec16);
		DEBUG_OUT("BPB_Media:       %d\n", sector->BPB_Media);
		DEBUG_OUT("BPB_FATSz16:     %d\n", sector->BPB_FATSz16);
		DEBUG_OUT("BPB_SecPerTrk:   %d\n", sector->BPB_SecPerTrk);
		DEBUG_OUT("BPB_NumHeads:    %d\n", sector->BPB_NumHeads);
		DEBUG_OUT("BPB_HiddSec:     %lu\n", (long unsigned int)sector->BPB_HiddSec);
		DEBUG_OUT("BPB_TotSec32:    %lu\n", (long unsigned int)sector->BPB_TotSec32);
	}

	FAT_Select_Partition(0);
	
	DEBUG_OUT("\n\n");
	uint32_t part0_addr = FAT_root_dir_addr(0);
	DEBUG_OUT("Part0_Addr: %lu\n\n", (long unsigned int)part0_addr);
	
	Print_All_Files_In_Directory_To_Cluster(0);
	Print_All_Files_In_Directory_To_Cluster(2);
	
	/*uint8_t file_buffer[512];
	FAT_Read_File(3, file_buffer, 0);
	for (uint16_t i = 0; i < 20; i++)
	{
		DEBUG_OUT("file_buffer[%d]: %d %c\n", i, file_buffer[i], file_buffer[i]);
	}
	
	DEBUG_OUT("Lets try read, write, read:\n");
	FAT_Read_File(4, file_buffer, 0);
	for (uint16_t i = 0; i < 20; i++)
	{
		DEBUG_OUT("file_buffer[%d]: %d %c\n", i, file_buffer[i], file_buffer[i]);
	}
	memcpy(file_buffer, "Hallo Peter", 11);
	FAT_Write_File(4, file_buffer, 0);
	FAT_Read_File(4, file_buffer, 0);
	for (uint16_t i = 0; i < 20; i++)
	{
		DEBUG_OUT("file_buffer[%d]: %d %c\n", i, file_buffer[i], file_buffer[i]);
	}
	
	FAT_Read_File(5, file_buffer, 0);
	for (uint16_t i = 0; i < 512; i++)
	{
		DEBUG_OUT("%c", file_buffer[i]);
	}
	FAT_Read_File(5, file_buffer, 1);
	for (uint16_t i = 0; i < 512; i++)
	{
		DEBUG_OUT("%c", file_buffer[i]);
	}*/
	
	uint32_t next_free_sektor = FAT_find_free_sektor(0);
	DEBUG_OUT("Next Free Sektor: %lu\n\n", next_free_sektor);

	while(1)
	{
		//TODO:: Please write your application code 
	}
}

void Print_All_Files_In_Directory_To_Cluster(uint16_t cluster)
{
	uint8_t i = 0;
	uint8_t ret = 0;
	do
	{
		struct t_DirEntry dir;
		ret = FAT_Read_Dir_Entry(cluster, i, &dir);
		DEBUG_OUT("FAT_Read_Dir_Entry: %d, %d:\n", cluster, i);
		if(ret == 0)
		{
			DEBUG_OUT("DIR_Name:              %.8s\n", dir.Dir_Name);
			DEBUG_OUT("DIR_Ending:            %.3s\n", dir.Dir_Ending);
			DEBUG_OUT("DIR_Attribute:         0x%X\n", dir.Dir_Attribute);
			DEBUG_OUT("DIR_Create_TimeTenth:  %d\n", dir.DIR_Create_TimeTenth);
			DEBUG_OUT("DIR_Create_Time:       %d\n", dir.DIR_Create_Time);
			DEBUG_OUT("DIR_Create_Date:       %d\n", dir.DIR_Create_Date);
			DEBUG_OUT("DIR_LastAccess_Date:   %d\n", dir.DIR_LastAccess_Date);
			DEBUG_OUT("DIR_FirstCluster_High: 0x%X\n", dir.DIR_FirstCluster_High);
			DEBUG_OUT("DIR_LastChange_Time:   %d\n", dir.DIR_LastChange_Time);
			DEBUG_OUT("DIR_LastChange_Date:   %d\n", dir.Dir_LastChange_Date);
			DEBUG_OUT("DIR_FirstCluster_Low:  0x%X\n", dir.Dir_FirstCluster_Low);
			DEBUG_OUT("DIR_Size:              %lu\n", (long unsigned int)dir.Dir_Size);
		}
		else if(ret == 1)
		{
			DEBUG_OUT("LAST ENTRY\n");
		}
		else if(ret == 2)
		{
			DEBUG_OUT("FREE ENTRY\n");
		}
		else if(ret == 6)
		{
			DEBUG_OUT("VOLUME LABEL: %.8s\n", dir.Dir_Name);
		}
		else if(ret == 7)
		{
			DEBUG_OUT("SUBDIR\n");
			DEBUG_OUT("DIR_Name:              %.8s\n", dir.Dir_Name);
			DEBUG_OUT("DIR_Ending:            %.3s\n", dir.Dir_Ending);
			DEBUG_OUT("DIR_Attribute:         0x%X\n", dir.Dir_Attribute);
			DEBUG_OUT("DIR_Create_TimeTenth:  %d\n", dir.DIR_Create_TimeTenth);
			DEBUG_OUT("DIR_Create_Time:       %d\n", dir.DIR_Create_Time);
			DEBUG_OUT("DIR_Create_Date:       %d\n", dir.DIR_Create_Date);
			DEBUG_OUT("DIR_LastAccess_Date:   %d\n", dir.DIR_LastAccess_Date);
			DEBUG_OUT("DIR_FirstCluster_High: 0x%X\n", dir.DIR_FirstCluster_High);
			DEBUG_OUT("DIR_LastChange_Time:   %d\n", dir.DIR_LastChange_Time);
			DEBUG_OUT("DIR_LastChange_Date:   %d\n", dir.Dir_LastChange_Date);
			DEBUG_OUT("DIR_FirstCluster_Low:  0x%X\n", dir.Dir_FirstCluster_Low);
			DEBUG_OUT("DIR_Size:              %lu\n", (long unsigned int)dir.Dir_Size);
		}
		DEBUG_OUT("\n");
		
		// 1:     200
		// 241: 1E200
		// 481: 3C200
		i++;
		
	} while(ret != 1);
}

