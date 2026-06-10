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
#include <asm/mach-types.h>

/*
 * Note! This could cause problems on the NetWinder
 */
#define DC21285_BASE ((volatile unsigned int *)0x42000160)
#define SER0_BASE    ((volatile unsigned char *)0x7c0003f8)

static inline void putc(char c)
{
	if (machine_is_netwinder()) {
		while ((SER0_BASE[5] & 0x60) != 0x60)
			barrier();
		SER0_BASE[0] = c;
	} else {
		while (DC21285_BASE[6] & 8);
		DC21285_BASE[0] = c;
	}
}

static inline void flush(void)
{
}

/*
 * nothing to do
 */
#define arch_decomp_setup()
#define arch_decomp_wdog()
