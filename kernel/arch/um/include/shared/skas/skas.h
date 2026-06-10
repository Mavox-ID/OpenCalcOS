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
#ifndef __SKAS_H
#define __SKAS_H

#include <sysdep/ptrace.h>

extern int userspace_pid[];
extern int proc_mm, ptrace_faultinfo, ptrace_ldt;
extern int skas_needs_stub;

extern int user_thread(unsigned long stack, int flags);
extern void new_thread_handler(void);
extern void handle_syscall(struct uml_pt_regs *regs);
extern int new_mm(unsigned long stack);
extern long execute_syscall_skas(void *r);
extern unsigned long current_stub_stack(void);

#endif
