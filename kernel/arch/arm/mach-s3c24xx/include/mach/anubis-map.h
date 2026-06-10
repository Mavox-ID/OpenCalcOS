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

#ifndef __ASM_ARCH_ANUBISMAP_H
#define __ASM_ARCH_ANUBISMAP_H

/* start peripherals off after the S3C2410 */

#define ANUBIS_IOADDR(x)	(S3C2410_ADDR((x) + 0x01800000))

#define ANUBIS_PA_CPLD		(S3C2410_CS1 | (1<<26))

/* we put the CPLD registers next, to get them out of the way */

#define ANUBIS_VA_CTRL1	    ANUBIS_IOADDR(0x00000000)	 /* 0x01800000 */
#define ANUBIS_PA_CTRL1	    (ANUBIS_PA_CPLD)

#define ANUBIS_VA_IDREG	    ANUBIS_IOADDR(0x00300000)	 /* 0x01B00000 */
#define ANUBIS_PA_IDREG	    (ANUBIS_PA_CPLD + (3<<23))

#define ANUBIS_IDEPRI	    ANUBIS_IOADDR(0x01000000)
#define ANUBIS_IDEPRIAUX    ANUBIS_IOADDR(0x01100000)
#define ANUBIS_IDESEC	    ANUBIS_IOADDR(0x01200000)
#define ANUBIS_IDESECAUX    ANUBIS_IOADDR(0x01300000)

#endif /* __ASM_ARCH_ANUBISMAP_H */
