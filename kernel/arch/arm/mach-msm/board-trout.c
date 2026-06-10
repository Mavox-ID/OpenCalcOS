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
#include <beep/init.h>
#include <beep/platform_device.h>
#include <beep/clkdev.h>

#include <asm/system_info.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/setup.h>

#include <mach/board.h>
#include <mach/hardware.h>
#include <mach/msm_iomap.h>

#include "devices.h"
#include "board-trout.h"
#include "common.h"

extern int trout_init_mmc(unsigned int);

static struct platform_device *devices[] __initdata = {
	&msm_device_uart3,
	&msm_device_smd,
	&msm_device_nand,
	&msm_device_hsusb,
	&msm_device_i2c,
};

static void __init trout_init_early(void)
{
	arch_ioremap_caller = __msm_ioremap_caller;
}

static void __init trout_init_irq(void)
{
	msm_init_irq();
}

static void __init trout_fixup(struct tag *tags, char **cmdline,
			       struct meminfo *mi)
{
	mi->nr_banks = 1;
	mi->bank[0].start = PHYS_OFFSET;
	mi->bank[0].size = (101*1024*1024);
}

static void __init trout_init(void)
{
	int rc;

	platform_add_devices(devices, ARRAY_SIZE(devices));

#ifdef CONFIG_MMC
        rc = trout_init_mmc(system_rev);
        if (rc)
                printk(KERN_CRIT "%s: MMC init failure (%d)\n", __func__, rc);
#endif

}

static struct map_desc trout_io_desc[] __initdata = {
	{
		.virtual = TROUT_CPLD_BASE,
		.pfn     = __phys_to_pfn(TROUT_CPLD_START),
		.length  = TROUT_CPLD_SIZE,
		.type    = MT_DEVICE_NONSHARED
	}
};

static void __init trout_map_io(void)
{
	msm_map_common_io();
	iotable_init(trout_io_desc, ARRAY_SIZE(trout_io_desc));

#ifdef CONFIG_MSM_DEBUG_UART3
	/* route UART3 to the "H2W" extended usb connector */
	writeb(0x80, TROUT_CPLD_BASE + 0x00);
#endif

	msm_clock_init(msm_clocks_7x01a, msm_num_clocks_7x01a);
}

static void __init trout_init_late(void)
{
	smd_debugfs_init();
}

MACHINE_START(TROUT, "HTC Dream")
	.atag_offset	= 0x100,
	.fixup		= trout_fixup,
	.map_io		= trout_map_io,
	.init_early	= trout_init_early,
	.init_irq	= trout_init_irq,
	.init_machine	= trout_init,
	.init_late	= trout_init_late,
	.timer		= &msm7x01_timer,
MACHINE_END
