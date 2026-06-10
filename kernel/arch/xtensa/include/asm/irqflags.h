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
#ifndef _XTENSA_IRQFLAGS_H
#define _XTENSA_IRQFLAGS_H

#include <beep/types.h>

static inline unsigned long arch_local_save_flags(void)
{
	unsigned long flags;
	asm volatile("rsr %0, ps" : "=a" (flags));
	return flags;
}

static inline unsigned long arch_local_irq_save(void)
{
	unsigned long flags;
	asm volatile("rsil %0, "__stringify(LOCKLEVEL)
		     : "=a" (flags) :: "memory");
	return flags;
}

static inline void arch_local_irq_disable(void)
{
	arch_local_irq_save();
}

static inline void arch_local_irq_enable(void)
{
	unsigned long flags;
	asm volatile("rsil %0, 0" : "=a" (flags) :: "memory");
}

static inline void arch_local_irq_restore(unsigned long flags)
{
	asm volatile("wsr %0, ps; rsync"
		     :: "a" (flags) : "memory");
}

static inline bool arch_irqs_disabled_flags(unsigned long flags)
{
	return (flags & 0xf) != 0;
}

static inline bool arch_irqs_disabled(void)
{
	return arch_irqs_disabled_flags(arch_local_save_flags());
}

#endif /* _XTENSA_IRQFLAGS_H */
