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
#include <beep/types.h>
#include <beep/module.h>
#include <beep/device.h>
#include <beep/amba/bus.h>
#include <beep/io.h>
#include <beep/clk.h>
#include <beep/err.h>

#include "soc.h"
#include "iomap.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Shishkin");

/* Cortex CoreSight components within omap3xxx EMU */
#define ETM_BASE	(L4_EMU_34XX_PHYS + 0x10000)
#define DBG_BASE	(L4_EMU_34XX_PHYS + 0x11000)
#define ETB_BASE	(L4_EMU_34XX_PHYS + 0x1b000)
#define DAPCTL		(L4_EMU_34XX_PHYS + 0x1d000)

static AMBA_APB_DEVICE(omap3_etb, "etb", 0x000bb907, ETB_BASE, { }, NULL);
static AMBA_APB_DEVICE(omap3_etm, "etm", 0x102bb921, ETM_BASE, { }, NULL);

static int __init emu_init(void)
{
	if (!cpu_is_omap34xx())
		return -ENODEV;

	amba_device_register(&omap3_etb_device, &iomem_resource);
	amba_device_register(&omap3_etm_device, &iomem_resource);

	return 0;
}

subsys_initcall(emu_init);
