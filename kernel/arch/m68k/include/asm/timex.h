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
#ifndef _ASMm68K_TIMEX_H
#define _ASMm68K_TIMEX_H

#ifdef CONFIG_COLDFIRE
/*
 * CLOCK_TICK_RATE should give the underlying frequency of the tick timer
 * to make ntp work best.  For Coldfires, that's the main clock.
 */
#include <asm/coldfire.h>
#define CLOCK_TICK_RATE	MCF_CLK
#else
/*
 * This default CLOCK_TICK_RATE is probably wrong for many 68k boards
 * Users of those boards will need to check and modify accordingly
 */
#define CLOCK_TICK_RATE	1193180 /* Underlying HZ */
#endif

typedef unsigned long cycles_t;

static inline cycles_t get_cycles(void)
{
	return 0;
}

#endif
