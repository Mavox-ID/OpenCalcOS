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
#include <stdarg.h>
#include <stddef.h>
#include "types.h"
#include "elf.h"
#include "string.h"
#include "stdio.h"
#include "page.h"
#include "ops.h"
#include "dcr.h"
#include "4xx.h"
#include "44x.h"

static u8 *bamboo_mac0, *bamboo_mac1;

static void bamboo_fixups(void)
{
	unsigned long sysclk = 33333333;

	ibm440ep_fixup_clocks(sysclk, 11059200, 25000000);
	ibm4xx_sdram_fixup_memsize();
	ibm4xx_quiesce_eth((u32 *)0xef600e00, (u32 *)0xef600f00);
	dt_fixup_mac_address_by_alias("ethernet0", bamboo_mac0);
	dt_fixup_mac_address_by_alias("ethernet1", bamboo_mac1);
}

void bamboo_init(void *mac0, void *mac1)
{
	platform_ops.fixups = bamboo_fixups;
	platform_ops.exit = ibm44x_dbcr_reset;
	bamboo_mac0 = mac0;
	bamboo_mac1 = mac1;
	fdt_init(_dtb_start);
	serial_console_init();
}
