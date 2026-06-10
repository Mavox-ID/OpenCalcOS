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
#ifndef _ASMALPHA_TIMEX_H
#define _ASMALPHA_TIMEX_H

/* With only one or two oddballs, we use the RTC as the ticker, selecting
   the 32.768kHz reference clock, which nicely divides down to our HZ.  */
#define CLOCK_TICK_RATE	32768

/*
 * Standard way to access the cycle counter.
 * Currently only used on SMP for scheduling.
 *
 * Only the low 32 bits are available as a continuously counting entity. 
 * But this only means we'll force a reschedule every 8 seconds or so,
 * which isn't an evil thing.
 */

typedef unsigned int cycles_t;

static inline cycles_t get_cycles (void)
{
	cycles_t ret;
	__asm__ __volatile__ ("rpcc %0" : "=r"(ret));
	return ret;
}

#endif
