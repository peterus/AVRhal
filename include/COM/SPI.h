/*
 * SPI.h
 *
 * Created: 30.08.2014 17:26:57
 *  Author: Peter Buchegger
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_Init(void);
uint8_t SPI_Write(uint8_t data);
void SPI_Write_Count(uint8_t * data, uint16_t data_count);
uint8_t SPI_Read(void);
void SPI_Read_Count(uint8_t * data, uint16_t data_count);

void SPI_SwitchFastMode(void);
void SPI_SwitchSlowMode(void);

#endif /* SPI_H_ */