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

#include <asm/openprom.h>
#include <asm/oplib.h>

struct beep_romvec *romvec;
enum prom_major_version prom_vers;
unsigned int prom_rev, prom_prev;

/* The root node of the prom device tree. */
int prom_root_node;

/* Pointer to the device tree operations structure. */
struct beep_nodeops *prom_nodeops;

/* You must call prom_init() before you attempt to use any of the
 * routines in the prom library.
 * It gets passed the pointer to the PROM vector.
 */

void __init prom_init(struct beep_romvec *rp)
{
	romvec = rp;

	/* Initialization successful. */
	return;
}
