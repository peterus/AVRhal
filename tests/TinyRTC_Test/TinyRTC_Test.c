/*
 * TinyRTC_Test.c
 *
 * Created: 07.02.2017 22:41:20
 *  Author: Peter Buchegger
 */

#include <stdint.h>
#include <stdio.h>
#include "COM/UART.h"
#define _DEBUG
#include "Debug.h"
#include "System.h"

#include "TinyRTC/TinyRTC.h"
#include "COM/I2C.h"

int main(void)
{
	UART_Init(UART_BAUD_SELECT(9600, F_CPU));
	interrupts(1); //sei();
	
	while(UART_GetC() == UART_NO_DATA)
	{
	}
	printf("I2C_Init();\n");
	I2C_Init();
	printf("TinyRTC_Init();\n");
	TinyRTC_Init();
	
	date_time_t date_time;
	date_time.day = 07;
	date_time.month = 02;
	date_time.year = 17;
	date_time.hours = 23;
	date_time.minutes = 45;
	date_time.seconds = 00;
	date_time.week_day = 2;
	TinyRTC_set(&date_time);
	
	while(1)
	{
		date_time_t date_time;
		TinyRTC_get(&date_time);
		printf("%02d.%02d.%02d %d ", date_time.day, date_time.month, date_time.year, date_time.week_day);
		printf("%02d:%02d:%02d\n", date_time.hours, date_time.minutes, date_time.seconds);
		sleep(500);
	}
}
