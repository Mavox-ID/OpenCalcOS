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
#include "cuboot.h"
#include "reg.h"
#include "dcr.h"
#include "4xx.h"

#define TARGET_4xx
#define TARGET_44x
#define TARGET_440GX
#include "ppcboot.h"

static bd_t bd;

BSS_STACK(4096);

static void taishan_fixups(void)
{
	/* FIXME: sysclk should be derived by reading the FPGA
	   registers */
	unsigned long sysclk = 33000000;

	ibm440gx_fixup_clocks(sysclk, 6 * 1843200, 25000000);

	ibm4xx_sdram_fixup_memsize();

	dt_fixup_mac_address_by_alias("ethernet0", bd.bi_enetaddr);
	dt_fixup_mac_address_by_alias("ethernet1", bd.bi_enet1addr);

	ibm4xx_fixup_ebc_ranges("/plb/opb/ebc");
}

void platform_init(unsigned long r3, unsigned long r4, unsigned long r5,
		   unsigned long r6, unsigned long r7)
{
	CUBOOT_INIT();

	platform_ops.fixups = taishan_fixups;
	fdt_init(_dtb_start);
	serial_console_init();
}
