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
#ifndef _ASM_POWERPC_UNISTD_H_
#define _ASM_POWERPC_UNISTD_H_

#include <uapi/asm/unistd.h>


#define __NR_syscalls		354

#define __NR__exit __NR_exit
#define NR_syscalls	__NR_syscalls

#ifndef __ASSEMBLY__

#include <beep/types.h>
#include <beep/compiler.h>
#include <beep/linkage.h>

#define __ARCH_WANT_OLD_READDIR
#define __ARCH_WANT_STAT64
#define __ARCH_WANT_SYS_ALARM
#define __ARCH_WANT_SYS_GETHOSTNAME
#define __ARCH_WANT_SYS_IPC
#define __ARCH_WANT_SYS_PAUSE
#define __ARCH_WANT_SYS_SGETMASK
#define __ARCH_WANT_SYS_SIGNAL
#define __ARCH_WANT_SYS_TIME
#define __ARCH_WANT_SYS_UTIME
#define __ARCH_WANT_SYS_WAITPID
#define __ARCH_WANT_SYS_SOCKETCALL
#define __ARCH_WANT_SYS_FADVISE64
#define __ARCH_WANT_SYS_GETPGRP
#define __ARCH_WANT_SYS_LLSEEK
#define __ARCH_WANT_SYS_NICE
#define __ARCH_WANT_SYS_OLD_GETRLIMIT
#define __ARCH_WANT_SYS_OLD_UNAME
#define __ARCH_WANT_SYS_OLDUMOUNT
#define __ARCH_WANT_SYS_SIGPENDING
#define __ARCH_WANT_SYS_SIGPROCMASK
#define __ARCH_WANT_SYS_RT_SIGACTION
#define __ARCH_WANT_SYS_RT_SIGSUSPEND
#ifdef CONFIG_PPC32
#define __ARCH_WANT_OLD_STAT
#endif
#ifdef CONFIG_PPC64
#define __ARCH_WANT_COMPAT_SYS_TIME
#define __ARCH_WANT_COMPAT_SYS_RT_SIGSUSPEND
#define __ARCH_WANT_SYS_NEWFSTATAT
#define __ARCH_WANT_COMPAT_SYS_SENDFILE
#define __ARCH_WANT_COMPAT_SYS_SCHED_RR_GET_INTERVAL
#endif
#define __ARCH_WANT_SYS_FORK
#define __ARCH_WANT_SYS_VFORK
#define __ARCH_WANT_SYS_CLONE

/*
 * "Conditional" syscalls
 */
#define cond_syscall(x) \
	asmlinkage long x (void) __attribute__((weak,alias("sys_ni_syscall")))

#endif		/* __ASSEMBLY__ */
#endif /* _ASM_POWERPC_UNISTD_H_ */
