/*
 * LCD.h
 *
 * Created: 28.09.2014 22:52:50
 *  Author: Peter Buchegger
 */ 


#ifndef LCD_H_
#define LCD_H_

#define MIN_X (0)
#define MAX_X (239)
#define MIN_Y (0)
#define MAX_Y (319)

typedef union {
	struct {
		uint8_t blue : 5;
		uint8_t green : 6;
		uint8_t red : 5;
	};
	uint16_t data;
} LCD_Color;

void LCD_Init(void);

void LCD_Activate(void);
void LCD_Deactivate(void);

void LCD_Write_Data(uint16_t data);
void LCD_Set_Address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_Set_Pixel(LCD_Color color, int16_t x, int16_t y);


void Paint(LCD_Color color);
void Paint_field(LCD_Color color, int16_t x1, int16_t y1, int16_t x2, int16_t y2);

#endif /* LCD_H_ */
