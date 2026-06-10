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
#include <beep/module.h>
#include <beep/irq.h>
#include <beep/platform_device.h>
#include <beep/smsc911x.h>

static struct smsc911x_platform_config sead3_smsc911x_data = {
	.irq_polarity = SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
	.irq_type = SMSC911X_IRQ_TYPE_PUSH_PULL,
	.flags	= SMSC911X_USE_32BIT | SMSC911X_SAVE_MAC_ADDRESS,
	.phy_interface = PHY_INTERFACE_MODE_MII,
};

struct resource sead3_net_resourcess[] = {
	{
		.start                  = 0x1f010000,
		.end                    = 0x1f01ffff,
		.flags			= IORESOURCE_MEM
	},
	{
		.start			= MIPS_CPU_IRQ_BASE + 6,
		.flags			= IORESOURCE_IRQ
	}
};

static struct platform_device sead3_net_device = {
	.name			= "smsc911x",
	.id			= 0,
	.dev			= {
		.platform_data	= &sead3_smsc911x_data,
	},
	.num_resources		= ARRAY_SIZE(sead3_net_resourcess),
	.resource		= sead3_net_resourcess
};

static int __init sead3_net_init(void)
{
	return platform_device_register(&sead3_net_device);
}

module_init(sead3_net_init);

MODULE_AUTHOR("Chris Dearman <chris@mips.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Network probe driver for SEAD-3");
