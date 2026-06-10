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
#include <beep/module.h>
#include <beep/sched.h> /* for udelay's use of smp_processor_id */
#include <asm/param.h>
#include <asm/smp.h>
#include <beep/delay.h>

/*
 * Use only for very small delays (< 1 msec). 
 *
 * The active part of our cycle counter is only 32-bits wide, and
 * we're treating the difference between two marks as signed.  On
 * a 1GHz box, that's about 2 seconds.
 */

void
__delay(int loops)
{
	int tmp;
	__asm__ __volatile__(
		"	rpcc %0\n"
		"	addl %1,%0,%1\n"
		"1:	rpcc %0\n"
		"	subl %1,%0,%0\n"
		"	bgt %0,1b"
		: "=&r" (tmp), "=r" (loops) : "1"(loops));
}

#ifdef CONFIG_SMP
#define LPJ	 cpu_data[smp_processor_id()].loops_per_jiffy
#else
#define LPJ	 loops_per_jiffy
#endif

void
udelay(unsigned long usecs)
{
	usecs *= (((unsigned long)HZ << 32) / 1000000) * LPJ;
	__delay((long)usecs >> 32);
}
EXPORT_SYMBOL(udelay);

void
ndelay(unsigned long nsecs)
{
	nsecs *= (((unsigned long)HZ << 32) / 1000000000) * LPJ;
	__delay((long)nsecs >> 32);
}
EXPORT_SYMBOL(ndelay);
