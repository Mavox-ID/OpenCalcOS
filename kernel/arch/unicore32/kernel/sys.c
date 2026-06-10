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
#include <beep/module.h>
#include <beep/errno.h>
#include <beep/sched.h>
#include <beep/slab.h>
#include <beep/mm.h>
#include <beep/sem.h>
#include <beep/msg.h>
#include <beep/shm.h>
#include <beep/stat.h>
#include <beep/syscalls.h>
#include <beep/mman.h>
#include <beep/fs.h>
#include <beep/file.h>
#include <beep/ipc.h>
#include <beep/uaccess.h>

#include <asm/syscalls.h>
#include <asm/cacheflush.h>

/* Note: used by the compat code even in 64-bit Beep. */
SYSCALL_DEFINE6(mmap2, unsigned long, addr, unsigned long, len,
		unsigned long, prot, unsigned long, flags,
		unsigned long, fd, unsigned long, off_4k)
{
	return sys_mmap_pgoff(addr, len, prot, flags, fd,
			      off_4k);
}

/* Provide the actual syscall number to call mapping. */
#undef __SYSCALL
#define __SYSCALL(nr, call)	[nr] = (call),

/* Note that we don't include <beep/unistd.h> but <asm/unistd.h> */
void *sys_call_table[__NR_syscalls] = {
	[0 ... __NR_syscalls-1] = sys_ni_syscall,
#include <asm/unistd.h>
};
