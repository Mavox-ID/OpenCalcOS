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
#ifndef _ASM_MICROBLAZE_DELAY_H
#define _ASM_MICROBLAZE_DELAY_H

extern inline void __delay(unsigned long loops)
{
	asm volatile ("# __delay		\n\t"		\
			"1: addi	%0, %0, -1\t\n"		\
			"bneid	%0, 1b		\t\n"		\
			"nop			\t\n"
			: "=r" (loops)
			: "0" (loops));
}

/*
 * Note that 19 * 226 == 4294 ==~ 2^32 / 10^6, so
 * loops = (4294 * usecs * loops_per_jiffy * HZ) / 2^32.
 *
 * The mul instruction gives us loops = (a * b) / 2^32.
 * We choose a = usecs * 19 * HZ and b = loops_per_jiffy * 226
 * because this lets us support a wide range of HZ and
 * loops_per_jiffy values without either a or b overflowing 2^32.
 * Thus we need usecs * HZ <= (2^32 - 1) / 19 = 226050910 and
 * loops_per_jiffy <= (2^32 - 1) / 226 = 19004280
 * (which corresponds to ~3800 bogomips at HZ = 100).
 * -- paulus
 */
#define __MAX_UDELAY	(226050910UL/HZ)	/* maximum udelay argument */
#define __MAX_NDELAY	(4294967295UL/HZ)	/* maximum ndelay argument */

extern unsigned long loops_per_jiffy;

extern inline void __udelay(unsigned int x)
{

	unsigned long long tmp =
		(unsigned long long)x * (unsigned long long)loops_per_jiffy \
			* 226LL;
	unsigned loops = tmp >> 32;

/*
	__asm__("mulxuu %0,%1,%2" : "=r" (loops) :
		"r" (x), "r" (loops_per_jiffy * 226));
*/
	__delay(loops);
}

extern void __bad_udelay(void);		/* deliberately undefined */
extern void __bad_ndelay(void);		/* deliberately undefined */

#define udelay(n) (__builtin_constant_p(n) ? \
	((n) > __MAX_UDELAY ? __bad_udelay() : __udelay((n) * (19 * HZ))) : \
	__udelay((n) * (19 * HZ)))

#define ndelay(n) (__builtin_constant_p(n) ? \
	((n) > __MAX_NDELAY ? __bad_ndelay() : __udelay((n) * HZ)) : \
	__udelay((n) * HZ))

#define muldiv(a, b, c)		(((a)*(b))/(c))

#endif /* _ASM_MICROBLAZE_DELAY_H */
