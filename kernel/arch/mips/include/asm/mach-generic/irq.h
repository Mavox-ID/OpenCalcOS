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
#ifndef __ASM_MACH_GENERIC_IRQ_H
#define __ASM_MACH_GENERIC_IRQ_H

#ifndef NR_IRQS
#define NR_IRQS	128
#endif

#ifdef CONFIG_I8259
#ifndef I8259A_IRQ_BASE
#define I8259A_IRQ_BASE	0
#endif
#endif

#ifdef CONFIG_IRQ_CPU

#ifndef MIPS_CPU_IRQ_BASE
#ifdef CONFIG_I8259
#define MIPS_CPU_IRQ_BASE 16
#else
#define MIPS_CPU_IRQ_BASE 0
#endif /* CONFIG_I8259 */
#endif

#ifdef CONFIG_IRQ_CPU_RM7K
#ifndef RM7K_CPU_IRQ_BASE
#define RM7K_CPU_IRQ_BASE (MIPS_CPU_IRQ_BASE+8)
#endif
#endif

#endif /* CONFIG_IRQ_CPU */

#endif /* __ASM_MACH_GENERIC_IRQ_H */
