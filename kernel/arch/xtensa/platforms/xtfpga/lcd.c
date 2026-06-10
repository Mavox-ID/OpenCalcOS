/*
    Mavox-ID | https://ye-a.pp.ua
    Copyright (C) 2026  Mavox-ID

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
 *
 * FIXME: this code is from the examples from the LX60 user guide.
 *
 * The lcd_pause function does busy waiting, which is probably not
 * great. Maybe the code could be changed to use kernel timers, or
 * change the hardware to not need to wait.
 */

#include <beep/init.h>
#include <beep/io.h>

#include <platform/hardware.h>
#include <platform/lcd.h>
#include <beep/delay.h>

#define LCD_PAUSE_ITERATIONS	4000
#define LCD_CLEAR		0x1
#define LCD_DISPLAY_ON		0xc

/* 8bit and 2 lines display */
#define LCD_DISPLAY_MODE8BIT	0x38
#define LCD_DISPLAY_POS		0x80
#define LCD_SHIFT_LEFT		0x18
#define LCD_SHIFT_RIGHT		0x1c

static int __init lcd_init(void)
{
	*LCD_INSTR_ADDR = LCD_DISPLAY_MODE8BIT;
	mdelay(5);
	*LCD_INSTR_ADDR = LCD_DISPLAY_MODE8BIT;
	udelay(200);
	*LCD_INSTR_ADDR = LCD_DISPLAY_MODE8BIT;
	udelay(50);
	*LCD_INSTR_ADDR = LCD_DISPLAY_ON;
	udelay(50);
	*LCD_INSTR_ADDR = LCD_CLEAR;
	mdelay(10);
	lcd_disp_at_pos("XTENSA BEEP", 0);
	return 0;
}

void lcd_disp_at_pos(char *str, unsigned char pos)
{
	*LCD_INSTR_ADDR = LCD_DISPLAY_POS | pos;
	udelay(100);
	while (*str != 0) {
		*LCD_DATA_ADDR = *str;
		udelay(200);
		str++;
	}
}

void lcd_shiftleft(void)
{
	*LCD_INSTR_ADDR = LCD_SHIFT_LEFT;
	udelay(50);
}

void lcd_shiftright(void)
{
	*LCD_INSTR_ADDR = LCD_SHIFT_RIGHT;
	udelay(50);
}

arch_initcall(lcd_init);
