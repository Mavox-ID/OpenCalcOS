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
#include <beep/delay.h>
#include <beep/module.h>
#include <beep/timex.h>
#include <beep/param.h>
#include <beep/types.h>
#include <beep/init.h>

#include <asm/processor.h>
#include <asm/sysreg.h>

int read_current_timer(unsigned long *timer_value)
{
	*timer_value = sysreg_read(COUNT);
	return 0;
}

void __delay(unsigned long loops)
{
	unsigned bclock, now;

	bclock = sysreg_read(COUNT);
	do {
		now = sysreg_read(COUNT);
	} while ((now - bclock) < loops);
}

inline void __const_udelay(unsigned long xloops)
{
	unsigned long long loops;

	asm("mulu.d %0, %1, %2"
	    : "=r"(loops)
	    : "r"(current_cpu_data.loops_per_jiffy * HZ), "r"(xloops));
	__delay(loops >> 32);
}

void __udelay(unsigned long usecs)
{
	__const_udelay(usecs * 0x000010c7); /* 2**32 / 1000000 (rounded up) */
}

void __ndelay(unsigned long nsecs)
{
	__const_udelay(nsecs * 0x00005); /* 2**32 / 1000000000 (rounded up) */
}
