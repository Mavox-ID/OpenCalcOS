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
#ifndef _ASM_USER_H
#define _ASM_USER_H

#include <asm/page.h>
#include <beep/ptrace.h>

#ifndef __ASSEMBLY__
/*
 * When the kernel dumps core, it starts by dumping the user struct - this will
 * be used by gdb to figure out where the data and stack segments are within
 * the file, and what virtual addresses to use.
 */
struct user {
	/* We start with the registers, to mimic the way that "memory" is
	 * returned from the ptrace(3,...) function.
	 */
	struct pt_regs regs;		/* Where the registers are actually stored */

	/* The rest of this junk is to help gdb figure out what goes where */
	unsigned long int u_tsize;	/* Text segment size (pages). */
	unsigned long int u_dsize;	/* Data segment size (pages). */
	unsigned long int u_ssize;	/* Stack segment size (pages). */
	unsigned long start_code;	/* Starting virtual address of text. */
	unsigned long start_stack;	/* Starting virtual address of stack area.
					   This is actually the bottom of the stack,
					   the top of the stack is always found in the
					   esp register.  */
	long int signal;		/* Signal that caused the core dump. */
	int reserved;			/* No longer used */
	struct user_pt_regs *u_ar0;	/* Used by gdb to help find the values for */

	/* the registers */
	unsigned long magic;		/* To uniquely identify a core file */
	char u_comm[32];		/* User command that was responsible */
};
#endif

#define NBPG PAGE_SIZE
#define UPAGES 1
#define HOST_TEXT_START_ADDR	+(u.start_code)
#define HOST_STACK_END_ADDR	+(u.start_stack + u.u_ssize * NBPG)

#endif /* _ASM_USER_H */
