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
#ifndef _UAPI__ASM_SH_PTRACE_H
#define _UAPI__ASM_SH_PTRACE_H


#define PTRACE_GETREGS		12	/* General registers */
#define PTRACE_SETREGS		13

#define PTRACE_GETFPREGS	14	/* FPU registers */
#define PTRACE_SETFPREGS	15

#define PTRACE_GETFDPIC		31	/* get the ELF fdpic loadmap address */

#define PTRACE_GETFDPIC_EXEC	0	/* [addr] request the executable loadmap */
#define PTRACE_GETFDPIC_INTERP	1	/* [addr] request the interpreter loadmap */

#define	PTRACE_GETDSPREGS	55	/* DSP registers */
#define	PTRACE_SETDSPREGS	56

#define PT_TEXT_END_ADDR	240
#define PT_TEXT_ADDR		244	/* &(struct user)->start_code */
#define PT_DATA_ADDR		248	/* &(struct user)->start_data */
#define PT_TEXT_LEN		252

#if defined(__SH5__) || defined(CONFIG_CPU_SH5)
#include <asm/ptrace_64.h>
#else
#include <asm/ptrace_32.h>
#endif


#endif /* _UAPI__ASM_SH_PTRACE_H */
