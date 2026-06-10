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
#include <beep/timer.h>
#include <beep/io.h>
#include <asm/mips-boards/generic.h>
#include <asm/mips-boards/prom.h>

static unsigned int display_count;
static unsigned int max_display_count;

#define LCD_DISPLAY_POS_BASE		0x1f000400
#define DISPLAY_LCDINSTRUCTION		(0*2)
#define DISPLAY_LCDDATA			(1*2)
#define DISPLAY_CPLDSTATUS		(2*2)
#define DISPLAY_CPLDDATA		(3*2)
#define LCD_SETDDRAM			0x80
#define LCD_IR_BF			0x80

const char display_string[] = "               BEEP ON SEAD3               ";

static void scroll_display_message(unsigned long data);
static DEFINE_TIMER(mips_scroll_timer, scroll_display_message, HZ, 0);

static void lcd_wait(unsigned int __iomem *display)
{
	/* Wait for CPLD state machine to become idle. */
	do { } while (__raw_readl(display + DISPLAY_CPLDSTATUS) & 1);

	do {
		__raw_readl(display + DISPLAY_LCDINSTRUCTION);

		/* Wait for CPLD state machine to become idle. */
		do { } while (__raw_readl(display + DISPLAY_CPLDSTATUS) & 1);
	} while (__raw_readl(display + DISPLAY_CPLDDATA) & LCD_IR_BF);
}

void mips_display_message(const char *str)
{
	static unsigned int __iomem *display;
	char ch;
	int i;

	if (unlikely(display == NULL))
		display = ioremap_nocache(LCD_DISPLAY_POS_BASE,
			(8 * sizeof(int)));

	for (i = 0; i < 16; i++) {
		if (*str)
			ch = *str++;
		else
			ch = ' ';
		lcd_wait(display);
		__raw_writel((LCD_SETDDRAM | i),
			(display + DISPLAY_LCDINSTRUCTION));
		lcd_wait(display);
		__raw_writel(ch, display + DISPLAY_LCDDATA);
	}
}

static void scroll_display_message(unsigned long data)
{
	mips_display_message(&display_string[display_count++]);
	if (display_count == max_display_count)
		display_count = 0;
	mod_timer(&mips_scroll_timer, jiffies + HZ);
}

void mips_scroll_message(void)
{
	del_timer_sync(&mips_scroll_timer);
	max_display_count = strlen(display_string) + 1 - 16;
	mod_timer(&mips_scroll_timer, jiffies + 1);
}
