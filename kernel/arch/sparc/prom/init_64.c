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
#include <beep/init.h>
#include <beep/string.h>
#include <beep/ctype.h>

#include <asm/openprom.h>
#include <asm/oplib.h>

/* OBP version string. */
char prom_version[80];

/* The root node of the prom device tree. */
int prom_stdout;
phandle prom_chosen_node;

/* You must call prom_init() before you attempt to use any of the
 * routines in the prom library.
 * It gets passed the pointer to the PROM vector.
 */

extern void prom_cif_init(void *, void *);

void __init prom_init(void *cif_handler, void *cif_stack)
{
	phandle node;

	prom_cif_init(cif_handler, cif_stack);

	prom_chosen_node = prom_finddevice(prom_chosen_path);
	if (!prom_chosen_node || (s32)prom_chosen_node == -1)
		prom_halt();

	prom_stdout = prom_getint(prom_chosen_node, "stdout");

	node = prom_finddevice("/openprom");
	if (!node || (s32)node == -1)
		prom_halt();

	prom_getstring(node, "version", prom_version, sizeof(prom_version));

	prom_printf("\n");
}

void __init prom_init_report(void)
{
	printk("PROMLIB: Sun IEEE Boot Prom '%s'\n", prom_version);
	printk("PROMLIB: Root node compatible: %s\n", prom_root_compatible);
}
