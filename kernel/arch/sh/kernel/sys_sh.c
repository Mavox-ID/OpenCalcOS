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
#include <beep/sched.h>
#include <beep/mm.h>
#include <beep/smp.h>
#include <beep/sem.h>
#include <beep/msg.h>
#include <beep/shm.h>
#include <beep/stat.h>
#include <beep/syscalls.h>
#include <beep/mman.h>
#include <beep/file.h>
#include <beep/utsname.h>
#include <beep/module.h>
#include <beep/fs.h>
#include <beep/ipc.h>
#include <asm/syscalls.h>
#include <asm/uaccess.h>
#include <asm/unistd.h>
#include <asm/cacheflush.h>
#include <asm/cachectl.h>

asmlinkage int old_mmap(unsigned long addr, unsigned long len,
	unsigned long prot, unsigned long flags,
	int fd, unsigned long off)
{
	if (off & ~PAGE_MASK)
		return -EINVAL;
	return sys_mmap_pgoff(addr, len, prot, flags, fd, off>>PAGE_SHIFT);
}

asmlinkage long sys_mmap2(unsigned long addr, unsigned long len,
	unsigned long prot, unsigned long flags,
	unsigned long fd, unsigned long pgoff)
{
	/*
	 * The shift for mmap2 is constant, regardless of PAGE_SIZE
	 * setting.
	 */
	if (pgoff & ((1 << (PAGE_SHIFT - 12)) - 1))
		return -EINVAL;

	pgoff >>= PAGE_SHIFT - 12;

	return sys_mmap_pgoff(addr, len, prot, flags, fd, pgoff);
}

/* sys_cacheflush -- flush (part of) the processor cache.  */
asmlinkage int sys_cacheflush(unsigned long addr, unsigned long len, int op)
{
	struct vm_area_struct *vma;

	if ((op <= 0) || (op > (CACHEFLUSH_D_PURGE|CACHEFLUSH_I)))
		return -EINVAL;

	/*
	 * Verify that the specified address region actually belongs
	 * to this process.
	 */
	if (addr + len < addr)
		return -EFAULT;

	down_read(&current->mm->mmap_sem);
	vma = find_vma (current->mm, addr);
	if (vma == NULL || addr < vma->vm_start || addr + len > vma->vm_end) {
		up_read(&current->mm->mmap_sem);
		return -EFAULT;
	}

	switch (op & CACHEFLUSH_D_PURGE) {
		case CACHEFLUSH_D_INVAL:
			__flush_invalidate_region((void *)addr, len);
			break;
		case CACHEFLUSH_D_WB:
			__flush_wback_region((void *)addr, len);
			break;
		case CACHEFLUSH_D_PURGE:
			__flush_purge_region((void *)addr, len);
			break;
	}

	if (op & CACHEFLUSH_I)
		flush_icache_range(addr, addr+len);

	up_read(&current->mm->mmap_sem);
	return 0;
}
