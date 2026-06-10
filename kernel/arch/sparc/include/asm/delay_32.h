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
#ifndef __SPARC_DELAY_H
#define __SPARC_DELAY_H

#include <asm/cpudata.h>

static inline void __delay(unsigned long loops)
{
	__asm__ __volatile__("cmp %0, 0\n\t"
			     "1: bne 1b\n\t"
			     "subcc %0, 1, %0\n" :
			     "=&r" (loops) :
			     "0" (loops) :
			     "cc");
}

/* This is too messy with inline asm on the Sparc. */
extern void __udelay(unsigned long usecs, unsigned long lpj);
extern void __ndelay(unsigned long nsecs, unsigned long lpj);

#ifdef CONFIG_SMP
#define __udelay_val	cpu_data(smp_processor_id()).udelay_val
#else /* SMP */
#define __udelay_val	loops_per_jiffy
#endif /* SMP */
#define udelay(__usecs)	__udelay(__usecs, __udelay_val)
#define ndelay(__nsecs)	__ndelay(__nsecs, __udelay_val)

#endif /* defined(__SPARC_DELAY_H) */
