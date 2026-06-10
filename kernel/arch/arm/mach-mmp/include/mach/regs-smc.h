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
#ifndef __ASM_MACH_REGS_SMC_H
#define __ASM_MACH_REGS_SMC_H

#include <mach/addr-map.h>

#define SMC_VIRT_BASE		(AXI_VIRT_BASE + 0x83800)
#define SMC_REG(x)		(SMC_VIRT_BASE + (x))

#define SMC_MSC0		SMC_REG(0x0020)
#define SMC_MSC1		SMC_REG(0x0024)
#define SMC_SXCNFG0		SMC_REG(0x0030)
#define SMC_SXCNFG1		SMC_REG(0x0034)
#define SMC_MEMCLKCFG		SMC_REG(0x0068)
#define SMC_CSDFICFG0		SMC_REG(0x0090)
#define SMC_CSDFICFG1		SMC_REG(0x0094)
#define SMC_CLK_RET_DEL		SMC_REG(0x00b0)
#define SMC_ADV_RET_DEL		SMC_REG(0x00b4)
#define SMC_CSADRMAP0		SMC_REG(0x00c0)
#define SMC_CSADRMAP1		SMC_REG(0x00c4)
#define SMC_WE_AP0		SMC_REG(0x00e0)
#define SMC_WE_AP1		SMC_REG(0x00e4)
#define SMC_OE_AP0		SMC_REG(0x00f0)
#define SMC_OE_AP1		SMC_REG(0x00f4)
#define SMC_ADV_AP0		SMC_REG(0x0100)
#define SMC_ADV_AP1		SMC_REG(0x0104)

#endif /* __ASM_MACH_REGS_SMC_H */
