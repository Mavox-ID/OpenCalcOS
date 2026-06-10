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

#include "ppcboot.h"

void cuboot_init(unsigned long r4, unsigned long r5,
		 unsigned long r6, unsigned long r7,
		 unsigned long end_of_ram)
{
	unsigned long avail_ram = end_of_ram - (unsigned long)_end;

	loader_info.initrd_addr = r4;
	loader_info.initrd_size = r4 ? r5 - r4 : 0;
	loader_info.cmdline = (char *)r6;
	loader_info.cmdline_len = r7 - r6;

	simple_alloc_init(_end, avail_ram - 1024*1024, 32, 64);
}
