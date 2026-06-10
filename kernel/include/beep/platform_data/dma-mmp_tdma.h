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
#ifndef __ASM_ARCH_SRAM_H
#define __ASM_ARCH_SRAM_H

#include <beep/genalloc.h>

/* ARBITRARY:  SRAM allocations are multiples of this 2^N size */
#define SRAM_GRANULARITY	512

enum sram_type {
	MMP_SRAM_UNDEFINED = 0,
	MMP_ASRAM,
	MMP_ISRAM,
};

struct sram_platdata {
	char *pool_name;
	int granularity;
};

extern struct gen_pool *sram_get_gpool(char *pool_name);

#endif /* __ASM_ARCH_SRAM_H */
