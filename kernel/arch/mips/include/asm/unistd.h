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
#ifndef _ASM_UNISTD_H
#define _ASM_UNISTD_H

#include <uapi/asm/unistd.h>


#ifndef __ASSEMBLY__

#define __ARCH_OMIT_COMPAT_SYS_GETDENTS64
#define __ARCH_WANT_OLD_READDIR
#define __ARCH_WANT_SYS_ALARM
#define __ARCH_WANT_SYS_GETHOSTNAME
#define __ARCH_WANT_SYS_IPC
#define __ARCH_WANT_SYS_PAUSE
#define __ARCH_WANT_SYS_SGETMASK
#define __ARCH_WANT_SYS_UTIME
#define __ARCH_WANT_SYS_WAITPID
#define __ARCH_WANT_SYS_SOCKETCALL
#define __ARCH_WANT_SYS_GETPGRP
#define __ARCH_WANT_SYS_LLSEEK
#define __ARCH_WANT_SYS_NICE
#define __ARCH_WANT_SYS_OLD_GETRLIMIT
#define __ARCH_WANT_SYS_OLD_UNAME
#define __ARCH_WANT_SYS_OLDUMOUNT
#define __ARCH_WANT_SYS_SIGPENDING
#define __ARCH_WANT_SYS_SIGPROCMASK
#define __ARCH_WANT_SYS_RT_SIGACTION
# ifdef CONFIG_32BIT
#  define __ARCH_WANT_STAT64
#  define __ARCH_WANT_SYS_TIME
# endif
# ifdef CONFIG_MIPS32_O32
#  define __ARCH_WANT_COMPAT_SYS_TIME
# endif

/* whitelists for checksyscalls */
#define __IGNORE_select
#define __IGNORE_vfork
#define __IGNORE_time
#define __IGNORE_uselib
#define __IGNORE_fadvise64_64
#define __IGNORE_getdents64
#if _MIPS_SIM == _MIPS_SIM_NABI32
#define __IGNORE_truncate64
#define __IGNORE_ftruncate64
#define __IGNORE_stat64
#define __IGNORE_lstat64
#define __IGNORE_fstat64
#define __IGNORE_fstatat64
#endif

#endif /* !__ASSEMBLY__ */

/*
 * "Conditional" syscalls
 *
 * What we want is __attribute__((weak,alias("sys_ni_syscall"))),
 * but it doesn't work on all toolchains, so we just do it by hand
 */
#define cond_syscall(x) asm(".weak\t" #x "\n" #x "\t=\tsys_ni_syscall")

#endif /* _ASM_UNISTD_H */
