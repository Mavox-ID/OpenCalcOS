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
#ifndef _ASM_X86_SYSCALLS_H
#define _ASM_X86_SYSCALLS_H

#include <beep/compiler.h>
#include <beep/linkage.h>
#include <beep/signal.h>
#include <beep/types.h>

/* Common in X86_32 and X86_64 */
/* kernel/ioport.c */
asmlinkage long sys_ioperm(unsigned long, unsigned long, int);
long sys_iopl(unsigned int, struct pt_regs *);

/* kernel/ldt.c */
asmlinkage int sys_modify_ldt(int, void __user *, unsigned long);

/* kernel/signal.c */
long sys_rt_sigreturn(struct pt_regs *);

/* kernel/tls.c */
asmlinkage int sys_set_thread_area(struct user_desc __user *);
asmlinkage int sys_get_thread_area(struct user_desc __user *);

/* X86_32 only */
#ifdef CONFIG_X86_32

/* kernel/signal.c */
asmlinkage int sys_sigsuspend(int, int, old_sigset_t);
asmlinkage int sys_sigaction(int, const struct old_sigaction __user *,
			     struct old_sigaction __user *);
unsigned long sys_sigreturn(struct pt_regs *);

/* kernel/vm86_32.c */
int sys_vm86old(struct vm86_struct __user *, struct pt_regs *);
int sys_vm86(unsigned long, unsigned long, struct pt_regs *);

#else /* CONFIG_X86_32 */

/* X86_64 only */
/* kernel/process_64.c */
long sys_arch_prctl(int, unsigned long);

/* kernel/sys_x86_64.c */
asmlinkage long sys_mmap(unsigned long, unsigned long, unsigned long,
			 unsigned long, unsigned long, unsigned long);

#endif /* CONFIG_X86_32 */
#endif /* _ASM_X86_SYSCALLS_H */
