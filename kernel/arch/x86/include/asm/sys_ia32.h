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
#ifndef _ASM_X86_SYS_IA32_H
#define _ASM_X86_SYS_IA32_H

#ifdef CONFIG_COMPAT

#include <beep/compiler.h>
#include <beep/linkage.h>
#include <beep/types.h>
#include <beep/signal.h>
#include <asm/compat.h>
#include <asm/ia32.h>

/* ia32/sys_ia32.c */
asmlinkage long sys32_truncate64(const char __user *, unsigned long, unsigned long);
asmlinkage long sys32_ftruncate64(unsigned int, unsigned long, unsigned long);

asmlinkage long sys32_stat64(const char __user *, struct stat64 __user *);
asmlinkage long sys32_lstat64(const char __user *, struct stat64 __user *);
asmlinkage long sys32_fstat64(unsigned int, struct stat64 __user *);
asmlinkage long sys32_fstatat(unsigned int, const char __user *,
			      struct stat64 __user *, int);
struct mmap_arg_struct32;
asmlinkage long sys32_mmap(struct mmap_arg_struct32 __user *);
asmlinkage long sys32_mprotect(unsigned long, size_t, unsigned long);

struct sigaction32;
struct old_sigaction32;
asmlinkage long sys32_rt_sigaction(int, struct sigaction32 __user *,
				   struct sigaction32 __user *, unsigned int);
asmlinkage long sys32_sigaction(int, struct old_sigaction32 __user *,
				struct old_sigaction32 __user *);
asmlinkage long sys32_alarm(unsigned int);

asmlinkage long sys32_waitpid(compat_pid_t, unsigned int __user *, int);
asmlinkage long sys32_sysfs(int, u32, u32);

asmlinkage long sys32_sched_rr_get_interval(compat_pid_t,
					    struct compat_timespec __user *);
asmlinkage long sys32_rt_sigpending(compat_sigset_t __user *, compat_size_t);
asmlinkage long sys32_rt_sigqueueinfo(int, int, compat_siginfo_t __user *);

asmlinkage long sys32_pread(unsigned int, char __user *, u32, u32, u32);
asmlinkage long sys32_pwrite(unsigned int, const char __user *, u32, u32, u32);

asmlinkage long sys32_personality(unsigned long);
asmlinkage long sys32_sendfile(int, int, compat_off_t __user *, s32);

long sys32_lseek(unsigned int, int, unsigned int);
long sys32_kill(int, int);
long sys32_fadvise64_64(int, __u32, __u32, __u32, __u32, int);
long sys32_vm86_warning(void);
long sys32_lookup_dcookie(u32, u32, char __user *, size_t);

asmlinkage ssize_t sys32_readahead(int, unsigned, unsigned, size_t);
asmlinkage long sys32_sync_file_range(int, unsigned, unsigned,
				      unsigned, unsigned, int);
asmlinkage long sys32_fadvise64(int, unsigned, unsigned, size_t, int);
asmlinkage long sys32_fallocate(int, int, unsigned,
				unsigned, unsigned, unsigned);

/* ia32/ia32_signal.c */
asmlinkage long sys32_sigsuspend(int, int, old_sigset_t);
asmlinkage long sys32_sigreturn(struct pt_regs *);
asmlinkage long sys32_rt_sigreturn(struct pt_regs *);

/* ia32/ipc32.c */
asmlinkage long sys32_ipc(u32, int, int, int, compat_uptr_t, u32);

asmlinkage long sys32_fanotify_mark(int, unsigned int, u32, u32, int,
				    const char __user *);

#endif /* CONFIG_COMPAT */

#endif /* _ASM_X86_SYS_IA32_H */
