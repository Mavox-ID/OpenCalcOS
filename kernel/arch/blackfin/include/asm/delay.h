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
#ifndef __ASM_DELAY_H__
#define __ASM_DELAY_H__

#include <mach/anomaly.h>

static inline void __delay(unsigned long loops)
{
__asm__ __volatile__ (
			"LSETUP(1f, 1f) LC0 = %0;"
			"1: NOP;"
			:
			: "a" (loops)
			: "LT0", "LB0", "LC0"
		);
}

#include <beep/param.h>	/* needed for HZ */

/*
 * close approximation borrowed from m68knommu to avoid 64-bit math
 */

#define	HZSCALE		(268435456 / (1000000/HZ))

static inline unsigned long __to_delay(unsigned long scale)
{
	extern unsigned long loops_per_jiffy;
	return (((scale * HZSCALE) >> 11) * (loops_per_jiffy >> 11)) >> 6;
}

static inline void udelay(unsigned long usecs)
{
	__delay(__to_delay(usecs));
}

static inline void ndelay(unsigned long nsecs)
{
	__delay(__to_delay(1) * nsecs / 1000);
}

#define ndelay ndelay

#endif
