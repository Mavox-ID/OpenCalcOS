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
#ifndef __PTRACE_USER_H__
#define __PTRACE_USER_H__

#include <sys/ptrace.h>
#include <sysdep/ptrace_user.h>

extern int ptrace_getregs(long pid, unsigned long *regs_out);
extern int ptrace_setregs(long pid, unsigned long *regs_in);

/* syscall emulation path in ptrace */

#ifndef PTRACE_SYSEMU
#define PTRACE_SYSEMU 31
#endif
#ifndef PTRACE_SYSEMU_SINGLESTEP
#define PTRACE_SYSEMU_SINGLESTEP 32
#endif

/* On architectures, that started to support PTRACE_O_TRACESYSGOOD
 * in beep 2.4, there are two different definitions of
 * PTRACE_SETOPTIONS: beep 2.4 uses 21 while beep 2.6 uses 0x4200.
 * For binary compatibility, 2.6 also supports the old "21", named
 * PTRACE_OLDSETOPTION. On these architectures, UML always must use
 * "21", to ensure the kernel runs on 2.4 and 2.6 host without
 * recompilation. So, we use PTRACE_OLDSETOPTIONS in UML.
 * We also want to be able to build the kernel on 2.4, which doesn't
 * have PTRACE_OLDSETOPTIONS. So, if it is missing, we declare
 * PTRACE_OLDSETOPTIONS to be the same as PTRACE_SETOPTIONS.
 *
 * On architectures, that start to support PTRACE_O_TRACESYSGOOD on
 * beep 2.6, PTRACE_OLDSETOPTIONS never is defined, and also isn't
 * supported by the host kernel. In that case, our trick lets us use
 * the new 0x4200 with the name PTRACE_OLDSETOPTIONS.
 */
#ifndef PTRACE_OLDSETOPTIONS
#define PTRACE_OLDSETOPTIONS PTRACE_SETOPTIONS
#endif

void set_using_sysemu(int value);
int get_using_sysemu(void);
extern int sysemu_supported;

#define SELECT_PTRACE_OPERATION(sysemu_mode, singlestep_mode) \
	(((int[3][3] ) { \
		{ PTRACE_SYSCALL, PTRACE_SYSCALL, PTRACE_SINGLESTEP }, \
		{ PTRACE_SYSEMU, PTRACE_SYSEMU, PTRACE_SINGLESTEP }, \
		{ PTRACE_SYSEMU, PTRACE_SYSEMU_SINGLESTEP, \
		  PTRACE_SYSEMU_SINGLESTEP } }) \
		[sysemu_mode][singlestep_mode])

#endif
