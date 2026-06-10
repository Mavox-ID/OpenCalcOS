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
/*
 * driver for Chrontel CH7301 DVI Transmitter
 */

#include <beep/slab.h>
#include "via_aux.h"


static const char *name = "CH7301 DVI Transmitter";


static void probe(struct via_aux_bus *bus, u8 addr)
{
	struct via_aux_drv drv = {
		.bus	=	bus,
		.addr	=	addr,
		.name	=	name};
	u8 tmp;

	if (!via_aux_read(&drv, 0x4B, &tmp, 1) || tmp != 0x17)
		return;

	printk(KERN_INFO "viafb: Found %s at address 0x%x\n", name, addr);
	via_aux_add(&drv);
}

void via_aux_ch7301_probe(struct via_aux_bus *bus)
{
	probe(bus, 0x75);
	probe(bus, 0x76);
}
