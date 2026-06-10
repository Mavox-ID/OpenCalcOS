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
#ifndef _ASM_IRQ_H
#define _ASM_IRQ_H

#include <asm/intctl-regs.h>
#include <asm/reset-regs.h>
#include <proc/irq.h>

/* this number is used when no interrupt has been assigned */
#define NO_IRQ		INT_MAX

/*
 * hardware irq numbers
 * - the ASB2364 has an FPGA with an IRQ multiplexer on it
 */
#ifdef CONFIG_MN10300_UNIT_ASB2364
#include <unit/irq.h>
#else
#define NR_CPU_IRQS	GxICR_NUM_IRQS
#define NR_IRQS		NR_CPU_IRQS
#endif

/* external hardware irq numbers */
#define NR_XIRQS	GxICR_NUM_XIRQS

#define irq_canonicalize(IRQ) (IRQ)

#endif /* _ASM_IRQ_H */
