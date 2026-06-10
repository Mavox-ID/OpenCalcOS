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
#ifndef __ASM_OPENRISC_TIMEX_H
#define __ASM_OPENRISC_TIMEX_H

#define get_cycles get_cycles

#include <asm-generic/timex.h>
#include <asm/spr.h>
#include <asm/spr_defs.h>

static inline cycles_t get_cycles(void)
{
	return mfspr(SPR_TTCR);
}

/* This isn't really used any more */
#define CLOCK_TICK_RATE 1000

#define ARCH_HAS_READ_CURRENT_TIMER

#endif
