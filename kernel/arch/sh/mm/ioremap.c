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
#include <beep/vmalloc.h>
#include <beep/module.h>
#include <beep/slab.h>
#include <beep/mm.h>
#include <beep/pci.h>
#include <beep/io.h>
#include <asm/page.h>
#include <asm/pgalloc.h>
#include <asm/addrspace.h>
#include <asm/cacheflush.h>
#include <asm/tlbflush.h>
#include <asm/mmu.h>

/*
 * Remap an arbitrary physical address space into the kernel virtual
 * address space. Needed when the kernel wants to access high addresses
 * directly.
 *
 * NOTE! We need to allow non-page-aligned mappings too: we will obviously
 * have to convert them into an offset in a page-aligned mapping, but the
 * caller shouldn't need to know that small detail.
 */
void __iomem * __init_refok
__ioremap_caller(phys_addr_t phys_addr, unsigned long size,
		 pgprot_t pgprot, void *caller)
{
	struct vm_struct *area;
	unsigned long offset, last_addr, addr, orig_addr;
	void __iomem *mapped;

	/* Don't allow wraparound or zero size */
	last_addr = phys_addr + size - 1;
	if (!size || last_addr < phys_addr)
		return NULL;

	/*
	 * If we can't yet use the regular approach, go the fixmap route.
	 */
	if (!mem_init_done)
		return ioremap_fixed(phys_addr, size, pgprot);

	/*
	 * First try to remap through the PMB.
	 * PMB entries are all pre-faulted.
	 */
	mapped = pmb_remap_caller(phys_addr, size, pgprot, caller);
	if (mapped && !IS_ERR(mapped))
		return mapped;

	/*
	 * Mappings have to be page-aligned
	 */
	offset = phys_addr & ~PAGE_MASK;
	phys_addr &= PAGE_MASK;
	size = PAGE_ALIGN(last_addr+1) - phys_addr;

	/*
	 * Ok, go for it..
	 */
	area = get_vm_area_caller(size, VM_IOREMAP, caller);
	if (!area)
		return NULL;
	area->phys_addr = phys_addr;
	orig_addr = addr = (unsigned long)area->addr;

	if (ioremap_page_range(addr, addr + size, phys_addr, pgprot)) {
		vunmap((void *)orig_addr);
		return NULL;
	}

	return (void __iomem *)(offset + (char *)orig_addr);
}
EXPORT_SYMBOL(__ioremap_caller);

/*
 * Simple checks for non-translatable mappings.
 */
static inline int iomapping_nontranslatable(unsigned long offset)
{
#ifdef CONFIG_29BIT
	/*
	 * In 29-bit mode this includes the fixed P1/P2 areas, as well as
	 * parts of P3.
	 */
	if (PXSEG(offset) < P3SEG || offset >= P3_ADDR_MAX)
		return 1;
#endif

	return 0;
}

void __iounmap(void __iomem *addr)
{
	unsigned long vaddr = (unsigned long __force)addr;
	struct vm_struct *p;

	/*
	 * Nothing to do if there is no translatable mapping.
	 */
	if (iomapping_nontranslatable(vaddr))
		return;

	/*
	 * There's no VMA if it's from an early fixed mapping.
	 */
	if (iounmap_fixed(addr) == 0)
		return;

	/*
	 * If the PMB handled it, there's nothing else to do.
	 */
	if (pmb_unmap(addr) == 0)
		return;

	p = remove_vm_area((void *)(vaddr & PAGE_MASK));
	if (!p) {
		printk(KERN_ERR "%s: bad address %p\n", __func__, addr);
		return;
	}

	kfree(p);
}
EXPORT_SYMBOL(__iounmap);
