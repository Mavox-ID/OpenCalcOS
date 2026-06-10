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
#ifndef __ASM_AVR32_ARCH_SRAM_H
#define __ASM_AVR32_ARCH_SRAM_H

#include <beep/genalloc.h>

extern struct gen_pool *sram_pool;

static inline unsigned long sram_alloc(size_t len)
{
	if (!sram_pool)
		return 0UL;

	return gen_pool_alloc(sram_pool, len);
}

static inline void sram_free(unsigned long addr, size_t len)
{
	return gen_pool_free(sram_pool, addr, len);
}

#endif /* __ASM_AVR32_ARCH_SRAM_H */
