/*
 * Graphics.c
 *
 * Created: 26.02.2019
 *  Author: Peter Buchegger
 */

#include <stdint.h>
#include <stdlib.h>

#include "LCD/LCD.h"
#include "Graphics.h"


void Draw_Line(LCD_Color color, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	uint16_t deltax = 0;
	uint16_t deltay = 0;
	uint16_t x = 0;
	uint16_t y = 0;
	uint16_t xinc1 = 0;
	uint16_t xinc2 = 0;
	uint16_t yinc1 = 0;
	uint16_t yinc2 = 0;
	uint16_t den = 0;
	uint16_t num = 0;
	uint16_t num_add = 0;
	uint16_t num_pixels = 0;
	uint16_t curpixel = 0;

	deltax = abs(x2 - x1);        /* The difference between the x's */
	deltay = abs(y2 - y1);        /* The difference between the y's */
	x = x1;                       /* Start x off at the first pixel */
	y = y1;                       /* Start y off at the first pixel */

	if (x2 >= x1)                 /* The x-values are increasing */
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else                          /* The x-values are decreasing */
	{
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1)                 /* The y-values are increasing */
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else                          /* The y-values are decreasing */
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay)         /* There is at least one x-value for every y-value */
	{
		xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
		yinc2 = 0;                  /* Don't change the y for every iteration */
		den = deltax;
		num = deltax / 2;
		num_add = deltay;
		num_pixels = deltax;         /* There are more x-values than y-values */
	}
	else                          /* There is at least one y-value for every x-value */
	{
		xinc2 = 0;                  /* Don't change the x for every iteration */
		yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
		den = deltay;
		num = deltay / 2;
		num_add = deltax;
		num_pixels = deltay;         /* There are more y-values than x-values */
	}

	for (curpixel = 0; curpixel <= num_pixels; curpixel++)
	{
		LCD_Set_Pixel(color, x, y);                 /* Draw the current pixel */
		num += num_add;                           /* Increase the numerator by the top of the fraction */
		if (num >= den)                           /* Check if numerator >= denominator */
		{
			num -= den;                             /* Calculate the new numerator value */
			x += xinc1;                             /* Change the x as appropriate */
			y += yinc1;                             /* Change the y as appropriate */
		}
		x += xinc2;                               /* Change the x as appropriate */
		y += yinc2;                               /* Change the y as appropriate */
	}
}

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

uint16_t Draw_Char(LCD_Color color, uint8_t c, uint16_t x_start, uint16_t y_start)
{
	GLCD_FONT * font = &GLCD_Font_6x8;
	uint8_t * start = font->char_bitmaps + (c - font->char_offset) * font->char_height;
	uint8_t y;
	for(y = 0; y < font->char_height; y++)
	{
		uint8_t byte = *start++;
		uint8_t mask = 0x01;
		uint8_t x = 0;
		for(x = 0; x < font->char_width; x++)
		{
			if(mask & byte)
			{
				LCD_Set_Pixel(color, x_start+x, y_start+y);
			}
			mask <<=1;
		}
	}
	return x_start + font->char_width;
}

void Draw_String(LCD_Color color, uint8_t * str, uint16_t x_start, uint16_t y_start)
{
	uint16_t x = x_start;
	while(*str)
	{
		x = Draw_Char(color, *str++, x, y_start);
	}
}

