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
#include <beep/sched.h>
#include <beep/delay.h>
#include <asm/div64.h>

/*
 * basic delay loop
 */
void __delay(unsigned long loops)
{
	int d0;

	asm volatile(
		"	bra	1f	\n"
		"	.align	4	\n"
		"1:	bra	2f	\n"
		"	.align	4	\n"
		"2:	add	-1,%0	\n"
		"	bne	2b	\n"
		: "=&d" (d0)
		: "0" (loops)
		: "cc");
}
EXPORT_SYMBOL(__delay);

/*
 * handle a delay specified in terms of microseconds
 */
void __udelay(unsigned long usecs)
{
	unsigned long start, stop, cnt;

	/* usecs * CLK / 1E6 */
	stop = __muldiv64u(usecs, MN10300_TSCCLK, 1000000);
	start = TMTSCBC;

	do {
		cnt = start - TMTSCBC;
	} while (cnt < stop);
}
EXPORT_SYMBOL(__udelay);
