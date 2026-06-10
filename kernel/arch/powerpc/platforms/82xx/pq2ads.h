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
#ifdef __KERNEL__
#ifndef __MACH_ADS8260_DEFS
#define __MACH_ADS8260_DEFS

#include <beep/seq_file.h>

/* The ADS8260 has 16, 32-bit wide control/status registers, accessed
 * only on word boundaries.
 * Not all are used (yet), or are interesting to us (yet).
 */

/* Things of interest in the CSR.
 */
#define BCSR0_LED0		((uint)0x02000000)      /* 0 == on */
#define BCSR0_LED1		((uint)0x01000000)      /* 0 == on */
#define BCSR1_FETHIEN		((uint)0x08000000)      /* 0 == enable*/
#define BCSR1_FETH_RST		((uint)0x04000000)      /* 0 == reset */
#define BCSR1_RS232_EN1		((uint)0x02000000)      /* 0 ==enable */
#define BCSR1_RS232_EN2		((uint)0x01000000)      /* 0 ==enable */
#define BCSR3_FETHIEN2		((uint)0x10000000)      /* 0 == enable*/
#define BCSR3_FETH2_RST		((uint)0x80000000)      /* 0 == reset */

#endif /* __MACH_ADS8260_DEFS */
#endif /* __KERNEL__ */
