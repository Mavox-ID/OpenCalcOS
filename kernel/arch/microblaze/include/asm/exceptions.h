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
#ifndef _ASM_MICROBLAZE_EXCEPTIONS_H
#define _ASM_MICROBLAZE_EXCEPTIONS_H

#ifdef __KERNEL__

#ifndef CONFIG_MMU
#define EX_HANDLER_STACK_SIZ	(4*19)
#endif

#ifndef __ASSEMBLY__

/* Macros to enable and disable HW exceptions in the MSR */
/* Define MSR enable bit for HW exceptions */
#define HWEX_MSR_BIT (1 << 8)

#if CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR
#define __enable_hw_exceptions()					\
	__asm__ __volatile__ ("	msrset	r0, %0;				\
				nop;"					\
				:					\
				: "i" (HWEX_MSR_BIT)			\
				: "memory")

#define __disable_hw_exceptions()					\
	__asm__ __volatile__ ("	msrclr r0, %0;				\
				nop;"					\
				:					\
				: "i" (HWEX_MSR_BIT)			\
				: "memory")
#else /* !CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR */
#define __enable_hw_exceptions()					\
	__asm__ __volatile__ ("						\
				mfs	r12, rmsr;			\
				nop;					\
				ori	r12, r12, %0;			\
				mts	rmsr, r12;			\
				nop;"					\
				:					\
				: "i" (HWEX_MSR_BIT)			\
				: "memory", "r12")

#define __disable_hw_exceptions()					\
	__asm__ __volatile__ ("						\
				mfs	r12, rmsr;			\
				nop;					\
				andi	r12, r12, ~%0;			\
				mts	rmsr, r12;			\
				nop;"					\
				:					\
				: "i" (HWEX_MSR_BIT)			\
				: "memory", "r12")
#endif /* CONFIG_XILINX_MICROBLAZE0_USE_MSR_INSTR */

asmlinkage void full_exception(struct pt_regs *regs, unsigned int type,
							int fsr, int addr);

asmlinkage void sw_exception(struct pt_regs *regs);
void bad_page_fault(struct pt_regs *regs, unsigned long address, int sig);

void die(const char *str, struct pt_regs *fp, long err);
void _exception(int signr, struct pt_regs *regs, int code, unsigned long addr);

#endif /*__ASSEMBLY__ */
#endif /* __KERNEL__ */
#endif /* _ASM_MICROBLAZE_EXCEPTIONS_H */
