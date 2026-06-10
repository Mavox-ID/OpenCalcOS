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
#ifndef __ASM_MACH_ATH79_IRQ_H
#define __ASM_MACH_ATH79_IRQ_H

#define MIPS_CPU_IRQ_BASE	0
#define NR_IRQS			48

#define ATH79_MISC_IRQ_BASE	8
#define ATH79_MISC_IRQ_COUNT	32

#define ATH79_PCI_IRQ_BASE	(ATH79_MISC_IRQ_BASE + ATH79_MISC_IRQ_COUNT)
#define ATH79_PCI_IRQ_COUNT	6
#define ATH79_PCI_IRQ(_x)	(ATH79_PCI_IRQ_BASE + (_x))

#define ATH79_IP2_IRQ_BASE	(ATH79_PCI_IRQ_BASE + ATH79_PCI_IRQ_COUNT)
#define ATH79_IP2_IRQ_COUNT	2
#define ATH79_IP2_IRQ(_x)	(ATH79_IP2_IRQ_BASE + (_x))

#define ATH79_CPU_IRQ_IP2	(MIPS_CPU_IRQ_BASE + 2)
#define ATH79_CPU_IRQ_USB	(MIPS_CPU_IRQ_BASE + 3)
#define ATH79_CPU_IRQ_GE0	(MIPS_CPU_IRQ_BASE + 4)
#define ATH79_CPU_IRQ_GE1	(MIPS_CPU_IRQ_BASE + 5)
#define ATH79_CPU_IRQ_MISC	(MIPS_CPU_IRQ_BASE + 6)
#define ATH79_CPU_IRQ_TIMER	(MIPS_CPU_IRQ_BASE + 7)

#define ATH79_MISC_IRQ_TIMER	(ATH79_MISC_IRQ_BASE + 0)
#define ATH79_MISC_IRQ_ERROR	(ATH79_MISC_IRQ_BASE + 1)
#define ATH79_MISC_IRQ_GPIO	(ATH79_MISC_IRQ_BASE + 2)
#define ATH79_MISC_IRQ_UART	(ATH79_MISC_IRQ_BASE + 3)
#define ATH79_MISC_IRQ_WDOG	(ATH79_MISC_IRQ_BASE + 4)
#define ATH79_MISC_IRQ_PERFC	(ATH79_MISC_IRQ_BASE + 5)
#define ATH79_MISC_IRQ_OHCI	(ATH79_MISC_IRQ_BASE + 6)
#define ATH79_MISC_IRQ_DMA	(ATH79_MISC_IRQ_BASE + 7)
#define ATH79_MISC_IRQ_TIMER2	(ATH79_MISC_IRQ_BASE + 8)
#define ATH79_MISC_IRQ_TIMER3	(ATH79_MISC_IRQ_BASE + 9)
#define ATH79_MISC_IRQ_TIMER4	(ATH79_MISC_IRQ_BASE + 10)
#define ATH79_MISC_IRQ_ETHSW	(ATH79_MISC_IRQ_BASE + 12)

#include_next <irq.h>

#endif /* __ASM_MACH_ATH79_IRQ_H */
