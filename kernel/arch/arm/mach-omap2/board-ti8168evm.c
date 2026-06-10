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
#include <beep/usb/musb.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>

#include "common.h"

static struct omap_musb_board_data musb_board_data = {
	.set_phy_power	= ti81xx_musb_phy_power,
	.interface_type	= MUSB_INTERFACE_ULPI,
	.mode           = MUSB_OTG,
	.power		= 500,
};

static void __init ti81xx_evm_init(void)
{
	omap_serial_init();
	omap_sdrc_init(NULL, NULL);
	usb_musb_init(&musb_board_data);
}

MACHINE_START(TI8168EVM, "ti8168evm")
	/* Maintainer: Texas Instruments */
	.atag_offset	= 0x100,
	.map_io		= ti81xx_map_io,
	.init_early	= ti81xx_init_early,
	.init_irq	= ti81xx_init_irq,
	.timer		= &omap3_timer,
	.init_machine	= ti81xx_evm_init,
	.init_late	= ti81xx_init_late,
	.restart	= omap44xx_restart,
MACHINE_END

MACHINE_START(TI8148EVM, "ti8148evm")
	/* Maintainer: Texas Instruments */
	.atag_offset	= 0x100,
	.map_io		= ti81xx_map_io,
	.init_early	= ti81xx_init_early,
	.init_irq	= ti81xx_init_irq,
	.timer		= &omap3_timer,
	.init_machine	= ti81xx_evm_init,
	.init_late	= ti81xx_init_late,
	.restart	= omap44xx_restart,
MACHINE_END
