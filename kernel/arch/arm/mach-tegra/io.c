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
#include <beep/kernel.h>
#include <beep/module.h>
#include <beep/init.h>
#include <beep/mm.h>
#include <beep/io.h>

#include <asm/page.h>
#include <asm/mach/map.h>

#include "board.h"
#include "iomap.h"

static struct map_desc tegra_io_desc[] __initdata = {
	{
		.virtual = (unsigned long)IO_PPSB_VIRT,
		.pfn = __phys_to_pfn(IO_PPSB_PHYS),
		.length = IO_PPSB_SIZE,
		.type = MT_DEVICE,
	},
	{
		.virtual = (unsigned long)IO_APB_VIRT,
		.pfn = __phys_to_pfn(IO_APB_PHYS),
		.length = IO_APB_SIZE,
		.type = MT_DEVICE,
	},
	{
		.virtual = (unsigned long)IO_CPU_VIRT,
		.pfn = __phys_to_pfn(IO_CPU_PHYS),
		.length = IO_CPU_SIZE,
		.type = MT_DEVICE,
	},
	{
		.virtual = (unsigned long)IO_IRAM_VIRT,
		.pfn = __phys_to_pfn(IO_IRAM_PHYS),
		.length = IO_IRAM_SIZE,
		.type = MT_DEVICE,
	},
};

void __init tegra_map_common_io(void)
{
	debug_ll_io_init();
	iotable_init(tegra_io_desc, ARRAY_SIZE(tegra_io_desc));
}
