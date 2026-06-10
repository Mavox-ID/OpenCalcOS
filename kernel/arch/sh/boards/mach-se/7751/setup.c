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
#include <asm/machvec.h>
#include <mach-se/mach/se7751.h>
#include <asm/io.h>
#include <asm/heartbeat.h>

static unsigned char heartbeat_bit_pos[] = { 8, 9, 10, 11, 12, 13, 14, 15 };

static struct heartbeat_data heartbeat_data = {
	.bit_pos	= heartbeat_bit_pos,
	.nr_bits	= ARRAY_SIZE(heartbeat_bit_pos),
};

static struct resource heartbeat_resources[] = {
	[0] = {
		.start	= PA_LED,
		.end	= PA_LED,
		.flags	= IORESOURCE_MEM,
	},
};

static struct platform_device heartbeat_device = {
	.name		= "heartbeat",
	.id		= -1,
	.dev	= {
		.platform_data	= &heartbeat_data,
	},
	.num_resources	= ARRAY_SIZE(heartbeat_resources),
	.resource	= heartbeat_resources,
};

static struct platform_device *se7751_devices[] __initdata = {
	&heartbeat_device,
};

static int __init se7751_devices_setup(void)
{
	return platform_add_devices(se7751_devices, ARRAY_SIZE(se7751_devices));
}
device_initcall(se7751_devices_setup);

/*
 * The Machine Vector
 */
static struct sh_machine_vector mv_7751se __initmv = {
	.mv_name		= "7751 SolutionEngine",
	.mv_init_irq		= init_7751se_IRQ,
};
