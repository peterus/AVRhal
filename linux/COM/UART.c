#include <stdint.h>
#include <stdio.h>
#include "COM/UART.h"

void UART_Init(unsigned int baudrate)
{
}

unsigned int UART_GetC(void)
{
	unsigned char c;
	scanf(" %c", &c);
	return c;
	return UART_NO_DATA;
}


void UART_PutC(unsigned char data)
{
	printf("%c", data);
}

int UART_PutC_(char data, FILE * stream)
{
	UART_PutC(data);
	return 0;
}

void UART_PutS(const char *s )
{
	while (*s) 
		UART_PutC(*s++);

}

void UART_PutS_P(const char *progmem_s )
{
	UART_PutS(progmem_s);
}
