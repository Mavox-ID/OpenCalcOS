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
#include <beep/sched.h>
#include <asm/param.h>

/*
 * Use only for very small delays (< 1 msec).
 *
 * The active part of our cycle counter is only 32-bits wide, and
 * we're treating the difference between two marks as signed.  On
 * a 1GHz box, that's about 2 seconds.
 */

void __delay(unsigned long loops)
{
	long long dummy;
	__asm__ __volatile__("gettr	tr0, %1\n\t"
			     "pta	$+4, tr0\n\t"
			     "addi	%0, -1, %0\n\t"
			     "bne	%0, r63, tr0\n\t"
			     "ptabs	%1, tr0\n\t":"=r"(loops),
			     "=r"(dummy)
			     :"0"(loops));
}

void __const_udelay(unsigned long xloops)
{
	__delay(xloops * (HZ * cpu_data[raw_smp_processor_id()].loops_per_jiffy));
}

void __udelay(unsigned long usecs)
{
	__const_udelay(usecs * 0x000010c6);  /* 2**32 / 1000000 */
}

void __ndelay(unsigned long nsecs)
{
	__const_udelay(nsecs * 0x00000005);
}
