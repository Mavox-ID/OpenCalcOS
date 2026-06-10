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
#ifndef _ASM_C6X_TIMEX_H
#define _ASM_C6X_TIMEX_H

#define CLOCK_TICK_RATE ((1000 * 1000000UL) / 6)

/* 64-bit timestamp */
typedef unsigned long long cycles_t;

static inline cycles_t get_cycles(void)
{
	unsigned l, h;

	asm volatile (" dint\n"
		      " mvc .s2 TSCL,%0\n"
		      " mvc .s2 TSCH,%1\n"
		      " rint\n"
		      : "=b"(l), "=b"(h));
	return ((cycles_t)h << 32) | l;
}

#endif /* _ASM_C6X_TIMEX_H */
