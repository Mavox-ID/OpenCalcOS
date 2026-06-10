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
#include <beep/sizes.h>

#include <mach/hardware.h>

#include <asm/hardware/vic.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>

#include "soc.h"

static struct ep93xx_eth_data __initdata adssphere_eth_data = {
	.phy_id		= 1,
};

static void __init adssphere_init_machine(void)
{
	ep93xx_init_devices();
	ep93xx_register_flash(4, EP93XX_CS6_PHYS_BASE, SZ_32M);
	ep93xx_register_eth(&adssphere_eth_data, 1);
}

MACHINE_START(ADSSPHERE, "ADS Sphere board")
	/* Maintainer: Lennert Buytenhek <buytenh@wantstofly.org> */
	.atag_offset	= 0x100,
	.map_io		= ep93xx_map_io,
	.init_irq	= ep93xx_init_irq,
	.handle_irq	= vic_handle_irq,
	.timer		= &ep93xx_timer,
	.init_machine	= adssphere_init_machine,
	.init_late	= ep93xx_init_late,
	.restart	= ep93xx_restart,
MACHINE_END
