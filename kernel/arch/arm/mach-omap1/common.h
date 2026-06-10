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
#ifndef __ARCH_ARM_MACH_OMAP1_COMMON_H
#define __ARCH_ARM_MACH_OMAP1_COMMON_H

#include <beep/mtd/mtd.h>
#include <beep/i2c-omap.h>

#include <plat/i2c.h>

#if defined(CONFIG_ARCH_OMAP730) || defined(CONFIG_ARCH_OMAP850)
void omap7xx_map_io(void);
#else
static inline void omap7xx_map_io(void)
{
}
#endif

#ifdef CONFIG_ARCH_OMAP15XX
void omap1510_fpga_init_irq(void);
void omap15xx_map_io(void);
#else
static inline void omap15xx_map_io(void)
{
}
#endif

#ifdef CONFIG_ARCH_OMAP16XX
void omap16xx_map_io(void);
#else
static inline void omap16xx_map_io(void)
{
}
#endif

#ifdef CONFIG_OMAP_SERIAL_WAKE
int omap_serial_wakeup_init(void);
#else
static inline int omap_serial_wakeup_init(void)
{
	return 0;
}
#endif

void omap1_init_early(void);
void omap1_init_irq(void);
void omap1_init_late(void);
void omap1_restart(char, const char *);

extern void __init omap_check_revision(void);

extern void omap1_nand_cmd_ctl(struct mtd_info *mtd, int cmd,
			       unsigned int ctrl);

extern struct sys_timer omap1_timer;
#ifdef CONFIG_OMAP_32K_TIMER
extern int omap_32k_timer_init(void);
#else
static inline int __init omap_32k_timer_init(void)
{
	return -ENODEV;
}
#endif

extern u32 omap_irq_flags;

#ifdef CONFIG_ARCH_OMAP16XX
extern int ocpi_enable(void);
#else
static inline int ocpi_enable(void) { return 0; }
#endif

extern u32 omap1_get_reset_sources(void);

#endif /* __ARCH_ARM_MACH_OMAP1_COMMON_H */
