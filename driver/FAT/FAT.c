/*
 * FAT.c
 *
 * Created: 04.12.2014 22:45:23
 *  Author: Peter Buchegger
 */ 

#include <stdint.h>
#include <string.h>
#define _DEBUG
#include "Debug.h"
#include "SDCard/SDCard.h"
#include "FAT.h"

struct t_MBR MBR_Data;
struct t_VBR VBR_Data[4];

uint8_t buffer[BLOCK_SIZE];
uint16_t volume_boot_record_addr;
uint32_t cluster_offset[4];
uint8_t partition = 0;

uint32_t fat_root_dir_addr(uint8_t partition);
void FAT_Load(uint16_t Cluster, uint32_t * Block);


int8_t FAT_Init(void)
{
	int8_t ret = FAT_Init_MBR();
	if(ret != 0)
	{
		return ret;
	}
	ret = 0;
	for (uint8_t i = 0; i < 4; i++)
	{
		int8_t tmp = FAT_Init_VBR(i);
		if(tmp >= 0)
		{
			ret = (1 << FAT_Init_VBR(i));
		}
	}
	return ret;
}

void FAT_Select_Partition(uint8_t parti)
{
	partition = parti;
}

int8_t FAT_Init_MBR(void)
{
	SDCard_Read_Sector(MASTER_BOOT_RECORD, buffer);
	if(buffer[510] == 0x55 && buffer[511] == 0xAA)
	{
		DEBUG_OUT("MBR Signature found!\n");
	}
	else
	{
		DEBUG_OUT("MBR Signature NOT found!\n");
		return 1;
	}
	//MBR_Data = *(struct t_MBR*)buffer;
	memcpy(&MBR_Data, buffer, sizeof(struct t_MBR));
	DEBUG_OUT("BootSignatur:  %d\n", MBR_Data.BootSignatur);
	return 0;
}

int8_t FAT_Init_VBR(uint8_t partition)
{
	/*DEBUG_OUT("\nStatus:        %d\n", MBR_Data.Partitiontable[partition].Status);
	DEBUG_OUT("CHSFirst:      %.3s\n", MBR_Data.Partitiontable[partition].CHSFirst);
	DEBUG_OUT("PartitionType: %d\n", MBR_Data.Partitiontable[partition].PartitionType);
	DEBUG_OUT("CHSLast:       %.3s\n", MBR_Data.Partitiontable[partition].CHSLast);
	DEBUG_OUT("StartSector:   %u\n", MBR_Data.Partitiontable[partition].StartSector);
	DEBUG_OUT("NumSectors:    %u\n", MBR_Data.Partitiontable[partition].NumSectors); // */
	
	volume_boot_record_addr = MBR_Data.Partitiontable[partition].StartSector;
	DEBUG_OUT("volume_boot_record_addr[%d]: 0x%x\n", partition, volume_boot_record_addr);
	if(volume_boot_record_addr == 0)
	{
		DEBUG_OUT("VBR Signature NOT found for Partition: %d!\n", partition);
		return -1;
	}
	SDCard_Read_Sector(volume_boot_record_addr, buffer);
	if(buffer[510] == 0x55 && buffer[511] == 0xAA)
	{
		DEBUG_OUT("VBR Signature found for Partition: %d!\n", partition);
	}
	else
	{
		DEBUG_OUT("VBR Signature NOT found for Partition: %d!\n", partition);
		return -2;
	}
	
	//VBR_Data[partition] = *(struct t_VBR *)buffer;
	memcpy(&VBR_Data[partition], buffer, sizeof(struct t_VBR));
	//cluster_size = VBR_Data[partition].BPB_SecPerClus;
	//fat_offset = VBR_Data[partition].BPB_RsvdSecCnt;

	cluster_offset[partition] = ((VBR_Data[partition].BPB_BytesPerSec * 32) / BLOCK_SIZE);
	cluster_offset[partition] += FAT_root_dir_addr(partition);
	
	return partition;
}

