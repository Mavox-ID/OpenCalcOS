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
#ifndef __SYSDEP_I386_PTRACE_H
#define __SYSDEP_I386_PTRACE_H

#define MAX_FP_NR HOST_FPX_SIZE

static inline void update_debugregs(int seq) {}

/* syscall emulation path in ptrace */

#ifndef PTRACE_SYSEMU
#define PTRACE_SYSEMU 31
#endif

void set_using_sysemu(int value);
int get_using_sysemu(void);
extern int sysemu_supported;

#ifndef PTRACE_SYSEMU_SINGLESTEP
#define PTRACE_SYSEMU_SINGLESTEP 32
#endif

#define UPT_SYSCALL_ARG1(r) UPT_BX(r)
#define UPT_SYSCALL_ARG2(r) UPT_CX(r)
#define UPT_SYSCALL_ARG3(r) UPT_DX(r)
#define UPT_SYSCALL_ARG4(r) UPT_SI(r)
#define UPT_SYSCALL_ARG5(r) UPT_DI(r)
#define UPT_SYSCALL_ARG6(r) UPT_BP(r)

extern void arch_init_registers(int pid);

#endif
