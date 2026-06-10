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
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 */

#include <beep/module.h>
#include <asm/addrspace.h>
#include <asm/byteorder.h>

#include <beep/vmalloc.h>
#include <beep/io.h>
#include <asm/pgalloc.h>

/*
 * Generic mapping function (not visible outside):
 */

/*
 * Remap an arbitrary physical address space into the kernel virtual
 * address space. Needed when the kernel wants to access high addresses
 * directly.
 *
 * NOTE! We need to allow non-page-aligned mappings too: we will obviously
 * have to convert them into an offset in a page-aligned mapping, but the
 * caller shouldn't need to know that small detail.
 */

#define IS_LOW512(addr) (!((unsigned long)(addr) & ~0x1fffffffUL))

void __iomem *
__ioremap(unsigned long phys_addr, unsigned long size, unsigned long flags)
{
	void __iomem * addr;
	struct vm_struct * area;
	unsigned long offset, last_addr;
	pgprot_t pgprot;

	/* Don't allow wraparound or zero size */
	last_addr = phys_addr + size - 1;
	if (!size || last_addr < phys_addr)
		return NULL;

	/*
	 * Map objects in the low 512mb of address space using KSEG1, otherwise
	 * map using page tables.
	 */
	if (IS_LOW512(phys_addr) && IS_LOW512(phys_addr + size - 1))
		return (void *) KSEG1ADDR(phys_addr);

	/*
	 * Don't allow anybody to remap normal RAM that we're using..
	 */
	if (phys_addr < virt_to_phys(high_memory)) {
		char *t_addr, *t_end;
		struct page *page;

		t_addr = __va(phys_addr);
		t_end = t_addr + (size - 1);

		for(page = virt_to_page(t_addr); page <= virt_to_page(t_end); page++)
			if(!PageReserved(page))
				return NULL;
	}

	pgprot = __pgprot(_PAGE_GLOBAL | _PAGE_PRESENT | _PAGE_READ
			  | _PAGE_WRITE | flags);

	/*
	 * Mappings have to be page-aligned
	 */
	offset = phys_addr & ~PAGE_MASK;
	phys_addr &= PAGE_MASK;
	size = PAGE_ALIGN(last_addr + 1) - phys_addr;

	/*
	 * Ok, go for it..
	 */
	area = get_vm_area(size, VM_IOREMAP);
	if (!area)
		return NULL;
	area->phys_addr = phys_addr;
	addr = (void __iomem *) area->addr;
	if (ioremap_page_range((unsigned long)addr, (unsigned long)addr + size,
			       phys_addr, pgprot)) {
		vunmap((void __force *) addr);
		return NULL;
	}

	return (void __iomem *) (offset + (char __iomem *)addr);
}

#define IS_KSEG1(addr) (((unsigned long)(addr) & ~0x1fffffffUL) == KSEG1)

void iounmap(volatile void __iomem *addr)
{
	if (!IS_KSEG1(addr))
		vfree((void *) (PAGE_MASK & (unsigned long) addr));
}

