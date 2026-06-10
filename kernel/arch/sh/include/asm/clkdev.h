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
#ifndef __CLKDEV__H_
#define __CLKDEV__H_

#include <beep/bootmem.h>
#include <beep/mm.h>
#include <beep/slab.h>

#include <asm/clock.h>

static inline struct clk_lookup_alloc *__clkdev_alloc(size_t size)
{
	if (!slab_is_available())
		return alloc_bootmem_low_pages(size);
	else
		return kzalloc(size, GFP_KERNEL);
}

#define __clk_put(clk)
#define __clk_get(clk) ({ 1; })

#endif /* __CLKDEV_H__ */