struct t_MBR const * const FAT_getMBR(void)
{
	return &MBR_Data;
}

struct t_VBR const * const FAT_getVBR(uint8_t partition)
{
	return &VBR_Data[partition];
}

uint32_t FAT_root_dir_addr(uint8_t partition)
{
	return VBR_Data[partition].BPB_RsvdSecCnt + (VBR_Data[partition].BPB_NumFATs * VBR_Data[partition].BPB_FATSz16) + MBR_Data.Partitiontable[partition].StartSector;
}

uint8_t FAT_Read_Dir_Entry(uint8_t dir_cluster, uint32_t Entry_Count, struct t_DirEntry * Entry)
{
	uint32_t Sektor = 0;
	uint32_t entry_counter = 0;
	
	if(dir_cluster == 0)
	{
		Sektor = FAT_root_dir_addr(0);
	}
	else
	{
		FAT_Load(dir_cluster, &Sektor);
		Sektor = ((Sektor - 2) * VBR_Data[partition].BPB_SecPerClus) + cluster_offset[partition];
		//DEBUG_OUT("FAT_Read_File: Sektor: %lu\n", Sektor);
	}
	
	for(uint32_t sek = Sektor; ; sek++)
	{
		SDCard_Read_Sector(sek, buffer);
		
		for(uint32_t i = 0; i < BLOCK_SIZE; i += 32)
		{
			if(entry_counter == Entry_Count)
			{
				//*Entry = *(struct t_DirEntry*)&buffer[i];
				memcpy(Entry, &buffer[i], sizeof(struct t_DirEntry));
				
				// check if it is the last (gost-)file:
				if(Entry->Dir_Name[0] == 0)
				{
					DEBUG_OUT("FAT: LAST_ENTRY!\n");
					return 1;
				}
				
				if(Entry->Dir_Name[0] == DIR_ENTRY_IS_FREE)
				{
					DEBUG_OUT("FAT: ENTRY_IS_FREE\n");
					return 2;
				}
				
				if(Entry->Dir_Attribute == ATTR_LONG_NAME)
				{
					DEBUG_OUT("FAT: LONG_NAME\n");
					return 3;
				}
				
				if((Entry->Dir_Attribute & ATTR_READ_ONLY) == ATTR_READ_ONLY)
				{
					DEBUG_OUT("FAT: READ_ONLY\n");
				}
			
				if((Entry->Dir_Attribute & ATTR_HIDDEN) == ATTR_HIDDEN)
				{
					DEBUG_OUT("FAT: HIDDEN\n");
					return 4;
				}
				
				if((Entry->Dir_Attribute & ATTR_SYSTEM) == ATTR_SYSTEM)
				{
					DEBUG_OUT("FAT: SYSTEM\n");
					return 5;
				}
				
				if((Entry->Dir_Attribute & ATTR_VOLUME_LABEL) == ATTR_VOLUME_LABEL)
				{
					DEBUG_OUT("FAT: VOLUME_LABEL\n");
					return 6;
				}
				
				if((Entry->Dir_Attribute & ATTR_SUBDIR) == ATTR_SUBDIR)
				{
					DEBUG_OUT("FAT: SUBDIR\n");
					return 7;
				}
				
				DEBUG_OUT("FAT: IS A FILE\n");
				return 0;
			}
			entry_counter++;
		}
	}
	return 2; // not reaceable
}

