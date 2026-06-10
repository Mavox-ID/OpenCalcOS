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
#ifndef _ASM_DELAY_H
#define _ASM_DELAY_H

#include <asm/param.h>
#include <asm/timer-regs.h>

/*
 * delay loop - runs at __core_clock_speed_HZ / 2 [there are 2 insns in the loop]
 */
extern unsigned long __delay_loops_MHz;

static inline void __delay(unsigned long loops)
{
	asm volatile("1:	subicc	%0,#1,%0,icc0	\n"
		     "		bnc	icc0,#2,1b	\n"
		     : "=r" (loops)
		     : "0" (loops)
		     : "icc0"
		     );
}

/*
 * Use only for very small delays ( < 1 msec).  Should probably use a
 * lookup table, really, as the multiplications take much too long with
 * short delays.  This is a "reasonable" implementation, though (and the
 * first constant multiplications gets optimized away if the delay is
 * a constant)
 */

extern unsigned long loops_per_jiffy;

static inline void udelay(unsigned long usecs)
{
	__delay(usecs * __delay_loops_MHz);
}

#define ndelay(n)	udelay((n) * 5)

#endif /* _ASM_DELAY_H */
