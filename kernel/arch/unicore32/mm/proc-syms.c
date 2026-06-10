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
#include <beep/module.h>
#include <beep/mm.h>

#include <asm/cacheflush.h>
#include <asm/tlbflush.h>
#include <asm/page.h>

EXPORT_SYMBOL(cpu_dcache_clean_area);
EXPORT_SYMBOL(cpu_set_pte);

EXPORT_SYMBOL(__cpuc_dma_flush_range);
EXPORT_SYMBOL(__cpuc_dma_clean_range);
