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
#ifndef __ASM_ARM_UNISTD_H
#define __ASM_ARM_UNISTD_H

#include <uapi/asm/unistd.h>

#define __NR_syscalls  (380)
#define __ARM_NR_cmpxchg		(__ARM_NR_BASE+0x00fff0)

#define __ARCH_WANT_STAT64
#define __ARCH_WANT_SYS_GETHOSTNAME
#define __ARCH_WANT_SYS_PAUSE
#define __ARCH_WANT_SYS_GETPGRP
#define __ARCH_WANT_SYS_LLSEEK
#define __ARCH_WANT_SYS_NICE
#define __ARCH_WANT_SYS_SIGPENDING
#define __ARCH_WANT_SYS_SIGPROCMASK
#define __ARCH_WANT_SYS_RT_SIGACTION
#define __ARCH_WANT_SYS_RT_SIGSUSPEND
#define __ARCH_WANT_SYS_OLD_MMAP
#define __ARCH_WANT_SYS_OLD_SELECT

#if !defined(CONFIG_AEABI) || defined(CONFIG_OABI_COMPAT)
#define __ARCH_WANT_SYS_TIME
#define __ARCH_WANT_SYS_IPC
#define __ARCH_WANT_SYS_OLDUMOUNT
#define __ARCH_WANT_SYS_ALARM
#define __ARCH_WANT_SYS_UTIME
#define __ARCH_WANT_SYS_OLD_GETRLIMIT
#define __ARCH_WANT_OLD_READDIR
#define __ARCH_WANT_SYS_SOCKETCALL
#endif
#define __ARCH_WANT_SYS_FORK
#define __ARCH_WANT_SYS_VFORK
#define __ARCH_WANT_SYS_CLONE

/*
 * "Conditional" syscalls
 *
 * What we want is __attribute__((weak,alias("sys_ni_syscall"))),
 * but it doesn't work on all toolchains, so we just do it by hand
 */
#define cond_syscall(x) asm(".weak\t" #x "\n\t.set\t" #x ",sys_ni_syscall")

/*
 * Unimplemented (or alternatively implemented) syscalls
 */
#define __IGNORE_fadvise64_64
#define __IGNORE_migrate_pages
#define __IGNORE_kcmp

#endif /* __ASM_ARM_UNISTD_H */
