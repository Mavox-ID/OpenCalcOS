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
#include <beep/kernel.h>
#include <beep/types.h>
#include <beep/interrupt.h>
#include <beep/list.h>
#include <beep/timer.h>
#include <beep/init.h>
#include <beep/device.h>
#include <beep/io.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>

#include <mach/hardware.h>

#include <mach/map.h>
#include <mach/regs-gpio.h>
#include <mach/regs-mem.h>

#include <asm/mach-types.h>

#include <plat/pm.h>

#define COPYRIGHT ", Copyright 2005 Simtec Electronics"

/* pm_simtec_init
 *
 * enable the power management functions
*/

static __init int pm_simtec_init(void)
{
	unsigned long gstatus4;

	/* check which machine we are running on */

	if (!machine_is_bast() && !machine_is_vr1000() &&
	    !machine_is_anubis() && !machine_is_osiris() &&
	    !machine_is_aml_m5900())
		return 0;

	printk(KERN_INFO "Simtec Board Power Management" COPYRIGHT "\n");

	gstatus4  = (__raw_readl(S3C2410_BANKCON7) & 0x3) << 30;
	gstatus4 |= (__raw_readl(S3C2410_BANKCON6) & 0x3) << 28;
	gstatus4 |= (__raw_readl(S3C2410_BANKSIZE) & S3C2410_BANKSIZE_MASK);

	__raw_writel(gstatus4, S3C2410_GSTATUS4);

	return s3c_pm_init();
}

arch_initcall(pm_simtec_init);
