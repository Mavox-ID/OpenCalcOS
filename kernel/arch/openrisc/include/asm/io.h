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
#ifndef __ASM_OPENRISC_IO_H
#define __ASM_OPENRISC_IO_H

/*
 * PCI: can we really do 0 here if we have no port IO?
 */
#define IO_SPACE_LIMIT		0

/* OpenRISC has no port IO */
#define HAVE_ARCH_PIO_SIZE	1
#define PIO_RESERVED		0X0UL
#define PIO_OFFSET		0
#define PIO_MASK		0

#include <asm-generic/io.h>
#include <asm/pgtable.h>

extern void __iomem *__ioremap(phys_addr_t offset, unsigned long size,
				pgprot_t prot);

static inline void __iomem *ioremap(phys_addr_t offset, unsigned long size)
{
	return __ioremap(offset, size, PAGE_KERNEL);
}

/* #define _PAGE_CI       0x002 */
static inline void __iomem *ioremap_nocache(phys_addr_t offset,
					     unsigned long size)
{
	return __ioremap(offset, size,
			 __pgprot(pgprot_val(PAGE_KERNEL) | _PAGE_CI));
}

extern void iounmap(void *addr);
#endif
