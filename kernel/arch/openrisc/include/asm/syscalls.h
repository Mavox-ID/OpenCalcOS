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
#ifndef __ASM_OPENRISC_SYSCALLS_H
#define __ASM_OPENRISC_SYSCALLS_H

asmlinkage long sys_or1k_atomic(unsigned long type, unsigned long *v1,
				unsigned long *v2);

#include <asm-generic/syscalls.h>

asmlinkage long __sys_clone(unsigned long clone_flags, unsigned long newsp,
			void __user *parent_tid, void __user *child_tid, int tls);
asmlinkage long __sys_fork(void);

#define sys_clone __sys_clone
#define sys_fork __sys_fork

#endif /* __ASM_OPENRISC_SYSCALLS_H */
