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
#include <beep/compiler.h>
#include <beep/timer.h>
#include <asm/io.h>
#include <asm/mips-boards/generic.h>
#include <asm/mips-boards/prom.h>

extern const char display_string[];
static unsigned int display_count;
static unsigned int max_display_count;

void mips_display_message(const char *str)
{
	static unsigned int __iomem *display = NULL;
	int i;

	if (unlikely(display == NULL))
		display = ioremap(ASCII_DISPLAY_POS_BASE, 16*sizeof(int));

	for (i = 0; i <= 14; i=i+2) {
	         if (*str)
		         __raw_writel(*str++, display + i);
		 else
		         __raw_writel(' ', display + i);
	}
}

static void scroll_display_message(unsigned long data);
static DEFINE_TIMER(mips_scroll_timer, scroll_display_message, HZ, 0);

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
	max_display_count = strlen(display_string) + 1 - 8;
	mod_timer(&mips_scroll_timer, jiffies + 1);
}
