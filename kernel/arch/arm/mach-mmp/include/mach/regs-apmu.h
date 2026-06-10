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
#ifndef __ASM_MACH_REGS_APMU_H
#define __ASM_MACH_REGS_APMU_H

#include <mach/addr-map.h>

#define APMU_FNCLK_EN	(1 << 4)
#define APMU_AXICLK_EN	(1 << 3)
#define APMU_FNRST_DIS	(1 << 1)
#define APMU_AXIRST_DIS	(1 << 0)

/* Wake Clear Register */
#define APMU_WAKE_CLR	APMU_REG(0x07c)

#define APMU_PXA168_KP_WAKE_CLR		(1 << 7)
#define APMU_PXA168_CFI_WAKE_CLR	(1 << 6)
#define APMU_PXA168_XD_WAKE_CLR		(1 << 5)
#define APMU_PXA168_MSP_WAKE_CLR	(1 << 4)
#define APMU_PXA168_SD4_WAKE_CLR	(1 << 3)
#define APMU_PXA168_SD3_WAKE_CLR	(1 << 2)
#define APMU_PXA168_SD2_WAKE_CLR	(1 << 1)
#define APMU_PXA168_SD1_WAKE_CLR	(1 << 0)

#endif /* __ASM_MACH_REGS_APMU_H */