void FAT_Load(uint16_t Cluster, uint32_t * Sektor)
{
	uint16_t FAT_Sektor_Store = 0;
	uint16_t FAT_Byte_Addresse;
	uint16_t FAT_Sektor_Addresse;
	
	for(uint16_t i = 0; ; i++)
	{
		if(i == *Sektor)
		{
			*Sektor = (0x0000FFFF & Cluster);
			DEBUG_OUT("FAT_Load: Sektor found\n");
			return;
		}
		if(Cluster == 0xFFFF)
		{
			DEBUG_OUT("FAT_Load: end of file\n");
			break; // End of file!
		}
		
		FAT_Byte_Addresse = (Cluster * 2) % BLOCK_SIZE;
		FAT_Sektor_Addresse = ((Cluster * 2) / BLOCK_SIZE) + MBR_Data.Partitiontable[partition].StartSector + VBR_Data[partition].BPB_RsvdSecCnt;
		
		if(FAT_Sektor_Addresse != FAT_Sektor_Store)
		{
			FAT_Sektor_Store = FAT_Sektor_Addresse;
			SDCard_Read_Sector(FAT_Sektor_Addresse, buffer);
		}
		
		DEBUG_OUT("FAT_Load: FAT_Byte_Addresse: %u\n", FAT_Byte_Addresse);
		
		Cluster = (buffer[FAT_Byte_Addresse + 1] << 8) + buffer[FAT_Byte_Addresse];
	}
}

void FAT_Read_File(uint16_t Cluster, uint8_t * file_buffer, uint32_t Sektor)
{
	uint32_t Block = (Sektor / VBR_Data[partition].BPB_SecPerClus);
	DEBUG_OUT("FAT_Read_File: Block: %lu\n", (long unsigned int)Block);

	FAT_Load(Cluster, &Block);
	Block = ((Block - 2) * VBR_Data[partition].BPB_SecPerClus) + cluster_offset[partition];
	Block += (Sektor % VBR_Data[partition].BPB_SecPerClus);
	
	DEBUG_OUT("FAT_Read_File: Block: %lu\n", (long unsigned int)Block);
	SDCard_Read_Sector(Block, file_buffer);
}

void FAT_Write_File(uint16_t Cluster, uint8_t * file_buffer, uint32_t Sektor)
{
	uint32_t Block = (Sektor / VBR_Data[partition].BPB_SecPerClus);
	DEBUG_OUT("FAT_Write_File: Block: %lu\n", (long unsigned int)Block);

	FAT_Load(Cluster, &Block);
	Block = ((Block - 2) * VBR_Data[partition].BPB_SecPerClus) + cluster_offset[partition];
	Block += (Sektor % VBR_Data[partition].BPB_SecPerClus);
	
	DEBUG_OUT("FAT_Write_File: Block: %lu\n", (long unsigned int)Block);
	SDCard_Write_Sector(Block, file_buffer);
}

uint32_t FAT_find_free_sektor(uint16_t Cluster)
{
	uint16_t FAT_Sektor_Store = 0;
	uint16_t FAT_Byte_Addresse;
	uint16_t FAT_Sektor_Addresse;
	
	for(uint32_t i = Cluster; ; i++)
	{
		FAT_Byte_Addresse = (i * 2) % BLOCK_SIZE;
		FAT_Sektor_Addresse = ((i * 2) / BLOCK_SIZE) + MBR_Data.Partitiontable[partition].StartSector + VBR_Data[partition].BPB_RsvdSecCnt;
		DEBUG_OUT("FAT_find_free_sektor: FAT_Sektor_Addresse: %u\n", FAT_Sektor_Addresse);
		
		if(FAT_Sektor_Addresse != FAT_Sektor_Store)
		{
			FAT_Sektor_Store = FAT_Sektor_Addresse;
			SDCard_Read_Sector(FAT_Sektor_Addresse, buffer);
		}
		
		DEBUG_OUT("FAT_find_free_sektor: FAT_Byte_Addresse: %u\n", FAT_Byte_Addresse);
		
		uint16_t next_cluster = (buffer[FAT_Byte_Addresse + 1] << 8) + buffer[FAT_Byte_Addresse];
		
		if(next_cluster == 0x0000)
		{
			DEBUG_OUT("FAT_find_free_sektor: found a free sektor: %ld\n", i);
			return i;
		}
		else
		{
			DEBUG_OUT("FAT_find_free_sektor: not a free sektor: %ld, 0x%04X\n", i, next_cluster);
		}
	}
}


