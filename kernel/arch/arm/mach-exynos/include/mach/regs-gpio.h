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
#ifndef __ASM_ARCH_REGS_GPIO_H
#define __ASM_ARCH_REGS_GPIO_H __FILE__

#include <mach/map.h>
#include <mach/irqs.h>

#define EINT_REG_NR(x)			(EINT_OFFSET(x) >> 3)
#define EINT_CON(b, x)			(b + 0xE00 + (EINT_REG_NR(x) * 4))
#define EINT_FLTCON(b, x)		(b + 0xE80 + (EINT_REG_NR(x) * 4))
#define EINT_MASK(b, x)			(b + 0xF00 + (EINT_REG_NR(x) * 4))
#define EINT_PEND(b, x)			(b + 0xF40 + (EINT_REG_NR(x) * 4))

#define EINT_OFFSET_BIT(x)		(1 << (EINT_OFFSET(x) & 0x7))

/* compatibility for plat-s5p/irq-pm.c */
#define EXYNOS4_EINT40CON		(S5P_VA_GPIO2 + 0xE00)
#define S5P_EINT_CON(x)			(EXYNOS4_EINT40CON + ((x) * 0x4))

#define EXYNOS4_EINT40FLTCON0		(S5P_VA_GPIO2 + 0xE80)
#define S5P_EINT_FLTCON(x)		(EXYNOS4_EINT40FLTCON0 + ((x) * 0x4))

#define EXYNOS4_EINT40MASK		(S5P_VA_GPIO2 + 0xF00)
#define S5P_EINT_MASK(x)		(EXYNOS4_EINT40MASK + ((x) * 0x4))

#define EXYNOS4_EINT40PEND		(S5P_VA_GPIO2 + 0xF40)
#define S5P_EINT_PEND(x)		(EXYNOS4_EINT40PEND + ((x) * 0x4))

#endif /* __ASM_ARCH_REGS_GPIO_H */
