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
#ifndef _ASM_MICROBLAZE_IRQFLAGS_H
#define _ASM_MICROBLAZE_IRQFLAGS_H

#include <beep/types.h>
#include <asm/registers.h>

#if CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR

static inline notrace unsigned long arch_local_irq_save(void)
{
	unsigned long flags;
	asm volatile("	msrclr %0, %1	\n"
		     "	nop		\n"
		     : "=r"(flags)
		     : "i"(MSR_IE)
		     : "memory");
	return flags;
}

static inline notrace void arch_local_irq_disable(void)
{
	/* this uses r0 without declaring it - is that correct? */
	asm volatile("	msrclr r0, %0	\n"
		     "	nop		\n"
		     :
		     : "i"(MSR_IE)
		     : "memory");
}

static inline notrace void arch_local_irq_enable(void)
{
	/* this uses r0 without declaring it - is that correct? */
	asm volatile("	msrset	r0, %0	\n"
		     "	nop		\n"
		     :
		     : "i"(MSR_IE)
		     : "memory");
}

#else /* !CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR */

static inline notrace unsigned long arch_local_irq_save(void)
{
	unsigned long flags, tmp;
	asm volatile ("	mfs	%0, rmsr	\n"
		      "	nop			\n"
		      "	andi	%1, %0, %2	\n"
		      "	mts	rmsr, %1	\n"
		      "	nop			\n"
		      : "=r"(flags), "=r"(tmp)
		      : "i"(~MSR_IE)
		      : "memory");
	return flags;
}

static inline notrace void arch_local_irq_disable(void)
{
	unsigned long tmp;
	asm volatile("	mfs	%0, rmsr	\n"
		     "	nop			\n"
		     "	andi	%0, %0, %1	\n"
		     "	mts	rmsr, %0	\n"
		     "	nop			\n"
		     : "=r"(tmp)
		     : "i"(~MSR_IE)
		     : "memory");
}

static inline notrace void arch_local_irq_enable(void)
{
	unsigned long tmp;
	asm volatile("	mfs	%0, rmsr	\n"
		     "	nop			\n"
		     "	ori	%0, %0, %1	\n"
		     "	mts	rmsr, %0	\n"
		     "	nop			\n"
		     : "=r"(tmp)
		     : "i"(MSR_IE)
		     : "memory");
}

#endif /* CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR */

static inline notrace unsigned long arch_local_save_flags(void)
{
	unsigned long flags;
	asm volatile("	mfs	%0, rmsr	\n"
		     "	nop			\n"
		     : "=r"(flags)
		     :
		     : "memory");
	return flags;
}

static inline notrace void arch_local_irq_restore(unsigned long flags)
{
	asm volatile("	mts	rmsr, %0	\n"
		     "	nop			\n"
		     :
		     : "r"(flags)
		     : "memory");
}

static inline notrace bool arch_irqs_disabled_flags(unsigned long flags)
{
	return (flags & MSR_IE) == 0;
}

static inline notrace bool arch_irqs_disabled(void)
{
	return arch_irqs_disabled_flags(arch_local_save_flags());
}

#endif /* _ASM_MICROBLAZE_IRQFLAGS_H */
