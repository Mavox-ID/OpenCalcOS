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
#ifndef __ASM_ARCH_REGS_WATCHDOG_H
#define __ASM_ARCH_REGS_WATCHDOG_H

#define S3C_WDOGREG(x) ((x) + S3C_VA_WATCHDOG)

#define S3C2410_WTCON	   S3C_WDOGREG(0x00)
#define S3C2410_WTDAT	   S3C_WDOGREG(0x04)
#define S3C2410_WTCNT	   S3C_WDOGREG(0x08)

/* the watchdog can either generate a reset pulse, or an
 * interrupt.
 */

#define S3C2410_WTCON_RSTEN   (0x01)
#define S3C2410_WTCON_INTEN   (1<<2)
#define S3C2410_WTCON_ENABLE  (1<<5)

#define S3C2410_WTCON_DIV16   (0<<3)
#define S3C2410_WTCON_DIV32   (1<<3)
#define S3C2410_WTCON_DIV64   (2<<3)
#define S3C2410_WTCON_DIV128  (3<<3)

#define S3C2410_WTCON_PRESCALE(x) ((x) << 8)
#define S3C2410_WTCON_PRESCALE_MASK (0xff00)

#endif /* __ASM_ARCH_REGS_WATCHDOG_H */


