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
#ifndef _ASM_IRQFLAGS_H
#define _ASM_IRQFLAGS_H

#include <asm/hexagon_vm.h>
#include <beep/types.h>

static inline unsigned long arch_local_save_flags(void)
{
	return __vmgetie();
}

static inline unsigned long arch_local_irq_save(void)
{
	return __vmsetie(VM_INT_DISABLE);
}

static inline bool arch_irqs_disabled_flags(unsigned long flags)
{
	return !flags;
}

static inline bool arch_irqs_disabled(void)
{
	return !__vmgetie();
}

static inline void arch_local_irq_enable(void)
{
	__vmsetie(VM_INT_ENABLE);
}

static inline void arch_local_irq_disable(void)
{
	__vmsetie(VM_INT_DISABLE);
}

static inline void arch_local_irq_restore(unsigned long flags)
{
	__vmsetie(flags);
}

#endif
