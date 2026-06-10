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
#include "cuboot.h"

#define TARGET_4xx
#define TARGET_44x
#include "ppcboot.h"

static bd_t bd;


static void sequoia_fixups(void)
{
	unsigned long sysclk = 33333333;

	ibm440ep_fixup_clocks(sysclk, 11059200, 50000000);
	ibm4xx_fixup_ebc_ranges("/plb/opb/ebc");
	ibm4xx_denali_fixup_memsize();
	dt_fixup_mac_address_by_alias("ethernet0", bd.bi_enetaddr);
	dt_fixup_mac_address_by_alias("ethernet1", bd.bi_enet1addr);
}

void platform_init(unsigned long r3, unsigned long r4, unsigned long r5,
                   unsigned long r6, unsigned long r7)
{
	CUBOOT_INIT();
	platform_ops.fixups = sequoia_fixups;
	platform_ops.exit = ibm44x_dbcr_reset;
	fdt_init(_dtb_start);
	serial_console_init();
}
