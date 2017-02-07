/*
 * TinyRTC.h
 *
 * Created: 07.02.2017 00:15:30
 *  Author: Peter Buchegger
 */

#ifndef TINY_RTC_H_
#define TINY_RTC_H_

typedef struct
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t week_day;
	uint8_t day;
	uint8_t month;
	uint8_t year;
} date_time_t;

void TinyRTC_Init(void);
void TinyRTC_get(date_time_t * time);
void TinyRTC_set(date_time_t * time);

#endif /* TINY_RTC_H_ */
