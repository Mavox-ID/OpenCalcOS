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
#ifndef _M68K_BLINKEN_H
#define _M68K_BLINKEN_H

#include <asm/setup.h>
#include <asm/io.h>

#define HP300_LEDS		0xf001ffff

extern unsigned char hp300_ledstate;

static __inline__ void blinken_leds(int on, int off)
{
	if (MACH_IS_HP300)
	{
		hp300_ledstate |= on;
		hp300_ledstate &= ~off;
		out_8(HP300_LEDS, ~hp300_ledstate);
	}
}

#endif
