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
/* needs arch/map.h including with this */

#ifndef __ASM_ARCH_OSIRISMAP_H
#define __ASM_ARCH_OSIRISMAP_H

/* start peripherals off after the S3C2410 */

#define OSIRIS_IOADDR(x)	(S3C2410_ADDR((x) + 0x04000000))

#define OSIRIS_PA_CPLD		(S3C2410_CS1 | (1<<26))

/* we put the CPLD registers next, to get them out of the way */

#define OSIRIS_VA_CTRL0		OSIRIS_IOADDR(0x00000000)
#define OSIRIS_PA_CTRL0		(OSIRIS_PA_CPLD)

#define OSIRIS_VA_CTRL1		OSIRIS_IOADDR(0x00100000)
#define OSIRIS_PA_CTRL1		(OSIRIS_PA_CPLD + (1<<23))

#define OSIRIS_VA_CTRL2		OSIRIS_IOADDR(0x00200000)
#define OSIRIS_PA_CTRL2		(OSIRIS_PA_CPLD + (2<<23))

#define OSIRIS_VA_CTRL3		OSIRIS_IOADDR(0x00300000)
#define OSIRIS_PA_CTRL3		(OSIRIS_PA_CPLD + (2<<23))

#define OSIRIS_VA_IDREG		OSIRIS_IOADDR(0x00700000)
#define OSIRIS_PA_IDREG		(OSIRIS_PA_CPLD + (7<<23))

#endif /* __ASM_ARCH_OSIRISMAP_H */
