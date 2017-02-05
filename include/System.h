/*
 * System.h
 *
 * Created: 30.09.2014 23:24:47
 *  Author: Peter Buchegger
 */ 


#ifndef SYSTEM_H_
#define SYSTEM_H_

void sleep(uint16_t ms);
void interrupts(uint8_t enable);

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#endif /* SYSTEM_H_ */
