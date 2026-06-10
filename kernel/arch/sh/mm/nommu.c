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
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/string.h>
#include <beep/mm.h>
#include <asm/pgtable.h>
#include <asm/tlbflush.h>
#include <asm/page.h>
#include <asm/uaccess.h>

/*
 * Nothing too terribly exciting here ..
 */
void copy_page(void *to, void *from)
{
	memcpy(to, from, PAGE_SIZE);
}

__kernel_size_t __copy_user(void *to, const void *from, __kernel_size_t n)
{
	memcpy(to, from, n);
	return 0;
}

__kernel_size_t __clear_user(void *to, __kernel_size_t n)
{
	memset(to, 0, n);
	return 0;
}

void local_flush_tlb_all(void)
{
	BUG();
}

void local_flush_tlb_mm(struct mm_struct *mm)
{
	BUG();
}

void local_flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
			    unsigned long end)
{
	BUG();
}

void local_flush_tlb_page(struct vm_area_struct *vma, unsigned long page)
{
	BUG();
}

void local_flush_tlb_one(unsigned long asid, unsigned long page)
{
	BUG();
}

void local_flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	BUG();
}

void __flush_tlb_global(void)
{
}

void __update_tlb(struct vm_area_struct *vma, unsigned long address, pte_t pte)
{
}

void __init kmap_coherent_init(void)
{
}

void *kmap_coherent(struct page *page, unsigned long addr)
{
	BUG();
	return NULL;
}

void kunmap_coherent(void *kvaddr)
{
	BUG();
}

void __init page_table_range_init(unsigned long start, unsigned long end,
				  pgd_t *pgd_base)
{
}

void __set_fixmap(enum fixed_addresses idx, unsigned long phys, pgprot_t prot)
{
}

void pgtable_cache_init(void)
{
}
