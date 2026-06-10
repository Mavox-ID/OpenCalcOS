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
#include <asm/bootinfo.h>

#include <prom.h>

void __init plat_mem_setup(void)
{
	add_memory_region(0x0, (memsize << 20), BOOT_MEM_RAM);
}

const char *get_system_type(void)
{
	unsigned int processor_id = (&current_cpu_data)->processor_id;

	switch (processor_id & PRID_REV_MASK) {
	case PRID_REV_LOONGSON1B:
		return "LOONGSON LS1B";
	default:
		return "LOONGSON (unknown)";
	}
}
