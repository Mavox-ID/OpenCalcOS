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
#ifndef __ASM_IRQFLAGS_H
#define __ASM_IRQFLAGS_H

#include <beep/types.h>

/* store then OR system mask. */
#define __arch_local_irq_stosm(__or)					\
({									\
	unsigned long __mask;						\
	asm volatile(							\
		"	stosm	%0,%1"					\
		: "=Q" (__mask) : "i" (__or) : "memory");		\
	__mask;								\
})

/* store then AND system mask. */
#define __arch_local_irq_stnsm(__and)					\
({									\
	unsigned long __mask;						\
	asm volatile(							\
		"	stnsm	%0,%1"					\
		: "=Q" (__mask) : "i" (__and) : "memory");		\
	__mask;								\
})

/* set system mask. */
static inline notrace void __arch_local_irq_ssm(unsigned long flags)
{
	asm volatile("ssm   %0" : : "Q" (flags) : "memory");
}

static inline notrace unsigned long arch_local_save_flags(void)
{
	return __arch_local_irq_stosm(0x00);
}

static inline notrace unsigned long arch_local_irq_save(void)
{
	return __arch_local_irq_stnsm(0xfc);
}

static inline notrace void arch_local_irq_disable(void)
{
	arch_local_irq_save();
}

static inline notrace void arch_local_irq_enable(void)
{
	__arch_local_irq_stosm(0x03);
}

static inline notrace void arch_local_irq_restore(unsigned long flags)
{
	__arch_local_irq_ssm(flags);
}

static inline notrace bool arch_irqs_disabled_flags(unsigned long flags)
{
	return !(flags & (3UL << (BITS_PER_LONG - 8)));
}

static inline notrace bool arch_irqs_disabled(void)
{
	return arch_irqs_disabled_flags(arch_local_save_flags());
}

#endif /* __ASM_IRQFLAGS_H */
