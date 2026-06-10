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
#ifndef _ASM_DM9000_H
#define _ASM_DM9000_H

#include <asm/mb-regs.h>

#define DM9000_ARCH_IOBASE	(__region_CS6 + 0x300)
#define DM9000_ARCH_IRQ		IRQ_CPU_EXTERNAL3	/* XIRQ #3 (shared with FPGA) */
#undef DM9000_ARCH_IRQ_ACTLOW				/* IRQ pin active high */
#define DM9000_ARCH_BUS_INFO	"CS6#+0x300"		/* bus info for ethtool */

#undef __is_PCI_IO
#define __is_PCI_IO(addr)	0	/* not PCI */

#undef inl
#define inl(addr)										\
({												\
	unsigned long __ioaddr = (unsigned long) addr;						\
	uint32_t x = readl(__ioaddr);								\
	((x & 0xff) << 24) | ((x & 0xff00) << 8) | ((x >> 8) & 0xff00) | ((x >> 24) & 0xff);	\
})

#undef insl
#define insl(a,b,l)	__insl(a,b,l,0) /* don't byte-swap */


#endif /* _ASM_DM9000_H */
