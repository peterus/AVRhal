/*
 * LCD.h
 *
 * Created: 28.09.2014 22:52:50
 *  Author: Peter Buchegger
 */ 


#ifndef LCD_H_
#define LCD_H_


void LCD_Init(void);

void LCD_PutS(char * str);


void Paint(uint16_t data);
void LCD_Write_Data(uint16_t data);
void LCD_Set_Address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);



#endif /* LCD_H_ */
