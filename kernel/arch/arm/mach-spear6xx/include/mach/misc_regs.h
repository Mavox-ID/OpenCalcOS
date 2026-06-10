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
#ifndef __MACH_MISC_REGS_H
#define __MACH_MISC_REGS_H

#include <mach/spear.h>

#define MISC_BASE		IOMEM(VA_SPEAR6XX_ICM3_MISC_REG_BASE)
#define DMA_CHN_CFG		(MISC_BASE + 0x0A0)

#endif /* __MACH_MISC_REGS_H */
