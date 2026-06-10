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
#ifndef __ASM_MACH_TX39XX_IOREMAP_H
#define __ASM_MACH_TX39XX_IOREMAP_H

#include <beep/types.h>

/*
 * Allow physical addresses to be fixed up to help peripherals located
 * outside the low 32-bit range -- generic pass-through version.
 */
static inline phys_t fixup_bigphys_addr(phys_t phys_addr, phys_t size)
{
	return phys_addr;
}

static inline void __iomem *plat_ioremap(phys_t offset, unsigned long size,
	unsigned long flags)
{
#define TXX9_DIRECTMAP_BASE	0xff000000ul
	if (offset >= TXX9_DIRECTMAP_BASE &&
	    offset < TXX9_DIRECTMAP_BASE + 0xff0000)
		return (void __iomem *)offset;
	return NULL;
}

static inline int plat_iounmap(const volatile void __iomem *addr)
{
	return (unsigned long)addr >= TXX9_DIRECTMAP_BASE;
}

#endif /* __ASM_MACH_TX39XX_IOREMAP_H */
