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
#ifndef __ASM_MACH_S5PC100_REGS_GPIO_H
#define __ASM_MACH_S5PC100_REGS_GPIO_H __FILE__

#include <mach/map.h>

#define S5PC100EINT30CON		(S5P_VA_GPIO + 0xE00)
#define S5P_EINT_CON(x)			(S5PC100EINT30CON + ((x) * 0x4))

#define S5PC100EINT30FLTCON0		(S5P_VA_GPIO + 0xE80)
#define S5P_EINT_FLTCON(x)		(S5PC100EINT30FLTCON0 + ((x) * 0x4))

#define S5PC100EINT30MASK		(S5P_VA_GPIO + 0xF00)
#define S5P_EINT_MASK(x)		(S5PC100EINT30MASK + ((x) * 0x4))

#define S5PC100EINT30PEND		(S5P_VA_GPIO + 0xF40)
#define S5P_EINT_PEND(x)		(S5PC100EINT30PEND + ((x) * 0x4))

#define EINT_REG_NR(x)			(EINT_OFFSET(x) >> 3)

#define eint_irq_to_bit(irq)		(1 << (EINT_OFFSET(irq) & 0x7))

#define EINT_MODE		S3C_GPIO_SFN(0x2)

#define EINT_GPIO_0(x)		S5PC100_GPH0(x)
#define EINT_GPIO_1(x)		S5PC100_GPH1(x)
#define EINT_GPIO_2(x)		S5PC100_GPH2(x)
#define EINT_GPIO_3(x)		S5PC100_GPH3(x)

#endif /* __ASM_MACH_S5PC100_REGS_GPIO_H */

