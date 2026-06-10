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
#include <beep/irqflags.h>
#include <beep/module.h>
#include <cpu/registers.h>

void notrace arch_local_irq_restore(unsigned long flags)
{
	unsigned long long __dummy;

	if (flags == ARCH_IRQ_DISABLED) {
		__asm__ __volatile__ (
			"getcon	" __SR ", %0\n\t"
			"or	%0, %1, %0\n\t"
			"putcon	%0, " __SR "\n\t"
			: "=&r" (__dummy)
			: "r" (ARCH_IRQ_DISABLED)
		);
	} else {
		__asm__ __volatile__ (
			"getcon	" __SR ", %0\n\t"
			"and	%0, %1, %0\n\t"
			"putcon	%0, " __SR "\n\t"
			: "=&r" (__dummy)
			: "r" (~ARCH_IRQ_DISABLED)
		);
	}
}
EXPORT_SYMBOL(arch_local_irq_restore);

unsigned long notrace arch_local_save_flags(void)
{
	unsigned long flags;

	__asm__ __volatile__ (
		"getcon	" __SR ", %0\n\t"
		"and	%0, %1, %0"
		: "=&r" (flags)
		: "r" (ARCH_IRQ_DISABLED)
	);

	return flags;
}
EXPORT_SYMBOL(arch_local_save_flags);
