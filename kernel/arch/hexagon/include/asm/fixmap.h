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
#ifndef _ASM_FIXMAP_H
#define _ASM_FIXMAP_H

/*
 * A lot of the fixmap info is already in mem-layout.h
 */
#include <asm/mem-layout.h>

/*
 * Full fixmap support involves set_fixmap() functions, but
 * these may not be needed if all we're after is an area for
 * highmem kernel mappings.
 */
#define	__fix_to_virt(x)	(FIXADDR_TOP - ((x) << PAGE_SHIFT))
#define	__virt_to_fix(x)	((FIXADDR_TOP - ((x)&PAGE_MASK)) >> PAGE_SHIFT)

extern void __this_fixmap_does_not_exist(void);

/**
 * fix_to_virt -- "index to address" translation.
 *
 * If anyone tries to use the idx directly without translation,
 * we catch the bug with a NULL-deference kernel oops. Illegal
 * ranges of incoming indices are caught too.
 */
static inline unsigned long fix_to_virt(const unsigned int idx)
{
	/*
	 * This branch gets completely eliminated after inlining,
	 * except when someone tries to use fixaddr indices in an
	 * illegal way. (such as mixing up address types or using
	 * out-of-range indices).
	 *
	 * If it doesn't get removed, the linker will complain
	 * loudly with a reasonably clear error message..
	 */
	if (idx >= __end_of_fixed_addresses)
		__this_fixmap_does_not_exist();

	return __fix_to_virt(idx);
}

static inline unsigned long virt_to_fix(const unsigned long vaddr)
{
	BUG_ON(vaddr >= FIXADDR_TOP || vaddr < FIXADDR_START);
	return __virt_to_fix(vaddr);
}

#define kmap_get_fixmap_pte(vaddr) \
	pte_offset_kernel(pmd_offset(pud_offset(pgd_offset_k(vaddr), \
				(vaddr)), (vaddr)), (vaddr))

#endif
