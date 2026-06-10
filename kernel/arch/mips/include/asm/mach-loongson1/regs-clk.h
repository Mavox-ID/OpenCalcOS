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
#ifndef __ASM_MACH_LOONGSON1_REGS_CLK_H
#define __ASM_MACH_LOONGSON1_REGS_CLK_H

#define LS1X_CLK_REG(x) \
		((void __iomem *)KSEG1ADDR(LS1X_CLK_BASE + (x)))

#define LS1X_CLK_PLL_FREQ		LS1X_CLK_REG(0x0)
#define LS1X_CLK_PLL_DIV		LS1X_CLK_REG(0x4)

/* Clock PLL Divisor Register Bits */
#define DIV_DC_EN			(0x1 << 31)
#define DIV_CPU_EN			(0x1 << 25)
#define DIV_DDR_EN			(0x1 << 19)

#define DIV_DC_SHIFT			26
#define DIV_CPU_SHIFT			20
#define DIV_DDR_SHIFT			14

#define DIV_DC_WIDTH			5
#define DIV_CPU_WIDTH			5
#define DIV_DDR_WIDTH			5

#endif /* __ASM_MACH_LOONGSON1_REGS_CLK_H */
