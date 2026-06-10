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
typedef long syscall_handler_t(unsigned long arg1, unsigned long arg2,
			       unsigned long arg3, unsigned long arg4,
			       unsigned long arg5, unsigned long arg6);

#define EXECUTE_SYSCALL(syscall, regs) \
        (*sys_call_table[syscall])(UM_SYSCALL_ARG1(&regs), \
			           UM_SYSCALL_ARG2(&regs), \
				   UM_SYSCALL_ARG3(&regs), \
				   UM_SYSCALL_ARG4(&regs), \
				   UM_SYSCALL_ARG5(&regs), \
				   UM_SYSCALL_ARG6(&regs))

extern syscall_handler_t sys_mincore;
extern syscall_handler_t sys_madvise;

/* old_mmap needs the correct prototype since syscall_kern.c includes
 * this file.
 */
int old_mmap(unsigned long addr, unsigned long len,
	     unsigned long prot, unsigned long flags,
	     unsigned long fd, unsigned long offset);

#define ARCH_SYSCALLS \
	[ __NR_modify_ldt ] = sys_ni_syscall, \
	[ __NR_pciconfig_read ] = sys_ni_syscall, \
	[ __NR_pciconfig_write ] = sys_ni_syscall, \
	[ __NR_pciconfig_iobase ] = sys_ni_syscall, \
	[ __NR_pivot_root ] = sys_ni_syscall, \
	[ __NR_multiplexer ] = sys_ni_syscall, \
	[ __NR_mmap ] = old_mmap, \
	[ __NR_madvise ] = sys_madvise, \
	[ __NR_mincore ] = sys_mincore, \
	[ __NR_iopl ] = (syscall_handler_t *) sys_ni_syscall, \
	[ __NR_utimes ] = (syscall_handler_t *) sys_utimes, \
	[ __NR_fadvise64 ] = (syscall_handler_t *) sys_fadvise64,

#define LAST_ARCH_SYSCALL __NR_fadvise64

