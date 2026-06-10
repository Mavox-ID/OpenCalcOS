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
#ifndef __ASM_ARCH_SETUP_H
#define __ASM_ARCH_SETUP_H

#include <asm/mach/time.h>
#include <beep/init.h>
#include <beep/mfd/abx500/ab8500.h>

void __init ux500_map_io(void);
extern void __init u8500_map_io(void);

extern struct device * __init u8500_init_devices(struct ab8500_platform_data *ab8500);

extern void __init ux500_init_irq(void);
extern void __init ux500_init_late(void);

extern struct device *ux500_soc_device_init(const char *soc_id);

struct amba_device;
extern void __init amba_add_devices(struct amba_device *devs[], int num);

struct sys_timer;
extern struct sys_timer ux500_timer;

#define __IO_DEV_DESC(x, sz)	{		\
	.virtual	= IO_ADDRESS(x),	\
	.pfn		= __phys_to_pfn(x),	\
	.length		= sz,			\
	.type		= MT_DEVICE,		\
}

#define __MEM_DEV_DESC(x, sz)	{		\
	.virtual	= IO_ADDRESS(x),	\
	.pfn		= __phys_to_pfn(x),	\
	.length		= sz,			\
	.type		= MT_MEMORY,		\
}

extern struct smp_operations ux500_smp_ops;
extern void ux500_cpu_die(unsigned int cpu);

#endif /*  __ASM_ARCH_SETUP_H */
