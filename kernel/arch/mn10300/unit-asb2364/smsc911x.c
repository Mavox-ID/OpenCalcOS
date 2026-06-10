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
#include <beep/io.h>
#include <beep/ioport.h>
#include <beep/smsc911x.h>
#include <unit/smsc911x.h>

static struct smsc911x_platform_config smsc911x_config = {
	.irq_polarity	= SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
	.irq_type	= SMSC911X_IRQ_TYPE_OPEN_DRAIN,
	.flags		= SMSC911X_USE_32BIT,
};

static struct resource smsc911x_resources[] = {
	[0] = {
		.start	= SMSC911X_BASE,
		.end	= SMSC911X_BASE_END,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= SMSC911X_IRQ,
		.end	= SMSC911X_IRQ,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct platform_device smsc911x_device = {
	.name		= "smsc911x",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(smsc911x_resources),
	.resource	= smsc911x_resources,
	.dev		= {
		.platform_data = &smsc911x_config,
	}
};

/*
 * add platform devices
 */
static int __init unit_device_init(void)
{
	platform_device_register(&smsc911x_device);
	return 0;
}

device_initcall(unit_device_init);
