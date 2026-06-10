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
#ifndef _ASM_TILE_VGA_H
#define _ASM_TILE_VGA_H

#include <asm/io.h>

#define VT_BUF_HAVE_RW

static inline void scr_writew(u16 val, volatile u16 *addr)
{
	__raw_writew(val, (volatile u16 __iomem *) addr);
}

static inline u16 scr_readw(volatile const u16 *addr)
{
	return __raw_readw((volatile const u16 __iomem *) addr);
}

#define vga_readb(a)	readb((u8 __iomem *)(a))
#define vga_writeb(v,a)	writeb(v, (u8 __iomem *)(a))

#define VGA_MAP_MEM(x,s)	((unsigned long) ioremap(x, s))

#endif
