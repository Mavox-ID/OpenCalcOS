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
#ifndef __MACH_PUV3_UNCOMPRESS_H__
#define __MACH_PUV3_UNCOMPRESS_H__

#include <mach/hardware.h>
#include <mach/ocd.h>

extern char input_data[];
extern char input_data_end[];

static void arch_decomp_puts(const char *ptr)
{
	char c;

	while ((c = *ptr++) != '\0') {
		if (c == '\n')
			putc('\r');
		putc(c);
	}
}
#define ARCH_HAVE_DECOMP_PUTS

#endif /* __MACH_PUV3_UNCOMPRESS_H__ */
