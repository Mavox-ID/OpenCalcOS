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
#include "ops.h"
#include "stdio.h"
#include "44x.h"

BSS_STACK(4096);

#define OPENBIOS_MAC_BASE	0xfffffe0c
#define OPENBIOS_MAC_OFFSET	0xc

void platform_init(void)
{
	unsigned long end_of_ram = 0x8000000;
	unsigned long avail_ram = end_of_ram - (unsigned long)_end;

	simple_alloc_init(_end, avail_ram, 32, 64);
	ebony_init((u8 *)OPENBIOS_MAC_BASE,
		   (u8 *)(OPENBIOS_MAC_BASE + OPENBIOS_MAC_OFFSET));
}
