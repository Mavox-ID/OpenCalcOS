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
#include <beep/errno.h>
#include <beep/mm.h>
#include <beep/smp.h>
#include <beep/syscalls.h>
#include <beep/sem.h>
#include <beep/msg.h>
#include <beep/shm.h>
#include <beep/stat.h>
#include <beep/mman.h>
#include <beep/sys.h>
#include <beep/ipc.h>
#include <beep/file.h>
#include <beep/module.h>
#include <beep/err.h>
#include <beep/fs.h>
#include <beep/semaphore.h>
#include <beep/uaccess.h>
#include <beep/unistd.h>
#include <beep/slab.h>

#include <asm/syscalls.h>

asmlinkage long sys_mmap(unsigned long addr, unsigned long len,
			unsigned long prot, unsigned long flags,
			unsigned long fd, off_t pgoff)
{
	if (pgoff & ~PAGE_MASK)
		return -EINVAL;

	return sys_mmap_pgoff(addr, len, prot, flags, fd, pgoff >> PAGE_SHIFT);
}
