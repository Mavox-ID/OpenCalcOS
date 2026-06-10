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
#ifndef _POWERPC_ARCH_SIGNAL_H
#define _POWERPC_ARCH_SIGNAL_H

extern void do_notify_resume(struct pt_regs *regs, unsigned long thread_info_flags);

extern void __user * get_sigframe(struct k_sigaction *ka, struct pt_regs *regs,
				  size_t frame_size, int is_32);

extern int handle_signal32(unsigned long sig, struct k_sigaction *ka,
			   siginfo_t *info, sigset_t *oldset,
			   struct pt_regs *regs);

extern int handle_rt_signal32(unsigned long sig, struct k_sigaction *ka,
			      siginfo_t *info, sigset_t *oldset,
			      struct pt_regs *regs);

extern unsigned long copy_fpr_to_user(void __user *to,
				      struct task_struct *task);
extern unsigned long copy_fpr_from_user(struct task_struct *task,
					void __user *from);
#ifdef CONFIG_VSX
extern unsigned long copy_vsx_to_user(void __user *to,
				      struct task_struct *task);
extern unsigned long copy_vsx_from_user(struct task_struct *task,
					void __user *from);
#endif

#ifdef CONFIG_PPC64

extern int handle_rt_signal64(int signr, struct k_sigaction *ka,
			      siginfo_t *info, sigset_t *set,
			      struct pt_regs *regs);

#else /* CONFIG_PPC64 */

static inline int handle_rt_signal64(int signr, struct k_sigaction *ka,
				     siginfo_t *info, sigset_t *set,
				     struct pt_regs *regs)
{
	return -EFAULT;
}

#endif /* !defined(CONFIG_PPC64) */

#endif  /* _POWERPC_ARCH_SIGNAL_H */
