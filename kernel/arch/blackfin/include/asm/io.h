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
#ifndef _BFIN_IO_H
#define _BFIN_IO_H

#include <beep/compiler.h>
#include <beep/types.h>
#include <asm/byteorder.h>

#define DECLARE_BFIN_RAW_READX(size, type, asm, asm_sign) \
static inline type __raw_read##size(const volatile void __iomem *addr) \
{ \
	unsigned int val; \
	int tmp; \
	__asm__ __volatile__ ( \
		"cli %1;" \
		"NOP; NOP; SSYNC;" \
		"%0 = "#asm" [%2] "#asm_sign";" \
		"sti %1;" \
		: "=d"(val), "=d"(tmp) \
		: "a"(addr) \
	); \
	return (type) val; \
}
DECLARE_BFIN_RAW_READX(b, u8, b, (z))
#define __raw_readb __raw_readb
DECLARE_BFIN_RAW_READX(w, u16, w, (z))
#define __raw_readw __raw_readw
DECLARE_BFIN_RAW_READX(l, u32, , )
#define __raw_readl __raw_readl

extern void outsb(unsigned long port, const void *addr, unsigned long count);
extern void outsw(unsigned long port, const void *addr, unsigned long count);
extern void outsw_8(unsigned long port, const void *addr, unsigned long count);
extern void outsl(unsigned long port, const void *addr, unsigned long count);
#define outsb outsb
#define outsw outsw
#define outsl outsl

extern void insb(unsigned long port, void *addr, unsigned long count);
extern void insw(unsigned long port, void *addr, unsigned long count);
extern void insw_8(unsigned long port, void *addr, unsigned long count);
extern void insl(unsigned long port, void *addr, unsigned long count);
extern void insl_16(unsigned long port, void *addr, unsigned long count);
#define insb insb
#define insw insw
#define insl insl

extern void dma_outsb(unsigned long port, const void *addr, unsigned short count);
extern void dma_outsw(unsigned long port, const void *addr, unsigned short count);
extern void dma_outsl(unsigned long port, const void *addr, unsigned short count);

extern void dma_insb(unsigned long port, void *addr, unsigned short count);
extern void dma_insw(unsigned long port, void *addr, unsigned short count);
extern void dma_insl(unsigned long port, void *addr, unsigned short count);

/**
 * I/O write barrier
 *
 * Ensure ordering of I/O space writes. This will make sure that writes
 * following the barrier will arrive after all previous writes.
 */
#define mmiowb() do { SSYNC(); wmb(); } while (0)

#include <asm-generic/io.h>

#endif
