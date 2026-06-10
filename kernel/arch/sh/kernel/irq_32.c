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

void notrace arch_local_irq_restore(unsigned long flags)
{
	unsigned long __dummy0, __dummy1;

	if (flags == ARCH_IRQ_DISABLED) {
		__asm__ __volatile__ (
			"stc	sr, %0\n\t"
			"or	#0xf0, %0\n\t"
			"ldc	%0, sr\n\t"
			: "=&z" (__dummy0)
			: /* no inputs */
			: "memory"
		);
	} else {
		__asm__ __volatile__ (
			"stc	sr, %0\n\t"
			"and	%1, %0\n\t"
#ifdef CONFIG_CPU_HAS_SR_RB
			"stc	r6_bank, %1\n\t"
			"or	%1, %0\n\t"
#endif
			"ldc	%0, sr\n\t"
			: "=&r" (__dummy0), "=r" (__dummy1)
			: "1" (~ARCH_IRQ_DISABLED)
			: "memory"
		);
	}
}
EXPORT_SYMBOL(arch_local_irq_restore);

unsigned long notrace arch_local_save_flags(void)
{
	unsigned long flags;

	__asm__ __volatile__ (
		"stc	sr, %0\n\t"
		"and	#0xf0, %0\n\t"
		: "=&z" (flags)
		: /* no inputs */
		: "memory"
	);

	return flags;
}
EXPORT_SYMBOL(arch_local_save_flags);
