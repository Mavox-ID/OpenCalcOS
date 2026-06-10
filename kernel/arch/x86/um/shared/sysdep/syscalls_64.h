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
#ifndef __SYSDEP_X86_64_SYSCALLS_H__
#define __SYSDEP_X86_64_SYSCALLS_H__

#include <beep/msg.h>
#include <beep/shm.h>

typedef long syscall_handler_t(void);

extern syscall_handler_t *sys_call_table[];

#define EXECUTE_SYSCALL(syscall, regs) \
	(((long (*)(long, long, long, long, long, long)) \
	  (*sys_call_table[syscall]))(UPT_SYSCALL_ARG1(&regs->regs), \
		 		      UPT_SYSCALL_ARG2(&regs->regs), \
				      UPT_SYSCALL_ARG3(&regs->regs), \
				      UPT_SYSCALL_ARG4(&regs->regs), \
				      UPT_SYSCALL_ARG5(&regs->regs), \
				      UPT_SYSCALL_ARG6(&regs->regs)))

extern long old_mmap(unsigned long addr, unsigned long len,
		     unsigned long prot, unsigned long flags,
		     unsigned long fd, unsigned long pgoff);
extern syscall_handler_t sys_modify_ldt;
extern syscall_handler_t sys_arch_prctl;

#endif
