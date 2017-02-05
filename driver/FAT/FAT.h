/*
 * FAT.h
 *
 * Created: 04.12.2014 22:45:37
 *  Author: Peter Buchegger
 */ 


#ifndef FAT_H_
#define FAT_H_

#define MASTER_BOOT_RECORD	0

struct t_Partitiontable
{
	uint8_t		Status;
	uint8_t		CHSFirst[3];
	uint8_t		PartitionType;
	uint8_t		CHSLast[3];
	uint32_t	StartSector;
	uint32_t	NumSectors;
};

struct t_MBR
{
	uint8_t		BootstrapCodeArea[446];
	struct		t_Partitiontable Partitiontable[4];
	uint16_t	BootSignatur;
};

#define VBR_ADDR 			0x1C6

struct t_VBR
{
	uint8_t		BS_jmpBoot[3];
	uint8_t		BS_OEMName[8];
	uint16_t	BPB_BytesPerSec;
	uint8_t		BPB_SecPerClus;
	uint16_t	BPB_RsvdSecCnt;
	uint8_t		BPB_NumFATs;
	uint16_t	BPB_RootEntCnt;
	uint16_t	BPB_TotSec16;
	uint8_t		BPB_Media;
	uint16_t	BPB_FATSz16;
	uint16_t	BPB_SecPerTrk;
	uint16_t	BPB_NumHeads;
	uint32_t	BPB_HiddSec;
	uint32_t	BPB_TotSec32;
};

#define DIR_ENTRY_IS_FREE	(0xE5)
#define ATTR_READ_ONLY		(0x01)
#define ATTR_HIDDEN			(0x02)
#define ATTR_SYSTEM			(0x04)
#define ATTR_VOLUME_LABEL	(0x08)
#define ATTR_LONG_NAME		(0x0F)
#define ATTR_SUBDIR			(0x10)
#define ATTR_ARCHIVE		(0x20)

struct t_DirEntry
{
	uint8_t		Dir_Name[8];
	uint8_t		Dir_Ending[3];
	uint8_t		Dir_Attribute;
	uint8_t		reservated;
	uint8_t		DIR_Create_TimeTenth;
	uint16_t	DIR_Create_Time;
	uint16_t	DIR_Create_Date;
	uint16_t	DIR_LastAccess_Date;
	uint16_t	DIR_FirstCluster_High;
	uint16_t	DIR_LastChange_Time;
	uint16_t	Dir_LastChange_Date;
	uint16_t	Dir_FirstCluster_Low;
	uint32_t	Dir_Size;
};

int8_t		FAT_Init(void);
int8_t		FAT_Init_MBR(void);
int8_t		FAT_Init_VBR(uint8_t partition);
void		FAT_Select_Partition(uint8_t parti);

uint32_t	FAT_root_dir_addr(uint8_t partition);
uint8_t		FAT_Read_Dir_Entry(uint8_t dir_cluster, uint32_t Entry_Count, struct t_DirEntry * Entry);
void		FAT_Read_File(uint16_t Cluster, uint8_t * file_buffer, uint32_t Sektor);
void		FAT_Write_File(uint16_t Cluster, uint8_t * file_buffer, uint32_t Sektor);

uint32_t FAT_find_free_sektor(uint16_t Cluster);

struct t_MBR const * const FAT_getMBR(void);
struct t_VBR const * const FAT_getVBR(uint8_t partition);


#endif /* FAT_H_ */
