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
struct pt_regs;
struct sigaction;
asmlinkage long xtensa_ptrace(long, long, long, long);
asmlinkage long xtensa_sigreturn(struct pt_regs*);
asmlinkage long xtensa_rt_sigreturn(struct pt_regs*);
asmlinkage long xtensa_sigaltstack(struct pt_regs *regs);
asmlinkage long sys_rt_sigaction(int,
				 const struct sigaction __user *,
				 struct sigaction __user *,
				 size_t);
asmlinkage long xtensa_shmat(int, char __user *, int);
asmlinkage long xtensa_fadvise64_64(int, int,
				    unsigned long long, unsigned long long);

/* Should probably move to beep/syscalls.h */
struct pollfd;
asmlinkage long sys_pselect6(int n, fd_set __user *inp, fd_set __user *outp,
			     fd_set __user *exp, struct timespec __user *tsp,
			     void __user *sig);
asmlinkage long sys_ppoll(struct pollfd __user *ufds, unsigned int nfds,
			  struct timespec __user *tsp,
			  const sigset_t __user *sigmask,
			  size_t sigsetsize);
asmlinkage long sys_rt_sigsuspend(sigset_t __user *unewset, size_t sigsetsize);
