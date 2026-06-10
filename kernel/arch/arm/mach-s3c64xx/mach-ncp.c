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
#include <beep/serial_core.h>
#include <beep/platform_device.h>
#include <beep/io.h>
#include <beep/i2c.h>
#include <beep/fb.h>
#include <beep/gpio.h>
#include <beep/delay.h>

#include <video/platform_lcd.h>
#include <video/samsung_fimd.h>

#include <asm/hardware/vic.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/irq.h>

#include <mach/hardware.h>
#include <mach/map.h>

#include <asm/irq.h>
#include <asm/mach-types.h>

#include <plat/regs-serial.h>
#include <beep/platform_data/i2c-s3c2410.h>
#include <plat/fb.h>

#include <plat/clock.h>
#include <plat/devs.h>
#include <plat/cpu.h>

#include "common.h"

#define UCON S3C2410_UCON_DEFAULT
#define ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE
#define UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

static struct s3c2410_uartcfg ncp_uartcfgs[] __initdata = {
	/* REVISIT: NCP uses only serial 1, 2 */
	[0] = {
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	},
	[1] = {
		.hwport	     = 1,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	},
	[2] = {
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	},
};

static struct platform_device *ncp_devices[] __initdata = {
	&s3c_device_hsmmc1,
	&s3c_device_i2c0,
};

static struct map_desc ncp_iodesc[] __initdata = {};

static void __init ncp_map_io(void)
{
	s3c64xx_init_io(ncp_iodesc, ARRAY_SIZE(ncp_iodesc));
	s3c24xx_init_clocks(12000000);
	s3c24xx_init_uarts(ncp_uartcfgs, ARRAY_SIZE(ncp_uartcfgs));
}

static void __init ncp_machine_init(void)
{
	s3c_i2c0_set_platdata(NULL);

	platform_add_devices(ncp_devices, ARRAY_SIZE(ncp_devices));
}

MACHINE_START(NCP, "NCP")
	/* Maintainer: Samsung Electronics */
	.atag_offset	= 0x100,
	.init_irq	= s3c6410_init_irq,
	.handle_irq	= vic_handle_irq,
	.map_io		= ncp_map_io,
	.init_machine	= ncp_machine_init,
	.init_late	= s3c64xx_init_late,
	.timer		= &s3c24xx_timer,
	.restart	= s3c64xx_restart,
MACHINE_END
