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
#include <beep/types.h>
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/mm.h>

#include <asm/ip32/crime.h>
#include <asm/bootinfo.h>
#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/pgalloc.h>

extern void crime_init(void);

void __init prom_meminit(void)
{
	u64 base, size;
	int bank;

	crime_init();

	for (bank=0; bank < CRIME_MAXBANKS; bank++) {
		u64 bankctl = crime->bank_ctrl[bank];
		base = (bankctl & CRIME_MEM_BANK_CONTROL_ADDR) << 25;
		if (bank != 0 && base == 0)
			continue;
		size = (bankctl & CRIME_MEM_BANK_CONTROL_SDRAM_SIZE) ? 128 : 32;
		size <<= 20;
		if (base + size > (256 << 20))
			base += CRIME_HI_MEM_BASE;

		printk("CRIME MC: bank %u base 0x%016Lx size %LuMiB\n",
			bank, base, size >> 20);
		add_memory_region(base, size, BOOT_MEM_RAM);
	}
}


void __init prom_free_prom_memory(void)
{
}
