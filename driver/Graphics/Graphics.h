/*
 * Graphics.h
 *
 * Created: 26.02.2019
 *  Author: Peter Buchegger
 */ 


#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <stdint.h>
#include "LCD/LCD.h"


void Draw_Line(LCD_Color color, int16_t x1, int16_t y1, int16_t x2, int16_t y2);


typedef struct
{
  uint8_t char_width;
  uint8_t char_height;
  uint8_t char_offset;
  uint8_t char_count;
  uint8_t * char_bitmaps;
} GLCD_FONT;


uint16_t Draw_Char(LCD_Color color, uint8_t c, uint16_t x_start, uint16_t y_start);
void Draw_String(LCD_Color color, uint8_t * str, uint16_t x_start, uint16_t y_start);


#endif /* GRAPHICS_H_ */
