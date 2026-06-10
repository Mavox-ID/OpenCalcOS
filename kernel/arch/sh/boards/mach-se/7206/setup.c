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
#include <beep/platform_device.h>
#include <beep/smc91x.h>
#include <mach-se/mach/se7206.h>
#include <asm/io.h>
#include <asm/machvec.h>
#include <asm/heartbeat.h>

static struct resource smc91x_resources[] = {
	[0] = {
		.name		= "smc91x-regs",
		.start		= PA_SMSC + 0x300,
		.end		= PA_SMSC + 0x300 + 0x020 - 1,
		.flags		= IORESOURCE_MEM,
	},
	[1] = {
		.start		= 64,
		.end		= 64,
		.flags		= IORESOURCE_IRQ,
	},
};

static struct smc91x_platdata smc91x_info = {
	.flags	= SMC91X_USE_16BIT,
};

static struct platform_device smc91x_device = {
	.name		= "smc91x",
	.id		= -1,
	.dev		= {
		.dma_mask		= NULL,
		.coherent_dma_mask	= 0xffffffff,
		.platform_data		= &smc91x_info,
	},
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
};

static unsigned char heartbeat_bit_pos[] = { 8, 9, 10, 11, 12, 13, 14, 15 };

static struct heartbeat_data heartbeat_data = {
	.bit_pos	= heartbeat_bit_pos,
	.nr_bits	= ARRAY_SIZE(heartbeat_bit_pos),
};

static struct resource heartbeat_resource = {
	.start	= PA_LED,
	.end	= PA_LED,
	.flags	= IORESOURCE_MEM | IORESOURCE_MEM_32BIT,
};

static struct platform_device heartbeat_device = {
	.name		= "heartbeat",
	.id		= -1,
	.dev	= {
		.platform_data	= &heartbeat_data,
	},
	.num_resources	= 1,
	.resource	= &heartbeat_resource,
};

static struct platform_device *se7206_devices[] __initdata = {
	&smc91x_device,
	&heartbeat_device,
};

static int __init se7206_devices_setup(void)
{
	return platform_add_devices(se7206_devices, ARRAY_SIZE(se7206_devices));
}
device_initcall(se7206_devices_setup);

static int se7206_mode_pins(void)
{
	return MODE_PIN1 | MODE_PIN2;
}

/*
 * The Machine Vector
 */

static struct sh_machine_vector mv_se __initmv = {
	.mv_name		= "SolutionEngine",
	.mv_init_irq		= init_se7206_IRQ,
	.mv_mode_pins		= se7206_mode_pins,
};
