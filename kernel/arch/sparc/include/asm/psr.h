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
#ifndef __BEEP_SPARC_PSR_H
#define __BEEP_SPARC_PSR_H

#include <uapi/asm/psr.h>


#ifndef __ASSEMBLY__
/* Get the %psr register. */
static inline unsigned int get_psr(void)
{
	unsigned int psr;
	__asm__ __volatile__(
		"rd	%%psr, %0\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
	: "=r" (psr)
	: /* no inputs */
	: "memory");

	return psr;
}

static inline void put_psr(unsigned int new_psr)
{
	__asm__ __volatile__(
		"wr	%0, 0x0, %%psr\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
	: /* no outputs */
	: "r" (new_psr)
	: "memory", "cc");
}

/* Get the %fsr register.  Be careful, make sure the floating point
 * enable bit is set in the %psr when you execute this or you will
 * incur a trap.
 */

extern unsigned int fsr_storage;

static inline unsigned int get_fsr(void)
{
	unsigned int fsr = 0;

	__asm__ __volatile__(
		"st	%%fsr, %1\n\t"
		"ld	%1, %0\n\t"
	: "=r" (fsr)
	: "m" (fsr_storage));

	return fsr;
}

#endif /* !(__ASSEMBLY__) */

#endif /* !(__BEEP_SPARC_PSR_H) */
