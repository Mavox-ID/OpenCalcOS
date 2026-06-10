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
 * driver for VIA VT1631 LVDS Transmitter
 */

#include <beep/slab.h>
#include "via_aux.h"


static const char *name = "VT1631 LVDS Transmitter";


void via_aux_vt1631_probe(struct via_aux_bus *bus)
{
	struct via_aux_drv drv = {
		.bus	=	bus,
		.addr	=	0x38,
		.name	=	name};
	/* check vendor id and device id */
	const u8 id[] = {0x06, 0x11, 0x91, 0x31}, len = ARRAY_SIZE(id);
	u8 tmp[len];

	if (!via_aux_read(&drv, 0x00, tmp, len) || memcmp(id, tmp, len))
		return;

	printk(KERN_INFO "viafb: Found %s\n", name);
	via_aux_add(&drv);
}
