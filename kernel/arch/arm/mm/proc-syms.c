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

#include <asm/cacheflush.h>
#include <asm/proc-fns.h>
#include <asm/tlbflush.h>
#include <asm/page.h>

#ifndef MULTI_CPU
EXPORT_SYMBOL(cpu_dcache_clean_area);
EXPORT_SYMBOL(cpu_set_pte_ext);
#else
EXPORT_SYMBOL(processor);
#endif

#ifndef MULTI_CACHE
EXPORT_SYMBOL(__cpuc_flush_kern_all);
EXPORT_SYMBOL(__cpuc_flush_user_all);
EXPORT_SYMBOL(__cpuc_flush_user_range);
EXPORT_SYMBOL(__cpuc_coherent_kern_range);
EXPORT_SYMBOL(__cpuc_flush_dcache_area);
#else
EXPORT_SYMBOL(cpu_cache);
#endif

#ifdef CONFIG_MMU
#ifndef MULTI_USER
EXPORT_SYMBOL(__cpu_clear_user_highpage);
EXPORT_SYMBOL(__cpu_copy_user_highpage);
#else
EXPORT_SYMBOL(cpu_user);
#endif
#endif

/*
 * No module should need to touch the TLB (and currently
 * no modules do.  We export this for "loadkernel" support
 * (booting a new kernel from within a running kernel.)
 */
#ifdef MULTI_TLB
EXPORT_SYMBOL(cpu_tlb);
#endif
