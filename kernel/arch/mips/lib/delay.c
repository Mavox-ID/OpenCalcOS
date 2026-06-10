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
#include <beep/param.h>
#include <beep/smp.h>

#include <asm/compiler.h>
#include <asm/war.h>

void __delay(unsigned long loops)
{
	__asm__ __volatile__ (
	"	.set	noreorder				\n"
	"	.align	3					\n"
	"1:	bnez	%0, 1b					\n"
#if __SIZEOF_LONG__ == 4
	"	subu	%0, 1					\n"
#else
	"	dsubu	%0, 1					\n"
#endif
	"	.set	reorder					\n"
	: "=r" (loops)
	: "0" (loops));
}
EXPORT_SYMBOL(__delay);

/*
 * Division by multiplication: you don't have to worry about
 * loss of precision.
 *
 * Use only for very small delays ( < 1 msec).  Should probably use a
 * lookup table, really, as the multiplications take much too long with
 * short delays.  This is a "reasonable" implementation, though (and the
 * first constant multiplications gets optimized away if the delay is
 * a constant)
 */

void __udelay(unsigned long us)
{
	unsigned int lpj = raw_current_cpu_data.udelay_val;

	__delay((us * 0x000010c7ull * HZ * lpj) >> 32);
}
EXPORT_SYMBOL(__udelay);

void __ndelay(unsigned long ns)
{
	unsigned int lpj = raw_current_cpu_data.udelay_val;

	__delay((ns * 0x00000005ull * HZ * lpj) >> 32);
}
EXPORT_SYMBOL(__ndelay);
