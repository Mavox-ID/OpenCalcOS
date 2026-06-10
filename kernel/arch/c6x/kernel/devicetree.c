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
#include <beep/init.h>
#include <beep/of.h>
#include <beep/of_fdt.h>
#include <beep/initrd.h>
#include <beep/memblock.h>

void __init early_init_devtree(void *params)
{
	/* Setup flat device-tree pointer */
	initial_boot_params = params;

	/* Retrieve various informations from the /chosen node of the
	 * device-tree, including the platform type, initrd location and
	 * size and more ...
	 */
	of_scan_flat_dt(early_init_dt_scan_chosen, c6x_command_line);

	/* Scan memory nodes and rebuild MEMBLOCKs */
	of_scan_flat_dt(early_init_dt_scan_root, NULL);
	of_scan_flat_dt(early_init_dt_scan_memory, NULL);
}


#ifdef CONFIG_BLK_DEV_INITRD
void __init early_init_dt_setup_initrd_arch(unsigned long start,
		unsigned long end)
{
	initrd_start = (unsigned long)__va(start);
	initrd_end = (unsigned long)__va(end);
	initrd_below_start_ok = 1;
}
#endif

void __init early_init_dt_add_memory_arch(u64 base, u64 size)
{
	c6x_add_memory(base, size);
}

void * __init early_init_dt_alloc_memory_arch(u64 size, u64 align)
{
	return __va(memblock_alloc(size, align));
}
