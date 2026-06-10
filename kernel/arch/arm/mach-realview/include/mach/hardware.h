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
#ifndef __ASM_ARCH_HARDWARE_H
#define __ASM_ARCH_HARDWARE_H

#include <asm/sizes.h>

/* macro to get at IO space when running virtually */
#ifdef CONFIG_MMU
/*
 * Statically mapped addresses:
 *
 * 10xx xxxx -> fbxx xxxx
 * 1exx xxxx -> fdxx xxxx
 * 1fxx xxxx -> fexx xxxx
 */
#define IO_ADDRESS(x)		(((x) & 0x03ffffff) + 0xfb000000)
#else
#define IO_ADDRESS(x)		(x)
#endif
#define __io_address(n)		IOMEM(IO_ADDRESS(n))

#endif
