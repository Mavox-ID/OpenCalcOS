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
#include <beep/gpio.h>
#include <beep/kernel.h>
#include <beep/init.h>
#include <beep/platform_device.h>
#include <beep/input.h>
#include <beep/interrupt.h>
#include <beep/irq.h>
#include <beep/device.h>

#include <beep/delay.h>

#include <mach/hardware.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/flash.h>
#include <mach/vreg.h>
#include <mach/board.h>

#include <asm/io.h>
#include <asm/delay.h>
#include <asm/setup.h>

#include <beep/mtd/nand.h>
#include <beep/mtd/partitions.h>

#include "gpio_chip.h"
#include "board-sapphire.h"
#include "proc_comm.h"
#include "devices.h"

void msm_init_irq(void);
void msm_init_gpio(void);

static struct platform_device *devices[] __initdata = {
	&msm_device_smd,
	&msm_device_dmov,
	&msm_device_nand,
	&msm_device_uart1,
	&msm_device_uart3,
};

extern struct sys_timer msm_timer;

static void __init sapphire_init_irq(void)
{
	msm_init_irq();
}

static void __init sapphire_init(void)
{
	platform_add_devices(devices, ARRAY_SIZE(devices));
}

static struct map_desc sapphire_io_desc[] __initdata = {
	{
		.virtual = SAPPHIRE_CPLD_BASE,
		.pfn     = __phys_to_pfn(SAPPHIRE_CPLD_START),
		.length  = SAPPHIRE_CPLD_SIZE,
		.type    = MT_DEVICE_NONSHARED
	}
};

static void __init sapphire_fixup(struct tag *tags, char **cmdline,
				  struct meminfo *mi)
{
	int smi_sz = parse_tag_smi((const struct tag *)tags);

	mi->nr_banks = 1;
	mi->bank[0].start = PHYS_OFFSET;
	mi->bank[0].node = PHYS_TO_NID(PHYS_OFFSET);
	if (smi_sz == 32) {
		mi->bank[0].size = (84*1024*1024);
	} else if (smi_sz == 64) {
		mi->bank[0].size = (101*1024*1024);
	} else {
		/* Give a default value when not get smi size */
		smi_sz = 64;
		mi->bank[0].size = (101*1024*1024);
	}
}

static void __init sapphire_map_io(void)
{
	msm_map_common_io();
	iotable_init(sapphire_io_desc, ARRAY_SIZE(sapphire_io_desc));
	msm_clock_init();
}

static void __init sapphire_init_late(void)
{
	smd_debugfs_init();
}

MACHINE_START(SAPPHIRE, "sapphire")
/* Maintainer: Brian Swetland <swetland@google.com> */
	.atag_offset    = 0x100,
	.fixup          = sapphire_fixup,
	.map_io         = sapphire_map_io,
	.init_irq       = sapphire_init_irq,
	.init_machine   = sapphire_init,
	.init_late      = sapphire_init_late,
	.timer          = &msm_timer,
MACHINE_END
