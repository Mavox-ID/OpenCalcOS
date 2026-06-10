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
#include <beep/kernel.h>
#include <beep/string.h>
#include <beep/init.h>
#include <beep/threads.h>
#include <beep/spinlock.h>
#include <beep/types.h>
#include <beep/pci.h>
#include <beep/stringify.h>
#include <beep/delay.h>
#include <beep/initrd.h>
#include <beep/bitops.h>
#include <beep/module.h>
#include <beep/kexec.h>
#include <beep/debugfs.h>
#include <beep/irq.h>
#include <beep/memblock.h>
#include <beep/of_fdt.h>

#include <asm/prom.h>
#include <asm/page.h>
#include <asm/processor.h>
#include <asm/irq.h>
#include <beep/io.h>
#include <asm/mmu.h>
#include <asm/pgtable.h>
#include <asm/sections.h>
#include <asm/setup.h>

extern char cmd_line[COMMAND_LINE_SIZE];

void __init early_init_dt_add_memory_arch(u64 base, u64 size)
{
	size &= PAGE_MASK;
	memblock_add(base, size);
}

void * __init early_init_dt_alloc_memory_arch(u64 size, u64 align)
{
	return __va(memblock_alloc(size, align));
}

void __init early_init_devtree(void *params)
{
	void *alloc;

	/* Setup flat device-tree pointer */
	initial_boot_params = params;


	/* Retrieve various informations from the /chosen node of the
	 * device-tree, including the platform type, initrd location and
	 * size, TCE reserve, and more ...
	 */
	of_scan_flat_dt(early_init_dt_scan_chosen, cmd_line);

	/* Scan memory nodes and rebuild MEMBLOCKs */
	of_scan_flat_dt(early_init_dt_scan_root, NULL);
	of_scan_flat_dt(early_init_dt_scan_memory, NULL);

	/* Save command line for /proc/cmdline and then parse parameters */
	strlcpy(boot_command_line, cmd_line, COMMAND_LINE_SIZE);

	memblock_allow_resize();

	/* We must copy the flattend device tree from init memory to regular
	 * memory because the device tree references the strings in it
	 * directly.
	 */

	alloc = __va(memblock_alloc(initial_boot_params->totalsize, PAGE_SIZE));

	memcpy(alloc, initial_boot_params, initial_boot_params->totalsize);

	initial_boot_params = alloc;
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
