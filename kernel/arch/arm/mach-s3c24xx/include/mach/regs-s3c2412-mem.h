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
#ifndef __ASM_ARM_REGS_S3C2412_MEM
#define __ASM_ARM_REGS_S3C2412_MEM

#define S3C2412_MEMREG(x) (S3C24XX_VA_MEMCTRL + (x))
#define S3C2412_EBIREG(x) (S3C2412_VA_EBI + (x))

#define S3C2412_SSMCREG(x) (S3C2412_VA_SSMC + (x))
#define S3C2412_SSMC(x, o) (S3C2412_SSMCREG((x * 0x20) + (o)))

#define S3C2412_BANKCFG			S3C2412_MEMREG(0x00)
#define S3C2412_BANKCON1		S3C2412_MEMREG(0x04)
#define S3C2412_BANKCON2		S3C2412_MEMREG(0x08)
#define S3C2412_BANKCON3		S3C2412_MEMREG(0x0C)

#define S3C2412_REFRESH			S3C2412_MEMREG(0x10)
#define S3C2412_TIMEOUT			S3C2412_MEMREG(0x14)

/* EBI control registers */

#define S3C2412_EBI_PR			S3C2412_EBIREG(0x00)
#define S3C2412_EBI_BANKCFG		S3C2412_EBIREG(0x04)

/* SSMC control registers */

#define S3C2412_SSMC_BANK(x)		S3C2412_SSMC(x, 0x00)
#define S3C2412_SMIDCYR(x)		S3C2412_SSMC(x, 0x00)
#define S3C2412_SMBWSTRD(x)		S3C2412_SSMC(x, 0x04)
#define S3C2412_SMBWSTWRR(x)		S3C2412_SSMC(x, 0x08)
#define S3C2412_SMBWSTOENR(x)		S3C2412_SSMC(x, 0x0C)
#define S3C2412_SMBWSTWENR(x)		S3C2412_SSMC(x, 0x10)
#define S3C2412_SMBCR(x)		S3C2412_SSMC(x, 0x14)
#define S3C2412_SMBSR(x)		S3C2412_SSMC(x, 0x18)
#define S3C2412_SMBWSTBRDR(x)		S3C2412_SSMC(x, 0x1C)

#endif /*  __ASM_ARM_REGS_S3C2412_MEM */
