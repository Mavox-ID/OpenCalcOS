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
#ifndef __MACH_PUV3_OCD_H__
#define __MACH_PUV3_OCD_H__

#if defined(CONFIG_DEBUG_OCD)
static inline void ocd_putc(unsigned int c)
{
	int status, i = 0x2000000;

	do {
		if (--i < 0)
			return;

		asm volatile ("movc %0, p1.c0, #0" : "=r" (status));
	} while (status & 2);

	asm("movc p1.c1, %0, #1" : : "r" (c));
}

#define putc(ch)	ocd_putc(ch)
#else
#define putc(ch)
#endif

#endif
