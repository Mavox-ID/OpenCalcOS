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
#define ASM_OFFSETS_C 1

#include <beep/kbuild.h>
#include <beep/threads.h>
#include <asm/native/irq.h>
#include <asm/xen/irq.h>

void foo(void)
{
	union paravirt_nr_irqs_max {
		char ia64_native_nr_irqs[IA64_NATIVE_NR_IRQS];
#ifdef CONFIG_XEN
		char xen_nr_irqs[XEN_NR_IRQS];
#endif
	};

	DEFINE(NR_IRQS, sizeof (union paravirt_nr_irqs_max));
}
