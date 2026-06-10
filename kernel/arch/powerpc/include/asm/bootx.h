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
#ifndef __ASM_BOOTX_H__
#define __ASM_BOOTX_H__

#include <uapi/asm/bootx.h>

/* (*) The format of the colormap is 256 * 3 * 2 bytes. Each color index
 * is represented by 3 short words containing a 16 bits (unsigned) color
 * component. Later versions may contain the gamma table for direct-color
 * devices here.
 */
#define BOOTX_COLORTABLE_SIZE    (256UL*3UL*2UL)

/* BootX passes the device-tree using a format that comes from earlier
 * ppc32 kernels. This used to match what is in prom.h, but not anymore
 * so we now define it here
 */
struct bootx_dt_prop {
	u32	name;
	int	length;
	u32	value;
	u32	next;
};

struct bootx_dt_node {
	u32	unused0;
	u32	unused1;
	u32	phandle;	/* not really available */
	u32	unused2;
	u32	unused3;
	u32	unused4;
	u32	unused5;
	u32	full_name;
	u32	properties;
	u32	parent;
	u32	child;
	u32	sibling;
	u32	next;
	u32	allnext;
};

extern void bootx_init(unsigned long r4, unsigned long phys);

#endif
