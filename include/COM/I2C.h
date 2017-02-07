/*
 * I2C.h
 *
 * Created: 30.08.2014 17:27:23
 *  Author: Peter Buchegger
 */

#ifndef I2C_H_
#define I2C_H_

#define I2C_READ	1
#define I2C_WRITE	0

void I2C_Init(void);
void I2C_Stop(void);
uint8_t I2C_Start(uint8_t addr, uint8_t mode);
uint8_t I2C_Rep_Start(uint8_t addr, uint8_t mode);
void I2C_Start_Wait(uint8_t addr, uint8_t mode);
uint8_t I2C_Write(uint8_t data);
uint8_t I2C_ReadAck(void);
uint8_t I2C_ReadNak(void);


#endif /* I2C_H_ */
