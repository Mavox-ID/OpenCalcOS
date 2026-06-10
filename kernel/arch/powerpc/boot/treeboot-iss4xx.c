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
#include "reg.h"
#include "io.h"
#include "dcr.h"
#include "4xx.h"
#include "44x.h"
#include "libfdt.h"

BSS_STACK(4096);

static u32 ibm4xx_memstart;

static void iss_4xx_fixups(void)
{
	void *memory;
	u32 reg[3];

	memory = finddevice("/memory");
	if (!memory)
		fatal("Can't find memory node\n");
	/* This assumes #address-cells = 2, #size-cells =1 and that */
	getprop(memory, "reg", reg, sizeof(reg));
	if (reg[2])
		/* If the device tree specifies the memory range, use it */
		ibm4xx_memstart = reg[1];
	else
		/* othersize, read it from the SDRAM controller */
		ibm4xx_sdram_fixup_memsize();
}

static void *iss_4xx_vmbeep_alloc(unsigned long size)
{
	return (void *)ibm4xx_memstart;
}

#define SPRN_PIR	0x11E	/* Processor Indentification Register */
void platform_init(void)
{
	unsigned long end_of_ram = 0x08000000;
	unsigned long avail_ram = end_of_ram - (unsigned long)_end;
	u32 pir_reg;

	simple_alloc_init(_end, avail_ram, 128, 64);
	platform_ops.fixups = iss_4xx_fixups;
	platform_ops.vmbeep_alloc = iss_4xx_vmbeep_alloc;
	platform_ops.exit = ibm44x_dbcr_reset;
	pir_reg = mfspr(SPRN_PIR);
	fdt_set_boot_cpuid_phys(_dtb_start, pir_reg);
	fdt_init(_dtb_start);
	serial_console_init();
}
