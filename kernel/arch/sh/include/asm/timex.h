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
#ifndef __ASM_SH_TIMEX_H
#define __ASM_SH_TIMEX_H

/*
 * Only parts using the legacy CPG code for their clock framework
 * implementation need to define their own Pclk value. If provided, this
 * can be used for accurately setting CLOCK_TICK_RATE, otherwise we
 * simply fall back on the i8253 PIT value.
 */
#ifdef CONFIG_SH_PCLK_FREQ
#define CLOCK_TICK_RATE		(CONFIG_SH_PCLK_FREQ / 4) /* Underlying HZ */
#else
#define CLOCK_TICK_RATE		1193180
#endif

#include <asm-generic/timex.h>

#endif /* __ASM_SH_TIMEX_H */
