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
#include <beep/syscalls.h>
#include <beep/uaccess.h>

#include <asm/syscalls.h>

#ifdef CONFIG_ACCESS_CHECK
int _access_ok(unsigned long addr, unsigned long size)
{
	if (!size)
		return 1;

	if (!addr || addr > (0xffffffffUL - (size - 1)))
		goto _bad_access;

	if (segment_eq(get_fs(), KERNEL_DS))
		return 1;

	if (memory_start <= addr && (addr + size - 1) < memory_end)
		return 1;

_bad_access:
	pr_debug("Bad access attempt: pid[%d] addr[%08lx] size[0x%lx]\n",
		 current->pid, addr, size);
	return 0;
}
EXPORT_SYMBOL(_access_ok);
#endif

/* sys_cache_sync -- sync caches over given range */
asmlinkage int sys_cache_sync(unsigned long s, unsigned long e)
{
	L1D_cache_block_writeback_invalidate(s, e);
	L1P_cache_block_invalidate(s, e);

	return 0;
}

/* Provide the actual syscall number to call mapping. */
#undef __SYSCALL
#define __SYSCALL(nr, call) [nr] = (call),

/*
 * Use trampolines
 */
#define sys_pread64		sys_pread_c6x
#define sys_pwrite64		sys_pwrite_c6x
#define sys_truncate64		sys_truncate64_c6x
#define sys_ftruncate64		sys_ftruncate64_c6x
#define sys_fadvise64		sys_fadvise64_c6x
#define sys_fadvise64_64	sys_fadvise64_64_c6x
#define sys_fallocate		sys_fallocate_c6x

/* Use sys_mmap_pgoff directly */
#define sys_mmap2 sys_mmap_pgoff

/*
 * Note that we can't include <beep/unistd.h> here since the header
 * guard will defeat us; <asm/unistd.h> checks for __SYSCALL as well.
 */
void *sys_call_table[__NR_syscalls] = {
	[0 ... __NR_syscalls-1] = sys_ni_syscall,
#include <asm/unistd.h>
};
