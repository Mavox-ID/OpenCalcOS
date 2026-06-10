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
#ifndef __UNICORE_IO_H__
#define __UNICORE_IO_H__

#ifdef __KERNEL__

#include <asm/byteorder.h>
#include <asm/memory.h>

#define PCI_IOBASE	PKUNITY_PCILIO_BASE
#include <asm-generic/io.h>

/*
 * __uc32_ioremap and __uc32_ioremap_cached takes CPU physical address.
 */
extern void __iomem *__uc32_ioremap(unsigned long, size_t);
extern void __iomem *__uc32_ioremap_cached(unsigned long, size_t);
extern void __uc32_iounmap(volatile void __iomem *addr);

/*
 * ioremap and friends.
 *
 * ioremap takes a PCI memory address, as specified in
 * Documentation/io-mapping.txt.
 *
 */
#define ioremap(cookie, size)		__uc32_ioremap(cookie, size)
#define ioremap_cached(cookie, size)	__uc32_ioremap_cached(cookie, size)
#define ioremap_nocache(cookie, size)	__uc32_ioremap(cookie, size)
#define iounmap(cookie)			__uc32_iounmap(cookie)

#define HAVE_ARCH_PIO_SIZE
#define PIO_OFFSET		(unsigned int)(PCI_IOBASE)
#define PIO_MASK		(unsigned int)(IO_SPACE_LIMIT)
#define PIO_RESERVED		(PIO_OFFSET + PIO_MASK + 1)

#endif	/* __KERNEL__ */
#endif	/* __UNICORE_IO_H__ */
