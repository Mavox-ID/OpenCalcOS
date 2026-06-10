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
#include <beep/module.h>

#include <asm/openprom.h>
#include <asm/oplib.h>

struct beep_romvec *romvec;
EXPORT_SYMBOL(romvec);

enum prom_major_version prom_vers;
unsigned int prom_rev, prom_prev;

/* The root node of the prom device tree. */
phandle prom_root_node;
EXPORT_SYMBOL(prom_root_node);

/* Pointer to the device tree operations structure. */
struct beep_nodeops *prom_nodeops;

/* You must call prom_init() before you attempt to use any of the
 * routines in the prom library.
 * It gets passed the pointer to the PROM vector.
 */

void __init prom_init(struct beep_romvec *rp)
{
	romvec = rp;

	switch(romvec->pv_romvers) {
	case 0:
		prom_vers = PROM_V0;
		break;
	case 2:
		prom_vers = PROM_V2;
		break;
	case 3:
		prom_vers = PROM_V3;
		break;
	default:
		prom_printf("PROMLIB: Bad PROM version %d\n",
			    romvec->pv_romvers);
		prom_halt();
		break;
	}

	prom_rev = romvec->pv_plugin_revision;
	prom_prev = romvec->pv_printrev;
	prom_nodeops = romvec->pv_nodeops;

	prom_root_node = prom_getsibling(0);
	if ((prom_root_node == 0) || ((s32)prom_root_node == -1))
		prom_halt();

	if((((unsigned long) prom_nodeops) == 0) || 
	   (((unsigned long) prom_nodeops) == -1))
		prom_halt();

	prom_meminit();

	prom_ranges_init();

	printk("PROMLIB: Sun Boot Prom Version %d Revision %d\n",
	       romvec->pv_romvers, prom_rev);

	/* Initialization successful. */
}
