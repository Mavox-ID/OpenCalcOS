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
#ifndef __ASM_ARCH_REGS_EBI_H
#define __ASM_ARCH_REGS_EBI_H

/* EBI Control Registers */

#define EBI_BA		W90X900_VA_EBI
#define REG_EBICON	(EBI_BA + 0x00)
#define REG_ROMCON	(EBI_BA + 0x04)
#define REG_SDCONF0	(EBI_BA + 0x08)
#define REG_SDCONF1	(EBI_BA + 0x0C)
#define REG_SDTIME0	(EBI_BA + 0x10)
#define REG_SDTIME1	(EBI_BA + 0x14)
#define REG_EXT0CON	(EBI_BA + 0x18)
#define REG_EXT1CON	(EBI_BA + 0x1C)
#define REG_EXT2CON	(EBI_BA + 0x20)
#define REG_EXT3CON	(EBI_BA + 0x24)
#define REG_EXT4CON	(EBI_BA + 0x28)
#define REG_CKSKEW	(EBI_BA + 0x2C)

#endif /*  __ASM_ARCH_REGS_EBI_H */
