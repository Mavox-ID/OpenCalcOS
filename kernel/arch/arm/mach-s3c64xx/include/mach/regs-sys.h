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
#ifndef __PLAT_REGS_SYS_H
#define __PLAT_REGS_SYS_H __FILE__

#define S3C_SYSREG(x)		(S3C_VA_SYS + (x))

#define S3C64XX_AHB_CON0	S3C_SYSREG(0x100)
#define S3C64XX_AHB_CON1	S3C_SYSREG(0x104)
#define S3C64XX_AHB_CON2	S3C_SYSREG(0x108)

#define S3C64XX_SDMA_SEL	S3C_SYSREG(0x110)

#define S3C64XX_OTHERS		S3C_SYSREG(0x900)

#define S3C64XX_OTHERS_USBMASK	(1 << 16)
#define S3C64XX_OTHERS_SYNCMUXSEL	(1 << 6)

#endif /* _PLAT_REGS_SYS_H */
