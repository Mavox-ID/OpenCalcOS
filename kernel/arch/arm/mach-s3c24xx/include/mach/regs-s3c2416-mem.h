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
#ifndef __ASM_ARM_REGS_S3C2416_MEM
#define __ASM_ARM_REGS_S3C2416_MEM

#ifndef S3C2416_MEMREG
#define S3C2416_MEMREG(x) (S3C24XX_VA_MEMCTRL + (x))
#endif

#define S3C2416_BANKCFG			S3C2416_MEMREG(0x00)
#define S3C2416_BANKCON1		S3C2416_MEMREG(0x04)
#define S3C2416_BANKCON2		S3C2416_MEMREG(0x08)
#define S3C2416_BANKCON3		S3C2416_MEMREG(0x0C)

#define S3C2416_REFRESH			S3C2416_MEMREG(0x10)
#define S3C2416_TIMEOUT			S3C2416_MEMREG(0x14)

#endif /*  __ASM_ARM_REGS_S3C2416_MEM */
