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
#include <beep/types.h>
#include <beep/platform_device.h>
#include <beep/interrupt.h>
#include <beep/input.h>
#include <beep/smsc911x.h>
#include <beep/gpio.h>
#include <asm/machvec.h>
#include <asm/io.h>

static struct smsc911x_platform_config smsc911x_config = {
	.phy_interface	= PHY_INTERFACE_MODE_MII,
	.irq_polarity	= SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
	.irq_type	= SMSC911X_IRQ_TYPE_PUSH_PULL,
	.flags		= SMSC911X_USE_16BIT | SMSC911X_SWAP_FIFO,
};

static struct resource smsc911x_resources[] = {
	[0] = {
		.start		= 0x24000000,
		.end		= 0x240000ff,
		.flags		= IORESOURCE_MEM,
	},
	[1] = {
		.start		= 85,
		.end		= 85,
		.flags		= IORESOURCE_IRQ,
	},
};

static struct platform_device smsc911x_device = {
	.name		= "smsc911x",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(smsc911x_resources),
	.resource	= smsc911x_resources,
	.dev		= {
		.platform_data = &smsc911x_config,
	},
};

static struct platform_device *rsk7269_devices[] __initdata = {
	&smsc911x_device,
};

static int __init rsk7269_devices_setup(void)
{
	return platform_add_devices(rsk7269_devices,
				    ARRAY_SIZE(rsk7269_devices));
}
device_initcall(rsk7269_devices_setup);
