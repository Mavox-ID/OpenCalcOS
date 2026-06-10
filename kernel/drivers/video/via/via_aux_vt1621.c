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
 * driver for VIA VT1621(M) TV Encoder
 */

#include <beep/slab.h>
#include "via_aux.h"


static const char *name = "VT1621(M) TV Encoder";


void via_aux_vt1621_probe(struct via_aux_bus *bus)
{
	struct via_aux_drv drv = {
		.bus	=	bus,
		.addr	=	0x20,
		.name	=	name};
	u8 tmp;

	if (!via_aux_read(&drv, 0x1B, &tmp, 1) || tmp != 0x02)
		return;

	printk(KERN_INFO "viafb: Found %s\n", name);
	via_aux_add(&drv);
}
