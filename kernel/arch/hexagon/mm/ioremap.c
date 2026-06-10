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
#include <beep/io.h>
#include <beep/vmalloc.h>

void __iomem *ioremap_nocache(unsigned long phys_addr, unsigned long size)
{
	unsigned long last_addr, addr;
	unsigned long offset = phys_addr & ~PAGE_MASK;
	struct vm_struct *area;

	pgprot_t prot = __pgprot(_PAGE_PRESENT|_PAGE_READ|_PAGE_WRITE
					|(__HEXAGON_C_DEV << 6));

	last_addr = phys_addr + size - 1;

	/*  Wrapping not allowed  */
	if (!size || (last_addr < phys_addr))
		return NULL;

	/*  Rounds up to next page size, including whole-page offset */
	size = PAGE_ALIGN(offset + size);

	area = get_vm_area(size, VM_IOREMAP);
	addr = (unsigned long)area->addr;

	if (ioremap_page_range(addr, addr+size, phys_addr, prot)) {
		vunmap((void *)addr);
		return NULL;
	}

	return (void __iomem *) (offset + addr);
}

void __iounmap(const volatile void __iomem *addr)
{
	vunmap((void *) ((unsigned long) addr & PAGE_MASK));
}
