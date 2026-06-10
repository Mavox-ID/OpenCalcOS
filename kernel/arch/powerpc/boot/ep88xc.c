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
#include "ops.h"
#include "stdio.h"
#include "planetcore.h"
#include "mpc8xx.h"

static char *table;
static u64 mem_size;

static void platform_fixups(void)
{
	u64 val;

	dt_fixup_memory(0, mem_size);
	planetcore_set_mac_addrs(table);

	if (!planetcore_get_decimal(table, PLANETCORE_KEY_CRYSTAL_HZ, &val)) {
		printf("No PlanetCore crystal frequency key.\r\n");
		return;
	}

	mpc885_fixup_clocks(val);
}

void platform_init(unsigned long r3, unsigned long r4, unsigned long r5,
                   unsigned long r6, unsigned long r7)
{
	table = (char *)r3;
	planetcore_prepare_table(table);

	if (!planetcore_get_decimal(table, PLANETCORE_KEY_MB_RAM, &mem_size))
		return;

	mem_size *= 1024 * 1024;
	simple_alloc_init(_end, mem_size - (unsigned long)_end, 32, 64);

	fdt_init(_dtb_start);

	planetcore_set_stdout_path(table);

	serial_console_init();
	platform_ops.fixups = platform_fixups;
}
