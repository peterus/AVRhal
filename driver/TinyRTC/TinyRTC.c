/*
 * TinyRTC.h
 *
 * Created: 07.02.2017 00:15:30
 *  Author: Peter Buchegger
 */

#include <inttypes.h>
#include "COM/I2C.h"
#include "TinyRTC/TinyRTC.h"

#define REG_SEC_ADDR		(0x00)
#define REG_MIN_ADDR		(0x01)
#define REG_H_ADDR			(0x02)
#define REG_WEEK_DAY_ADDR	(0x03)
#define REG_DAY_ADDR		(0x04)
#define REG_MONTH_ADDR		(0x05)
#define REG_YEAR_ADDR		(0x06)
#define REG_CONTROL_ADDR	(0x07)

#define REG_START			REG_SEC_ADDR
#define REG_END				REG_CONTROL_ADDR

typedef union
{
	struct
	{
		uint8_t sec		: 4;
		uint8_t sec_10	: 3;
		uint8_t ch		: 1;
	};
	uint8_t value;
} reg_sec_t;

typedef union
{
	struct
	{
		uint8_t min		: 4;
		uint8_t min_10	: 3;
		uint8_t			: 1;
	};
	uint8_t value;
} reg_min_t;

typedef union
{
	struct
	{
		uint8_t h		: 4;
		uint8_t h_10	: 2;
		uint8_t sel_12	: 1;
		uint8_t			: 1;
	};
	uint8_t value;
} reg_h_t;

typedef union
{
	struct
	{
		uint8_t week_day: 3;
		uint8_t			: 5;
	};
	uint8_t value;
} reg_week_day_t;

typedef union
{
	struct
	{
		uint8_t day		: 4;
		uint8_t day_10	: 2;
		uint8_t			: 2;
	};
	uint8_t value;
} reg_day_t;

typedef union
{
	struct
	{
		uint8_t month	: 4;
		uint8_t month_10 : 1;
		uint8_t			: 3;
	};
	uint8_t value;
} reg_month_t;

typedef union
{
	struct
	{
		uint8_t year	: 4;
		uint8_t year_10	: 4;
	};
	uint8_t value;
} reg_year_t;

typedef union
{
	struct
	{
		uint8_t rs0		: 1;
		uint8_t rs1		: 1;
		uint8_t			: 2;
		uint8_t sqwe	: 1;
		uint8_t			: 2;
		uint8_t out		: 1;
	};
	uint8_t value;
} reg_control_t;

typedef union
{
	struct
	{
		reg_sec_t		reg_sec;
		reg_min_t		reg_min;
		reg_h_t			reg_h;
		reg_week_day_t	reg_week_day;
		reg_day_t		reg_day;
		reg_month_t		reg_month;
		reg_year_t		reg_year;
		reg_control_t	reg_control;
	};
	uint8_t values[8];
} reg_tiny_rtc_t;

void TinyRTC_Init(void)
{
	I2C_Start(0xD0, I2C_WRITE);
	I2C_Write(REG_CONTROL_ADDR);
	I2C_Write(0x00);
	I2C_Stop();
}

void TinyRTC_get(date_time_t * time)
{
	I2C_Start(0xD0, I2C_WRITE);
	I2C_Write(REG_SEC_ADDR);
	I2C_Rep_Start(0xD0, I2C_READ);
	
	reg_tiny_rtc_t reg_tiny_rtc;
	
	for(uint8_t i = REG_START; i < REG_END; i++)
	{
		reg_tiny_rtc.values[i] = I2C_ReadAck();
	}
	I2C_ReadNak();
	I2C_Stop();
	
	time->seconds = reg_tiny_rtc.reg_sec.sec_10 * 10 + reg_tiny_rtc.reg_sec.sec;
	time->minutes = reg_tiny_rtc.reg_min.min_10 * 10 + reg_tiny_rtc.reg_min.min;
	time->hours = reg_tiny_rtc.reg_h.h_10 * 10 + reg_tiny_rtc.reg_h.h;
	time->week_day = reg_tiny_rtc.reg_week_day.week_day;
	time->day = reg_tiny_rtc.reg_day.day_10 * 10 + reg_tiny_rtc.reg_day.day;
	time->month = reg_tiny_rtc.reg_month.month_10 * 10 + reg_tiny_rtc.reg_month.month;
	time->year = reg_tiny_rtc.reg_year.year_10 * 10 + reg_tiny_rtc.reg_year.year;
}

void TinyRTC_set(date_time_t * time)
{
	I2C_Start(0xD0, I2C_WRITE);
	I2C_Write(REG_SEC_ADDR);
	
	reg_tiny_rtc_t reg_tiny_rtc;
	
	reg_tiny_rtc.reg_sec.sec_10 = time->seconds / 10;
	reg_tiny_rtc.reg_sec.sec = time->seconds % 10;
	reg_tiny_rtc.reg_min.min_10 = time->minutes / 10;
	reg_tiny_rtc.reg_min.min = time->minutes % 10;
	reg_tiny_rtc.reg_h.h_10 = time->hours / 10;
	reg_tiny_rtc.reg_h.h = time->hours % 10;
	reg_tiny_rtc.reg_week_day.week_day = time->week_day;
	reg_tiny_rtc.reg_day.day_10 = time->day / 10;
	reg_tiny_rtc.reg_day.day = time->day % 10;
	reg_tiny_rtc.reg_month.month_10 = time->month / 10;
	reg_tiny_rtc.reg_month.month = time->month % 10;
	reg_tiny_rtc.reg_year.year_10 = time->year / 10;
	reg_tiny_rtc.reg_year.year = time->year % 10;
	
	for(uint8_t i = REG_START; i < REG_END; i++)
	{
		I2C_Write(reg_tiny_rtc.values[i]);
	}
	I2C_ReadNak();
	I2C_Stop();
}



