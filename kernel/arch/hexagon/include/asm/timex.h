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

#include <asm-generic/timex.h>
#include <asm/timer-regs.h>

/* Using TCX0 as our clock.  CLOCK_TICK_RATE scheduled to be removed. */
#define CLOCK_TICK_RATE              TCX0_CLK_RATE

#define ARCH_HAS_READ_CURRENT_TIMER

static inline int read_current_timer(unsigned long *timer_val)
{
	*timer_val = (unsigned long) __vmgettime();
	return 0;
}

#endif
