/*
 * Graphics_Test.c
 *
 * Created: 26.02.2019
 *  Author: Peter Buchegger
 */ 

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "System.h"
#include "LCD/LCD.h"
#include "Graphics/Graphics.h"

LCD_Color black;
LCD_Color red;
LCD_Color blue;
LCD_Color green;
LCD_Color white;

void do_faecher(void)
{
	uint16_t i = 0;
	uint16_t offset = 4;
	for(i = 0; i <= MAX_X; i += offset)
	{
		Draw_Line(red, MAX_X/2, MAX_Y/2, i, MAX_Y);
	}
	for(i = 0; i <= MAX_X; i += offset)
	{
		Draw_Line(blue, MAX_X/2, MAX_Y/2, i, 0);
	}
	for(i = 0; i <= MAX_Y; i += offset)
	{
		Draw_Line(green, MAX_X/2, MAX_Y/2, MAX_X, i);
	}
	for(i = 0; i <= MAX_Y; i += offset)
	{
		Draw_Line(white, MAX_X/2, MAX_Y/2, 0, i);
	}
}

void do_kreise(float R, uint16_t n)
{
	float x_old = 0;
	float y_old = 0;
	uint8_t draw = 0;
	for(uint16_t i = 0; i <= n; i++)
	{
		float alpha = 2*M_PI*i/n;
		float x = MAX_X/2 + sin(alpha) * R;
		float y = MAX_Y/2 + cos(alpha) * R;
		if(draw)
		{
			Draw_Line(black, x_old, y_old, x, y);
		}
		x_old = x;
		y_old = y;
		draw = 1;
	}
}

void do_blume(float R, uint16_t n)
{
	float x_old = 0;
	float y_old = 0;
	uint8_t draw = 0;
	for(uint16_t i = 0; i <= n; i++)
	{
		float alpha_k = 2*M_PI*i/n;
		float x_k = MAX_X/2 + sin(alpha_k) * R;
		float y_k = MAX_Y/2 + cos(alpha_k) * R;

		float x = x_k + sin(9*alpha_k) * R/2;
		float y = y_k + cos(9*alpha_k) * R/2;
		if(draw)
		{
			Draw_Line(black, x_old, y_old, x, y);
		}
		x_old = x;
		y_old = y;
		draw = 1;
	}
}

void do_char()
{
	uint16_t pos = Draw_Char(red, 'A', 50, 50);
	pos = Draw_Char(red, 'B', pos, 50);
	Draw_Char(red, 'C', pos, 50);

	Draw_String(red, "Hello World!", 50, 100);
}

int main(void)
{
	LCD_Init();

	black.data = 0;

	red.data = 0;
	red.red = 0x1F;

	blue.data = 0;
	blue.blue = 0x1F;

	green.data = 0;
	green.green = 0x1F;

	white.red = 0b11111;
	white.blue = 0b11111;
	white.green = 0b111111;

	LCD_Activate();
	Paint(white);
	LCD_Deactivate();

	LCD_Activate();

	//do_faecher();
	//do_kreise(140.0, 100);
	//do_blume(70.0, 200);
	do_char();

	LCD_Deactivate();

	while(1)
	{
	}
}
