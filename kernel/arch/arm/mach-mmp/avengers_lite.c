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
#include <beep/init.h>
#include <beep/kernel.h>
#include <beep/platform_device.h>

#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <mach/addr-map.h>
#include <mach/mfp-pxa168.h>
#include <mach/pxa168.h>
#include <mach/irqs.h>


#include "common.h"
#include <beep/delay.h>

/* Avengers lite MFP configurations */
static unsigned long avengers_lite_pin_config_V16F[] __initdata = {
	/* DEBUG_UART */
	GPIO88_UART2_TXD,
	GPIO89_UART2_RXD,
};

static void __init avengers_lite_init(void)
{
	mfp_config(ARRAY_AND_SIZE(avengers_lite_pin_config_V16F));

	/* on-chip devices */
	pxa168_add_uart(2);
	platform_device_register(&pxa168_device_gpio);
}

MACHINE_START(AVENGERS_LITE, "PXA168 Avengers lite Development Platform")
	.map_io		= mmp_map_io,
	.nr_irqs	= MMP_NR_IRQS,
	.init_irq       = pxa168_init_irq,
	.timer          = &pxa168_timer,
	.init_machine   = avengers_lite_init,
	.restart	= pxa168_restart,
MACHINE_END
