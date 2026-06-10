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

#include <mach/hardware.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>

#include <mach/mux.h>

#include <mach/usb.h>

#include "common.h"

/* assume no Mini-AB port */

#ifdef CONFIG_ARCH_OMAP15XX
static struct omap_usb_config generic1510_usb_config __initdata = {
	.register_host	= 1,
	.register_dev	= 1,
	.hmc_mode	= 16,
	.pins[0]	= 3,
};
#endif

#if defined(CONFIG_ARCH_OMAP16XX)
static struct omap_usb_config generic1610_usb_config __initdata = {
#ifdef CONFIG_USB_OTG
	.otg		= 1,
#endif
	.register_host	= 1,
	.register_dev	= 1,
	.hmc_mode	= 16,
	.pins[0]	= 6,
};
#endif

static void __init omap_generic_init(void)
{
#ifdef CONFIG_ARCH_OMAP15XX
	if (cpu_is_omap15xx()) {
		/* mux pins for uarts */
		omap_cfg_reg(UART1_TX);
		omap_cfg_reg(UART1_RTS);
		omap_cfg_reg(UART2_TX);
		omap_cfg_reg(UART2_RTS);
		omap_cfg_reg(UART3_TX);
		omap_cfg_reg(UART3_RX);

		omap1_usb_init(&generic1510_usb_config);
	}
#endif
#if defined(CONFIG_ARCH_OMAP16XX)
	if (!cpu_is_omap1510()) {
		omap1_usb_init(&generic1610_usb_config);
	}
#endif

	omap_serial_init();
	omap_register_i2c_bus(1, 100, NULL, 0);
}

MACHINE_START(OMAP_GENERIC, "Generic OMAP1510/1610/1710")
	/* Maintainer: Tony Lindgren <tony@atomide.com> */
	.atag_offset	= 0x100,
	.map_io		= omap16xx_map_io,
	.init_early	= omap1_init_early,
	.init_irq	= omap1_init_irq,
	.init_machine	= omap_generic_init,
	.init_late	= omap1_init_late,
	.timer		= &omap1_timer,
	.restart	= omap1_restart,
MACHINE_END
