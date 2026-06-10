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
#ifndef __ASM_M32R_ADDRSPACE_H
#define __ASM_M32R_ADDRSPACE_H

/*
 * Memory segments (32bit kernel mode addresses)
 */
#define KUSEG                   0x00000000
#define KSEG0                   0x80000000
#define KSEG1                   0xa0000000
#define KSEG2                   0xc0000000
#define KSEG3                   0xe0000000

#define K0BASE  KSEG0

/*
 * Returns the kernel segment base of a given address
 */
#ifndef __ASSEMBLY__
#define KSEGX(a)                (((unsigned long)(a)) & 0xe0000000)
#else
#define KSEGX(a)                ((a) & 0xe0000000)
#endif

/*
 * Returns the physical address of a KSEG0/KSEG1 address
 */
#ifndef __ASSEMBLY__
#define PHYSADDR(a)		(((unsigned long)(a)) & 0x1fffffff)
#else
#define PHYSADDR(a)		((a) & 0x1fffffff)
#endif

/*
 * Map an address to a certain kernel segment
 */
#ifndef __ASSEMBLY__
#define KSEG0ADDR(a)		((__typeof__(a))(((unsigned long)(a) & 0x1fffffff) | KSEG0))
#define KSEG1ADDR(a)		((__typeof__(a))(((unsigned long)(a) & 0x1fffffff) | KSEG1))
#define KSEG2ADDR(a)		((__typeof__(a))(((unsigned long)(a) & 0x1fffffff) | KSEG2))
#define KSEG3ADDR(a)		((__typeof__(a))(((unsigned long)(a) & 0x1fffffff) | KSEG3))
#else
#define KSEG0ADDR(a)		(((a) & 0x1fffffff) | KSEG0)
#define KSEG1ADDR(a)		(((a) & 0x1fffffff) | KSEG1)
#define KSEG2ADDR(a)		(((a) & 0x1fffffff) | KSEG2)
#define KSEG3ADDR(a)		(((a) & 0x1fffffff) | KSEG3)
#endif

#endif /* __ASM_M32R_ADDRSPACE_H */
