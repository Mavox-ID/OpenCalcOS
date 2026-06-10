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
#ifndef __ASM_ARCH_VERSATILE_H
#define __ASM_ARCH_VERSATILE_H

#include <beep/amba/bus.h>
#include <beep/of_platform.h>

extern void __init versatile_init(void);
extern void __init versatile_init_early(void);
extern void __init versatile_init_irq(void);
extern void __init versatile_map_io(void);
extern struct sys_timer versatile_timer;
extern void versatile_restart(char, const char *);
extern unsigned int mmc_status(struct device *dev);
#ifdef CONFIG_OF
extern struct of_dev_auxdata versatile_auxdata_lookup[];
#endif

#define APB_DEVICE(name, busid, base, plat)	\
static AMBA_APB_DEVICE(name, busid, 0, VERSATILE_##base##_BASE, base##_IRQ, plat)

#define AHB_DEVICE(name, busid, base, plat)	\
static AMBA_AHB_DEVICE(name, busid, 0, VERSATILE_##base##_BASE, base##_IRQ, plat)

#endif
