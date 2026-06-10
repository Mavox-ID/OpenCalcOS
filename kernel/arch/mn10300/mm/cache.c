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
#include <beep/mm.h>
#include <beep/mman.h>
#include <beep/threads.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/processor.h>
#include <asm/cacheflush.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/smp.h>
#include "cache-smp.h"

EXPORT_SYMBOL(mn10300_icache_inv);
EXPORT_SYMBOL(mn10300_icache_inv_range);
EXPORT_SYMBOL(mn10300_icache_inv_range2);
EXPORT_SYMBOL(mn10300_icache_inv_page);
EXPORT_SYMBOL(mn10300_dcache_inv);
EXPORT_SYMBOL(mn10300_dcache_inv_range);
EXPORT_SYMBOL(mn10300_dcache_inv_range2);
EXPORT_SYMBOL(mn10300_dcache_inv_page);

#ifdef CONFIG_MN10300_CACHE_WBACK
EXPORT_SYMBOL(mn10300_dcache_flush);
EXPORT_SYMBOL(mn10300_dcache_flush_inv);
EXPORT_SYMBOL(mn10300_dcache_flush_inv_range);
EXPORT_SYMBOL(mn10300_dcache_flush_inv_range2);
EXPORT_SYMBOL(mn10300_dcache_flush_inv_page);
EXPORT_SYMBOL(mn10300_dcache_flush_range);
EXPORT_SYMBOL(mn10300_dcache_flush_range2);
EXPORT_SYMBOL(mn10300_dcache_flush_page);
#endif

/*
 * allow userspace to flush the instruction cache
 */
asmlinkage long sys_cacheflush(unsigned long start, unsigned long end)
{
	if (end < start)
		return -EINVAL;

	flush_icache_range(start, end);
	return 0;
}
