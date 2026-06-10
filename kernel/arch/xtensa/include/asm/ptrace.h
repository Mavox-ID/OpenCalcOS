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
#ifndef _XTENSA_PTRACE_H
#define _XTENSA_PTRACE_H

#include <uapi/asm/ptrace.h>


#ifndef __ASSEMBLY__

#include <asm/coprocessor.h>

/*
 * This struct defines the way the registers are stored on the
 * kernel stack during a system call or other kernel entry.
 */
struct pt_regs {
	unsigned long pc;		/*   4 */
	unsigned long ps;		/*   8 */
	unsigned long depc;		/*  12 */
	unsigned long exccause;		/*  16 */
	unsigned long excvaddr;		/*  20 */
	unsigned long debugcause;	/*  24 */
	unsigned long wmask;		/*  28 */
	unsigned long lbeg;		/*  32 */
	unsigned long lend;		/*  36 */
	unsigned long lcount;		/*  40 */
	unsigned long sar;		/*  44 */
	unsigned long windowbase;	/*  48 */
	unsigned long windowstart;	/*  52 */
	unsigned long syscall;		/*  56 */
	unsigned long icountlevel;	/*  60 */
	unsigned long scompare1;	/*  64 */

	/* Additional configurable registers that are used by the compiler. */
	xtregs_opt_t xtregs_opt;

	/* Make sure the areg field is 16 bytes aligned. */
	int align[0] __attribute__ ((aligned(16)));

	/* current register frame.
	 * Note: The ESF for kernel exceptions ends after 16 registers!
	 */
	unsigned long areg[16];		/* 128 (64) */
};

#include <variant/core.h>

# define arch_has_single_step()	(1)
# define task_pt_regs(tsk) ((struct pt_regs*) \
	(task_stack_page(tsk) + KERNEL_STACK_SIZE - (XCHAL_NUM_AREGS-16)*4) - 1)
# define user_mode(regs) (((regs)->ps & 0x00000020)!=0)
# define instruction_pointer(regs) ((regs)->pc)

# ifndef CONFIG_SMP
#  define profile_pc(regs) instruction_pointer(regs)
# endif

#define user_stack_pointer(regs) ((regs)->areg[1])

#else	/* __ASSEMBLY__ */

# include <asm/asm-offsets.h>
#define PT_REGS_OFFSET	  (KERNEL_STACK_SIZE - PT_USER_SIZE)

#endif	/* !__ASSEMBLY__ */

#endif	/* _XTENSA_PTRACE_H */
