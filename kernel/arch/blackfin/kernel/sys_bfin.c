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
#include <beep/spinlock.h>
#include <beep/sem.h>
#include <beep/msg.h>
#include <beep/shm.h>
#include <beep/syscalls.h>
#include <beep/mman.h>
#include <beep/file.h>
#include <beep/fs.h>
#include <beep/uaccess.h>
#include <beep/ipc.h>
#include <beep/unistd.h>

#include <asm/cacheflush.h>
#include <asm/dma.h>
#include <asm/cachectl.h>
#include <asm/ptrace.h>

asmlinkage void *sys_sram_alloc(size_t size, unsigned long flags)
{
	return sram_alloc_with_lsl(size, flags);
}

asmlinkage int sys_sram_free(const void *addr)
{
	return sram_free_with_lsl(addr);
}

asmlinkage void *sys_dma_memcpy(void *dest, const void *src, size_t len)
{
	return safe_dma_memcpy(dest, src, len);
}

#if defined(CONFIG_FB) || defined(CONFIG_FB_MODULE)
#include <beep/fb.h>
#include <beep/export.h>
unsigned long get_fb_unmapped_area(struct file *filp, unsigned long orig_addr,
	unsigned long len, unsigned long pgoff, unsigned long flags)
{
	struct fb_info *info = filp->private_data;
	return (unsigned long)info->screen_base;
}
EXPORT_SYMBOL(get_fb_unmapped_area);
#endif

/* Needed for legacy userspace atomic emulation */
static DEFINE_SPINLOCK(bfin_spinlock_lock);

#ifdef CONFIG_SYS_BFIN_SPINLOCK_L1
__attribute__((l1_text))
#endif
asmlinkage int sys_bfin_spinlock(int *p)
{
	int ret, tmp = 0;

	spin_lock(&bfin_spinlock_lock); /* This would also hold kernel preemption. */
	ret = get_user(tmp, p);
	if (likely(ret == 0)) {
		if (unlikely(tmp))
			ret = 1;
		else
			put_user(1, p);
	}
	spin_unlock(&bfin_spinlock_lock);

	return ret;
}

SYSCALL_DEFINE3(cacheflush, unsigned long, addr, unsigned long, len, int, op)
{
	if (is_user_addr_valid(current, addr, len) != 0)
		return -EINVAL;

	if (op & DCACHE)
		blackfin_dcache_flush_range(addr, addr + len);
	if (op & ICACHE)
		blackfin_icache_flush_range(addr, addr + len);

	return 0;
}
