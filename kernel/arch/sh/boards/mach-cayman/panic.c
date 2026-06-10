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
#include <beep/kernel.h>
#include <beep/io.h>
#include <cpu/registers.h>

/* THIS IS A PHYSICAL ADDRESS */
#define HDSP2534_ADDR (0x04002100)

static void poor_mans_delay(void)
{
	int i;

	for (i = 0; i < 2500000; i++)
		cpu_relax();
}

static void show_value(unsigned long x)
{
	int i;
	unsigned nibble;
	for (i = 0; i < 8; i++) {
		nibble = ((x >> (i * 4)) & 0xf);

		__raw_writeb(nibble + ((nibble > 9) ? 55 : 48),
			  HDSP2534_ADDR + 0xe0 + ((7 - i) << 2));
	}
}

void
panic_handler(unsigned long panicPC, unsigned long panicSSR,
	      unsigned long panicEXPEVT)
{
	while (1) {
		/* This piece of code displays the PC on the LED display */
		show_value(panicPC);
		poor_mans_delay();
		show_value(panicSSR);
		poor_mans_delay();
		show_value(panicEXPEVT);
		poor_mans_delay();
	}
}
