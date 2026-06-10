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
#ifndef _ASM_H8300_CACHEFLUSH_H
#define _ASM_H8300_CACHEFLUSH_H

/*
 * Cache handling functions
 * No Cache memory all dummy functions
 */

#define flush_cache_all()
#define	flush_cache_mm(mm)
#define	flush_cache_dup_mm(mm)		do { } while (0)
#define	flush_cache_range(vma,a,b)
#define	flush_cache_page(vma,p,pfn)
#define ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 0
#define	flush_dcache_page(page)
#define	flush_dcache_mmap_lock(mapping)
#define	flush_dcache_mmap_unlock(mapping)
#define	flush_icache()
#define	flush_icache_page(vma,page)
#define	flush_icache_range(start,len)
#define flush_cache_vmap(start, end)
#define flush_cache_vunmap(start, end)
#define	cache_push_v(vaddr,len)
#define	cache_push(paddr,len)
#define	cache_clear(paddr,len)

#define	flush_dcache_range(a,b)

#define	flush_icache_user_range(vma,page,addr,len)

#define copy_to_user_page(vma, page, vaddr, dst, src, len) \
	memcpy(dst, src, len)
#define copy_from_user_page(vma, page, vaddr, dst, src, len) \
	memcpy(dst, src, len)

#endif /* _ASM_H8300_CACHEFLUSH_H */
