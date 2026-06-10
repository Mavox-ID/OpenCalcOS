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
#ifndef __UNICORE_IRQFLAGS_H__
#define __UNICORE_IRQFLAGS_H__

#ifdef __KERNEL__

#include <asm/ptrace.h>

#define ARCH_IRQ_DISABLED	(PRIV_MODE | PSR_I_BIT)
#define ARCH_IRQ_ENABLED	(PRIV_MODE)

/*
 * Save the current interrupt enable state.
 */
static inline unsigned long arch_local_save_flags(void)
{
	unsigned long temp;

	asm volatile("mov %0, asr" : "=r" (temp) : : "memory", "cc");

	return temp & PSR_c;
}

/*
 * restore saved IRQ state
 */
static inline void arch_local_irq_restore(unsigned long flags)
{
	unsigned long temp;

	asm volatile(
		"mov	%0, asr\n"
		"mov.a	asr, %1\n"
		"mov.f	asr, %0"
		: "=&r" (temp)
		: "r" (flags)
		: "memory", "cc");
}

#include <asm-generic/irqflags.h>

#endif
#endif
