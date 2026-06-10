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
#ifndef _ASM_TIMEX_H
#define _ASM_TIMEX_H

#include <unit/timex.h>

#define TICK_SIZE (tick_nsec / 1000)

#define CLOCK_TICK_RATE MN10300_JCCLK /* Underlying HZ */

#ifdef __KERNEL__

extern cycles_t cacheflush_time;

static inline cycles_t get_cycles(void)
{
	return read_timestamp_counter();
}

extern int init_clockevents(void);
extern int init_clocksource(void);

#endif /* __KERNEL__ */

#endif /* _ASM_TIMEX_H */
