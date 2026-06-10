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
#ifndef __MACH_GENERIC_H
#define __MACH_GENERIC_H

#include <beep/amba/pl08x.h>
#include <beep/init.h>
#include <beep/platform_device.h>
#include <beep/amba/bus.h>
#include <asm/mach/time.h>
#include <asm/mach/map.h>

/* Add spear3xx family device structure declarations here */
extern struct sys_timer spear3xx_timer;
extern struct pl022_ssp_controller pl022_plat_data;
extern struct pl08x_platform_data pl080_plat_data;

/* Add spear3xx family function declarations here */
void __init spear_setup_of_timer(void);
void __init spear3xx_clk_init(void);
void __init spear3xx_map_io(void);
void __init spear3xx_dt_init_irq(void);

void spear_restart(char, const char *);

#endif /* __MACH_GENERIC_H */
