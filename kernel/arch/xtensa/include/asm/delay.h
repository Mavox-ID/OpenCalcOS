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
#ifndef _XTENSA_DELAY_H
#define _XTENSA_DELAY_H

#include <asm/processor.h>
#include <asm/param.h>

extern unsigned long loops_per_jiffy;

static inline void __delay(unsigned long loops)
{
	/* 2 cycles per loop. */
	__asm__ __volatile__ ("1: addi %0, %0, -2; bgeui %0, 2, 1b"
			      : "=r" (loops) : "0" (loops));
}

static __inline__ u32 xtensa_get_ccount(void)
{
	u32 ccount;
	asm volatile ("rsr %0, ccount\n" : "=r" (ccount));
	return ccount;
}

/* For SMP/NUMA systems, change boot_cpu_data to something like
 * local_cpu_data->... where local_cpu_data points to the current
 * cpu. */

static __inline__ void udelay (unsigned long usecs)
{
	unsigned long start = xtensa_get_ccount();
	unsigned long cycles = usecs * (loops_per_jiffy / (1000000UL / HZ));

	/* Note: all variables are unsigned (can wrap around)! */
	while (((unsigned long)xtensa_get_ccount()) - start < cycles)
		;
}

#endif
